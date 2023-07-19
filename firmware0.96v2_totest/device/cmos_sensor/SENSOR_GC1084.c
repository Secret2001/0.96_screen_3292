#include "cmos_sensor.h"

#if DEV_SENSOR_GC1084 > 0

SENSOR_INIT_SECTION const unsigned char gc1084InitTable[]=
{	
	/******************
	Mclk=27MHz
	Pclk=32MHz
	//window_size=1280*720
	//Rowtime = 44.4444us
	//VTS=750,HTS=1442
	***************/
	/******cisctl rst******/
	0x03,0xfe,0xf0,
	0x03,0xfe,0xf0,
	0x03,0xfe,0xf0,
	0x03,0xfe,0x00,
	/***,0x***PLL******/
	0x03,0xf2,0x00,
	0x03,0xf3,0x0f,
	0x03,0xf4,0x36,
	0x03,0xf5,0xc0,
	0x03,0xf6,0x13,
	0x03,0xf7,0x01,
	0x03,0xf8,0x10,
	0x03,0xf9,0x43,
	0x03,0xfa,0x00,
	0x03,0xfc,0x8e,
	/***,0x***frame structure******/
	0x0d,0x05,0x06,
	0x0d,0x06,0xac,
	0x0d,0x07,0x00,
	0x0d,0x08,0x10, 
	0x0d,0x0a,0x03, 
	0x00,0x0c,0x03, ////
	
	0x0d,0x0d,0x02,/////
	0x0d,0x0e,0xe0, 
	
	0x00,0x0f,0x05,
	0x00,0x10,0x08, 
	0x00,0x17,0x0c, 
	0x0d,0x73,0x92, 
	0x0d,0x76,0x00, 
	0x0d,0x41,0x02,
	0x0d,0x42,0xee, 
	0x0d,0x7a,0x0c, 
	/***,0x*** out ******/
//	0x01,0x53,0xa0,
	0x01,0x90,0x01,
	0x01,0x92,0x08,////
	0x01,0x94,0x00,
	0x01,0x95,0x02,
	0x01,0x96,0xd0,
	0x01,0x97,0x05,
	0x01,0x98,0x00,
	/***,0x*** Analog ******/
	0x00,0x6b,0x18,
	0x0d,0xb0,0x9d,
	0x0d,0xb1,0x00,
	0x0d,0xb2,0xac,
	0x0d,0xb3,0xd5,
	0x0d,0xb4,0x00,
	0x0d,0xb5,0x97,
	0x0d,0xb6,0x09,
	0x00,0xd2,0xfc,
	0x0d,0x19,0x31,
	0x0d,0x20,0x40,
	0x0d,0x25,0xcb,
	0x0d,0x27,0x03,
	0x0d,0x29,0x40,
	0x0d,0x43,0x20,
	0x00,0x58,0x60,
	0x00,0xd6,0x66,
	0x00,0xd7,0x19,
	0x00,0x93,0x02,
	0x00,0xd9,0x14,
	0x00,0xda,0xc1,
	0x0d,0x2a,0x00,
	0x0d,0x28,0x04,
	0x0d,0x53,0x12,
	0x0d,0xc2,0x84,
	0x00,0x50,0x30,
	0x00,0x80,0x07,
	0x00,0x8c,0x05,
	0x00,0x8d,0xa8,
	/***,0x*** dark sun ******/
	0x00,0x77,0x01,
	0x00,0x78,0x04,
	0x00,0x79,0x65,
	0x00,0x67,0xc0,
	0x00,0x54,0xff,
	0x00,0x55,0x02,
	0x00,0x56,0x00,
	0x00,0x57,0x10,
	0x00,0x5a,0xff,
	0x00,0x5b,0x07,
	/***,0x*** sram ******/
	0x00,0xd5,0x03, 
	0x01,0x02,0xa9,
	/***,0x*** exp & gain ******/
	0x0d,0x03,0x02,
	0x0d,0x04,0xd0,
	0x00,0x7a,0x60,
	0x04,0xe0,0xff,


	/***,0x*** blk *******/
	0x04,0x14,0x75,
	0x04,0x15,0x75,
	0x04,0x16,0x75,
	0x04,0x17,0x75,
	/***,0x*** mipi ******/


	
	0x01,0x53,0x00,
	0x00,0xdc,0x05,
	0x00,0xdd,0xea,

	
	0x02,0x90,0x0b,
	0x02,0x3e,0x40,
	0x03,0x1e,0x3e,
	0xff,0xff,0xff
};

