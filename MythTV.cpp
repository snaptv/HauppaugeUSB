/*  -*- Mode: c++ -*-
 *
 * Copyright (C) John Poet 2018
 *
 * This file is part of HauppaugeUSB.
 *
 * HauppaugeUSB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HauppaugeUSB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HauppaugeUSB.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MythTV.h"
#include <unistd.h>
#include <poll.h>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;
using namespace boost::algorithm;

const string VERSION = "0.1";

MythTV::MythTV(const Parameters & params)
    : m_buffer_max(188 * 100000),
      m_block_size(m_buffer_max / 4),
      m_buffer(this),
      m_commands(this),
      m_params(params),
      m_dev(nullptr),
      m_run(true),
      m_fatal(false),
      m_streaming(false),
      m_xon(false),
      m_ready(false)
{
    m_buffer.Start();
    m_commands.Start();
}

MythTV::~MythTV(void)
{
    Terminate();

    m_commands.Join();
    m_buffer.Join();

    std::lock_guard<std::mutex> lock(m_flow_mutex);
    delete m_dev;
    m_dev = nullptr;
}

void MythTV::Terminate(void)
{
    LOG(Logger::CRIT) <<"Terminating." << flush;
    StopEncoding(true);
    m_run = false;

    m_flow_cond.notify_all();
    m_run_cond.notify_all();
}

void MythTV::Wait(void)
{
    for (;;)
    {
        {
            std::unique_lock<std::mutex> lk(m_run_mutex);

            m_run_cond.wait_for(lk, std::chrono::milliseconds(2500));
            if (!m_run)
                break;
        }

        if (m_streaming)
        {
            // Check for wedged state.
            auto tm = std::chrono::system_clock::now() -
                      std::chrono::seconds(60);
            if (m_buffer.HeartBeat() < tm)
                Fatal("We seem to be wedged!");
        }
    }
}

void MythTV::OpenDev(void)
{
    std::lock_guard<std::mutex> lock(m_flow_mutex);

    if (m_dev != nullptr)
        return;

    m_dev = new HauppaugeDev(m_params);
    if (!m_dev)
    {
        Fatal("Unable to create Hauppauge dev.");
        return;
    }
    if (!(*m_dev))
    {
        delete m_dev;
        m_dev = nullptr;
        Fatal(m_dev->ErrorString());
        return;
    }

    if (!m_usbio.Open(m_params.serial))
    {
        delete m_dev;
        m_dev = nullptr;
        Fatal(m_usbio.ErrorString());
        return;
    }

    if (!m_dev->Open(m_usbio, &getWriteCallBack()))
    {
        Fatal(m_dev->ErrorString());
        delete m_dev;
        m_dev = nullptr;

        m_usbio.Close();

        return;
    }

    m_ready = true;
    m_flow_cond.notify_all();
}

void MythTV::Fatal(const string & msg)
{
    LOG(Logger::CRIT) << msg << flush;

    std::unique_lock<std::mutex> lk(m_run_mutex);
    m_fatal_msg = msg;
    m_fatal = true;
    m_run   = false;

    Terminate();
}

bool MythTV::StartEncoding(void)
{
    if (m_streaming)
    {
        LOG(Logger::WARNING) << "Already streaming!" << flush;
        return true;
    }
    if (!m_ready)
    {
        LOG(Logger::CRIT) << "Hauppauge device not ready." << flush;
        return false;
    }

    if (m_dev->StartEncoding())
    {
        m_streaming = true;
        m_flow_cond.notify_all();
        return true;
    }

    return false;
}

bool MythTV::StopEncoding(bool soft)
{
    if (!m_streaming)
    {
        if (!soft)
            LOG(Logger::WARNING) << "Already not streaming!" << flush;
        return true;
    }
    if (!m_ready)
    {
        LOG(Logger::CRIT) << "Hauppauge device not ready." << flush;
        return false;
    }

    m_flow_mutex.lock();
    if (!m_dev)
    {
        LOG(Logger::CRIT) << "Invalid Hauppauge device." << flush;
        m_flow_mutex.unlock();
        return false;
    }
    m_flow_mutex.unlock();

    if (m_dev->StopEncoding())
    {
        m_streaming = false;
        m_flow_cond.notify_all();
        return true;
    }

    return false;
}

bool Commands::send_status(const string & command, const string & status)
{
    int len = write(2, status.data(), status.size());
    write(2, "\n", 1);

    if (len != static_cast<int>(status.size()))
    {
        LOG(Logger::ERR) << "Status -- Wrote " << len
                         << " of " << status.size()
                         << " bytes of status '" << status << "'" << flush;
        return false;
    }
    else
        LOG(Logger::NOTICE) << command << ": '" << status << "'" << flush;

    return true;
}

bool Commands::process_command(const string & cmd)
{
    LOG(Logger::DEBUG) << "Processing '" << cmd << "'" << flush;

    if (starts_with(cmd, "Version?"))
    {
        std::unique_lock<std::mutex> lk(m_parent->m_run_mutex);
        if (m_parent->m_fatal)
            send_status(cmd, "ERR:" + m_parent->m_fatal_msg);
        else
            send_status(cmd, "OK:" + VERSION);
        return true;
    }
    if (starts_with(cmd, "HasLock?"))
    {
        if (m_parent->m_ready)
            send_status(cmd, "OK:Yes");
        else
            send_status(cmd, "OK:No");
        return true;
    }
    if (starts_with(cmd, "SignalStrengthPercent"))
    {
        if (m_parent->m_ready)
            send_status(cmd, "OK:100");
        else
            send_status(cmd, "OK:20");
        return true;
    }
    if (starts_with(cmd, "LockTimeout"))
    {
        send_status(cmd, "OK:12000");
        m_parent->OpenDev();
        return true;
    }
    if (starts_with(cmd, "HasTuner?"))
    {
        send_status(cmd, "OK:No");
        return true;
    }
    if (starts_with(cmd, "HasPictureAttributes?"))
    {
        send_status(cmd, "OK:No");
        return true;
    }
    if (starts_with(cmd, "SendBytes"))
    {
        // Used when FlowControl is Polling
        send_status(cmd, "ERR:Not supported");
    }
    else if (starts_with(cmd, "XON"))
    {
        // Used when FlowControl is XON/XOFF
        send_status(cmd, "OK");
        m_parent->m_xon = true;
        m_parent->m_flow_cond.notify_all();
    }
    else if (starts_with(cmd, "XOFF"))
    {
        send_status(cmd, "OK");
        // Used when FlowControl is XON/XOFF
        m_parent->m_xon = false;
        m_parent->m_flow_cond.notify_all();
    }
    else if (starts_with(cmd, "TuneChannel"))
    {
        // Used if we announce that we have a 'tuner'
        send_status(cmd, "ERR:Not supported");
    }
    else if (starts_with(cmd, "IsOpen?"))
    {
        std::unique_lock<std::mutex> lk(m_parent->m_run_mutex);
        if (m_parent->m_fatal)
            send_status(cmd, "ERR:" + m_parent->m_fatal_msg);
        else if (m_parent->m_ready)
            send_status(cmd, "OK:Open");
        else
            send_status(cmd, "WARN:Not Open yet");
    }
    else if (starts_with(cmd, "CloseRecorder"))
    {
        send_status(cmd, "OK:Terminating");
        m_parent->Terminate();
        return true;
    }
    else if (starts_with(cmd, "FlowControl?"))
    {
        send_status(cmd, "OK:XON/XOFF");
    }
    else if (starts_with(cmd, "BlockSize"))
    {
        m_parent->BlockSize(stoul(cmd.substr(10)));
        send_status(cmd, "OK");
    }
    else if (starts_with(cmd, "StartStreaming"))
    {
        if (m_parent->StartEncoding())
            send_status(cmd, "OK:Started");
        else
            send_status(cmd, "ERR:Failed to start encoding.");
    }
    else if (starts_with(cmd, "StopStreaming"))
    {
        /* This does not close the stream!  When Myth is done with
         * this 'recording' ExternalChannel::EnterPowerSavingMode()
         * will be called, which invokes CloseRecorder() */
        if (m_parent->StopEncoding())
            send_status(cmd, "OK:Stopped");
        else
            send_status(cmd, "ERR:Failed to start encoding.");
    }
    else
        send_status(cmd, "ERR:Unrecognized command");

    return true;
}

