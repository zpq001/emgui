/*****************************************************
    Font generation template
*****************************************************/

#include <stdint.h>
#include "guiFonts.h"

static const uint8_t font_h12_data [] =
{
    // symbol 0x20
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x21
    0x7F, 0x7F, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x22
    0x0B, 0x07, 0x00, 0x0B, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    // symbol 0x23
    0xCC, 0xFF, 0xFF, 0xCC, 0xFF, 0xFF, 0xCC, 0x00,
    0x00, 0x03, 0x03, 0x00, 0x03, 0x03, 0x00, 0x00,

    // symbol 0x24
    0x9E, 0xBF, 0x33, 0xFF, 0x33, 0xF7, 0xE6, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x25
    0x87, 0xC5, 0x67, 0x30, 0x98, 0x8C, 0x86, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x03, 0x02, 0x03, 0x00,

    // symbol 0x26
    0xEE, 0xFF, 0x33, 0x7F, 0xEE, 0xC0, 0x40, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x03, 0x00,

    // symbol 0x27
    0x0B, 0x07, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x28
    0xFE, 0xFF, 0x03, 0x00, 0x01, 0x03, 0x03, 0x00,

    // symbol 0x29
    0x03, 0xFF, 0xFE, 0x00, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x2A
    0x30, 0xB6, 0xFE, 0xFC, 0xFE, 0xB6, 0x30, 0x00,
    0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00,

    // symbol 0x2B
    0x30, 0x30, 0xFC, 0xFC, 0x30, 0x30, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x2C
    0x00, 0x00, 0x00, 0x0B, 0x07, 0x00,

    // symbol 0x2D
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x2E
    0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x2F
    0x00, 0xC0, 0xF0, 0x3C, 0x0F, 0x03, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x30
    0xFE, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x31
    0x18, 0x1C, 0x0E, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x00,

    // symbol 0x32
    0x06, 0x87, 0xC3, 0xE3, 0x73, 0x3F, 0x1E, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0x33
    0x86, 0x87, 0x33, 0x33, 0x33, 0xFF, 0xEE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x34
    0xFF, 0xFF, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00,

    // symbol 0x35
    0xBF, 0xBF, 0x33, 0x33, 0x33, 0xF3, 0xE3, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x36
    0xFE, 0xFF, 0x33, 0x33, 0x33, 0xF7, 0xE6, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x37
    0x03, 0x03, 0x83, 0xE3, 0xFB, 0x3F, 0x0F, 0x00,
    0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x38
    0xEE, 0xFF, 0x33, 0x33, 0x33, 0xFF, 0xEE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x39
    0x9E, 0xBF, 0x33, 0x33, 0x33, 0xFF, 0xFE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x3A
    0x0C, 0x0C, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x3B
    0x0C, 0x0C, 0x00, 0x0B, 0x07, 0x00,

    // symbol 0x3C
    0x30, 0x78, 0xFC, 0xCE, 0x87, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x03, 0x03, 0x00,

    // symbol 0x3D
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x3E
    0x03, 0x87, 0xCE, 0xFC, 0x78, 0x30, 0x00, 0x03,
    0x03, 0x01, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x3F
    0x06, 0x07, 0x63, 0x73, 0x3F, 0x1E, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x00, 0x00, 0x00,

    // symbol 0x40
    0xFE, 0xFF, 0x03, 0x73, 0x4B, 0x7F, 0x7E, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x41
    0xF8, 0xFC, 0xCE, 0xC7, 0xC3, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x42
    0xFF, 0xFF, 0x33, 0x33, 0x33, 0xFF, 0xEE, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x43
    0xFE, 0xFF, 0x03, 0x03, 0x03, 0x87, 0x86, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x44
    0xFF, 0xFF, 0x03, 0x03, 0x87, 0xFE, 0xFC, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00,

    // symbol 0x45
    0xFF, 0xFF, 0x33, 0x33, 0x33, 0x03, 0x03, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0x46
    0xFF, 0xFF, 0x33, 0x33, 0x33, 0x03, 0x03, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x47
    0xFE, 0xFF, 0x03, 0x33, 0x33, 0xF7, 0xF6, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x48
    0xFF, 0xFF, 0x30, 0x30, 0x30, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x49
    0x03, 0xFF, 0xFF, 0x03, 0x00, 0x03, 0x03, 0x03,
    0x03, 0x00,

    // symbol 0x4A
    0x80, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x4B
    0xFF, 0xFF, 0x78, 0xFC, 0xCE, 0x87, 0x03, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00,

    // symbol 0x4C
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0x4D
    0xFF, 0xFF, 0x0E, 0x1C, 0x1C, 0x0E, 0xFF, 0xFF,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,

    // symbol 0x4E
    0xFF, 0xFF, 0x1C, 0x38, 0x70, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x4F
    0xFE, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x50
    0xFF, 0xFF, 0x33, 0x33, 0x33, 0x3F, 0x1E, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x51
    0xFE, 0xFF, 0x03, 0xC3, 0xC3, 0xFF, 0xFE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x07, 0x07, 0x01, 0x00,

    // symbol 0x52
    0xFF, 0xFF, 0x73, 0xF3, 0xF3, 0xBF, 0x1E, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00,

    // symbol 0x53
    0x9E, 0xBF, 0x33, 0x33, 0x33, 0xF7, 0xE6, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x54
    0x03, 0x03, 0xFF, 0xFF, 0x03, 0x03, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x00, 0x00, 0x00,

    // symbol 0x55
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x56
    0x3F, 0xFF, 0xE0, 0xC0, 0xE0, 0xFF, 0x3F, 0x00,
    0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00,

    // symbol 0x57
    0xFF, 0xFF, 0x80, 0xF0, 0xF0, 0x80, 0xFF, 0xFF,
    0x01, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x01,

    // symbol 0x58
    0x87, 0xCF, 0xFC, 0x78, 0xFC, 0xCF, 0x87, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x59
    0x0F, 0x1F, 0xF8, 0xF8, 0x1F, 0x0F, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x00, 0x00, 0x00,

    // symbol 0x5A
    0xC3, 0xE3, 0x73, 0x3B, 0x1F, 0x0F, 0x07, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0x5B
    0xFF, 0xFF, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03,
    0x03, 0x00,

    // symbol 0x5C
    0x03, 0x0F, 0x3C, 0xF0, 0xC0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x5D
    0x03, 0x03, 0xFF, 0xFF, 0x00, 0x03, 0x03, 0x03,
    0x03, 0x00,

    // symbol 0x5E
    0x0C, 0x0E, 0x07, 0x07, 0x0E, 0x0C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x5F
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0x60
    0x03, 0x07, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,

    // symbol 0x61
    0xC0, 0xEC, 0x6C, 0x6C, 0xFC, 0xF8, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x01, 0x03, 0x00,

    // symbol 0x62
    0xFF, 0xFF, 0x18, 0x18, 0xF8, 0xF0, 0x00, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x63
    0xF8, 0xFC, 0x0C, 0x0C, 0x9C, 0x98, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x64
    0xF0, 0xF8, 0x18, 0x18, 0xFF, 0xFF, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0x65
    0xF8, 0xFC, 0x6C, 0x6C, 0x7C, 0x78, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00,

    // symbol 0x66
    0x18, 0xFE, 0xFF, 0x1B, 0x1B, 0x00, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x00,

    // symbol 0x67
    0x78, 0xFC, 0xCC, 0xC8, 0xFC, 0xFC, 0x00, 0x00,
    0x06, 0x06, 0x06, 0x07, 0x03, 0x00,

    // symbol 0x68
    0xFF, 0xFF, 0x18, 0x18, 0xF8, 0xF0, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x69
    0xFB, 0xFB, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x6A
    0x00, 0x00, 0x00, 0xFB, 0xFB, 0x00, 0x03, 0x07,
    0x06, 0x07, 0x03, 0x00,

    // symbol 0x6B
    0xFF, 0xFF, 0xF0, 0xF8, 0x9C, 0x0C, 0x00, 0x03,
    0x03, 0x00, 0x01, 0x03, 0x03, 0x00,

    // symbol 0x6C
    0xFF, 0xFF, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x6D
    0xFC, 0xFC, 0x1C, 0x78, 0x1C, 0xFC, 0xF8, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x6E
    0xFC, 0xFC, 0x18, 0x0C, 0xFC, 0xF8, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x6F
    0xF8, 0xFC, 0x0C, 0x0C, 0xFC, 0xF8, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x70
    0xFC, 0xFC, 0xCC, 0xCC, 0xFC, 0x78, 0x00, 0x07,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x71
    0x3C, 0x7E, 0x66, 0x66, 0xFE, 0xFE, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x72
    0xFC, 0xFC, 0x18, 0x0C, 0x1C, 0x18, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x73
    0x78, 0x7C, 0x6C, 0x6C, 0xEC, 0xEC, 0x00, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x74
    0x0C, 0x0C, 0xFC, 0xFC, 0x0C, 0x0C, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x00, 0x00, 0x00,

    // symbol 0x75
    0xFC, 0xFC, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x76
    0xFC, 0xFC, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0x00,
    0x01, 0x03, 0x03, 0x01, 0x00, 0x00,

    // symbol 0x77
    0xFC, 0xFC, 0x00, 0xC0, 0x00, 0xFC, 0xFC, 0x00,
    0x01, 0x03, 0x03, 0x01, 0x03, 0x03, 0x01, 0x00,

    // symbol 0x78
    0x9C, 0xFC, 0x60, 0x60, 0xFC, 0x9C, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x79
    0x3C, 0x7C, 0x60, 0x60, 0xFC, 0xFC, 0x00, 0x03,
    0x07, 0x06, 0x06, 0x07, 0x03, 0x00,

    // symbol 0x7A
    0x8C, 0xCC, 0xEC, 0x7C, 0x3C, 0x1C, 0x00, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0x7B
    0x30, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x01, 0x03,
    0x03, 0x00,

    // symbol 0x7C
    0xFF, 0xFF, 0x00, 0x03, 0x03, 0x00,

    // symbol 0x7D
    0x03, 0xFF, 0xFE, 0x30, 0x00, 0x03, 0x03, 0x01,
    0x00, 0x00,

    // symbol 0x7E
    0x06, 0x03, 0x07, 0x07, 0x06, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0x80
    0xFF, 0x01, 0x89, 0xFD, 0x81, 0x01, 0xFF, 0x00,
    0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x00,

    // symbol 0x81
    0xFF, 0x01, 0xC5, 0xA5, 0x9D, 0x01, 0xFF, 0x00,
    0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x00,

    // symbol 0x82
    0xC0, 0xC0, 0x00, 0xF0, 0xF0, 0xC0, 0xF0, 0xF0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,

    // symbol 0xA8
    0xFF, 0xFF, 0x33, 0x33, 0x33, 0x03, 0x03, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0xA9
    0xFE, 0x07, 0x73, 0x8B, 0x8B, 0x53, 0x07, 0xFE,
    0x03, 0x07, 0x06, 0x06, 0x06, 0x06, 0x07, 0x03,

    // symbol 0xB0
    0x0E, 0x1F, 0x1B, 0x1F, 0x0E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    // symbol 0xB8
    0xF8, 0xFD, 0x6C, 0x6C, 0x7D, 0x38, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00,

    // symbol 0xC0
    0xF8, 0xFC, 0xCE, 0xC7, 0xC3, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xC1
    0xFF, 0xFF, 0x33, 0x33, 0x33, 0xF3, 0xE3, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xC2
    0xFF, 0xFF, 0x33, 0x33, 0x33, 0xFF, 0xEE, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xC3
    0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0xC4
    0x00, 0xFE, 0xFF, 0x03, 0x03, 0xFF, 0xFF, 0x00,
    0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07,

    // symbol 0xC5
    0xFF, 0xFF, 0x33, 0x33, 0x33, 0x33, 0x03, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00,

    // symbol 0xC6
    0x03, 0xCF, 0xFC, 0xFF, 0xFF, 0xFC, 0xCF, 0x03,
    0x03, 0x03, 0x00, 0x03, 0x03, 0x00, 0x03, 0x03,

    // symbol 0xC7
    0x86, 0x87, 0x33, 0x33, 0x33, 0xFF, 0xCE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xC8
    0xFF, 0xFF, 0x70, 0x38, 0x1C, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xC9
    0xFF, 0xFF, 0x70, 0x3B, 0x1C, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xCA
    0xFF, 0xFF, 0x78, 0xFC, 0xCE, 0x87, 0x03, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00,

    // symbol 0xCB
    0x00, 0xFE, 0xFF, 0x03, 0x03, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x01, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xCC
    0xFF, 0xFF, 0x0E, 0x3C, 0x3C, 0x0E, 0xFF, 0xFF,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,

    // symbol 0xCD
    0xFF, 0xFF, 0x30, 0x30, 0x30, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xCE
    0xFE, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xCF
    0xFF, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xD0
    0xFF, 0xFF, 0x63, 0x63, 0x63, 0x7F, 0x3E, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0xD1
    0xFE, 0xFF, 0x03, 0x03, 0x03, 0x87, 0x86, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xD2
    0x03, 0x03, 0xFF, 0xFF, 0x03, 0x03, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x00, 0x00, 0x00,

    // symbol 0xD3
    0x9F, 0xBF, 0x30, 0x30, 0xB0, 0xFF, 0xFF, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00,

    // symbol 0xD4
    0x3E, 0x7F, 0x63, 0xFF, 0xFF, 0x63, 0x7F, 0x3E,
    0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00,

    // symbol 0xD5
    0x87, 0xCF, 0xFC, 0x30, 0xFC, 0xCF, 0x87, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xD6
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x06,

    // symbol 0xD7
    0x1F, 0x3F, 0x30, 0x30, 0x30, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xD8
    0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,

    // symbol 0xD9
    0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07,

    // symbol 0xDA
    0x03, 0xFF, 0xFF, 0x18, 0x18, 0xF8, 0xF0, 0x00,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xDB
    0xFF, 0xFF, 0x18, 0xF8, 0xF0, 0x00, 0xFF, 0xFF,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03,

    // symbol 0xDC
    0xFF, 0xFF, 0x18, 0x18, 0xF8, 0xF0, 0x00, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xDD
    0x86, 0x87, 0x33, 0x33, 0x33, 0xFF, 0xFE, 0x00,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xDE
    0xFF, 0xFF, 0x30, 0xFE, 0xFF, 0x03, 0xFF, 0xFE,
    0x03, 0x03, 0x00, 0x01, 0x03, 0x03, 0x03, 0x01,

    // symbol 0xDF
    0x1E, 0xBF, 0xF3, 0xF3, 0x73, 0xFF, 0xFF, 0x00,
    0x03, 0x03, 0x01, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xE0
    0xC0, 0xE8, 0x6C, 0x6C, 0xFC, 0xF8, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x01, 0x03, 0x00,

    // symbol 0xE1
    0xF8, 0xFC, 0x6C, 0x6C, 0xEE, 0xC6, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xE2
    0xFC, 0xFC, 0x6C, 0x6C, 0xFC, 0xD8, 0x00, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xE3
    0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0xE4
    0x00, 0xFC, 0xFC, 0x0C, 0xFC, 0xFC, 0x00, 0x00,
    0x07, 0x07, 0x03, 0x03, 0x03, 0x07, 0x07, 0x00,

    // symbol 0xE5
    0xF8, 0xFC, 0x6C, 0x6C, 0x7C, 0x38, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00,

    // symbol 0xE6
    0x9C, 0xFC, 0x60, 0xFC, 0xFC, 0x60, 0xFC, 0x9C,
    0x03, 0x03, 0x00, 0x03, 0x03, 0x00, 0x03, 0x03,

    // symbol 0xE7
    0x08, 0x0C, 0x6C, 0x6C, 0xFC, 0x98, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xE8
    0xFC, 0xFC, 0xE0, 0x70, 0xFC, 0xFC, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xE9
    0xFC, 0xFC, 0xE3, 0x71, 0xFC, 0xFC, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xEA
    0xFC, 0xFC, 0xF0, 0xF8, 0x9C, 0x0C, 0x00, 0x03,
    0x03, 0x00, 0x01, 0x03, 0x03, 0x00,

    // symbol 0xEB
    0x80, 0xE0, 0x78, 0x1C, 0xFC, 0xFC, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xEC
    0xFC, 0xFC, 0x38, 0x70, 0x38, 0xFC, 0xFC, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xED
    0xFC, 0xFC, 0x60, 0x60, 0xFC, 0xFC, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xEE
    0xF8, 0xFC, 0x0C, 0x0C, 0xFC, 0xF8, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xEF
    0xFC, 0xFC, 0x0C, 0x0C, 0xFC, 0xFC, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xF0
    0xFC, 0xFC, 0xCC, 0xCC, 0xFC, 0x78, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00,

    // symbol 0xF1
    0xF8, 0xFC, 0x0C, 0x0C, 0x9C, 0x98, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xF2
    0x0C, 0x0C, 0xFC, 0xFC, 0x0C, 0x0C, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x00, 0x00, 0x00,

    // symbol 0xF3
    0x3C, 0x7C, 0x60, 0x60, 0xFC, 0xFC, 0x00, 0x03,
    0x07, 0x06, 0x06, 0x07, 0x03, 0x00,

    // symbol 0xF4
    0xF0, 0xF8, 0x98, 0xFC, 0xFC, 0x98, 0xF8, 0xF0,
    0x00, 0x01, 0x01, 0x07, 0x07, 0x01, 0x01, 0x00,

    // symbol 0xF5
    0x9C, 0xFC, 0x60, 0x60, 0xFC, 0x9C, 0x00, 0x03,
    0x03, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xF6
    0xFC, 0xFC, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x06, 0x00,

    // symbol 0xF7
    0x3C, 0x7C, 0x60, 0x60, 0xFC, 0xFC, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x03, 0x00,

    // symbol 0xF8
    0xFC, 0xFC, 0x00, 0xF0, 0xF0, 0x00, 0xFC, 0xFC,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,

    // symbol 0xF9
    0xFC, 0xFC, 0x00, 0xFC, 0xFC, 0x00, 0xFC, 0xFC,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07,

    // symbol 0xFA
    0x0C, 0xFC, 0xFC, 0x30, 0x30, 0xF0, 0xE0, 0x00,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xFB
    0xFC, 0xFC, 0x30, 0xF0, 0xE0, 0x00, 0xFC, 0xFC,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03,

    // symbol 0xFC
    0xFC, 0xFC, 0x30, 0x30, 0xF0, 0xE0, 0x00, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xFD
    0x08, 0x0C, 0x6C, 0x6C, 0xFC, 0xF8, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x00,

    // symbol 0xFE
    0xFC, 0xFC, 0x60, 0xF8, 0xFC, 0x0C, 0xFC, 0xF8,
    0x03, 0x03, 0x00, 0x01, 0x03, 0x03, 0x03, 0x01,

    // symbol 0xFF
    0x38, 0xFC, 0xEC, 0xEC, 0xFC, 0xFC, 0x00, 0x03,
    0x03, 0x01, 0x00, 0x03, 0x03, 0x00,

};



