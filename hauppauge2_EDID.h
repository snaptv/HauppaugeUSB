#ifndef _hauppauge2_EDID_h_
#define _hauppauge2_EDID_h_

#include <cstdint>

/* HD-PVR2 EDID */

/* updated 1080p60&50, LPCM Only Audio, RGB only */
static const uint8_t edidHDPVR2_1080p6050_pcm_fix_rgb[] = {
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, //0x00   0
  0x20, 0x77, 0x04, 0xE5, 0x00, 0x00, 0x00, 0x00, //0x08   8
  0x35, 0x16, 0x01, 0x03, 0x80, 0x00, 0x00, 0x78, //0x10  16
  0x02, 0xAA, 0x33, 0xA4, 0x55, 0x48, 0x93, 0x25, //0x18  24
  0x10, 0x45, 0x47, 0x20, 0x00, 0x00, 0x81, 0x00, //0x20  32
  0x81, 0x80, 0x8B, 0xC0, 0x4B, 0xC0, 0x95, 0x00, //0x28  40
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, //0x30  48
  0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, //0x38  56
  0x45, 0x00, 0x10, 0x09, 0x00, 0x00, 0x00, 0x1E, //0x40  64
  0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, //0x48  72
  0x6E, 0x28, 0x55, 0x00, 0x10, 0x09, 0x00, 0x00, //0x50  80
  0x00, 0x1E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x48, //0x58  88
  0x44, 0x2D, 0x50, 0x56, 0x52, 0x32, 0x20, 0x20, //0x60  96
  0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFD, //0x68 104
  0x00, 0x17, 0x3D, 0x0F, 0x44, 0x0F, 0x00, 0x0A, //0x70 112
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x20, //0x78 120

  0x02, 0x03, 0x23, 0xC1, 0x50, 0x90, 0x22, 0x20, //0x80
  0x05, 0x04, 0x14, 0x13, 0x03, 0x12, 0x02, 0x11, //0x88
  0x07, 0x16, 0x06, 0x15, 0x01, 0x23, 0x09, 0x07, //0x90
  0x07, 0x83, 0x01, 0x00, 0x00, 0x65, 0x03, 0x0C, //0x98
  0x00, 0x10, 0x00, 0x01, 0x1D, 0x80, 0x18, 0x71, //0xA0 SPA@0xA1
  0x1C, 0x16, 0x20, 0x58, 0x2C, 0x25, 0x00, 0x10, //0xA8
  0x09, 0x00, 0x00, 0x00, 0x9E, 0x01, 0x1D, 0x00, //0xB0
  0x72, 0x51, 0xD0, 0x1E, 0x20, 0x6E, 0x28, 0x55, //0xB8
  0x00, 0x10, 0x09, 0x00, 0x00, 0x00, 0x1E, 0x8C, //0xC0
  0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10, //0xC8
  0x3E, 0x96, 0x00, 0x10, 0x09, 0x00, 0x00, 0x00, //0xD0
  0x18, 0x8C, 0x0A, 0xD0, 0x90, 0x20, 0x40, 0x31, //0xD8
  0x20, 0x0C, 0x40, 0x55, 0x00, 0x10, 0x09, 0x00, //0xE0
  0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, //0xE8
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xF0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7D, //0xF8
};//end Edid data

static const uint8_t  edidHDPVR2_1080p6050_pcm_fix_rgbSpaLoc = 0xA1;