_SEN_YGAMA_TABLE_ const u16 gc1084_ygama[_SEN_YGAMA_CLASSES_][256]={
#if 1
//y_gama[5]   r =1.165
{0x1,0x9,0x10,0x17,0x1d,0x23,0x29,0x2f,0x34,0x3a,0x3f,0x45,0x4a,0x4f,0x55,0x5a,0x5f,0x64,0x69,0x6e,0x73,0x78,0x7d,0x82,0x86,0x8b,0x90,0x95,0x99,0x9e,0xa3,0xa7,
0xac,0xb1,0xb5,0xba,0xbe,0xc3,0xc7,0xcc,0xd0,0xd5,0xd9,0xdd,0xe2,0xe6,0xeb,0xef,0xf3,0xf8,0xfc,0x100,0x105,0x109,0x10d,0x112,0x116,0x11a,0x11e,0x123,0x127,0x12b,0x12f,0x133,
0x138,0x13c,0x140,0x144,0x148,0x14c,0x150,0x155,0x159,0x15d,0x161,0x165,0x169,0x16d,0x171,0x175,0x179,0x17d,0x181,0x185,0x189,0x18d,0x191,0x195,0x199,0x19d,0x1a1,0x1a5,0x1a9,0x1ad,0x1b1,0x1b5,
0x1b9,0x1bd,0x1c1,0x1c5,0x1c9,0x1cd,0x1d1,0x1d5,0x1d9,0x1dc,0x1e0,0x1e4,0x1e8,0x1ec,0x1f0,0x1f4,0x1f8,0x1fb,0x1ff,0x203,0x207,0x20b,0x20f,0x213,0x216,0x21a,0x21e,0x222,0x226,0x229,0x22d,0x231,
0x235,0x239,0x23c,0x240,0x244,0x248,0x24b,0x24f,0x253,0x257,0x25a,0x25e,0x262,0x266,0x269,0x26d,0x271,0x275,0x278,0x27c,0x280,0x283,0x287,0x28b,0x28f,0x292,0x296,0x29a,0x29d,0x2a1,0x2a5,0x2a8,
0x2ac,0x2b0,0x2b3,0x2b7,0x2bb,0x2be,0x2c2,0x2c6,0x2c9,0x2cd,0x2d1,0x2d4,0x2d8,0x2db,0x2df,0x2e3,0x2e6,0x2ea,0x2ee,0x2f1,0x2f5,0x2f8,0x2fc,0x300,0x303,0x307,0x30a,0x30e,0x312,0x315,0x319,0x31c,
0x320,0x323,0x327,0x32b,0x32e,0x332,0x335,0x339,0x33c,0x340,0x344,0x347,0x34b,0x34e,0x352,0x355,0x359,0x35c,0x360,0x363,0x367,0x36a,0x36e,0x371,0x375,0x378,0x37c,0x380,0x383,0x387,0x38a,0x38e,
0x391,0x395,0x398,0x39c,0x39f,0x3a3,0x3a6,0x3a9,0x3ad,0x3b0,0x3b4,0x3b7,0x3bb,0x3be,0x3c2,0x3c5,0x3c9,0x3cc,0x3d0,0x3d3,0x3d7,0x3da,0x3de,0x3e1,0x3e4,0x3e8,0x3eb,0x3ef,0x3f2,0x3f6,0x3f9,0x3fc},
#endif
#if 1
//y_gama[7]   r =1.35
{0x3,0x12,0x1d,0x27,0x30,0x38,0x40,0x48,0x4f,0x56,0x5d,0x64,0x6a,0x71,0x77,0x7d,0x84,0x8a,0x90,0x95,0x9b,0xa1,0xa6,0xac,0xb2,0xb7,0xbc,0xc2,0xc7,0xcc,0xd1,0xd6,
0xdc,0xe1,0xe6,0xeb,0xf0,0xf4,0xf9,0xfe,0x103,0x108,0x10d,0x111,0x116,0x11b,0x11f,0x124,0x128,0x12d,0x131,0x136,0x13a,0x13f,0x143,0x148,0x14c,0x151,0x155,0x159,0x15e,0x162,0x166,0x16a,
0x16f,0x173,0x177,0x17b,0x180,0x184,0x188,0x18c,0x190,0x194,0x198,0x19c,0x1a1,0x1a5,0x1a9,0x1ad,0x1b1,0x1b5,0x1b9,0x1bd,0x1c1,0x1c4,0x1c8,0x1cc,0x1d0,0x1d4,0x1d8,0x1dc,0x1e0,0x1e4,0x1e8,0x1eb,
0x1ef,0x1f3,0x1f7,0x1fb,0x1fe,0x202,0x206,0x20a,0x20d,0x211,0x215,0x219,0x21c,0x220,0x224,0x227,0x22b,0x22f,0x232,0x236,0x23a,0x23d,0x241,0x245,0x248,0x24c,0x24f,0x253,0x256,0x25a,0x25e,0x261,
0x265,0x268,0x26c,0x26f,0x273,0x276,0x27a,0x27d,0x281,0x284,0x288,0x28b,0x28f,0x292,0x296,0x299,0x29d,0x2a0,0x2a3,0x2a7,0x2aa,0x2ae,0x2b1,0x2b5,0x2b8,0x2bb,0x2bf,0x2c2,0x2c5,0x2c9,0x2cc,0x2d0,
0x2d3,0x2d6,0x2da,0x2dd,0x2e0,0x2e4,0x2e7,0x2ea,0x2ed,0x2f1,0x2f4,0x2f7,0x2fb,0x2fe,0x301,0x304,0x308,0x30b,0x30e,0x312,0x315,0x318,0x31b,0x31e,0x322,0x325,0x328,0x32b,0x32f,0x332,0x335,0x338,
0x33b,0x33f,0x342,0x345,0x348,0x34b,0x34e,0x352,0x355,0x358,0x35b,0x35e,0x361,0x365,0x368,0x36b,0x36e,0x371,0x374,0x377,0x37a,0x37d,0x381,0x384,0x387,0x38a,0x38d,0x390,0x393,0x396,0x399,0x39c,
0x39f,0x3a3,0x3a6,0x3a9,0x3ac,0x3af,0x3b2,0x3b5,0x3b8,0x3bb,0x3be,0x3c1,0x3c4,0x3c7,0x3ca,0x3cd,0x3d0,0x3d3,0x3d6,0x3d9,0x3dc,0x3df,0x3e2,0x3e5,0x3e8,0x3eb,0x3ee,0x3f1,0x3f4,0x3f7,0x3fa,0x3fd},
#endif
#if 1
//y_gama[9]   r =1.555
{0x7,0x1f,0x2f,0x3c,0x48,0x52,0x5c,0x66,0x6f,0x77,0x80,0x88,0x90,0x97,0x9e,0xa6,0xad,0xb3,0xba,0xc1,0xc7,0xcd,0xd4,0xda,0xe0,0xe6,0xeb,0xf1,0xf7,0xfd,0x102,0x108,
0x10d,0x112,0x118,0x11d,0x122,0x127,0x12c,0x131,0x136,0x13b,0x140,0x145,0x14a,0x14f,0x154,0x158,0x15d,0x162,0x166,0x16b,0x16f,0x174,0x178,0x17d,0x181,0x186,0x18a,0x18f,0x193,0x197,0x19b,0x1a0,
0x1a4,0x1a8,0x1ac,0x1b0,0x1b5,0x1b9,0x1bd,0x1c1,0x1c5,0x1c9,0x1cd,0x1d1,0x1d5,0x1d9,0x1dd,0x1e1,0x1e5,0x1e9,0x1ec,0x1f0,0x1f4,0x1f8,0x1fc,0x200,0x203,0x207,0x20b,0x20e,0x212,0x216,0x21a,0x21d,
0x221,0x225,0x228,0x22c,0x22f,0x233,0x237,0x23a,0x23e,0x241,0x245,0x248,0x24c,0x24f,0x253,0x256,0x25a,0x25d,0x261,0x264,0x267,0x26b,0x26e,0x272,0x275,0x278,0x27c,0x27f,0x282,0x286,0x289,0x28c,
0x290,0x293,0x296,0x299,0x29d,0x2a0,0x2a3,0x2a6,0x2aa,0x2ad,0x2b0,0x2b3,0x2b7,0x2ba,0x2bd,0x2c0,0x2c3,0x2c6,0x2ca,0x2cd,0x2d0,0x2d3,0x2d6,0x2d9,0x2dc,0x2df,0x2e2,0x2e5,0x2e9,0x2ec,0x2ef,0x2f2,
0x2f5,0x2f8,0x2fb,0x2fe,0x301,0x304,0x307,0x30a,0x30d,0x310,0x313,0x316,0x319,0x31c,0x31f,0x322,0x325,0x328,0x32a,0x32d,0x330,0x333,0x336,0x339,0x33c,0x33f,0x342,0x345,0x347,0x34a,0x34d,0x350,
0x353,0x356,0x359,0x35b,0x35e,0x361,0x364,0x367,0x36a,0x36c,0x36f,0x372,0x375,0x378,0x37a,0x37d,0x380,0x383,0x385,0x388,0x38b,0x38e,0x390,0x393,0x396,0x399,0x39b,0x39e,0x3a1,0x3a3,0x3a6,0x3a9,
0x3ac,0x3ae,0x3b1,0x3b4,0x3b6,0x3b9,0x3bc,0x3be,0x3c1,0x3c4,0x3c6,0x3c9,0x3cc,0x3ce,0x3d1,0x3d4,0x3d6,0x3d9,0x3db,0x3de,0x3e1,0x3e3,0x3e6,0x3e9,0x3eb,0x3ee,0x3f0,0x3f3,0x3f6,0x3f8,0x3fb,0x3fd},
#endif
#if 1
//y_gama[11]   r =1.77
{0xd,0x2f,0x44,0x54,0x63,0x70,0x7c,0x87,0x91,0x9b,0xa5,0xae,0xb6,0xbf,0xc7,0xcf,0xd6,0xde,0xe5,0xec,0xf3,0xfa,0x100,0x107,0x10d,0x113,0x11a,0x120,0x126,0x12b,0x131,0x137,
0x13c,0x142,0x147,0x14d,0x152,0x157,0x15d,0x162,0x167,0x16c,0x171,0x176,0x17b,0x180,0x184,0x189,0x18e,0x192,0x197,0x19c,0x1a0,0x1a5,0x1a9,0x1ae,0x1b2,0x1b6,0x1bb,0x1bf,0x1c3,0x1c7,0x1cc,0x1d0,
0x1d4,0x1d8,0x1dc,0x1e0,0x1e4,0x1e8,0x1ec,0x1f0,0x1f4,0x1f8,0x1fc,0x200,0x204,0x207,0x20b,0x20f,0x213,0x216,0x21a,0x21e,0x222,0x225,0x229,0x22c,0x230,0x234,0x237,0x23b,0x23e,0x242,0x245,0x249,
0x24c,0x250,0x253,0x257,0x25a,0x25d,0x261,0x264,0x267,0x26b,0x26e,0x271,0x275,0x278,0x27b,0x27f,0x282,0x285,0x288,0x28b,0x28f,0x292,0x295,0x298,0x29b,0x29e,0x2a2,0x2a5,0x2a8,0x2ab,0x2ae,0x2b1,
0x2b4,0x2b7,0x2ba,0x2bd,0x2c0,0x2c3,0x2c6,0x2c9,0x2cc,0x2cf,0x2d2,0x2d5,0x2d8,0x2db,0x2de,0x2e1,0x2e4,0x2e7,0x2e9,0x2ec,0x2ef,0x2f2,0x2f5,0x2f8,0x2fb,0x2fd,0x300,0x303,0x306,0x309,0x30b,0x30e,
0x311,0x314,0x317,0x319,0x31c,0x31f,0x322,0x324,0x327,0x32a,0x32c,0x32f,0x332,0x334,0x337,0x33a,0x33c,0x33f,0x342,0x344,0x347,0x34a,0x34c,0x34f,0x352,0x354,0x357,0x359,0x35c,0x35f,0x361,0x364,
0x366,0x369,0x36b,0x36e,0x370,0x373,0x375,0x378,0x37b,0x37d,0x380,0x382,0x385,0x387,0x38a,0x38c,0x38e,0x391,0x393,0x396,0x398,0x39b,0x39d,0x3a0,0x3a2,0x3a5,0x3a7,0x3a9,0x3ac,0x3ae,0x3b1,0x3b3,
0x3b5,0x3b8,0x3ba,0x3bd,0x3bf,0x3c1,0x3c4,0x3c6,0x3c8,0x3cb,0x3cd,0x3cf,0x3d2,0x3d4,0x3d6,0x3d9,0x3db,0x3dd,0x3e0,0x3e2,0x3e4,0x3e7,0x3e9,0x3eb,0x3ee,0x3f0,0x3f2,0x3f4,0x3f7,0x3f9,0x3fb,0x3fe},
#endif
#if 1
//y_gama[13]   r =2.005
{0x16,0x44,0x5d,0x71,0x82,0x91,0x9f,0xab,0xb7,0xc2,0xcc,0xd6,0xdf,0xe8,0xf1,0xf9,0x101,0x109,0x111,0x118,0x120,0x127,0x12d,0x134,0x13b,0x141,0x148,0x14e,0x154,0x15a,0x160,0x165,
0x16b,0x171,0x176,0x17c,0x181,0x186,0x18c,0x191,0x196,0x19b,0x1a0,0x1a5,0x1aa,0x1ae,0x1b3,0x1b8,0x1bc,0x1c1,0x1c6,0x1ca,0x1ce,0x1d3,0x1d7,0x1dc,0x1e0,0x1e4,0x1e8,0x1ed,0x1f1,0x1f5,0x1f9,0x1fd,
0x201,0x205,0x209,0x20d,0x211,0x214,0x218,0x21c,0x220,0x224,0x227,0x22b,0x22f,0x232,0x236,0x23a,0x23d,0x241,0x244,0x248,0x24b,0x24f,0x252,0x256,0x259,0x25c,0x260,0x263,0x267,0x26a,0x26d,0x270,
0x274,0x277,0x27a,0x27d,0x281,0x284,0x287,0x28a,0x28d,0x290,0x294,0x297,0x29a,0x29d,0x2a0,0x2a3,0x2a6,0x2a9,0x2ac,0x2af,0x2b2,0x2b5,0x2b8,0x2bb,0x2be,0x2c1,0x2c3,0x2c6,0x2c9,0x2cc,0x2cf,0x2d2,
0x2d5,0x2d7,0x2da,0x2dd,0x2e0,0x2e3,0x2e5,0x2e8,0x2eb,0x2ee,0x2f0,0x2f3,0x2f6,0x2f8,0x2fb,0x2fe,0x300,0x303,0x306,0x308,0x30b,0x30e,0x310,0x313,0x315,0x318,0x31b,0x31d,0x320,0x322,0x325,0x327,
0x32a,0x32c,0x32f,0x331,0x334,0x336,0x339,0x33b,0x33e,0x340,0x343,0x345,0x348,0x34a,0x34c,0x34f,0x351,0x354,0x356,0x358,0x35b,0x35d,0x360,0x362,0x364,0x367,0x369,0x36b,0x36e,0x370,0x372,0x375,
0x377,0x379,0x37c,0x37e,0x380,0x382,0x385,0x387,0x389,0x38b,0x38e,0x390,0x392,0x394,0x397,0x399,0x39b,0x39d,0x39f,0x3a2,0x3a4,0x3a6,0x3a8,0x3aa,0x3ad,0x3af,0x3b1,0x3b3,0x3b5,0x3b7,0x3ba,0x3bc,
0x3be,0x3c0,0x3c2,0x3c4,0x3c6,0x3c8,0x3cb,0x3cd,0x3cf,0x3d1,0x3d3,0x3d5,0x3d7,0x3d9,0x3db,0x3dd,0x3df,0x3e1,0x3e3,0x3e5,0x3e8,0x3ea,0x3ec,0x3ee,0x3f0,0x3f2,0x3f4,0x3f6,0x3f8,0x3fa,0x3fc,0x3fe},
#endif
#if 1
//y_gama[14]   r =2.13
{0x1c,0x50,0x6b,0x81,0x93,0xa3,0xb1,0xbe,0xca,0xd6,0xe0,0xea,0xf4,0xfd,0x106,0x10f,0x117,0x11f,0x127,0x12e,0x136,0x13d,0x144,0x14b,0x151,0x158,0x15e,0x164,0x16b,0x171,0x176,0x17c,
0x182,0x188,0x18d,0x193,0x198,0x19d,0x1a2,0x1a7,0x1ac,0x1b1,0x1b6,0x1bb,0x1c0,0x1c5,0x1c9,0x1ce,0x1d3,0x1d7,0x1dc,0x1e0,0x1e5,0x1e9,0x1ed,0x1f1,0x1f6,0x1fa,0x1fe,0x202,0x206,0x20a,0x20e,0x212,
0x216,0x21a,0x21e,0x222,0x226,0x229,0x22d,0x231,0x234,0x238,0x23c,0x23f,0x243,0x247,0x24a,0x24e,0x251,0x255,0x258,0x25b,0x25f,0x262,0x266,0x269,0x26c,0x26f,0x273,0x276,0x279,0x27c,0x280,0x283,
0x286,0x289,0x28c,0x28f,0x293,0x296,0x299,0x29c,0x29f,0x2a2,0x2a5,0x2a8,0x2ab,0x2ae,0x2b1,0x2b4,0x2b6,0x2b9,0x2bc,0x2bf,0x2c2,0x2c5,0x2c8,0x2cb,0x2cd,0x2d0,0x2d3,0x2d6,0x2d8,0x2db,0x2de,0x2e1,
0x2e3,0x2e6,0x2e9,0x2eb,0x2ee,0x2f1,0x2f3,0x2f6,0x2f9,0x2fb,0x2fe,0x301,0x303,0x306,0x308,0x30b,0x30d,0x310,0x312,0x315,0x318,0x31a,0x31d,0x31f,0x322,0x324,0x326,0x329,0x32b,0x32e,0x330,0x333,
0x335,0x337,0x33a,0x33c,0x33f,0x341,0x343,0x346,0x348,0x34a,0x34d,0x34f,0x351,0x354,0x356,0x358,0x35b,0x35d,0x35f,0x361,0x364,0x366,0x368,0x36a,0x36d,0x36f,0x371,0x373,0x376,0x378,0x37a,0x37c,
0x37e,0x381,0x383,0x385,0x387,0x389,0x38b,0x38e,0x390,0x392,0x394,0x396,0x398,0x39a,0x39c,0x39f,0x3a1,0x3a3,0x3a5,0x3a7,0x3a9,0x3ab,0x3ad,0x3af,0x3b1,0x3b3,0x3b5,0x3b7,0x3b9,0x3bb,0x3bd,0x3c0,
0x3c2,0x3c4,0x3c6,0x3c8,0x3ca,0x3cc,0x3ce,0x3d0,0x3d1,0x3d3,0x3d5,0x3d7,0x3d9,0x3db,0x3dd,0x3df,0x3e1,0x3e3,0x3e5,0x3e7,0x3e9,0x3eb,0x3ed,0x3ef,0x3f1,0x3f2,0x3f4,0x3f6,0x3f8,0x3fa,0x3fc,0x3fe},
#endif
#if 1
//y_gama[15]   r =2.26
{0x23,0x5c,0x7a,0x91,0xa4,0xb5,0xc4,0xd1,0xde,0xea,0xf5,0xff,0x109,0x113,0x11c,0x124,0x12d,0x135,0x13d,0x144,0x14c,0x153,0x15a,0x161,0x168,0x16e,0x175,0x17b,0x181,0x187,0x18d,0x193,
0x198,0x19e,0x1a3,0x1a9,0x1ae,0x1b3,0x1b8,0x1bd,0x1c3,0x1c7,0x1cc,0x1d1,0x1d6,0x1db,0x1df,0x1e4,0x1e8,0x1ed,0x1f1,0x1f6,0x1fa,0x1fe,0x202,0x207,0x20b,0x20f,0x213,0x217,0x21b,0x21f,0x223,0x227,
0x22a,0x22e,0x232,0x236,0x23a,0x23d,0x241,0x245,0x248,0x24c,0x24f,0x253,0x256,0x25a,0x25d,0x261,0x264,0x267,0x26b,0x26e,0x271,0x275,0x278,0x27b,0x27e,0x282,0x285,0x288,0x28b,0x28e,0x291,0x294,
0x297,0x29a,0x29d,0x2a0,0x2a3,0x2a6,0x2a9,0x2ac,0x2af,0x2b2,0x2b5,0x2b8,0x2bb,0x2be,0x2c1,0x2c3,0x2c6,0x2c9,0x2cc,0x2cf,0x2d1,0x2d4,0x2d7,0x2d9,0x2dc,0x2df,0x2e2,0x2e4,0x2e7,0x2e9,0x2ec,0x2ef,
0x2f1,0x2f4,0x2f7,0x2f9,0x2fc,0x2fe,0x301,0x303,0x306,0x308,0x30b,0x30d,0x310,0x312,0x315,0x317,0x31a,0x31c,0x31f,0x321,0x323,0x326,0x328,0x32a,0x32d,0x32f,0x332,0x334,0x336,0x339,0x33b,0x33d,
0x340,0x342,0x344,0x346,0x349,0x34b,0x34d,0x34f,0x352,0x354,0x356,0x358,0x35b,0x35d,0x35f,0x361,0x363,0x366,0x368,0x36a,0x36c,0x36e,0x370,0x372,0x375,0x377,0x379,0x37b,0x37d,0x37f,0x381,0x383,
0x385,0x387,0x38a,0x38c,0x38e,0x390,0x392,0x394,0x396,0x398,0x39a,0x39c,0x39e,0x3a0,0x3a2,0x3a4,0x3a6,0x3a8,0x3aa,0x3ac,0x3ae,0x3b0,0x3b2,0x3b4,0x3b6,0x3b8,0x3b9,0x3bb,0x3bd,0x3bf,0x3c1,0x3c3,
0x3c5,0x3c7,0x3c9,0x3cb,0x3cd,0x3ce,0x3d0,0x3d2,0x3d4,0x3d6,0x3d8,0x3da,0x3dc,0x3dd,0x3df,0x3e1,0x3e3,0x3e5,0x3e7,0x3e8,0x3ea,0x3ec,0x3ee,0x3f0,0x3f1,0x3f3,0x3f5,0x3f7,0x3f9,0x3fa,0x3fc,0x3fe},
#endif
#if 1
//y_gama[16]   r =2.395
{0x2a,0x6a,0x8a,0xa2,0xb6,0xc8,0xd7,0xe5,0xf2,0xfe,0x109,0x114,0x11e,0x128,0x131,0x13a,0x142,0x14b,0x152,0x15a,0x162,0x169,0x170,0x177,0x17d,0x184,0x18a,0x191,0x197,0x19d,0x1a3,0x1a8,
0x1ae,0x1b4,0x1b9,0x1be,0x1c4,0x1c9,0x1ce,0x1d3,0x1d8,0x1dd,0x1e2,0x1e6,0x1eb,0x1f0,0x1f4,0x1f9,0x1fd,0x201,0x206,0x20a,0x20e,0x213,0x217,0x21b,0x21f,0x223,0x227,0x22b,0x22f,0x233,0x236,0x23a,
0x23e,0x242,0x245,0x249,0x24d,0x250,0x254,0x257,0x25b,0x25e,0x262,0x265,0x269,0x26c,0x26f,0x273,0x276,0x279,0x27c,0x280,0x283,0x286,0x289,0x28c,0x290,0x293,0x296,0x299,0x29c,0x29f,0x2a2,0x2a5,
0x2a8,0x2ab,0x2ae,0x2b1,0x2b3,0x2b6,0x2b9,0x2bc,0x2bf,0x2c2,0x2c4,0x2c7,0x2ca,0x2cd,0x2d0,0x2d2,0x2d5,0x2d8,0x2da,0x2dd,0x2e0,0x2e2,0x2e5,0x2e8,0x2ea,0x2ed,0x2ef,0x2f2,0x2f4,0x2f7,0x2f9,0x2fc,
0x2fe,0x301,0x303,0x306,0x308,0x30b,0x30d,0x310,0x312,0x315,0x317,0x319,0x31c,0x31e,0x320,0x323,0x325,0x327,0x32a,0x32c,0x32e,0x331,0x333,0x335,0x337,0x33a,0x33c,0x33e,0x340,0x343,0x345,0x347,
0x349,0x34c,0x34e,0x350,0x352,0x354,0x356,0x358,0x35b,0x35d,0x35f,0x361,0x363,0x365,0x367,0x369,0x36b,0x36e,0x370,0x372,0x374,0x376,0x378,0x37a,0x37c,0x37e,0x380,0x382,0x384,0x386,0x388,0x38a,
0x38c,0x38e,0x390,0x392,0x394,0x396,0x398,0x39a,0x39b,0x39d,0x39f,0x3a1,0x3a3,0x3a5,0x3a7,0x3a9,0x3ab,0x3ad,0x3ae,0x3b0,0x3b2,0x3b4,0x3b6,0x3b8,0x3ba,0x3bb,0x3bd,0x3bf,0x3c1,0x3c3,0x3c5,0x3c6,
0x3c8,0x3ca,0x3cc,0x3ce,0x3cf,0x3d1,0x3d3,0x3d5,0x3d6,0x3d8,0x3da,0x3dc,0x3de,0x3df,0x3e1,0x3e3,0x3e4,0x3e6,0x3e8,0x3ea,0x3eb,0x3ed,0x3ef,0x3f1,0x3f2,0x3f4,0x3f6,0x3f7,0x3f9,0x3fb,0x3fc,0x3fe},
#endif
};
	
