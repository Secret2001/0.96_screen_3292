#include "cmos_sensor.h"

#if DEV_SENSOR_SIV121DS > 0

SENSOR_INIT_SECTION const unsigned char SIV121DInitTable[]= 
{

	0x03,0x85,
	0x04,0x03,			//0x03  0'  , 0x00  180'
	0x05,0x07,
	0x06,0x00,
	0x07,0x00,
	0x08,0x00,
	0x09,0x00,
	0x0a,0x00,
	0x0b,0x00,
	0x0c,0x00,
	0x0d,0x00,
	0x0e,0x00,
	0x0f,0x00,
	0x10,0x13,
	0x11,0x04,
	0x12,0x0a,
	0x13,0x1f,
	0x14,0x17,
	0x15,0x00,
	0x16,0x89,
	0x17,0x60,
	0x18,0x16,
	0x19,0x00,
	0x1a,0x00,
	0x1b,0x90,
	0x1c,0x00,
	0x1d,0x00,
	0x1e,0x00,
	0x1f,0x52,

	//0x20,((HBLANK_BASE>>8)<<4)|(VBLANK_BASE>>8),//HB[11:8]+VB[11:8]
	//0x21,HBLANK_BASE & 0xff,
	//0x22,VBLANK_BASE & 0xff,
	0x23,0x00,
	0x24,0x00,
	0x25,0x67,
	0x26,0x00,
	0x27,0x00,
	0x28,0x00,
	0x29,0x00,
	0x2a,0x00,
	0x2b,0x00,
	0x2c,0x00,
	0x2d,0x00,
	0x2e,0x00,
	0x2f,0x00,
	0x30,0x01,
	0x31,0xf4,
	0x32,0x16,
	0x33,0x06,
	0x34,0x7d,
	0x35,0x96,
	0x36,0x7d,
	0x37,0x96,
	0x38,0x00,
	0x39,0x00,
	0x3a,0x00,
	0x3b,0x00,
	0x3c,0x00,
	0x3d,0x00,
	0x3e,0x00,
	0x3f,0x00,
	0x40,0x80,
	0x41,0x83,
	0x42,0x80,
	0x43,0xc0,
	0x44,0x48,
	0x45,0x28,
	0x46,0x08,
	0x47,0x15,
	0x48,0x14,
	0x49,0x0c,
	0x4a,0x42,
	0x4b,0xc4,
	0x4c,0x3c,
	0x4d,0x50,
	0x4e,0x17,
	0x4f,0x8a,
	0x50,0x94,
	0x51,0x60,
	0x52,0x90,
	0x53,0x70,
	0x54,0x00,
	0x55,0x00,
	0x56,0x00,
	0x57,0x00,
	0x58,0x00,
	0x59,0x00,
	0x5a,0x00,
	0x5b,0x02,
	0x5c,0x33,
	0x5d,0xf8,
	0x5e,0x00,
	0x5f,0x00,
	0x60,0xc0,
	0x61,0x88,
	0x62,0x01,
	0x63,0x80,
	0x64,0x80,
	0x65,0xc8,
	0x66,0x8d,
	0x67,0xc3,
	0x68,0x88,
	0x69,0x90,
	0x6a,0x68,
	0x6b,0xa4,
	0x6c,0x72,
	0x6d,0x88,
	0x6e,0x77,
	0x6f,0xa8,
	0x70,0xd8,
	0x71,0x40,
	0x72,0x05,
	0x73,0x02,
	0x74,0x0c,
	0x75,0x60,
	0x76,0x64,
	0x77,0xa8,
	0x78,0x9a,
	0x79,0x00,
	0x7a,0xa0,
	0x7b,0x95,
	0x7c,0x80,
	0x7d,0x00,
	0x7e,0x00,
	0x7f,0x40,
	0x80,0xaf,
	0x81,0x19,
	0x82,0x3d,//0x1d,//
	0x83,0x00,
	0x84,0xff,
	0x85,0x00,
	0x86,0xa1,
	0x87,0x00,
	0x88,0x24,
	0x89,0x0f,
	0x8a,0x80,
	0x8b,0x80,
	0x8c,0x80,
	0x8d,0x80,
	0x8e,0x00,
	0x8f,0x00,
	0x90,0x00,
	0x91,0x00,
	0x92,0x44,
	0x93,0x0c,
	0x94,0x10,
	0x95,0x18,
	0x96,0x0c,
	0x97,0x10,
	0x98,0x14,
	0x99,0x18,
	0x9a,0x50,
	0x9b,0x00,
	0x9c,0x12,
	0x9d,0x10,
	0x9e,0x10,
	0x9f,0x12,
	0xa0,0x10,
	0xa1,0x10,
	0xa2,0x10,
	0xa3,0x10,
	0xa4,0xaa,
	0xa5,0xaa,
	0xa6,0xaa,
	0xa7,0xa9,
	0xa8,0x87,
	0xa9,0x22,
	0xaa,0x27,
	0xab,0x22,
	0xac,0x22,
	0xad,0x12,
	0xae,0x11,
	0xaf,0x98,
	0xb0,0x80,
	0xb1,0x00,
	0xb2,0x02,
	0xb3,0x0a,
	0xb4,0x18,
	0xb5,0x37,
	0xb6,0x54,
	0xb7,0x6d,
	0xb8,0x82,
	0xb9,0x95,
	0xba,0xa5,
	0xbb,0xb2,
	0xbc,0xca,
	0xbd,0xdf,
	0xbe,0xf0,
	0xbf,0xf8,
	0xc0,0xff,
	0xc1,0x3d,
	0xc2,0xc6,
	0xc3,0xfd,
	0xc4,0x10,
	0xc5,0x21,
	0xc6,0x10,
	0xc7,0xf3,
	0xc8,0xbd,
	0xc9,0x50,
	0xca,0x90,
	0xcb,0x28,
	0xcc,0x38,
	0xcd,0x06,
	0xce,0x06,
	0xcf,0x50,
	0xd0,0x50,
	0xd1,0x38,
	0xd2,0x86,
	0xd3,0x00,
	0xd4,0x10,
	0xd5,0x15,
	0xd6,0x13,
	0xd7,0x00,
	0xd8,0x00,
	0xd9,0x00,
	0xda,0x00,
	0xdb,0xff,
	0xdc,0x00,
	0xdd,0xff,
	0xde,0x00,
	0xdf,0xff,
	0xe0,0x00,
	0xe1,0x38,
	0xe2,0x66,
	0xe3,0x00,
	0xe4,0x00,
	0xe5,0x00,
	0xe6,0x44,
	0xe7,0x00,
	0xe8,0x00,
	0xe9,0x00,
	0xea,0x00,
	0xeb,0x00,
	0xec,0x00,
	0xed,0x00,
	0xee,0x00,
	0xef,0x00,
	0xf0,0x24,
	0xf1,0x00,
	0xf2,0x80,
	0xf3,0x00,
	0xf4,0xe0,
	0xf5,0x00,
	0xf6,0x00,
	0xf7,0x00,
	0xf8,0x00,
	0xf9,0x00,
	0xfa,0x00,
	0xfb,0x00,
	0xfc,0x00,
	0xfd,0x00,
	0xfe,0x00,
	0xff,0x00,     
-1,-1};