/* updated 1080p60&50, LPCM_AC3 Audio, RGB only */
static const uint8_t  edidHDPVR2_1080p6050_ac3_fix_rgb[] = {
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, //0x00
  0x20, 0x77, 0x04, 0xE5, 0x00, 0x00, 0x00, 0x00, //0x08
  0x35, 0x16, 0x01, 0x03, 0x80, 0x00, 0x00, 0x78, //0x10
  0x02, 0xAA, 0x33, 0xA4, 0x55, 0x48, 0x93, 0x25, //0x18
  0x10, 0x45, 0x47, 0x20, 0x00, 0x00, 0x81, 0x00, //0x20
  0x81, 0x80, 0x8B, 0xC0, 0x4B, 0xC0, 0x95, 0x00, //0x28
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, //0x30
  0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, //0x38
  0x45, 0x00, 0x10, 0x09, 0x00, 0x00, 0x00, 0x1E, //0x40
  0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, //0x48
  0x6E, 0x28, 0x55, 0x00, 0x10, 0x09, 0x00, 0x00, //0x50
  0x00, 0x1E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x48, //0x58
  0x44, 0x2D, 0x50, 0x56, 0x52, 0x32, 0x20, 0x20, //0x60
  0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFD, //0x68
  0x00, 0x17, 0x3D, 0x0F, 0x44, 0x0F, 0x00, 0x0A, //0x70
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x20, //0x78

  0x02, 0x03, 0x26, 0xC1, 0x50, 0x90, 0x22, 0x20, //0x80
  0x05, 0x04, 0x14, 0x13, 0x03, 0x12, 0x02, 0x11, //0x88
  0x07, 0x16, 0x06, 0x15, 0x01, 0x26, 0x09, 0x07, //0x90
  0x07, 0x15, 0x07, 0x30, 0x83, 0x0F, 0x00, 0x00, //0x98
  0x65, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x01, 0x1D, //0xA0 SPA@0xA4
  0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C, //0xA8
  0x25, 0x00, 0x10, 0x09, 0x00, 0x00, 0x00, 0x9E, //0xB0
  0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, //0xB8
  0x6E, 0x28, 0x55, 0x00, 0x10, 0x09, 0x00, 0x00, //0xC0
  0x00, 0x1E, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, //0xC8
  0x2D, 0x10, 0x10, 0x3E, 0x96, 0x00, 0x10, 0x09, //0xD0
  0x00, 0x00, 0x00, 0x18, 0x8C, 0x0A, 0xD0, 0x90, //0xD8
  0x20, 0x40, 0x31, 0x20, 0x0C, 0x40, 0x55, 0x00, //0xE0
  0x10, 0x09, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, //0xE8
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xF0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, //0xF8
};//end Edid data

static const uint8_t edidHDPVR2_1080p6050_ac3_fix_rgbSpaLoc = 0xA4;


/* 1080p60&50, Atmos Audio */
static const uint8_t edidHDPVR2_1080p6050_atmos[] = {
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, //0x00
    0x25, 0xD4, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, //0x08
    0x20, 0x19, 0x01, 0x03, 0x80, 0x00, 0x00, 0x78, //0x10
    0x1A, 0xEE, 0x91, 0xA3, 0x54, 0x4C, 0x99, 0x26, //0x18
    0x0F, 0x50, 0x54, 0xA1, 0x4B, 0x00, 0x31, 0x40, //0x20
    0x45, 0x40, 0x61, 0x40, 0x71, 0x40, 0x81, 0x80, //0x28
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, //0x30
    0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, //0x38
    0x45, 0x00, 0x40, 0x84, 0x63, 0x00, 0x00, 0x1E, //0x40
    0x66, 0x21, 0x50, 0xB0, 0x51, 0x00, 0x1B, 0x30, //0x48
    0x40, 0x70, 0x36, 0x00, 0x40, 0x84, 0x63, 0x00, //0x50
    0x00, 0x1E, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x0F, //0x58
    0x4B, 0x1E, 0x53, 0x10, 0x00, 0x00, 0x00, 0x00, //0x60
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, //0x68
    0x00, 0x49, 0x4E, 0x54, 0x45, 0x47, 0x52, 0x41, //0x70
    0x4C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x01, 0x52, //0x78
    0x02, 0x03, 0x36, 0x71, 0x48, 0x90, 0x22, 0x20, //0x80
    0x05, 0x04, 0x03, 0x02, 0x01, 0x35, 0x0F, 0x7F, //0x88
    0x07, 0x15, 0x07, 0x50, 0x3D, 0x1E, 0xC0, 0x4D, //0x90
    0x02, 0x00, 0x57, 0x06, 0x01, 0x5F, 0x7E, 0x03, //0x98
    0x67, 0x7E, 0x01, 0x83, 0x5F, 0x00, 0x00, 0x6A, //0xA0
    0x03, 0x0C, 0x00, 0x10, 0x00, 0xB8, 0x2D, 0x20, //0xA8
    0x80, 0x00, 0xE3, 0x05, 0x03, 0x01, 0x02, 0x3A, //0xB0
    0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, //0xB8
    0x45, 0x00, 0x40, 0x84, 0x63, 0x00, 0x00, 0x1E, //0xC0
    0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, //0xC8
    0x58, 0x2C, 0x25, 0x00, 0x40, 0x84, 0x63, 0x00, //0xD0
    0x00, 0x9E, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, //0xD8
    0x1E, 0x20, 0x6E, 0x28, 0x55, 0x00, 0x40, 0x84, //0xE0
    0x63, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, //0XE8
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xF0
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8D, //0xF8
};

static const uint8_t edidHDPVR2_1080p6050_atmos_SPAloc = 0xAB;

#endif