_SEN_RGBGAMA_TABLE_ const u8 gc1084_rgbgama[_SEN_RGBGAMA_CLASSES_][256] = {

#if 1
//rgb_gamma[6]   r =0.85
{0,0,1,1,2,2,3,4,4,5,5,6,7,8,8,9,10,10,11,12,13,13,14,15,16,16,17,18,19,20,20,21,
22,23,24,25,25,26,27,28,29,30,30,31,32,33,34,35,36,37,37,38,39,40,41,42,43,44,45,45,46,47,48,49,
50,51,52,53,54,55,56,57,58,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,
81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,
113,114,115,116,117,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,137,138,139,140,141,142,143,144,145,146,
147,148,149,151,152,153,154,155,156,157,158,159,160,161,163,164,165,166,167,168,169,170,171,173,174,175,176,177,178,179,180,181,
183,184,185,186,187,188,189,190,192,193,194,195,196,197,198,199,201,202,203,204,205,206,207,209,210,211,212,213,214,215,217,218,
219,220,221,222,223,225,226,227,228,229,230,232,233,234,235,236,237,239,240,241,242,243,244,246,247,248,249,250,251,253,254,255,
},
#endif 

#if 1
//rgb_gamma[7]   r =0.9
{0,0,1,2,2,3,4,5,5,6,7,8,8,9,10,11,12,12,13,14,15,16,17,18,18,19,20,21,22,23,24,24,
25,26,27,28,29,30,31,32,32,33,34,35,36,37,38,39,40,41,42,43,44,44,45,46,47,48,49,50,51,52,53,54,
55,56,57,58,59,60,61,62,63,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,
119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,145,146,147,148,149,150,151,
152,153,154,155,156,157,158,159,160,161,162,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,180,181,182,183,184,185,
186,187,188,189,190,191,192,194,195,196,197,198,199,200,201,202,203,204,205,207,208,209,210,211,212,213,214,215,216,217,219,220,
221,222,223,224,225,226,227,228,230,231,232,233,234,235,236,237,238,239,241,242,243,244,245,246,247,248,249,251,252,253,254,255,
},
#endif

#if 1
//rgb_gamma[8]   r =0.95
{0,1,1,2,3,4,5,6,7,7,8,9,10,11,12,13,14,15,16,17,17,18,19,20,21,22,23,24,25,26,27,28,
29,30,31,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,
91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,
123,124,125,126,127,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,
156,157,158,159,160,161,162,163,164,165,166,167,168,169,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,
189,190,191,192,193,194,195,196,197,198,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,
222,223,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,246,247,248,249,250,251,252,253,254,255,
},
#endif

#if 1
//rgb_gamma[9]   r =1
{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
},
#endif

#if 1
//rgb_gamma[10]   r =1.05
{0,1,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,22,23,24,25,26,27,28,29,30,31,32,33,34,
35,36,37,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,
68,69,70,71,72,73,74,75,76,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,
101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,
132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,
164,165,166,167,168,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,
195,196,197,198,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,223,224,
225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,245,246,247,248,249,250,251,252,253,254,255,
},
#endif

#if 1
//rgb_gamma[11]   r =1.1
{0,2,3,5,6,7,9,10,11,12,14,15,16,17,18,20,21,22,23,24,25,26,28,29,30,31,32,33,34,35,37,38,
39,40,41,42,43,44,45,46,47,48,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,70,71,72,
73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,
105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,130,131,132,133,134,135,
136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,156,157,158,159,160,161,162,163,164,165,166,
167,168,169,170,171,172,173,174,175,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,191,192,193,194,195,196,
197,198,199,200,201,202,203,204,205,205,206,207,208,209,210,211,212,213,214,215,216,217,217,218,219,220,221,222,223,224,225,226,
227,228,229,229,230,231,232,233,234,235,236,237,238,239,240,240,241,242,243,244,245,246,247,248,249,250,250,251,252,253,254,255,
},
#endif

#if 1
//rgb_gamma[12]   r =1.15
{1,2,4,6,7,9,10,11,13,14,15,17,18,19,21,22,23,24,26,27,28,29,30,32,33,34,35,36,37,39,40,41,
42,43,44,45,47,48,49,50,51,52,53,54,55,56,58,59,60,61,62,63,64,65,66,67,68,69,70,71,73,74,75,76,
77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,
109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,131,132,133,134,135,136,137,138,139,
140,141,142,143,144,145,146,147,148,149,150,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,165,166,167,168,169,
170,171,172,173,174,175,176,177,177,178,179,180,181,182,183,184,185,186,187,188,188,189,190,191,192,193,194,195,196,197,197,198,
199,200,201,202,203,204,205,206,206,207,208,209,210,211,212,213,214,215,215,216,217,218,219,220,221,222,223,223,224,225,226,227,
228,229,230,231,231,232,233,234,235,236,237,238,238,239,240,241,242,243,244,245,245,246,247,248,249,250,251,252,252,253,254,255,
},
#endif

#if 1
//rgb_gamma[13]   r =1.2
{1,3,5,7,8,10,11,13,14,16,17,19,20,22,23,24,26,27,28,29,31,32,33,34,36,37,38,39,41,42,43,44,
45,47,48,49,50,51,52,53,55,56,57,58,59,60,61,62,63,65,66,67,68,69,70,71,72,73,74,75,76,78,79,80,
81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,
113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
144,145,146,146,147,148,149,150,151,152,153,154,155,156,157,158,158,159,160,161,162,163,164,165,166,167,168,168,169,170,171,172,
173,174,175,176,177,177,178,179,180,181,182,183,184,185,186,186,187,188,189,190,191,192,193,193,194,195,196,197,198,199,200,200,
201,202,203,204,205,206,207,207,208,209,210,211,212,213,214,214,215,216,217,218,219,220,220,221,222,223,224,225,226,226,227,228,
229,230,231,232,232,233,234,235,236,237,237,238,239,240,241,242,243,243,244,245,246,247,248,248,249,250,251,252,253,253,254,255,
},
#endif

};