void Commands::Run(void)
{
    string cmd;
    int    timeout = 250;

    int ret;
    int poll_cnt = 1;
    struct pollfd polls[2];
    memset(polls, 0, sizeof(polls));

    polls[0].fd      = 0;
    polls[0].events  = POLLIN | POLLPRI;
    polls[0].revents = 0;

    Logger::setThreadName("Commands");
    LOG(Logger::INFO) << "Command parser: ready." << flush;

    while (m_parent->m_run)
    {
        ret = poll(polls, poll_cnt, timeout);

        if (polls[0].revents & POLLHUP)
        {
            LOG(Logger::ERR) << "poll eof (POLLHUP)" << flush;
            break;
        }
        else if (polls[0].revents & POLLNVAL)
        {
            m_parent->Fatal("poll error");
            return;
        }

        if (polls[0].revents & POLLIN)
        {
            if (ret > 0)
            {
                std::getline(std::cin, cmd);
                if (!process_command(cmd))
                    m_parent->Fatal("Invalid command");
            }
            else if (ret < 0)
            {
                if ((EOVERFLOW == errno))
                {
                    LOG(Logger::ERR) << "command overflow" << flush;
                    break; // we have an error to handle
                }

                if ((EAGAIN == errno) || (EINTR  == errno))
                {
                    LOG(Logger::ERR) << "retry command read." << flush;
                    continue; // errors that tell you to try again
                }

                LOG(Logger::ERR) << "unknown error reading command." << flush;
            }
        }
    }

    LOG(Logger::INFO) << "Command parser: shutting down" << flush;
}

