#include <gb.h>

unsigned char modfliptitle[] = {
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
};
unsigned char modflip2title[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};


UWORD walkpal1[] = {
	RGB( 0,  0,  0), RGB( 8,  8,  7), RGB(31, 31, 31), RGB(16, 15, 14), 
	RGB(12, 12, 11), RGB( 7,  8,  8), RGB(19, 20, 20), RGB( 1,  1,  1), 
	RGB( 4,  3,  2), RGB(15, 17, 15), RGB(27, 28, 28), RGB( 7,  7,  7), 
	RGB( 4,  1,  1), RGB(15, 16, 13), RGB(26, 23, 24), RGB(10,  8,  7), 
	RGB( 1,  1,  1), RGB(10, 16,  7), RGB(29, 28, 28), RGB(20, 15, 15), 
	RGB( 8,  3,  3), RGB(10,  8,  7), RGB( 3, 25, 22), RGB(16, 11, 11), 
	RGB( 4,  3,  3), RGB( 9,  8,  7), RGB(24, 20, 15), RGB(16, 11, 11), 
	RGB(16, 16, 12), RGB( 1,  1,  1), RGB(24, 15, 18), RGB( 7,  8,  6), 
};

UWORD walkpal2[] = {
	RGB( 0,  0,  0), RGB(22, 20, 18), RGB( 8,  8,  8), RGB(13, 11, 12), 
	RGB( 9,  7,  7), RGB( 2,  2,  2), RGB(16, 17, 12), RGB( 6,  8,  4), 
	RGB( 2, 10, 19), RGB(22, 20, 16), RGB(24,  8,  8), RGB(13, 11, 12), 
	RGB(17, 15, 15), RGB(31, 31, 31), RGB( 8,  7,  7), RGB( 1,  1,  1), 
	RGB( 3,  4,  3), RGB(22, 20, 18), RGB( 8,  8,  8), RGB(13, 11, 12), 
	RGB(28, 29,  0), RGB(18, 16, 16), RGB( 8,  5,  8), RGB(14, 10, 12), 
	RGB( 2, 14, 19), RGB(22, 20, 18), RGB( 8, 12,  8), RGB(15, 11, 13), 
	RGB( 2,  1,  1), RGB(23, 23, 24), RGB( 8,  8,  8), RGB(12, 11, 12), 
};

UWORD walkpal3[] = {
	RGB( 0,  0,  0), RGB(15, 16, 16), RGB( 8,  8,  7), RGB(12, 16, 12), 
	RGB(16, 15, 16), RGB( 1,  1,  1), RGB(26, 24, 23), RGB(31, 31, 31), 
	RGB( 9, 25,  7), RGB(12, 24, 16), RGB( 9,  8,  7), RGB(12, 16, 12), 
	RGB( 9, 29, 15), RGB(15, 16, 16), RGB( 8,  9,  7), RGB(12, 16, 13), 
	RGB(23, 21, 15), RGB( 1,  1,  1), RGB( 9,  8,  7), RGB(15, 16, 12), 
	RGB(24, 24, 23), RGB(15, 20, 17), RGB( 8,  8,  5), RGB(11, 16, 12), 
	RGB(16, 11, 12), RGB( 4,  3,  4), RGB( 9,  8,  7), RGB(15, 16, 15), 
	RGB(13, 25, 15), RGB(10, 16, 16), RGB( 8, 10,  7), RGB(12, 16, 12), 
};

UWORD walkpal4[] = {
	RGB( 0,  0,  0), RGB( 7,  8,  6), RGB(20, 15, 16), RGB(12, 10, 10), 
	RGB( 1,  0,  0), RGB(15, 15, 16), RGB(23, 24, 22), RGB(31, 31, 31), 
	RGB(28, 11, 15), RGB( 7,  9,  6), RGB(20, 15, 16), RGB( 8, 26, 10), 
	RGB(15, 15, 14), RGB( 7,  8,  6), RGB( 1,  1,  1), RGB(25, 24, 24), 
	RGB(29, 11, 15), RGB( 6,  8,  6), RGB(20, 15, 16), RGB( 4, 10, 10), 
	RGB(15, 13, 14), RGB( 6,  4,  5), RGB(20, 20, 19), RGB(12,  9, 10), 
	RGB(28, 11, 15), RGB( 7,  8,  6), RGB(20, 31, 18), RGB(12, 10, 14), 
	RGB(30, 11, 15), RGB( 7,  8,  6), RGB(21, 15, 18), RGB(12, 18, 26), 
};

