/*  -*- Mode: c++ -*-
 *
 *  Copyright (C) John Poet 2018
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


#include "Common.h"

using namespace std;

bool StartEncoding(encoderDev_DXT_t & encDev, FX2Device_t & fx2)

{
    if (!encDev.startCapture())
    {
        LOG(Logger::CRIT) << "Encoder start capture FAILED" << flush;
        encDev.stopCapture();
        return false;
    }
    LOG(Logger::NOTICE) << "Capture started" << flush;

    LOG(Logger::DEBUG) << "\nPORT_A: [0x" << fx2.getPortDir(FX2_PORT_A)
                       << "] 0x" << fx2.getPortState(FX2_PORT_A) << '\n'
                       << "PORT_B: [0x" << fx2.getPortDir(FX2_PORT_B)
                       << "] 0x" << fx2.getPortState(FX2_PORT_B) << '\n'
                       << "PORT_C: [0x" << fx2.getPortDir(FX2_PORT_C)
                       << "] 0x" << fx2.getPortState(FX2_PORT_C) << '\n'
                       << "PORT_D: [0x" << fx2.getPortDir(FX2_PORT_D)
                       << "] 0x" << fx2.getPortState(FX2_PORT_D) << '\n'
                       << "PORT_E: [0x" << fx2.getPortDir(FX2_PORT_E)
                       << "] 0x" << fx2.getPortState(FX2_PORT_E) << '\n'
                       << "CTL_PORTS: [0x" << fx2.getPortDir(FX2_CTL_PORTS)
                       << "] 0x" << fx2.getPortState(FX2_CTL_PORTS) << flush;

    return true;
}

bool StopEncoding(encoderDev_DXT_t & encDev, FX2Device_t & fx2)
{
    LOG(Logger::DEBUG) << "\nPORT_A: [0x" << fx2.getPortDir(FX2_PORT_A)
                       << "] 0x" << fx2.getPortState(FX2_PORT_A) << '\n'
                       << "PORT_B: [0x" << fx2.getPortDir(FX2_PORT_B)
                       << "] 0x" << fx2.getPortState(FX2_PORT_B) << '\n'
                       << "PORT_C: [0x" << fx2.getPortDir(FX2_PORT_C)
                       << "] 0x" << fx2.getPortState(FX2_PORT_C) << '\n'
                       << "PORT_D: [0x" << fx2.getPortDir(FX2_PORT_D)
                       << "] 0x" << fx2.getPortState(FX2_PORT_D) << '\n'
                       << "PORT_E: [0x" << fx2.getPortDir(FX2_PORT_E)
                       << "] 0x" << fx2.getPortState(FX2_PORT_E)<< '\n'
                       << "CTL_PORTS: [0x" << fx2.getPortDir(FX2_CTL_PORTS)
                       << "] 0x" << fx2.getPortState(FX2_CTL_PORTS) << flush;

    if (!encDev.stopCapture())
    {
        LOG(Logger::CRIT) << "Encoder stop capture FAILED" << flush;
        return false;
    }

    LOG(Logger::NOTICE) << "Capture stopped" << flush;

    return true;
}