Buffer::Buffer(MythTV * parent)
    : m_thread(),
      m_parent(parent),
      m_cb(std::bind(&Buffer::Fill, this, std::placeholders::_1,
                     std::placeholders::_2))
{
    m_heartbeat = std::chrono::system_clock::now();
}

void Buffer::Fill(void * data, size_t len)
{
    if (len < 1)
        return;

    static int dropped = 0;

    m_parent->m_flow_mutex.lock();
    if (m_data.size() < MAX_QUEUE)
    {
        block_t blk(reinterpret_cast<uint8_t *>(data),
                    reinterpret_cast<uint8_t *>(data) + len);

        m_data.push(blk);
        dropped = 0;
    }
    else if (++dropped % 25 == 0)
    {
        LOG(Logger::WARNING) << "Packet queue overrun.  Dropped " << dropped
                             << "packets." << flush;
    }

    m_parent->m_flow_mutex.unlock();
    m_parent->m_flow_cond.notify_all();

    m_heartbeat = std::chrono::system_clock::now();
}

void Buffer::Run(void)
{
    bool       is_empty = false;
    bool       wait = false;
    time_t     send_time = time (NULL) + (60 * 5);
    uint64_t   write_total = 0;
    uint64_t   written = 0;
    uint64_t   write_cnt = 0;
    uint64_t   empty_cnt = 0;

    Logger::setThreadName("Buffer");
    LOG(Logger::INFO) << "Buffer: Ready for data." << flush;

    while (m_parent->m_run)
    {
        if (wait)
        {
            std::unique_lock<std::mutex> lk(m_parent->m_flow_mutex);
            m_parent->m_flow_cond.wait(lk);
            wait = false;
        }

        if (send_time < static_cast<double>(time (NULL)))
        {
            // Every 5 minutes, write out some statistics.
            send_time = time (NULL) + (60 * 5);
            write_total += written;
            if (m_parent->m_streaming)
                LOG(Logger::NOTICE) << "Count: " << write_cnt
                                    << ", Empty cnt: " << empty_cnt
                                    << ", Written: " << written
                                    << ", Total: " << write_total
                                    << flush;
            else
                LOG(Logger::NOTICE) << "Not streaming." << flush;

            write_cnt = empty_cnt = written = 0;
        }

        if (m_parent->m_streaming)
        {
            if (m_parent->m_xon)
            {
                block_t pkt;
                m_parent->m_flow_mutex.lock();
                if (!m_data.empty())
                {
                    pkt = m_data.front();
                    m_data.pop();
                    is_empty = m_data.empty();
                }
                m_parent->m_flow_mutex.unlock();

                if (!pkt.empty())
                {
                    write(1, pkt.data(), pkt.size());
                    written += pkt.size();
                    ++write_cnt;
                }

                if (is_empty)
                {
                    wait = true;
                    ++empty_cnt;
                }
            }
            else
                wait = true;
        }
        else
        {
            // Clear packet queue
            m_parent->m_flow_mutex.lock();
            if (!m_data.empty())
            {
                stack_t dummy;
                std::swap(m_data, dummy);
            }
            m_parent->m_flow_mutex.unlock();

            wait = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }

    LOG(Logger::INFO) << "Buffer: shutting down" << flush;
}