UWORD walkpal5[] = {
	RGB( 0,  0,  0), RGB( 7,  7,  8), RGB( 4,  3,  3), RGB(16, 14, 13), 
	RGB( 1,  1,  0), RGB(15, 15, 16), RGB(25, 23, 22), RGB(31, 31, 31), 
	RGB(24, 25,  3), RGB( 7,  7,  8), RGB( 4,  3,  3), RGB(16,  7, 13), 
	RGB(24, 22, 22), RGB(10,  7,  8), RGB( 4,  2,  2), RGB(17, 14, 14), 
	RGB(11, 12,  7), RGB( 7,  7,  8), RGB( 2,  1,  0), RGB(20, 15, 15), 
	RGB(11, 12,  9), RGB( 7,  7,  8), RGB( 4,  4,  2), RGB(16, 14, 13), 
	RGB(27, 26, 23), RGB( 7,  7,  8), RGB( 4,  2,  1), RGB(16, 15, 12), 
	RGB(13, 14, 12), RGB(19, 20, 18), RGB( 5,  8,  3), RGB(26, 25, 25), 
};

UWORD walkpal6[] = {
	RGB( 0,  0,  0), RGB(31, 31, 31), RGB( 8,  8,  7), RGB(16, 15, 14), 
	RGB(30, 24,  5), RGB(31, 30, 31), RGB( 8,  8,  5), RGB(16, 15, 15), 
	RGB(30, 24,  5), RGB(31, 31, 29), RGB( 8,  8,  7), RGB(16,  7,  6), 
	RGB(12,  9,  7), RGB(31, 31, 31), RGB( 8,  8,  6), RGB(16, 12, 13), 
	RGB( 8,  8,  7), RGB(24, 23, 22), RGB( 2,  2,  2), RGB(16, 14, 13), 
	RGB(26, 24, 22), RGB(20, 15, 14), RGB( 2,  1,  1), RGB(16, 10,  7), 
	RGB(14, 24,  5), RGB(31, 31, 31), RGB( 8,  8, 23), RGB(16, 15, 15), 
	RGB(22, 24,  5), RGB(31, 31, 31), RGB(10,  8,  3), RGB(16, 15, 14), 
};

UWORD walkpal7[] = {
	RGB( 0,  0,  0), RGB(23, 24, 22), RGB(16, 16, 11), RGB(31, 31, 31), 
	RGB(29, 30, 19), RGB(23, 16, 30), RGB(16, 16, 10), RGB(31, 31, 31), 
	RGB(29, 28, 27), RGB(23, 24, 20), RGB(16, 16, 27), RGB(31, 31, 31), 
	RGB(29, 30, 27), RGB(23, 24, 30), RGB(16, 16, 11), RGB(23, 31, 15), 
	RGB( 0,  0,  0), RGB( 7,  8,  8), RGB( 3,  4,  4), RGB(16, 15, 16), 
	RGB(29, 30, 27), RGB(23, 24, 18), RGB(16, 20, 11), RGB(27, 31, 31), 
	RGB(16, 14, 13), RGB( 4,  2,  1), RGB(23, 23, 22), RGB( 9,  8,  8), 
	RGB(29, 30, 27), RGB(23, 28, 22), RGB(16, 16, 11), RGB(30, 30, 31), 
};

UWORD walkpal8[] = {
	RGB( 0,  0,  0), RGB( 5,  6,  4), RGB(16, 18, 15), RGB(12, 16, 31), 
	RGB( 4,  3,  4), RGB( 0,  0,  0), RGB( 8,  7,  8), RGB(13, 13, 16), 
	RGB( 1,  1,  1), RGB(17, 16, 14), RGB(23, 22, 19), RGB(10,  8,  8), 
	RGB(13,  9, 10), RGB( 9,  5,  7), RGB(18, 16, 15), RGB(15, 16, 13), 
	RGB(12, 11,  8), RGB( 5,  7,  4), RGB(16, 16, 11), RGB( 7,  6, 31), 
	RGB(12,  0,  9), RGB( 5,  6,  4), RGB(16, 18, 15), RGB(12, 16, 30), 
	RGB(15, 16, 16), RGB( 0,  0,  0), RGB(31, 31, 31), RGB( 6,  8,  3), 
	RGB( 2, 23, 29), RGB(15, 16, 16), RGB(28, 28, 26), RGB( 7,  6,  5), 
};

