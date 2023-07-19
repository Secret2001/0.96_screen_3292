#include "cmos_sensor.h"

#if DEV_SENSOR_GC0307 > 0

SENSOR_INIT_SECTION const unsigned char GC0307InitTable[]=
{
/*
	0x01,// [7:0]:driver type,0x01:sensor whith ISP; 0x02:ISP; 0x03:sensor whithout isp;	
	
	0x01,0x6E,0x36,0x00,// [7:0]:XCLK(BE)
	0x00,0x01,0x86,0xA0,// [7:0]:BAUDRATE(BE)
	
	0x00,//	[7:0]:chip_ID_addr>>8,when AddrByteNum == 2; 0 when  AddrByteNum == 1
	0x00,// [7:0]:chip_ID_addr
	0x00,// [7:0]:chip_ID  
	0x99,//
	0x00,0x00,0x00,0x00,//resverd
	
	0x02,0x80,//image_width
	0x01,0xE0,//image_height
	0x43,// [7:0]:read ID
	0x42,// [7:0]:write ID
	0x01,//	[7:0]:AddrByteNum ; 
	0x01,// [7:0]:DataByteNum
	
	0x04,// [2:0]:ldo_config_para
	0x01,// [7:0]:ID nums
*/	
/*
	0xF0,0x00,
	0x43,0x00,
	0x44,0xA3,
	0x41,0x00,
	//0x01,(u32)HBLANK_BASE & 0xff,//HB[7:0]
	//0x02,(u32)VBLANK_BASE & 0xff,//VB[7:0]
	0x03,0x05,
	0x04,0x46,
	0x05,0x00,
	0x06,0x00,
	0x07,0x00,
	0x08,0x00,
	0x09,0x01,
	0x0f,0x82,
	//0x10,(((u32)VBLANK_BASE >> 8)<<4)|((u32)HBLANK_BASE >> 8), ////VB/HB [9:8]
	0x0A,0xE8,
	0x0B,0x02,
	0x0C,0x80,
	0x0D,0x22,
	0x0E,0x02,
	0x0F,0x82,
	0x45,0x24,
	
	0x11,0x05,
	0x12,0x70,
	0x13,0x80,
	0x14,0x00,
	0x15,0xBA,
	0x16,0x13,
	0x17,0x52,
	0x18,0xC0,
	0x19,0x06,
	0x1A,0x06,
	0x1B,0x00,
	0x1C,0x02,
	0x1D,0x02,
	0x1E,0x0D,
	0x1F,0x32,
	0x20,0x40,
	0x21,0x40,
	0x22,0x40,
	0x23,0x88,
	0x24,0x96,
	0x25,0x30,
	0x26,0xD0,
	0x27,0x00,
	//0x28,0x02,//AEC_exp_level_1bit11to8	
	//0x29,0x0d,//AEC_exp_level_1bit7to0	
	//0x2a,0x02,//AEC_exp_level_2bit11to8	
	//0x2b,0x0d,//AEC_exp_level_2bit7to0		   
	//0x2c,0x02,//AEC_exp_level_3bit11to8	659 - 8FPS,  8ca - 6FPS  //    
	//0x2d,0x0d,//AEC_exp_level_3bit7to0		   
	//0x2e,0x05,//AEC_exp_level_4bit11to8	4FPS 
	//0x2f,0xdc,//AEC_exp_level_4bit7to0   
	0x28,0x02,
	0x29,0x58,
	0x2A,0x03,
	0x2B,0x84,
	0x2C,0x03,
	0x2D,0x84,	
	0x2E,0x03,
	0x2F,0x84,
	0x30,0x20,
	0x31,0x00,
	0x32,0x04,
	0x33,0x90,
	0x34,0x10,
	0x35,0xD8,
	0x36,0x40,
	0x37,0x02,
	0x38,0x02,
	0x39,0x02,
	0x3A,0x02,
	0x3B,0x00,
	0x3C,0x00,
	0x3D,0x00,
	0x3E,0x00,
	0x3F,0x00,
	0x40,0x7E,
	0x42,0x10,
	0x43,0x40,
	0x44,0xE2,
	0x46,0x42,
	0x47,0x2C,//0x2C,
	0x48,0xC3,
	0x49,0x00,
	0x4A,0x00,
	0x4B,0x00,
	0x4C,0x00,
	0x4E,0x23,
	0x4F,0x01,
	0x50,0x0C,
	0x51,0x20,
	0x52,0x08,
	0x53,0x00,
	0x54,0x00,
	0x55,0x00,
	0x56,0x77,
	0x57,0x08,
	0x58,0x88,
	0x59,0x0F,
	0x5A,0x40,
	0x5B,0x3A,
	0x5C,0x68,
	0x5D,0x78,
	0x5E,0x00,
	0x5F,0x00,
	0x60,0x00,
	0x61,0x80,
	0x62,0x00,
	0x63,0x80,
	0x64,0x00,
	0x65,0x98,
	0x66,0x00,
	0x67,0x80,
	0x68,0x14,
	0x69,0x58,
	0x6A,0xF6,
	0x6B,0xFB,
	0x6C,0xF4,
	0x6D,0x5A,
	0x6E,0xE6,
	0x6F,0x00,
	0x70,0x14,
	0x71,0x1C,
	0x72,0x20,
	0x73,0x10,
	0x74,0x3C,
	0x75,0x52,
	0x76,0x00,
	0x77,0x80,
	0x78,0x00,
	0x79,0x00,
	0x7A,0x00,
	0x7B,0x40,
	0x7C,0x00,
	0x7D,0x0F,
	0x7E,0x35,
	0x7F,0x86,
	0x80,0x0C,
	0x81,0x0C,
	0x82,0x88,
	0x83,0x18,
	0x84,0x18,
	0x85,0x04,
	0x86,0x02,
	0x87,0x34,
	0x88,0x04,
	0x89,0x01,
	0x8A,0x50,
	0x8B,0x50,
	0x8C,0x07,
	0x8D,0x67,
	0x8E,0x02,
	0x8F,0x1A,
	0x90,0x2C,
	0x91,0x41,
	0x92,0x51,
	0x93,0x61,
	0x94,0x6F,
	0x95,0x7C,
	0x96,0x92,
	0x97,0xA4,
	0x98,0xB4,
	0x99,0xC0,
	0x9A,0xCC,
	0x9B,0xD5,
	0x9C,0xDE,
	0x9D,0xEB,
	0x9E,0xF5,
	0x9F,0xFC,
	0xA0,0x40,
	0xA1,0x40,
	0xA2,0x34,
	0xA3,0x34,
	0xA4,0xC8,
	0xA5,0x02,
	0xA6,0x28,
	0xA7,0x02,
	0xA8,0xEE,
	0xA9,0x12,
	0xAA,0x01,
	0xAB,0x20,
	0xAC,0xF0,
	0xAD,0x10,
	0xAE,0x18,
	0xAF,0x74,
	0xB0,0xBF,
	0xB1,0x20,
	0xB2,0x6C,
	0xB3,0x40,
	0xB4,0x04,
	0xB5,0x70,
	0xB6,0x40,
	0xB7,0x00,
	0xB8,0x38,
	0xB9,0xC3,
	0xBA,0x0F,
	
	0xBB,0x42,
	0xBC,0x60,
	0xBD,0x50,
	0xBE,0x50,
	
	0xBF,0x0C,
	0xC0,0x06,
	0xC1,0x60,
	0xC2,0xF1,
	0xC3,0x40,
	0xC4,0x1C,
	0xC5,0x56,
	0xC6,0x1D,
	
	0xC7,0x4B,
	0xC8,0x40,
	0xC9,0x44,
	
	0xCA,0x70,
	0xCB,0x70,
	0xCC,0x78,
	0xCD,0x80,
	0xCE,0x80,
	0xCF,0x80,
	
	0xF0,0x00,
	0x41,0x2F,	
	0xff,0x01,	
*/
	0xf0,0x00,
    0x43,0x00, // Initail Sequence Write In.//========= close output
    0x44,0xa3,
    0x40,0x10, //========= close some functions// open them after configure their parmameters
    0x41,0x00,          
    0x42,0x10,                      
    0x47,0x00, //mode1,                  
    0x48,0xc3, //mode2,  
    0x49,0x00, //dither_mode         
    0x4a,0x00, //clock_gating_en
    0x4b,0x00, //mode_reg3
    0x4E,0x23, //sync mode
    0x4F,0x01, //AWB, AEC, every N frame 
    //0x01,0xc0, //HB//========= frame timing
    //0x02,0x35, //VB//0c
    0x1C,0x00, //Vs_st
    0x1D,0x00, //Vs_et
    0x10,0x00, //high 4 bits of VB, HB
    0x11,0x05, //row_tail,  AD_pipe_number
    0x03,0x01, //row_start
    0x04,0x2c, //========= windowing
    0x05,0x00, //row_start
    0x06,0x00,
    0x07,0x00, //col start
    0x08,0x00,
    0x09,0x01, //win height
    0x0A,0xE8,
    0x0B,0x02, //win width, pixel array only 640
    0x0C,0x80, //========= analog
    0x0D,0x22, //rsh_width
    0x0E,0x02, //CISCTL mode2,  
    0x0F,0x82, //CISCTL mode1
    0x12,0x70, //7 hrst, 6_4 darsg,
    0x13,0x00, //7 CISCTL_restart, 0 apwd
    0x14,0x00, //NA
    0x15,0xba, //7_4 vref
    0x16,0x13, //5to4 _coln_r,  __1to0__da18
    0x17,0x52, //opa_r, ref_r, sRef_r
    0x18,0xc0, //analog_mode, best case for left band.
    0x1E,0x0d, //tsp_width          
    0x1F,0x32, //sh_delay//========= offset
    0x47,0x00, //7__test_image, __6__fixed_pga, //__5__auto_DN,__4__CbCr_fix, //__3to2__dark_sequence, __1__allow_pclk_vcync, __0__LSC_test_image
    0x19,0x06, //pga_o           
    0x1a,0x06, //pga_e           
    0x31,0x00, //4  //pga_oFFset ,   high 8bits of 11bits
    0x3B,0x00, //global_oFFset, low 8bits of 11bits
    0x59,0x0f, //offset_mode    
    0x58,0x88, //DARK_VALUE_RATIO_G,  DARK_VALUE_RATIO_RB
    0x57,0x08, //DARK_CURRENT_RATE
    0x56,0x77, //PGA_OFFSET_EVEN_RATIO, PGA_OFFSET_ODD_RATIO
    0x35,0xd8, //blk_mode//========= blk
    0x36,0x40, 
    0x3C,0x00,
    0x3D,0x00,
    0x3E,0x00,
    0x3F,0x00,
    0xb5,0x70,
    0xb6,0x40,
    0xb7,0x00,
    0xb8,0x38,
    0xb9,0xc3,        
    0xba,0x0f,
    0x7e,0x35,
    0x7f,0x86, 
    0x5c,0x68, //78
    0x5d,0x68, //88
    0x61,0x80, //manual_gain_g1  //========= manual_gain 
    0x63,0x80, //manual_gain_r
    0x65,0x98, //manual_gai_b, 0xa0=1.25, 0x98=1.1875
    0x67,0x80, //manual_gain_g2
    0x68,0x14, //global_manual_gain   2.4bits
    0x69,0x58, //54//58//=========CC _R
    0x6A,0xf6, //ff
    0x6B,0xfb, //fe
    0x6C,0xf4, //ff
    0x6D,0x5a, //5f
    0x6E,0xe6, //e1
    0x6f,0x00,                      
    0x70,0x14, //=========lsc     
    0x71,0x1c,
    0x72,0x20,
    0x73,0x10,  
    0x74,0x3c, //480/8
    0x75,0x52, // 640/8                                                                   
    0x7d,0x2f, //dn_mode  //=========dn     
    0x80,0x0c, //when auto_dn, check 7e,7f
    0x81,0x0c,
    0x82,0x44,                                                                                                   
    0x83,0x18, //DD_TH1    //dd                      
    0x84,0x18, //DD_TH2                       
    0x85,0x04, //DD_TH3                                                                                               
    0x87,0x34, //32 b DNDD_low_range X16,  DNDD_low_range_C_weight_center                                                                                         
    0x88,0x04, //=========intp-ee                                                      
    0x89,0x01,                                        
    0x8a,0x50, //60                                          
    0x8b,0x50, //60                                          
    0x8c,0x07,                                                                                               
    0x50,0x0c,                                  
    0x5f,0x3c,                                                                                                                 
    0x8e,0x02,                                                            
    0x86,0x02,                                                                                              
    0x51,0x20,                                                              
    0x52,0x08, 
    0x53,0x00,                                                                         
    0x77,0x80, //contrast_center   //========= YCP //contrast_center                                                                  
    0x78,0x00, //fixed_Cb                                                                          
    0x79,0x00, //fixed_Cr                                                                          
    0x7a,0x00, //luma_offset                                                                                                                                                             
    0x7b,0x40, //hue_cos                                                                           
    0x7c,0x00, //hue_sin  //saturation                                                                                  
    0xa0,0x40, //global_saturation
    0xa1,0x40, //luma_contrast                                                                     
    0xa2,0x34, //saturation_Cb//0x34                                                                   
    0xa3,0x34, //saturation_Cr//0x34                          
    0xa4,0xc8,                                                                
    0xa5,0x02,
    0xa6,0x28,                                                                            
    0xa7,0x02, //skin                                                                                               
    0xa8,0xee,                                                            
    0xa9,0x12,                                                            
    0xaa,0x01,                                                        
    0xab,0x20,                                                    
    0xac,0xf0,                                                        
    0xad,0x10, //========= ABS
    0xae,0x18, //  black_pixel_target_number 
    0xaf,0x74,
    0xb0,0xe0,    
    0xb1,0x20,
    0xb2,0x6c,
    0xb3,0x40,
    0xb4,0x04, //========= AWB 
    0xbb,0x42,
    0xbc,0x60,
    0xbd,0x50,
    0xbe,0x50,
    0xbf,0x0c,
    0xc0,0x06,
    0xc1,0x70,
    0xc2,0xf1, //f4
    0xc3,0x40,
    0xc4,0x1c, //18
    0xc5,0x56, 
    0xc6,0x1d,   
    0xca,0x56, //0x70
    0xcb,0x52, //0x70
    0xcc,0x66, //0x78
    0xcd,0x80, //R_ratio                                      
    0xce,0x80, //G_ratio  , cold_white white                                    
    0xcf,0x80, //B_ratio     //=========  aecT  
    0x20,0x06, //02
    0x21,0xc0,
    0x22,0x60,   
    0x23,0x88,
    0x24,0x96,
    0x25,0x30,
    0x26,0xd0,
    0x27,0x00,
    0x28,0x02, //AEC_exp_level_1bit11to8   
    0x29,0x0d, //AEC_exp_level_1bit7to0    
    0x2a,0x02, //AEC_exp_level_2bit11to8   
    0x2b,0x1d, //AEC_exp_level_2bit7to0           
    0x2c,0x02, //AEC_exp_level_3bit11to8   659 - 8FPS,  8ca - 6FPS  //    
    0x2d,0x0d, //AEC_exp_level_3bit7to0           
    0x2e,0x05, //AEC_exp_level_4bit11to8   4FPS 
    0x2f,0xdc, //AEC_exp_level_4bit7to0   
    0x30,0x20,                        
    0x31,0x00,                     
    0x32,0x1c,
    0x33,0x90,            
    0x34,0x10,  
    0xd0,0x34, //[2]  1  before gamma,  0 after gamma
    0xd1,0x50, //AEC_target_Y//0x50                         
    0xd2,0x61, //f2     
    0xd4,0x4b, //96
    0xd5,0x01, // 10 
    0xd6,0x4b, //antiflicker_step //96                      
    0xd7,0x03, //AEC_exp_time_min //10              
    0xd8,0x02, 
    0xdd,0x12, //========= measure window                                      
    0xe0,0x03,                       
    0xe1,0x02,                           
    0xe2,0x27,                               
    0xe3,0x1e,               
    0xe8,0x3b,                   
    0xe9,0x6e,                       
    0xea,0x2c,                   
    0xeb,0x50,                   
    0xec,0x73,  //========= close_frame                                                 
    0xed,0x00, //close_frame_num1 ,can be use to reduce FPS               
    0xee,0x00, //close_frame_num2  
    0xef,0x00, //close_frame_num
    0xf0,0x01, //select page1 
    0x00,0x20,                            
    0x01,0x20,                            
    0x02,0x20,                                  
    0x03,0x20,                          
    0x04,0x78,
    0x05,0x78,                   
    0x06,0x78,                                
    0x07,0x78,                                   
    //0x10,0x04,                        
    0x11,0x04,                            
    0x12,0x04,                        
    0x13,0x04,                            
    0x14,0x01,                            
    0x15,0x01,                            
    0x16,0x01,                       
    0x17,0x01,                       
    0x20,0x00,                    
    0x21,0x00,                    
    0x22,0x00,                        
    0x23,0x00,                        
    0x24,0x00,                    
    0x25,0x00,                        
    0x26,0x00,                    
    0x27,0x00,                        
    0x40,0x11, //=============================lscP 
    0x45,0x06,   
    0x46,0x06,           
    0x47,0x05,
    0x48,0x04,  
    0x49,0x03,       
    0x4a,0x03,
    0x62,0xd8,
    0x63,0x24,
    0x64,0x24,
    0x65,0x24,
    0x66,0xd8,
    0x67,0x24,
    0x5a,0x00,
    0x5b,0x00,
    0x5c,0x00,
    0x5d,0x00,
    0x5e,0x00,
    0x5f,0x00, //============================= ccP 
    0x69,0x03, //cc_mode//CC_G
    0x70,0x5d,
    0x71,0xed,
    0x72,0xff,
    0x73,0xe5,
    0x74,0x5f,
    0x75,0xe6, //CC_B
    0x76,0x41,
    0x77,0xef,
    0x78,0xff,
    0x79,0xff,
    0x7a,0x5f,
    0x7b,0xfa, //============================= AGP
    0x7e,0x00, 
    0x7f,0x00, //select gamma  
    0x80,0xc8, 
    0x81,0x06, 
    0x82,0x08, 
    0x83,0x13, // 相当于0x20对应的Gamma
    0x84,0x23, 
    0x85,0x35, 
    0x86,0x44, 
    0x87,0x53, 
    0x88,0x60, 
    0x89,0x6D, 
    0x8a,0x84, 
    0x8b,0x98, 
    0x8c,0xaa, 
    0x8d,0xb8, 
    0x8e,0xc6, 
    0x8f,0xd1, 
    0x90,0xdb, 
    0x91,0xea, 
    0x92,0xf5, 
    0x93,0xFb, //about gamma1 is hex r oct
    0x94,0x04, 
    0x95,0x0E, 
    0x96,0x1B, 
    0x97,0x28, 
    0x98,0x35, 
    0x99,0x41, 
    0x9a,0x4E, 
    0x9b,0x67, 
    0x9c,0x7E, 
    0x9d,0x94, 
    0x9e,0xA7, 
    0x9f,0xBA, 
    0xa0,0xC8, 
    0xa1,0xD4, 
    0xa2,0xE7, 
    0xa3,0xF4, 
    0xa4,0xFA,
    0xf0,0x00, //set back to page0  
    0x40,0x7e,
    0x41,0x2f,
    0x43,0x40,
    0x44,0xE2,
    0x0f,0xb2,
    0x45,0x27,
    0x47,0x2c,

-1,-1};