_SEN_LSC_TABLE_ const u16 gc1084_lsc_tab[572]={
#if 1  
413,349,310,285,272,272,271,280,303,344,405,
398,332,296,274,267,264,266,272,291,324,383,
381,321,287,265,259,257,261,264,278,313,369,
372,312,275,261,258,252,255,258,270,304,357,
367,310,273,258,257,251,252,258,269,297,351,
364,307,272,258,255,248,250,256,270,292,348,
368,308,272,258,256,256,251,259,268,299,353,
378,317,278,265,257,254,257,263,272,306,359,
401,328,292,269,262,261,260,266,279,316,369,
431,343,308,283,272,271,271,276,291,334,392,
466,374,327,298,283,276,281,286,311,354,429,
506,417,351,319,303,291,294,306,336,388,457,
512,420,359,321,305,296,298,309,339,395,459,

407,345,307,281,269,267,268,273,296,334,395,
383,326,295,272,265,259,262,267,280,317,371,
378,317,284,261,257,255,259,260,269,306,357,
365,308,275,258,255,252,254,256,266,299,347,
367,307,270,257,256,252,251,256,264,294,342,
366,307,273,258,255,248,248,254,267,289,341,
367,308,275,261,253,253,251,260,263,293,347,
379,312,280,265,259,255,257,263,271,303,353,
397,329,294,268,264,261,261,266,277,310,364,
435,347,310,285,276,271,272,275,292,330,384,
468,378,332,300,286,279,281,287,310,351,422,
512,425,358,326,306,300,298,311,336,390,455,
517,429,367,331,308,302,306,313,341,394,460,

404,341,304,279,269,270,268,278,299,342,408,
382,324,292,271,264,262,264,269,290,324,382,
374,313,285,261,256,256,263,264,275,313,371,
369,306,273,259,258,254,257,258,270,307,357,
359,304,273,257,256,252,253,260,272,300,357,
364,306,272,259,259,250,252,259,273,294,350,
363,306,273,260,257,256,253,260,268,300,356,
377,311,278,265,260,259,260,269,276,310,362,
394,323,291,269,263,264,265,270,282,322,375,
425,345,312,284,272,273,277,280,294,338,396,
459,371,327,299,287,281,285,288,314,357,431,
495,415,355,324,305,295,299,309,341,398,457,
501,418,359,326,305,300,303,313,346,402,456,

418,348,311,287,274,273,272,282,303,343,409,
392,332,298,275,268,262,267,272,292,324,385,
384,321,289,267,259,256,262,265,279,313,370,
376,313,277,261,258,253,258,259,273,305,361,
371,312,273,260,255,254,252,261,270,301,354,
374,308,275,261,257,250,250,258,269,294,350,
371,311,276,261,255,255,252,261,268,299,356,
382,319,279,264,258,257,257,266,272,307,363,
404,328,293,271,264,260,262,268,278,315,373,
441,346,312,283,274,269,272,274,291,333,391,
472,378,331,298,285,276,283,284,311,355,433,
517,419,355,320,302,292,293,306,337,390,458,
523,426,359,326,304,298,297,309,342,396,471
#else
	400,344,304,285,272,274,275,285,301,334,382,
	386,330,292,274,266,263,266,272,291,319,368,
	378,322,285,265,261,257,263,268,281,310,353,
	366,314,276,262,257,256,258,263,276,299,341,
	358,312,273,256,254,252,255,262,274,297,339,
	354,306,274,257,253,253,253,259,271,291,334,
	353,308,273,258,255,250,253,257,271,292,333,
	359,311,274,259,254,254,254,260,271,296,337,
	368,316,276,261,254,257,257,264,274,300,346,
	382,329,287,270,264,262,264,267,280,309,360,
	400,346,300,277,267,267,270,276,295,330,378,
	436,361,317,292,277,277,276,289,319,349,402,
	569,363,319,294,279,280,278,292,318,352,471,
	
	377,327,296,278,269,270,269,277,292,322,358,
	366,318,285,269,263,263,264,267,282,308,351,
	355,310,281,263,259,255,259,265,273,299,336,
	351,305,276,259,254,256,258,264,270,289,328,
	344,304,271,256,253,252,256,259,268,290,324,
	343,302,271,260,254,253,255,257,269,286,323,
	346,303,272,258,254,251,254,256,265,285,320,
	348,303,273,260,254,256,256,261,269,290,325,
	354,307,280,264,256,259,258,265,273,295,332,
	368,322,289,271,266,262,264,270,277,301,344,
	383,339,299,276,269,268,271,274,292,319,360,
	415,355,317,293,277,278,278,290,316,337,384,
	517,357,321,296,282,281,279,289,317,342,436,
	
	380,330,296,279,268,271,272,279,295,327,368,
	367,317,289,270,263,262,265,268,287,314,360,
	357,310,279,262,258,257,263,267,280,304,345,
	349,307,273,258,256,256,258,263,274,295,336,
	343,303,271,255,252,253,256,264,271,295,331,
	342,300,273,258,254,254,255,260,271,293,329,
	344,302,271,257,255,253,257,259,271,293,329,
	346,305,273,260,254,257,257,266,272,293,335,
	353,309,276,261,257,259,258,266,274,298,341,
	366,323,286,270,263,265,268,268,282,307,351,
	379,337,295,275,271,268,275,278,294,324,367,
	406,349,312,290,279,277,278,292,314,342,387,
	546,353,316,293,279,278,277,291,317,342,456,
	
	404,343,303,285,272,275,272,284,301,334,380,
	390,330,294,273,265,264,266,271,291,320,371,
	377,321,286,266,260,258,260,269,281,309,354,
	370,316,277,261,256,256,257,265,276,299,342,
	361,311,274,256,253,253,255,262,273,298,341,
	360,309,273,258,253,251,253,260,272,293,335,
	358,310,273,259,254,249,253,258,271,294,335,
	365,314,277,260,253,255,255,262,270,295,339,
	368,317,277,262,256,256,256,265,275,302,348,
	383,329,288,270,263,261,265,267,279,309,361,
	403,350,301,277,268,265,271,276,295,330,380,
	440,363,321,294,277,276,276,289,319,350,404,
	599,369,322,294,279,277,278,291,317,351,489

#endif

};