UWORD walkpal9[] = {
	RGB( 0,  0,  0), RGB(31, 31, 31), RGB( 8,  8,  8), RGB(15, 17, 17), 
	RGB(12, 10, 11), RGB(15, 12, 13), RGB( 9,  8,  8), RGB(22, 18, 12), 
	RGB( 8,  7,  5), RGB(31, 23, 29), RGB(10, 11,  8), RGB(15, 17, 16), 
	RGB(12, 16, 10), RGB(19, 19, 17), RGB(28, 23, 23), RGB( 4,  4,  2), 
	RGB( 1,  1,  1), RGB(28, 26, 23), RGB( 9,  9,  9), RGB(15, 16, 16), 
	RGB(12, 11,  7), RGB(27, 28, 28), RGB(16, 15, 16), RGB(15, 24, 20), 
	RGB( 3,  4,  3), RGB(23, 31, 29), RGB( 8,  8,  8), RGB(15,  1, 18), 
	RGB( 8,  7,  6), RGB( 2,  1,  1), RGB(24, 20, 15), RGB(16, 13, 12), 
};

UWORD walkpal10[] = {
	RGB( 0,  0,  0), RGB(31, 31, 31), RGB( 8,  7,  7), RGB( 2,  2,  2), 
	RGB(21, 15,  1), RGB(31, 31, 13), RGB( 8,  7,  7), RGB( 3,  3,  3), 
	RGB(11, 10,  9), RGB(27, 26, 25), RGB(19, 15, 16), RGB( 2,  1,  1), 
	RGB(11, 10,  9), RGB(20, 17, 15), RGB( 8,  6,  5), RGB( 2,  2,  2), 
	RGB(24, 15,  9), RGB(31, 31, 30), RGB( 8,  7,  7), RGB( 2,  2,  2), 
	RGB(11, 10, 11), RGB(29, 29, 28), RGB( 8,  6,  6), RGB( 0,  0,  0), 
	RGB(16, 15, 13), RGB(25, 24, 22), RGB( 7,  7,  6), RGB( 1,  1,  1), 
	RGB(10, 11, 10), RGB(28, 23, 30), RGB( 8,  7,  6), RGB( 2,  2,  1), 
};

UWORD walkpal11[] = {
	RGB( 0,  0,  0), RGB( 7,  8,  6), RGB(14, 13, 12), RGB(24, 24, 20), 
	RGB(19, 15, 15), RGB(31, 31, 31), RGB( 0,  0,  0), RGB( 2,  1,  1), 
	RGB(26,  5,  9), RGB( 7,  8,  6), RGB(12, 13, 12), RGB(24, 17, 20), 
	RGB(30,  5,  9), RGB( 7,  8, 14), RGB(14, 13, 12), RGB(24, 25, 20), 
	RGB(10,  7,  7), RGB( 6,  4,  2), RGB(15, 14,  9), RGB(25, 24, 17), 
	RGB(16, 14, 13), RGB( 7,  8,  7), RGB( 5,  4,  4), RGB(12,  7,  9), 
	RGB( 2,  4,  1), RGB( 7,  8,  7), RGB(14, 14, 13), RGB(24, 24, 22), 
	RGB(20, 15, 20), RGB( 7,  8,  7), RGB(14, 14, 14), RGB(24, 24, 22), 
};

UWORD walkpal12[] = {
	RGB( 0,  0,  0), RGB(25, 25, 23), RGB( 7,  8,  8), RGB(13, 13, 11), 
	RGB(31, 31, 31), RGB(15, 15, 16), RGB(25, 23, 24), RGB( 1,  1,  1), 
	RGB( 3, 30, 16), RGB(16, 16, 16), RGB( 6,  8,  8), RGB(11, 11, 11), 
	RGB( 7,  7,  8), RGB( 1,  2,  1), RGB(21, 19, 18), RGB(12, 11, 11), 
	RGB(11, 28, 16), RGB(25, 25, 23), RGB( 7, 10,  8), RGB(13, 12, 11), 
	RGB(15, 28, 16), RGB(25, 25, 23), RGB( 7,  8,  8), RGB( 5, 13, 10), 
	RGB(11, 28, 16), RGB(25, 25, 23), RGB(15, 12,  0), RGB(13, 13, 11), 
	RGB(31, 28, 20), RGB(25, 25, 23), RGB( 7,  8,  8), RGB(13, 13, 11), 
};