static void GC0307_rotate(u32 r)
{

	u8 buf[2];
	buf[0] = 0x0f;
	buf[1] = 0x82|(r<<4);
//	sensor_iic_enable();
//	sensor_iic_info();
	sensor_iic_write(buf);
// sensor_iic_disable();
}

static void GC0307_hvblank(u32 h,u32 v)
{
	u32 i;
	const u8 t[][2] = {
		{0x01,h & 0xff},//0x6a//0xde //HB[7:0]
		{0x02,v & 0xff},  //0x0c //VB[7:0]
		{0x10,((v >> 8)<<4)|(h >> 8)} //{0x0f,0x00}, //VB/HB [11:8]
	};
	for(i=0;i<3;i++)
		sensor_iic_write((u8 *)&t[i][0]);
}

SENSOR_OP_SECTION const Sensor_Op_t gc0307_cmd= 
{
	.rotate_adapt = {0},
	.hvb_adapt = {0x6a,0x70,0x6a,0x70},
	. mclk = 24000000,
	.p_fun_adapt = {GC0307_rotate,GC0307_hvblank,NULL},
};

SENSOR_HEADER_ITEM_SECTION const Sensor_Init_t gc0307_init=
{
	.sensor_struct_addr =	(u32 *)&gc0307_cmd,      
	.sensor_struct_size = sizeof(Sensor_Op_t),
	.sensor_init_tab_adr =	(u32 *)GC0307InitTable,     
	.sensor_init_tab_size = sizeof(GC0307InitTable),
	.id               =	0x99,                    
	.w_cmd            =	0x42,                    
	.r_cmd            =	0x43,                    
	.addr_num         =	0x01,                    
	.data_num         =	0x01,                    
	.id_reg           =	0x00                     
};

#endif