void reg_gc1084_wr(u16 addr,u8 val)
{
	u8 iicbuf[3];
	iicbuf[0] = ((addr >> 8) & 0xff);
	iicbuf[1] = (addr & 0xff);
	iicbuf[2] = val;
	sensor_iic_write(iicbuf);
}

static void gc1084_rotate(u32 r)
{
	reg_gc1084_wr(0x0015,r?1:0);
	reg_gc1084_wr(0x0d15,r?3:0);
}

static void gc1084_hvblank(u32 h,u32 v)
{
	u32 i,hb,vb;
	hb = h;//(h - 694) / 2;
	vb = v;//v - 724 - 16;
	const u8 t[][3] = {
		{0x0d,0x05,(hb >> 8)&0xf},
		{0x0d,0x06,hb & 0xff},
		{0x0d,0x41,(vb >> 8)&0xf},
		{0x0d,0x42,vb & 0xff},
	};
	for(i=0;i<4;i++)
		sensor_iic_write((u8 *)&t[i][0]);
}
static void sensor_gc1084_exp_wr(u32 EV)
{
	reg_gc1084_wr(0x0d03,(EV>>8)&0xff);
	reg_gc1084_wr(0x0d04,EV&0xff);	
}

static UINT32 gainLevelTable[30] = {64,76,90,106,128,152,179,212,256,303,358,425,512,607,716,848,1024,1214,1434,1699,2048,2427,2865,3393,4096,4855,5730,6809,8192,0xffffffff};
static UINT8 regValTable[29][6] = { 
{0x00, 0x00, 0x00, 0x80, 0x01, 0x00},
{0x0a, 0x00, 0x00, 0x80, 0x01, 0x0b},
{0x00, 0x01, 0x00, 0x80, 0x01, 0x19},
{0x0a, 0x01, 0x00, 0x80, 0x01, 0x2a},
{0x00, 0x02, 0x00, 0x80, 0x02, 0x00},
{0x0a, 0x02, 0x00, 0x80, 0x02, 0x17},
{0x00, 0x03, 0x00, 0x80, 0x02, 0x33},
{0x0a, 0x03, 0x00, 0x80, 0x03, 0x14},
{0x00, 0x04, 0x00, 0x90, 0x04, 0x00},
{0x0a, 0x04, 0x00, 0x90, 0x04, 0x2f},
{0x00, 0x05, 0x00, 0x90, 0x05, 0x26},
{0x0a, 0x05, 0x00, 0x90, 0x06, 0x28},
{0x00, 0x06, 0x00, 0xa0, 0x08, 0x00},
{0x0a, 0x06, 0x00, 0xa0, 0x09, 0x1e},
{0x12, 0x46, 0x00, 0xa0, 0x0b, 0x0c},
{0x19, 0x66, 0x00, 0xa0, 0x0d, 0x10},
{0x00, 0x04, 0x01, 0xa0, 0x10, 0x00},						
{0x0a, 0x04, 0x01, 0xa0, 0x12, 0x3d},
{0x00, 0x05, 0x01, 0xb0, 0x16, 0x19},
{0x0a, 0x05, 0x01, 0xc0, 0x1a, 0x23},
{0x00, 0x06, 0x01, 0xc0, 0x20, 0x00},
{0x0a, 0x06, 0x01, 0xc0, 0x25, 0x3b},
{0x12, 0x46, 0x01, 0xc0, 0x2c, 0x30},
{0x19, 0x66, 0x01, 0xd0, 0x35, 0x01},
{0x20, 0x06, 0x01, 0xe0, 0x3f, 0x3f},
{0x25, 0x06, 0x01, 0xe0, 0x3f, 0x3f},
{0x29, 0x26, 0x01, 0xe0, 0x3f, 0x3f},
{0x2c, 0xc6, 0x01, 0xf0, 0x3f, 0x3f},
{0x30, 0x06, 0x01, 0xf0, 0x3f, 0x3f},
};