static const uint8_t font_h12_code_table[166] =
{
    0x20,
    0x21,
    0x22,
    0x23,
    0x24,
    0x25,
    0x26,
    0x27,
    0x28,
    0x29,
    0x2A,
    0x2B,
    0x2C,
    0x2D,
    0x2E,
    0x2F,
    0x30,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
    0x3A,
    0x3B,
    0x3C,
    0x3D,
    0x3E,
    0x3F,
    0x40,
    0x41,
    0x42,
    0x43,
    0x44,
    0x45,
    0x46,
    0x47,
    0x48,
    0x49,
    0x4A,
    0x4B,
    0x4C,
    0x4D,
    0x4E,
    0x4F,
    0x50,
    0x51,
    0x52,
    0x53,
    0x54,
    0x55,
    0x56,
    0x57,
    0x58,
    0x59,
    0x5A,
    0x5B,
    0x5C,
    0x5D,
    0x5E,
    0x5F,
    0x60,
    0x61,
    0x62,
    0x63,
    0x64,
    0x65,
    0x66,
    0x67,
    0x68,
    0x69,
    0x6A,
    0x6B,
    0x6C,
    0x6D,
    0x6E,
    0x6F,
    0x70,
    0x71,
    0x72,
    0x73,
    0x74,
    0x75,
    0x76,
    0x77,
    0x78,
    0x79,
    0x7A,
    0x7B,
    0x7C,
    0x7D,
    0x7E,
    0x80,
    0x81,
    0x82,
    0xA8,
    0xA9,
    0xB0,
    0xB8,
    0xC0,
    0xC1,
    0xC2,
    0xC3,
    0xC4,
    0xC5,
    0xC6,
    0xC7,
    0xC8,
    0xC9,
    0xCA,
    0xCB,
    0xCC,
    0xCD,
    0xCE,
    0xCF,
    0xD0,
    0xD1,
    0xD2,
    0xD3,
    0xD4,
    0xD5,
    0xD6,
    0xD7,
    0xD8,
    0xD9,
    0xDA,
    0xDB,
    0xDC,
    0xDD,
    0xDE,
    0xDF,
    0xE0,
    0xE1,
    0xE2,
    0xE3,
    0xE4,
    0xE5,
    0xE6,
    0xE7,
    0xE8,
    0xE9,
    0xEA,
    0xEB,
    0xEC,
    0xED,
    0xEE,
    0xEF,
    0xF0,
    0xF1,
    0xF2,
    0xF3,
    0xF4,
    0xF5,
    0xF6,
    0xF7,
    0xF8,
    0xF9,
    0xFA,
    0xFB,
    0xFC,
    0xFD,
    0xFE,
    0xFF,
};