static void SIV121D_rotate(u32 r)
{
	unsigned char buf[2];
	buf[0] = 0x04;

	buf[1] = (r<<0);
//	sensor_iic_enable();
//	sensor_iic_info();		
	sensor_iic_write(buf);	

//	 sensor_iic_diable();	

}

static void SIV121D_hvblank(u32 h,u32 v)
{

	u32 i;
	const u8 t[][2] = {
		{0X20, ((h>>8)<<4)|(v>>8)},
		{0X21, h & 0xff},
		{0X22, v & 0xff},
	};

//	sensor_iic_enable();
//	sensor_iic_info();	

	for(i=0;i<6;i++)
		sensor_iic_write((u8 *)&t[i][0]);
//	 sensor_iic_diable();			
//	return (h<<16)|v;

}
SENSOR_OP_SECTION const Sensor_Op_t siv121d_cmd= 
{
	.rotate_adapt = {0},
	.hvb_adapt = {0x6a,0x20,0x6a,0x20},
	. mclk = 24000000,
	.p_fun_adapt = {SIV121D_rotate,SIV121D_hvblank,NULL},
};


SENSOR_HEADER_ITEM_SECTION const Sensor_Init_t siv121d_init=
{
	.sensor_struct_addr =	(u32 *)&siv121d_cmd, 
	.sensor_struct_size = sizeof(Sensor_Op_t),
	.sensor_init_tab_adr =	(u32 *)SIV121DInitTable,     
	.sensor_init_tab_size = sizeof(SIV121DInitTable),
	.id               =	0xde,                
	.w_cmd            =	0x66,                
	.r_cmd            =	0x67,                
	.addr_num         =	0x01,                
	.data_num         =	0x01,                
	.id_reg           =	0x01,                
};


#endif