UWORD walkpal13[] = {
	RGB( 0,  0,  0), RGB(24, 19, 20), RGB( 9, 10,  9), RGB( 3,  3,  3), 
	RGB(26, 31,  2), RGB(26, 17, 21), RGB(11, 10,  9), RGB( 6,  3,  3), 
	RGB(24, 23, 21), RGB(19, 17, 16), RGB(11, 10,  8), RGB( 1,  1,  1), 
	RGB(26, 24, 24), RGB(16, 16, 16), RGB( 9,  9,  8), RGB( 2,  2,  2), 
	RGB(27, 23, 11), RGB(16, 17, 16), RGB(11, 11,  8), RGB( 6,  8,  3), 
	RGB(16, 14, 16), RGB( 7,  6,  8), RGB(12, 10, 10), RGB(30, 13,  1), 
	RGB(29, 30, 28), RGB(24, 22, 21), RGB( 9, 10,  9), RGB( 2,  2,  2), 
	RGB( 0,  0,  0), RGB(31, 31, 31), RGB( 7,  7,  8), RGB(16, 16, 16), 
};

UWORD walkpal14[] = {
	RGB( 0,  0,  0), RGB(10,  9,  7), RGB( 3,  4,  3), RGB(21, 21, 24),
	RGB(14, 15, 14), RGB(31, 31, 31), RGB( 7,  7,  8), RGB( 0,  0,  0),
	RGB(15, 18, 16), RGB( 8,  9,  7), RGB( 3,  4,  2), RGB(27, 28, 27),
	RGB(13, 11,  7), RGB( 8,  8,  6), RGB( 2,  2,  1), RGB(19, 18, 16),
	RGB( 8,  8,  7), RGB(15, 15, 15), RGB( 2,  1,  1), RGB(23, 22, 24),
	RGB(27, 26, 21), RGB(10,  1,  7), RGB( 3,  4,  7), RGB(23, 21, 24),
	RGB(18, 16, 15), RGB( 3,  4,  3), RGB( 9,  8,  8), RGB(13, 12, 12),
	RGB(27, 26,  5), RGB(24,  9,  7), RGB( 3,  4,  3), RGB(21, 21, 24),
};

UWORD walkpal15[] = {
	RGB( 0,  0,  0), RGB( 1,  2,  1), RGB(31, 31, 31), RGB(29, 30, 29),
	RGB(10,  7,  9), RGB( 1,  2,  1), RGB(31, 31, 26), RGB(29, 31, 21),
	RGB(31,  5,  9), RGB( 1,  0,  1), RGB(25, 22, 31), RGB(31, 14, 28),
	RGB(14,  7, 13), RGB( 1, 10,  1), RGB(31, 31, 31), RGB(29, 30, 25),
	RGB( 7,  7,  8), RGB( 1,  1,  1), RGB(24, 24, 22), RGB(16, 16, 16),
	RGB(30,  7, 29), RGB( 1,  2,  1), RGB(31, 31, 31), RGB(29, 26, 31),
	RGB(10,  8,  7), RGB(16, 12, 12), RGB(22, 20, 17), RGB( 8,  4,  3),
	RGB(12, 12,  9), RGB( 1,  1,  1), RGB(21, 20, 17), RGB(29, 29, 28),
};


UWORD walkpal16[] = {
	RGB( 0,  0,  0), RGB( 2,  2,  1), RGB(31, 31, 31), RGB( 4,  4,  3), 
	RGB( 7,  7,  3), RGB( 1,  2,  0), RGB(18, 17, 11), RGB(13, 16,  7), 
	RGB( 7,  8,  7), RGB( 2,  1,  1), RGB(24, 24, 24), RGB(15, 16, 15), 
	RGB(19,  0, 23), RGB( 0,  0,  1), RGB(31, 23, 31), RGB(16,  4,  3), 
	RGB( 7,  9,  8), RGB( 1,  0,  0), RGB(14, 13, 12), RGB( 6,  6,  4), 
	RGB(19, 17, 15), RGB( 1,  1,  1), RGB(29, 30, 27), RGB( 7,  7,  7), 
	RGB(12,  7,  9), RGB( 3,  2,  3), RGB(20, 15, 14), RGB( 7,  5,  6), 
	RGB( 7,  7,  7), RGB( 2,  2,  1), RGB( 0, 25, 20), RGB( 5,  4,  4), 
} ;

UWORD *walkpals[] = {
	walkpal1, walkpal2, walkpal3, walkpal4, 
	walkpal5, walkpal6, walkpal7, walkpal8, 
	walkpal9, walkpal10, walkpal11, walkpal12, 
	walkpal13, walkpal14, walkpal15, walkpal16, 
};

unsigned char walkmap[] =
{
	0xFF,0xFF,0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x7E,0x7F,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,0xC0,0xC1,0xC2,0xC3,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xEE,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFF,0xFF,0xFF,
};