static void sensor_gc1084_gain_wr(u32 gain)
{
	int i;
	UINT32 tol_dig_gain = 0;
	//u8 iicbuf[8];
	gain=gain>>2;
	for(i = 0; i < sizeof(gainLevelTable) / sizeof(UINT32); i++)
	{
		if((gainLevelTable[i] <= gain)&&(gain < gainLevelTable[i+1]))
			break;
	}
	tol_dig_gain = gain*64/gainLevelTable[i];

	reg_gc1084_wr(0x00d1,regValTable[i][0]);
	reg_gc1084_wr(0x00d0,regValTable[i][1]);
	reg_gc1084_wr(0x031d,0x2e);
	reg_gc1084_wr(0x0dc1,regValTable[i][2]);
	reg_gc1084_wr(0x031d,0x28);
	reg_gc1084_wr(0x0155,regValTable[i][3]);
	reg_gc1084_wr(0x00b8,regValTable[i][4]);
	reg_gc1084_wr(0x00b9,regValTable[i][5]);

	reg_gc1084_wr(0x00b1,(tol_dig_gain>>6));
	reg_gc1084_wr(0x00b2,((tol_dig_gain&0x3f)<<2));
}



static void sensor_gc1084_exp_gain_wr(u32 exp,u32 gain){
	sensor_gc1084_exp_wr(exp);
	sensor_gc1084_gain_wr(gain);	
}

