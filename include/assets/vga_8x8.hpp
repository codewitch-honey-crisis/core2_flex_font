
// Generated by https://honeythecodewitch.com/gfx/converter
// --------------------------------------------------------
// Add #define VGA_8X8_IMPLEMENTATION
// to exactly one CPP file before including this file.
// --------------------------------------------------------

#ifndef VGA_8X8_HPP
#define VGA_8X8_HPP
#include <Arduino.h>
#ifndef ESP32
    #include <avr/pgmspace.h>
#else
    #include <pgmspace.h>
#endif
#include <gfx.hpp>

extern const uint8_t vga_8x8_data[] PROGMEM;
extern gfx::const_buffer_stream vga_8x8_stream;
extern const gfx::font vga_8x8;
#endif

#ifdef VGA_8X8_IMPLEMENTATION

const uint8_t vga_8x8_data[] PROGMEM = {
	0x4d,0x5a,0xf1,0x00,0x01,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0xff,0xff,0x00,0x00,
	0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,
	0x0e,0x1f,0xba,0x0e,0x00,0xb4,0x09,0xcd,0x21,0xb8,0x01,0x4c,0xcd,0x21,0x54,0x68,
	0x69,0x73,0x20,0x70,0x72,0x6f,0x67,0x72,0x61,0x6d,0x20,0x72,0x65,0x71,0x75,0x69,
	0x72,0x65,0x73,0x20,0x4d,0x69,0x63,0x72,0x6f,0x73,0x6f,0x66,0x74,0x20,0x57,0x69,
	0x6e,0x64,0x6f,0x77,0x73,0x2e,0x0d,0x0a,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x4e,0x45,0x05,0x3c,0x9d,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x08,0x83,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x2b,0x00,0x40,0x00,0x40,0x00,0x88,0x00,0x9d,0x00,0x9d,0x00,0x1e,0x01,0x00,0x00,
	0x00,0x00,0x04,0x00,0x00,0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
	0x04,0x00,0x07,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x15,0x00,0x09,0x00,0x50,0x0c,
	0x40,0x00,0x00,0x00,0x00,0x00,0x08,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,
	0xca,0x00,0x30,0x1c,0x01,0x80,0x00,0x00,0x00,0x00,0x10,0x80,0x01,0x00,0x00,0x00,
	0x00,0x00,0xe8,0x00,0x16,0x00,0x30,0x0c,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
	0x07,0x46,0x4f,0x4e,0x54,0x44,0x49,0x52,0x11,0x42,0x6d,0x34,0x33,0x37,0x20,0x41,
	0x43,0x4d,0x20,0x56,0x47,0x41,0x20,0x38,0x78,0x38,0x00,0x00,0x00,0x00,0x27,0x46,
	0x4f,0x4e,0x54,0x52,0x45,0x53,0x20,0x31,0x30,0x30,0x2c,0x39,0x36,0x2c,0x39,0x36,
	0x20,0x3a,0x20,0x42,0x6d,0x34,0x33,0x37,0x20,0x41,0x43,0x4d,0x20,0x56,0x47,0x41,
	0x20,0x38,0x78,0x38,0x20,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x01,0x00,0x01,0x00,0x00,0x02,0x94,0x0c,0x00,0x00,0x46,0x4f,0x4e,0x20,0x63,0x6f,
	0x6e,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x62,0x79,0x20,0x56,0x69,0x6c,0x65,
	0x52,0x2c,0x20,0x32,0x30,0x32,0x30,0x3b,0x20,0x6c,0x69,0x63,0x65,0x6e,0x73,0x65,
	0x3a,0x20,0x43,0x43,0x20,0x42,0x59,0x2d,0x53,0x41,0x20,0x34,0x2e,0x30,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x60,0x00,0x60,0x00,0x07,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x01,0xff,0x08,0x00,0x08,0x00,0x30,0x08,
	0x00,0x08,0x00,0x00,0xff,0x00,0x20,0x00,0x01,0x00,0x00,0x00,0x00,0x82,0x0c,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x6d,0x34,0x33,0x37,0x20,0x41,0x43,0x4d,0x20,
	0x56,0x47,0x41,0x20,0x38,0x78,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x02,0x94,0x0c,0x00,0x00,0x46,0x4f,0x4e,0x20,0x63,0x6f,0x6e,0x76,0x65,0x72,
	0x73,0x69,0x6f,0x6e,0x20,0x62,0x79,0x20,0x56,0x69,0x6c,0x65,0x52,0x2c,0x20,0x32,
	0x30,0x32,0x30,0x3b,0x20,0x6c,0x69,0x63,0x65,0x6e,0x73,0x65,0x3a,0x20,0x43,0x43,
	0x20,0x42,0x59,0x2d,0x53,0x41,0x20,0x34,0x2e,0x30,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x06,0x00,0x60,0x00,0x60,0x00,0x07,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x90,0x01,0xff,0x08,0x00,0x08,0x00,0x30,0x08,0x00,0x08,0x00,0x00,
	0xff,0x00,0x20,0x00,0x01,0x00,0x00,0x00,0x00,0x82,0x0c,0x00,0x00,0x00,0x00,0x00,
	0x00,0x7a,0x04,0x00,0x00,0x00,0x08,0x00,0x7a,0x04,0x08,0x00,0x82,0x04,0x08,0x00,
	0x8a,0x04,0x08,0x00,0x92,0x04,0x08,0x00,0x9a,0x04,0x08,0x00,0xa2,0x04,0x08,0x00,
	0xaa,0x04,0x08,0x00,0xb2,0x04,0x08,0x00,0xba,0x04,0x08,0x00,0xc2,0x04,0x08,0x00,
	0xca,0x04,0x08,0x00,0xd2,0x04,0x08,0x00,0xda,0x04,0x08,0x00,0xe2,0x04,0x08,0x00,
	0xea,0x04,0x08,0x00,0xf2,0x04,0x08,0x00,0xfa,0x04,0x08,0x00,0x02,0x05,0x08,0x00,
	0x0a,0x05,0x08,0x00,0x12,0x05,0x08,0x00,0x1a,0x05,0x08,0x00,0x22,0x05,0x08,0x00,
	0x2a,0x05,0x08,0x00,0x32,0x05,0x08,0x00,0x3a,0x05,0x08,0x00,0x42,0x05,0x08,0x00,
	0x4a,0x05,0x08,0x00,0x52,0x05,0x08,0x00,0x5a,0x05,0x08,0x00,0x62,0x05,0x08,0x00,
	0x6a,0x05,0x08,0x00,0x72,0x05,0x08,0x00,0x7a,0x05,0x08,0x00,0x82,0x05,0x08,0x00,
	0x8a,0x05,0x08,0x00,0x92,0x05,0x08,0x00,0x9a,0x05,0x08,0x00,0xa2,0x05,0x08,0x00,
	0xaa,0x05,0x08,0x00,0xb2,0x05,0x08,0x00,0xba,0x05,0x08,0x00,0xc2,0x05,0x08,0x00,
	0xca,0x05,0x08,0x00,0xd2,0x05,0x08,0x00,0xda,0x05,0x08,0x00,0xe2,0x05,0x08,0x00,
	0xea,0x05,0x08,0x00,0xf2,0x05,0x08,0x00,0xfa,0x05,0x08,0x00,0x02,0x06,0x08,0x00,
	0x0a,0x06,0x08,0x00,0x12,0x06,0x08,0x00,0x1a,0x06,0x08,0x00,0x22,0x06,0x08,0x00,
	0x2a,0x06,0x08,0x00,0x32,0x06,0x08,0x00,0x3a,0x06,0x08,0x00,0x42,0x06,0x08,0x00,
	0x4a,0x06,0x08,0x00,0x52,0x06,0x08,0x00,0x5a,0x06,0x08,0x00,0x62,0x06,0x08,0x00,
	0x6a,0x06,0x08,0x00,0x72,0x06,0x08,0x00,0x7a,0x06,0x08,0x00,0x82,0x06,0x08,0x00,
	0x8a,0x06,0x08,0x00,0x92,0x06,0x08,0x00,0x9a,0x06,0x08,0x00,0xa2,0x06,0x08,0x00,
	0xaa,0x06,0x08,0x00,0xb2,0x06,0x08,0x00,0xba,0x06,0x08,0x00,0xc2,0x06,0x08,0x00,
	0xca,0x06,0x08,0x00,0xd2,0x06,0x08,0x00,0xda,0x06,0x08,0x00,0xe2,0x06,0x08,0x00,
	0xea,0x06,0x08,0x00,0xf2,0x06,0x08,0x00,0xfa,0x06,0x08,0x00,0x02,0x07,0x08,0x00,
	0x0a,0x07,0x08,0x00,0x12,0x07,0x08,0x00,0x1a,0x07,0x08,0x00,0x22,0x07,0x08,0x00,
	0x2a,0x07,0x08,0x00,0x32,0x07,0x08,0x00,0x3a,0x07,0x08,0x00,0x42,0x07,0x08,0x00,
	0x4a,0x07,0x08,0x00,0x52,0x07,0x08,0x00,0x5a,0x07,0x08,0x00,0x62,0x07,0x08,0x00,
	0x6a,0x07,0x08,0x00,0x72,0x07,0x08,0x00,0x7a,0x07,0x08,0x00,0x82,0x07,0x08,0x00,
	0x8a,0x07,0x08,0x00,0x92,0x07,0x08,0x00,0x9a,0x07,0x08,0x00,0xa2,0x07,0x08,0x00,
	0xaa,0x07,0x08,0x00,0xb2,0x07,0x08,0x00,0xba,0x07,0x08,0x00,0xc2,0x07,0x08,0x00,
	0xca,0x07,0x08,0x00,0xd2,0x07,0x08,0x00,0xda,0x07,0x08,0x00,0xe2,0x07,0x08,0x00,
	0xea,0x07,0x08,0x00,0xf2,0x07,0x08,0x00,0xfa,0x07,0x08,0x00,0x02,0x08,0x08,0x00,
	0x0a,0x08,0x08,0x00,0x12,0x08,0x08,0x00,0x1a,0x08,0x08,0x00,0x22,0x08,0x08,0x00,
	0x2a,0x08,0x08,0x00,0x32,0x08,0x08,0x00,0x3a,0x08,0x08,0x00,0x42,0x08,0x08,0x00,
	0x4a,0x08,0x08,0x00,0x52,0x08,0x08,0x00,0x5a,0x08,0x08,0x00,0x62,0x08,0x08,0x00,
	0x6a,0x08,0x08,0x00,0x72,0x08,0x08,0x00,0x7a,0x08,0x08,0x00,0x82,0x08,0x08,0x00,
	0x8a,0x08,0x08,0x00,0x92,0x08,0x08,0x00,0x9a,0x08,0x08,0x00,0xa2,0x08,0x08,0x00,
	0xaa,0x08,0x08,0x00,0xb2,0x08,0x08,0x00,0xba,0x08,0x08,0x00,0xc2,0x08,0x08,0x00,
	0xca,0x08,0x08,0x00,0xd2,0x08,0x08,0x00,0xda,0x08,0x08,0x00,0xe2,0x08,0x08,0x00,
	0xea,0x08,0x08,0x00,0xf2,0x08,0x08,0x00,0xfa,0x08,0x08,0x00,0x02,0x09,0x08,0x00,
	0x0a,0x09,0x08,0x00,0x12,0x09,0x08,0x00,0x1a,0x09,0x08,0x00,0x22,0x09,0x08,0x00,
	0x2a,0x09,0x08,0x00,0x32,0x09,0x08,0x00,0x3a,0x09,0x08,0x00,0x42,0x09,0x08,0x00,
	0x4a,0x09,0x08,0x00,0x52,0x09,0x08,0x00,0x5a,0x09,0x08,0x00,0x62,0x09,0x08,0x00,
	0x6a,0x09,0x08,0x00,0x72,0x09,0x08,0x00,0x7a,0x09,0x08,0x00,0x82,0x09,0x08,0x00,
	0x8a,0x09,0x08,0x00,0x92,0x09,0x08,0x00,0x9a,0x09,0x08,0x00,0xa2,0x09,0x08,0x00,
	0xaa,0x09,0x08,0x00,0xb2,0x09,0x08,0x00,0xba,0x09,0x08,0x00,0xc2,0x09,0x08,0x00,
	0xca,0x09,0x08,0x00,0xd2,0x09,0x08,0x00,0xda,0x09,0x08,0x00,0xe2,0x09,0x08,0x00,
	0xea,0x09,0x08,0x00,0xf2,0x09,0x08,0x00,0xfa,0x09,0x08,0x00,0x02,0x0a,0x08,0x00,
	0x0a,0x0a,0x08,0x00,0x12,0x0a,0x08,0x00,0x1a,0x0a,0x08,0x00,0x22,0x0a,0x08,0x00,
	0x2a,0x0a,0x08,0x00,0x32,0x0a,0x08,0x00,0x3a,0x0a,0x08,0x00,0x42,0x0a,0x08,0x00,
	0x4a,0x0a,0x08,0x00,0x52,0x0a,0x08,0x00,0x5a,0x0a,0x08,0x00,0x62,0x0a,0x08,0x00,
	0x6a,0x0a,0x08,0x00,0x72,0x0a,0x08,0x00,0x7a,0x0a,0x08,0x00,0x82,0x0a,0x08,0x00,
	0x8a,0x0a,0x08,0x00,0x92,0x0a,0x08,0x00,0x9a,0x0a,0x08,0x00,0xa2,0x0a,0x08,0x00,
	0xaa,0x0a,0x08,0x00,0xb2,0x0a,0x08,0x00,0xba,0x0a,0x08,0x00,0xc2,0x0a,0x08,0x00,
	0xca,0x0a,0x08,0x00,0xd2,0x0a,0x08,0x00,0xda,0x0a,0x08,0x00,0xe2,0x0a,0x08,0x00,
	0xea,0x0a,0x08,0x00,0xf2,0x0a,0x08,0x00,0xfa,0x0a,0x08,0x00,0x02,0x0b,0x08,0x00,
	0x0a,0x0b,0x08,0x00,0x12,0x0b,0x08,0x00,0x1a,0x0b,0x08,0x00,0x22,0x0b,0x08,0x00,
	0x2a,0x0b,0x08,0x00,0x32,0x0b,0x08,0x00,0x3a,0x0b,0x08,0x00,0x42,0x0b,0x08,0x00,
	0x4a,0x0b,0x08,0x00,0x52,0x0b,0x08,0x00,0x5a,0x0b,0x08,0x00,0x62,0x0b,0x08,0x00,
	0x6a,0x0b,0x08,0x00,0x72,0x0b,0x08,0x00,0x7a,0x0b,0x08,0x00,0x82,0x0b,0x08,0x00,
	0x8a,0x0b,0x08,0x00,0x92,0x0b,0x08,0x00,0x9a,0x0b,0x08,0x00,0xa2,0x0b,0x08,0x00,
	0xaa,0x0b,0x08,0x00,0xb2,0x0b,0x08,0x00,0xba,0x0b,0x08,0x00,0xc2,0x0b,0x08,0x00,
	0xca,0x0b,0x08,0x00,0xd2,0x0b,0x08,0x00,0xda,0x0b,0x08,0x00,0xe2,0x0b,0x08,0x00,
	0xea,0x0b,0x08,0x00,0xf2,0x0b,0x08,0x00,0xfa,0x0b,0x08,0x00,0x02,0x0c,0x08,0x00,
	0x0a,0x0c,0x08,0x00,0x12,0x0c,0x08,0x00,0x1a,0x0c,0x08,0x00,0x22,0x0c,0x08,0x00,
	0x2a,0x0c,0x08,0x00,0x32,0x0c,0x08,0x00,0x3a,0x0c,0x08,0x00,0x42,0x0c,0x08,0x00,
	0x4a,0x0c,0x08,0x00,0x52,0x0c,0x08,0x00,0x5a,0x0c,0x08,0x00,0x62,0x0c,0x08,0x00,
	0x6a,0x0c,0x08,0x00,0x72,0x0c,0x08,0x00,0x7a,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7e,0x81,0xa5,0x81,0xbd,0x99,0x81,0x7e,0x7e,0xdb,0xff,0xff,0xc3,0xe7,
	0x7e,0x00,0x36,0x7f,0x7f,0x7f,0x3e,0x1c,0x08,0x00,0x08,0x1c,0x3e,0x7f,0x3e,0x1c,
	0x08,0x00,0x18,0x3c,0x18,0x66,0xff,0x66,0x18,0x3c,0x08,0x1c,0x3e,0x7f,0x7f,0x3e,
	0x08,0x1c,0x00,0x00,0x18,0x3c,0x3c,0x18,0x00,0x00,0xff,0xff,0xe7,0xc3,0xc3,0xe7,
	0xff,0xff,0x00,0x3c,0x66,0x42,0x42,0x66,0x3c,0x00,0xff,0xc3,0x99,0xbd,0xbd,0x99,
	0xc3,0xff,0x3f,0x0d,0x1c,0x3e,0x63,0x63,0x3e,0x00,0x3e,0x63,0x63,0x3e,0x1c,0x7f,
	0x1c,0x00,0x0e,0x0f,0x0d,0x0d,0x1c,0x7f,0x1c,0x00,0x0f,0x3b,0x37,0x3b,0x33,0x37,
	0x77,0x70,0x18,0xdb,0x3c,0xe7,0x3c,0xdb,0x18,0x00,0x60,0x78,0x7e,0x7f,0x7e,0x78,
	0x60,0x00,0x03,0x0f,0x3f,0x7f,0x3f,0x0f,0x03,0x00,0x18,0x3c,0x7e,0x18,0x18,0x7e,
	0x3c,0x18,0x66,0x66,0x66,0x66,0x66,0x00,0x66,0x00,0x3f,0x6d,0x6d,0x3d,0x0d,0x0d,
	0x0d,0x00,0x3f,0x70,0x3e,0x63,0x63,0x3e,0x07,0x7e,0x00,0x00,0x00,0x00,0xff,0xff,
	0xff,0x00,0x3c,0x7e,0x18,0x18,0x7e,0x3c,0x18,0x7e,0x18,0x3c,0x7e,0x18,0x18,0x18,
	0x18,0x00,0x18,0x18,0x18,0x18,0x7e,0x3c,0x18,0x00,0x18,0x0c,0x06,0x7f,0x06,0x0c,
	0x18,0x00,0x0c,0x18,0x30,0x7f,0x30,0x18,0x0c,0x00,0x00,0x00,0x00,0x60,0x60,0x7f,
	0x00,0x00,0x00,0x24,0x66,0xff,0x66,0x24,0x00,0x00,0x08,0x1c,0x1c,0x3e,0x3e,0x7f,
	0x7f,0x00,0x7f,0x7f,0x3e,0x3e,0x1c,0x1c,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00,0x33,0x66,0xcc,0x00,0x00,0x00,
	0x00,0x00,0x36,0x36,0x7f,0x36,0x36,0x7f,0x36,0x36,0x18,0x7e,0x58,0x38,0x1c,0x1a,
	0x7e,0x18,0xe3,0xa6,0xec,0x18,0x37,0x65,0xc7,0x00,0x3c,0x66,0x3c,0x38,0x6d,0x66,
	0x3d,0x00,0x06,0x0c,0x18,0x00,0x00,0x00,0x00,0x00,0x1c,0x30,0x60,0x60,0x60,0x30,
	0x1c,0x00,0x38,0x0c,0x06,0x06,0x06,0x0c,0x38,0x00,0x63,0x36,0x1c,0x7f,0x1c,0x36,
	0x63,0x00,0x18,0x18,0x18,0x7e,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
	0x18,0x30,0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
	0x18,0x00,0x02,0x06,0x0c,0x18,0x30,0x60,0x40,0x00,0x3e,0x63,0x63,0x6b,0x63,0x63,
	0x3e,0x00,0x1c,0x3c,0x0c,0x0c,0x0c,0x0c,0x0c,0x00,0x3e,0x63,0x03,0x0e,0x38,0x60,
	0x7f,0x00,0x7c,0x06,0x06,0x3c,0x06,0x06,0x7c,0x00,0x0e,0x1e,0x36,0x66,0x7f,0x06,
	0x06,0x00,0x7e,0x60,0x7c,0x06,0x06,0x06,0x7c,0x00,0x1e,0x30,0x60,0x7e,0x63,0x63,
	0x3e,0x00,0x7e,0x66,0x0c,0x18,0x30,0x30,0x30,0x00,0x3e,0x63,0x36,0x1c,0x36,0x63,
	0x3e,0x00,0x3e,0x63,0x63,0x3f,0x03,0x06,0x7c,0x00,0x00,0x00,0x18,0x18,0x00,0x18,
	0x18,0x00,0x00,0x00,0x18,0x18,0x00,0x18,0x18,0x30,0x0c,0x18,0x30,0x60,0x30,0x18,
	0x0c,0x00,0x00,0x00,0x7e,0x00,0x7e,0x00,0x00,0x00,0x30,0x18,0x0c,0x06,0x0c,0x18,
	0x30,0x00,0x3e,0x63,0x06,0x0c,0x0c,0x00,0x0c,0x00,0x3e,0x63,0x6f,0x69,0x6f,0x60,
	0x3f,0x00,0x3c,0x66,0x66,0x7e,0x66,0x66,0x66,0x00,0x7e,0x63,0x63,0x7e,0x63,0x63,
	0x7e,0x00,0x1e,0x33,0x60,0x60,0x60,0x33,0x1e,0x00,0x7c,0x66,0x63,0x63,0x63,0x66,
	0x7c,0x00,0x7e,0x60,0x60,0x7c,0x60,0x60,0x7e,0x00,0x7e,0x60,0x60,0x7c,0x60,0x60,
	0x60,0x00,0x1e,0x33,0x63,0x60,0x67,0x33,0x1e,0x00,0x63,0x63,0x63,0x7f,0x63,0x63,
	0x63,0x00,0x3c,0x18,0x18,0x18,0x18,0x18,0x3c,0x00,0x06,0x06,0x06,0x06,0x66,0x66,
	0x3c,0x00,0x63,0x66,0x6c,0x78,0x6c,0x66,0x63,0x00,0x30,0x30,0x30,0x30,0x30,0x30,
	0x3f,0x00,0x63,0x77,0x7f,0x6b,0x63,0x63,0x63,0x00,0x63,0x73,0x7b,0x6f,0x67,0x63,
	0x63,0x00,0x3e,0x63,0x63,0x63,0x63,0x63,0x3e,0x00,0x7e,0x63,0x63,0x7e,0x60,0x60,
	0x60,0x00,0x3e,0x63,0x63,0x63,0x7b,0x6e,0x3c,0x07,0x7e,0x63,0x63,0x7e,0x6c,0x66,
	0x63,0x00,0x3e,0x63,0x30,0x1c,0x06,0x63,0x3e,0x00,0x7e,0x18,0x18,0x18,0x18,0x18,
	0x18,0x00,0x63,0x63,0x63,0x63,0x63,0x63,0x3e,0x00,0x63,0x63,0x63,0x63,0x36,0x1c,
	0x08,0x00,0x63,0x63,0x63,0x6b,0x6b,0x7f,0x36,0x00,0x63,0x63,0x36,0x1c,0x36,0x63,
	0x63,0x00,0x63,0x63,0x63,0x3e,0x0c,0x0c,0x0c,0x00,0x7f,0x06,0x0c,0x18,0x30,0x60,
	0x7f,0x00,0x3e,0x30,0x30,0x30,0x30,0x30,0x3e,0x00,0x40,0x60,0x30,0x18,0x0c,0x06,
	0x02,0x00,0x3e,0x06,0x06,0x06,0x06,0x06,0x3e,0x00,0x1c,0x36,0x63,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x30,0x18,0x0c,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x3c,0x06,0x3e,0x66,0x3f,0x00,0x60,0x60,0x7c,0x66,0x66,0x66,
	0x7c,0x00,0x00,0x00,0x3e,0x63,0x60,0x60,0x3f,0x00,0x06,0x06,0x3e,0x66,0x66,0x66,
	0x3e,0x00,0x00,0x00,0x3c,0x66,0x7c,0x60,0x3e,0x00,0x1e,0x30,0x30,0x7c,0x30,0x30,
	0x30,0x00,0x00,0x00,0x3f,0x63,0x63,0x3f,0x03,0x7e,0x60,0x60,0x6c,0x76,0x66,0x66,
	0x66,0x00,0x18,0x00,0x38,0x18,0x18,0x18,0x18,0x00,0x06,0x00,0x06,0x06,0x06,0x06,
	0x66,0x3c,0x60,0x60,0x66,0x6c,0x78,0x6c,0x66,0x00,0x18,0x18,0x18,0x18,0x18,0x18,
	0x0c,0x00,0x00,0x00,0x76,0x7f,0x6b,0x6b,0x63,0x00,0x00,0x00,0x6c,0x76,0x66,0x66,
	0x66,0x00,0x00,0x00,0x3e,0x63,0x63,0x63,0x3e,0x00,0x00,0x00,0x7c,0x66,0x66,0x7c,
	0x60,0x60,0x00,0x00,0x3e,0x66,0x66,0x3e,0x06,0x06,0x00,0x00,0x36,0x3b,0x30,0x30,
	0x30,0x00,0x00,0x00,0x3e,0x70,0x3c,0x0e,0x7c,0x00,0x18,0x18,0x7e,0x18,0x18,0x18,
	0x0e,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x3b,0x00,0x00,0x00,0x66,0x66,0x66,0x3c,
	0x18,0x00,0x00,0x00,0x63,0x63,0x6b,0x7f,0x36,0x00,0x00,0x00,0x63,0x36,0x1c,0x36,
	0x63,0x00,0x00,0x00,0x66,0x66,0x66,0x3e,0x06,0x7c,0x00,0x00,0x7e,0x0c,0x18,0x30,
	0x7e,0x00,0x0e,0x18,0x18,0x78,0x18,0x18,0x0e,0x00,0x18,0x18,0x18,0x00,0x18,0x18,
	0x18,0x00,0x70,0x18,0x18,0x0e,0x18,0x18,0x70,0x00,0x3b,0x6e,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x3c,0x66,0xc3,0xc3,0xff,0x00,0x00,0x3e,0x63,0x60,0x60,0x63,0x3e,
	0x18,0x30,0x66,0x00,0x66,0x66,0x66,0x66,0x3b,0x00,0x0c,0x10,0x3c,0x66,0x7c,0x60,
	0x3e,0x00,0x3e,0x41,0x1c,0x06,0x3e,0x66,0x3f,0x00,0x36,0x00,0x3c,0x06,0x3e,0x66,
	0x3f,0x00,0x18,0x08,0x3c,0x06,0x3e,0x66,0x3f,0x00,0x3c,0x66,0x3c,0x06,0x3e,0x66,
	0x3f,0x00,0x00,0x00,0x3e,0x60,0x60,0x3e,0x18,0x30,0x7e,0xc3,0x3c,0x66,0x7c,0x60,
	0x3e,0x00,0x36,0x00,0x3c,0x66,0x7c,0x60,0x3e,0x00,0x18,0x08,0x3c,0x66,0x7c,0x60,
	0x3e,0x00,0x6c,0x00,0x38,0x18,0x18,0x18,0x18,0x00,0x3e,0x41,0x1c,0x0c,0x0c,0x0c,
	0x0c,0x00,0x0c,0x04,0x38,0x18,0x18,0x18,0x18,0x00,0x66,0x18,0x3c,0x66,0x7e,0x66,
	0x66,0x00,0x18,0x24,0x3c,0x66,0x7e,0x66,0x66,0x00,0x0c,0x7e,0x60,0x7c,0x60,0x60,
	0x7e,0x00,0x00,0x00,0x7e,0x19,0x3f,0x4c,0x77,0x00,0x1f,0x36,0x66,0x7f,0x66,0x66,
	0x67,0x00,0x7e,0x81,0x3c,0x66,0x66,0x66,0x3c,0x00,0x66,0x00,0x3c,0x66,0x66,0x66,
	0x3c,0x00,0x18,0x08,0x3c,0x66,0x66,0x66,0x3c,0x00,0x7e,0x81,0x66,0x66,0x66,0x66,
	0x3b,0x00,0x18,0x08,0x66,0x66,0x66,0x66,0x3b,0x00,0x36,0x00,0x63,0x63,0x63,0x3f,
	0x03,0x7e,0x63,0x00,0x3e,0x63,0x63,0x63,0x63,0x3e,0x63,0x00,0x63,0x63,0x63,0x63,
	0x63,0x3e,0x08,0x08,0x3e,0x60,0x60,0x3e,0x08,0x08,0x0f,0x19,0x18,0x7e,0x18,0x18,
	0x7f,0x00,0x66,0x66,0x3c,0x7e,0x18,0x7e,0x18,0x18,0x7c,0x66,0x66,0x7c,0x64,0x6f,
	0x64,0x67,0x07,0x0d,0x0c,0x3f,0x0c,0x0c,0x4c,0x38,0x0c,0x10,0x3c,0x06,0x3e,0x66,
	0x3f,0x00,0x18,0x20,0x1c,0x0c,0x0c,0x0c,0x0c,0x00,0x0c,0x10,0x3e,0x63,0x63,0x63,
	0x3e,0x00,0x0c,0x10,0x66,0x66,0x66,0x66,0x3b,0x00,0x71,0x8e,0x6c,0x76,0x66,0x66,
	0x66,0x00,0x73,0x8c,0x63,0x73,0x6b,0x67,0x63,0x00,0x3e,0x66,0x3f,0x00,0x7f,0x00,
	0x00,0x00,0x3c,0x66,0x3c,0x00,0x7e,0x00,0x00,0x00,0x18,0x00,0x18,0x18,0x30,0x63,
	0x63,0x3e,0x00,0x00,0x7f,0x60,0x60,0x60,0x60,0x00,0x00,0x00,0x7f,0x03,0x03,0x03,
	0x03,0x00,0x63,0x66,0x6c,0x1f,0x31,0x67,0x4c,0x4f,0x63,0x66,0x6c,0x1b,0x35,0x69,
	0x4f,0x41,0x18,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x33,0x66,0xcc,0x66,0x33,
	0x00,0x00,0x00,0xcc,0x66,0x33,0x66,0xcc,0x00,0x00,0x11,0x44,0x11,0x44,0x11,0x44,
	0x11,0x44,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0xdd,0x77,0xdd,0x77,0xdd,0x77,
	0xdd,0x77,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xf8,0x18,
	0x18,0x18,0x18,0x18,0xf8,0x18,0xf8,0x18,0x18,0x18,0x36,0x36,0x36,0x36,0xf6,0x36,
	0x36,0x36,0x00,0x00,0x00,0x00,0xfe,0x36,0x36,0x36,0x00,0x00,0xf8,0x18,0xf8,0x18,
	0x18,0x18,0x36,0x36,0xf6,0x06,0xf6,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,
	0x36,0x36,0x00,0x00,0xfe,0x06,0xf6,0x36,0x36,0x36,0x36,0x36,0xf6,0x06,0xfe,0x00,
	0x00,0x00,0x36,0x36,0x36,0x36,0xfe,0x00,0x00,0x00,0x18,0x18,0xf8,0x18,0xf8,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1f,0x00,
	0x00,0x00,0x18,0x18,0x18,0x18,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x18,
	0x18,0x18,0x18,0x18,0x18,0x18,0x1f,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0xff,0x00,
	0x00,0x00,0x18,0x18,0x18,0x18,0xff,0x18,0x18,0x18,0x18,0x18,0x1f,0x18,0x1f,0x18,
	0x18,0x18,0x36,0x36,0x36,0x36,0x37,0x36,0x36,0x36,0x36,0x36,0x37,0x30,0x3f,0x00,
	0x00,0x00,0x00,0x00,0x3f,0x30,0x37,0x36,0x36,0x36,0x36,0x36,0xf7,0x00,0xff,0x00,
	0x00,0x00,0x00,0x00,0xff,0x00,0xf7,0x36,0x36,0x36,0x36,0x36,0x37,0x30,0x37,0x36,
	0x36,0x36,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0x00,0x36,0x36,0xf7,0x00,0xf7,0x36,
	0x36,0x36,0x18,0x18,0xff,0x00,0xff,0x00,0x00,0x00,0x36,0x36,0x36,0x36,0xff,0x00,
	0x00,0x00,0x00,0x00,0xff,0x00,0xff,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0xff,0x36,
	0x36,0x36,0x36,0x36,0x36,0x36,0x3f,0x00,0x00,0x00,0x18,0x18,0x1f,0x18,0x1f,0x00,
	0x00,0x00,0x00,0x00,0x1f,0x18,0x1f,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x3f,0x36,
	0x36,0x36,0x36,0x36,0x36,0x36,0xff,0x36,0x36,0x36,0x18,0x18,0xff,0x18,0xff,0x18,
	0x18,0x18,0x18,0x18,0x18,0x18,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x18,
	0x18,0x18,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xff,
	0xff,0xff,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,
	0x0f,0x0f,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x7b,0xce,0xcc,0xce,
	0x7b,0x00,0x3c,0x66,0x66,0x6e,0x63,0x63,0x6e,0x00,0x3f,0x33,0x30,0x30,0x30,0x30,
	0x30,0x00,0x00,0x00,0x7f,0xb6,0x36,0x36,0x36,0x00,0x7f,0x71,0x38,0x1c,0x38,0x71,
	0x7f,0x00,0x00,0x00,0x3f,0x66,0x66,0x66,0x3c,0x00,0x00,0x00,0x66,0x66,0x66,0x7b,
	0x60,0x60,0x00,0x00,0x3f,0x4c,0x0c,0x0c,0x0c,0x00,0x18,0x7e,0xdb,0xdb,0xdb,0x7e,
	0x18,0x00,0x3c,0x66,0xc3,0xbd,0xc3,0x66,0x3c,0x00,0x3c,0x66,0xc3,0xc3,0xc3,0x66,
	0xe7,0x00,0x3e,0x70,0x3c,0x66,0x66,0x66,0x3c,0x00,0x00,0x00,0x7e,0xdb,0xdb,0x7e,
	0x00,0x00,0x18,0x18,0x7e,0xdb,0xdb,0x7e,0x18,0x18,0x00,0x00,0x3e,0x60,0x3c,0x60,
	0x3e,0x00,0x3e,0x63,0x63,0x63,0x63,0x63,0x63,0x00,0x7f,0x00,0x00,0x7f,0x00,0x00,
	0x7f,0x00,0x18,0x18,0x7e,0x18,0x18,0x00,0x7e,0x00,0x38,0x1c,0x0e,0x1c,0x38,0x00,
	0x7e,0x00,0x1c,0x38,0x70,0x38,0x1c,0x00,0x7e,0x00,0x0e,0x1b,0x1b,0x18,0x18,0x18,
	0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xd8,0xd8,0x70,0x00,0x18,0x00,0x7e,0x00,0x18,
	0x00,0x00,0x00,0x00,0x3b,0x6e,0x00,0x3b,0x6e,0x00,0x00,0x3c,0x66,0x3c,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x3c,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,
	0x00,0x00,0x0f,0x0c,0x0c,0x8c,0xcc,0x6c,0x3c,0x18,0x6c,0x36,0x36,0x36,0x00,0x00,
	0x00,0x00,0x7c,0x0e,0x3c,0x60,0x7e,0x00,0x00,0x00,0x00,0x00,0x7c,0x7c,0x7c,0x7c,
	0x7c,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x42,0x6d,0x34,0x33,0x37,0x20,0x41,0x43,0x4d,0x20,0x56,0x47,0x41,0x20,
	0x38,0x78,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x58,0x01,0x34,0x00,0x56,0x53,0x5f,0x56,0x45,0x52,0x53,0x49,0x4f,0x4e,0x5f,0x49,
	0x4e,0x46,0x4f,0x00,0xbd,0x04,0xef,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xeb,0x00,0x00,0x00,0x53,0x74,0x72,0x69,
	0x6e,0x67,0x46,0x69,0x6c,0x65,0x49,0x6e,0x66,0x6f,0x00,0x00,0xd3,0x00,0x00,0x00,
	0x30,0x34,0x30,0x39,0x30,0x34,0x45,0x34,0x00,0x00,0x00,0x00,0x16,0x00,0x06,0x00,
	0x43,0x6f,0x6d,0x70,0x61,0x6e,0x79,0x4e,0x61,0x6d,0x65,0x00,0x56,0x69,0x6c,0x65,
	0x52,0x00,0x00,0x00,0x15,0x00,0x01,0x00,0x46,0x69,0x6c,0x65,0x44,0x65,0x73,0x63,
	0x72,0x69,0x70,0x74,0x69,0x6f,0x6e,0x00,0x00,0x00,0x00,0x00,0x1f,0x00,0x0f,0x00,
	0x46,0x69,0x6c,0x65,0x56,0x65,0x72,0x73,0x69,0x6f,0x6e,0x00,0x32,0x2e,0x32,0x20,
	0x28,0x4e,0x6f,0x76,0x20,0x32,0x30,0x32,0x30,0x29,0x00,0x00,0x15,0x00,0x01,0x00,
	0x49,0x6e,0x74,0x65,0x72,0x6e,0x61,0x6c,0x4e,0x61,0x6d,0x65,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x15,0x00,0x01,0x00,0x4c,0x65,0x67,0x61,0x6c,0x43,0x6f,0x70,
	0x79,0x72,0x69,0x67,0x68,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x19,0x00,0x01,0x00,
	0x4f,0x72,0x69,0x67,0x69,0x6e,0x61,0x6c,0x46,0x69,0x6c,0x65,0x6e,0x61,0x6d,0x65,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x01,0x00,0x50,0x72,0x6f,0x64,
	0x75,0x63,0x74,0x4e,0x61,0x6d,0x65,0x00,0x00,0x00,0x00,0x00,0x15,0x00,0x01,0x00,
	0x50,0x72,0x6f,0x64,0x75,0x63,0x74,0x56,0x65,0x72,0x73,0x69,0x6f,0x6e,0x00,0x00,
	0x00,0x00,0x00,0x00,0x24,0x00,0x00,0x00,0x56,0x61,0x72,0x46,0x69,0x6c,0x65,0x49,
	0x6e,0x66,0x6f,0x00,0x14,0x00,0x04,0x00,0x54,0x72,0x61,0x6e,0x73,0x6c,0x61,0x74,
	0x69,0x6f,0x6e,0x00,0x09,0x04,0xe4,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

gfx::const_buffer_stream vga_8x8_stream(vga_8x8_data, sizeof(vga_8x8_data));
const gfx::font vga_8x8(&vga_8x8_stream);
#endif