static const uint8_t font_h12_width_table[166] =
{
    8,
    3,
    6,
    8,
    8,
    8,
    8,
    3,
    4,
    4,
    8,
    7,
    3,
    7,
    3,
    7,
    8,
    6,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    3,
    3,
    7,
    8,
    7,
    7,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    5,
    7,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    7,
    8,
    8,
    8,
    8,
    7,
    8,
    5,
    7,
    5,
    7,
    8,
    5,
    7,
    7,
    7,
    7,
    7,
    6,
    7,
    7,
    3,
    6,
    7,
    3,
    8,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    8,
    7,
    7,
    7,
    5,
    3,
    5,
    7,
    8,
    8,
    8,
    8,
    8,
    6,
    7,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    7,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    7,
    8,
    8,
    8,
    7,
    7,
    7,
    7,
    8,
    7,
    8,
    7,
    7,
    7,
    7,
    7,
    8,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    8,
    7,
    8,
    7,
    8,
    8,
    8,
    8,
    7,
    7,
    8,
    7,
};

static const uint16_t font_h12_offset_table[166] =
{
    0,
    16,
    22,
    34,
    50,
    66,
    82,
    98,
    104,
    112,
    120,
    136,
    150,
    156,
    170,
    176,
    190,
    206,
    218,
    234,
    250,
    266,
    282,
    298,
    314,
    330,
    346,
    352,
    358,
    372,
    388,
    402,
    416,
    432,
    448,
    464,
    480,
    496,
    512,
    528,
    544,
    560,
    570,
    584,
    600,
    616,
    632,
    648,
    664,
    680,
    696,
    712,
    728,
    742,
    758,
    774,
    790,
    806,
    820,
    836,
    846,
    860,
    870,
    884,
    900,
    910,
    924,
    938,
    952,
    966,
    980,
    992,
    1006,
    1020,
    1026,
    1038,
    1052,
    1058,
    1074,
    1088,
    1102,
    1116,
    1130,
    1144,
    1158,
    1172,
    1186,
    1200,
    1216,
    1230,
    1244,
    1258,
    1268,
    1274,
    1284,
    1298,
    1314,
    1330,
    1346,
    1362,
    1378,
    1390,
    1404,
    1420,
    1436,
    1452,
    1468,
    1484,
    1500,
    1516,
    1532,
    1548,
    1564,
    1580,
    1596,
    1612,
    1628,
    1644,
    1660,
    1676,
    1692,
    1706,
    1722,
    1738,
    1754,
    1770,
    1786,
    1802,
    1818,
    1834,
    1850,
    1864,
    1880,
    1896,
    1912,
    1926,
    1940,
    1954,
    1968,
    1984,
    1998,
    2014,
    2028,
    2042,
    2056,
    2070,
    2084,
    2100,
    2114,
    2128,
    2142,
    2156,
    2170,
    2184,
    2198,
    2214,
    2228,
    2244,
    2258,
    2274,
    2290,
    2306,
    2322,
    2336,
    2350,
    2366,
};


/*
    uint8_t height;                     // font chars height
    uint8_t width;                      // actual for monospaced, ignored for variable-width fonts
    uint8_t charCount;                  // Total number of chars in the font
    uint8_t spacing;                    // Additional space between chars
    uint8_t bytesPerChar;               // Actual for monospaced, ignored for variable-length fonts
    uint8_t firstCharCode;              // Used if there is no charTable - specifies first avaliable char code in the font.
    const uint8_t *codeTable;           // Used if not all symbols are prensent in the font. Otherwise must be 0.
    const uint8_t *widthTable;          // Used if font is not monospaced. Otherwise must be 0.
    const uint16_t *offsetTable;        //
    const uint8_t *data;                // Font data - contiguous byte array
    */

const tFont font_h12 =
{
    12,          // font height
    0,                      // font width - not used with variable width
    166,          // total chars count
    0,                      // spacing
    0,                      // bytesPerChar - not used with variable width
    0,                      // firstCharCode - not used with char table
    font_h12_code_table,    // character description table
    font_h12_width_table,	// character width table
    font_h12_offset_table,	//
    font_h12_data           // font data
};