SENSOR_OP_SECTION const Sensor_Op_t gc1084_cmd = 
{
	.typ =CSI_TYPE_RAW10,
	.pixelw = 1280,
	.pixelh= 720,
	.hsyn = 1,
	.vsyn = 0,
	.colrarray = 1,//2'h0: RG/GB  2'h1:GR/BG  2'h2:BG/GR  2'h3:GB/RG
	.AVDD = SYS_VOL_V2_8,//3.3
	.DVDD = SYS_VOL_V1_8,//1.5
	.VDDIO = SYS_VOL_V2_8,//1.8
	.rotate_adapt = {1},
	.hvb_adapt = {32000000,980,0,0,0xff,20,0}, //25 20
	//.mclk = 24000000,//19000000
	.mclk = 24000000,//19000000
	.pclk_fir_en = 0, ///
	.pclk_fir_class = 0,
	.pclk_inv_en = 1,
	.csi_tun = 11,
	.isp_all_mod = 	(_ISP_FREE_<<_AE_POS_       |_ISP_EN_<<_BLC_POS_        |_ISP_DIS_<<_LSC_POS_         \
					|_ISP_EN_<<_DDC_POS_ 	   |_ISP_AUTO_<<_AWB_POS_      |_ISP_EN_<<_CCM_POS_         \
					|_ISP_DIS_<<_DGAIN_POS_     |_ISP_EN_<<_YGAMA_POS_    |_ISP_AUTO_<<_RGB_GAMA_POS_  \
					|_ISP_DIS_<<_CH_POS_        |_ISP_EN_<<_VDE_POS_      |_ISP_AUTO_<<_EE_POS_        \
					|_ISP_EN_<<_CFD_POS_     |_ISP_AUTO_<<_SAJ_POS_),

	.ae_adapt = {.exp_adapt = {4,{30,40,50,60,70,80,85,90},3,195*256,12,4,1024*32,0x6342,15000},//28->36
				.hgrm_adapt = {256,256,512,768,1024,144,288,432,576,0x11111111,0x11122211,0x22211222,0x1,
							   {8,8,8,8,8,8,8,8},{8,8,8,8,8,8,8,8}}},//0.5,2,2
	.blc_adapt ={-60,-60,-60,-60,{0,8,8,8,8,8,8,8},5},  
	//.blc_adapt ={-40,-44,-44,-40,{0,8,8,8,8,8,8,8},5}, 
	.ddc_adapt = {2,2,0,0,16,{4,4,4,4,4,4,4,4},{8,8,8,8,8,8,8,8},1,{6,6,5,5,4,4,3,3},{0,0,0,0,0,0,0,0},{6,20,30,40,50,80,120},0,10,7},
	.awb_adapt = {0x03,191,265,552,3,2,0xa,0xcc,0xff,0,0xff,0,0,{(400 << 20) | (256<< 10) | (380<< 0),//0xff,0,0xff,0 //0,3,0,3
				 (368 << 20) | (256<< 10) | (350<< 0),(465 << 20) | (256<< 10) | (225<< 0),
				 (370 << 20) | (256<< 10) | (385<< 0),(370 << 20) | (256<< 10) | (385<< 0)},
				 0,{0x5,0x0a,0x0f,0x14,0x19,0x1e,0x23,0x28},{0x5,0x0a,0x0f,0x14,0x19,0x1e,0x23,0x28},{0x8,0x0f,0x16,0x1e,0x24,0x2d,0x34,0x3c},0x0a,
				 0,0,0,0,0,0,{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
				 {	232,232,229,227,225,221,217,210,204,197,191,185,181,174,170,166,165,162,158,155,150,138,128,121,117,114,109,105,101,98,94,89,
					232,229,225,221,217,212,207,196,190,181,176,168,162,159,156,154,152,147,143,137,123,111,106,104,101,101,97,94,92,90,89,88,
					231,221,216,209,202,191,181,176,170,161,156,146,143,143,138,136,127,118,103,98,96,94,92,89,89,87,85,83,83,83,85,88,
					231,212,198,188,178,170,165,157,148,142,137,133,130,126,121,116,108,94,90,85,84,82,81,81,81,81,80,80,80,81,84,88}},				 
	.ccm_adapt = {{256-15,-28,-30,
			     -15,296,-10,
				  30,-12,256+40},
				0,0,0},  

	.rgbdgain_adapt = {{64,64,64,64,64,64,64,64,64},{64,64,64,64,64,64,64,64}},
	.ygama_adapt = {0,{7,7,7,7,7,7,7,7},0,0,0xff,144,208,96,144,1,{0}},
	.rgbgama_adapt = {0,{5,5,5,5,5,5,5,5},{20,12,4,4,4,0,0,0},0,0xff,0,0xff,0,0xff,64,224,4000,{0}},//2

	.ch_adapt = {1,1,{0,1,0,0,0,0},{320,192,320,128,256,384},{64,64,192,0,128,256},
	                  {0,10,0,0,0,0},
	                  {0,10,0,0,0,0},
					  {0,10,0,0,0,0},
				 {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
				 {16,16,16,16,16,16,16,16},8},
	.vde_adapt = {0xb0,0x80,0x80,0x80,{8,32,64,64,64,64,64,64,64},{16,16,16,16,16,16,16,16},8},
	.ee_adapt = {1,{4,3,3,2,1,1,0,0},{4,3,3,2,1,1,0,0},{8,8,8,8,8,8,8,8},{4,8,12,14,16,16,18,18},{0x5,0x5,0x6,0x7,0x8,0x8,0x8,0x8},{0,0,0,0,0,0,0,0},6},//1f,8   
	.cfd_adapt = {4,0xe0,0x20,1,1,0xff,1,0,1},
	.saj_adapt = {{16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},{10,12,14,14,16,16,17,18},8},
	.md_adapt = {40,40,1,1,1280,180,720},
	.p_fun_adapt = {gc1084_rotate,gc1084_hvblank,sensor_gc1084_exp_gain_wr},
	//.p_fun_adapt = {NULL,NULL,NULL},
};



SENSOR_HEADER_ITEM_SECTION  const Sensor_Init_t gc1084_init=
{
	.sensor_struct_addr =	(u32 *)&gc1084_cmd, 
	.sensor_struct_size = sizeof(Sensor_Op_t),
	.sensor_init_tab_adr =	 (u8 *) gc1084InitTable,    
	.sensor_init_tab_size = sizeof(gc1084InitTable),
	.rgb_gamma_tab_adr =	(u32 *)gc1084_rgbgama,     
	.rgb_gamma_tab_size = sizeof(gc1084_rgbgama),
	.ygamma_tab_adr =	(u32 *)gc1084_ygama,     
	.ygamma_tab_size = sizeof(gc1084_ygama),
	.lsc_tab_adr =	(u32 *)gc1084_lsc_tab,     
	.lsc_tab_size = sizeof(gc1084_lsc_tab),	
	.id               =	0x84,               
	.w_cmd            =	0x6e,               
	.r_cmd            =	0x6f,               
	.addr_num         =	0x02,               
	.data_num         =	0x01,               
	.sensor_name	  = "gc1084",
	.id_reg           =	0x03f1    //
};
#endif
 
 
 
 