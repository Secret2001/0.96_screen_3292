#include "cmos_sensor.h"

#if DEV_SENSOR_NT99141 > 0



#define NT99141_I2C_BAUD        (20000)         //400K
#define NT99141_I2C_READ_ADDR   (0x55)
#define NT99141_I2C_WRITE_ADDR  (0x54)
#define NT99141_CHIP_ID_ADDR    (0x3000)//*/


#define __RAW_INTERFACE__


SENSOR_INIT_SECTION const unsigned char NT99141InitTable[]=
{
#if 0
	0x31,0x09,0x04,
	0x30,0x40,0x04,
	0x30,0x41,0x02,
	0x30,0x42,0xff,
	0x30,0x43,0x08,
	0x30,0x52,0xe0,
	0x30,0x53,0x0E,
	0x30,0x5f,0x33,
	0x31,0x00,0x07,
	0x31,0x06,0x03,
	0x31,0x05,0x01,
	0x31,0x08,0x05,
	0x31,0x10,0x22,
	0x31,0x11,0x57,
	0x31,0x12,0x22,
	0x31,0x13,0x55,
	0x31,0x14,0x05,
	0x31,0x35,0x00,
	0x32,0xf0,0x01,
	0x32,0x90,0x01,
	0x32,0x91,0x80,
	0x32,0x96,0x01,
	0x32,0x97,0x73,
  0x32,0x50,0xC0,  //CA
  0x32,0x51,0x01,  //Top boundary of R/G
  0x32,0x52,0x4F,  // 
  0x32,0x53,0x86,  //Bottom boundary of R/G
  0x32,0x54,0x00,  //Top boundary of B/G
  0x32,0x55,0xC7,  // 
  0x32,0x56,0x75,  //Bottom boundary of B/G
  0x32,0x57,0x46,
  0x32,0x58,0x0A,
  0x32,0x9B,0x31,  
  0x32,0xA1,0x00,  
  0x32,0xA2,0xE8,  
  0x32,0xA3,0x01,  
  0x32,0xA4,0xa8,  
  0x32,0xA5,0x01,  
  0x32,0xA6,0x61,  
  0x32,0xA7,0x01,  
  0x32,0xA8,0xE0, 
  0x32,0x10,0x03, //LSC
  0x32,0x11,0x03,
  0x32,0x12,0x03,
  0x32,0x13,0x03,
  0x32,0x14,0x01,
  0x32,0x15,0x01,
  0x32,0x16,0x01,
  0x32,0x17,0x01,
  0x32,0x18,0x01,
  0x32,0x19,0x01,
  0x32,0x1A,0x01,
  0x32,0x1B,0x01,       
  0x32,0x1C,0x00,       
  0x32,0x1D,0x00,       
  0x32,0x1E,0x00,       
  0x32,0x1F,0x00,
  0x32,0x32,0xC6, 
	0x32,0x70,0x00,  //[Gamma_DXWY] 
  0x32,0x71,0x0A, 
  0x32,0x72,0x14, 
  0x32,0x73,0x28, 
  0x32,0x74,0x3B, 
  0x32,0x75,0x4C, 
  0x32,0x76,0x6B, 
  0x32,0x77,0x86, 
  0x32,0x78,0x9D, 
  0x32,0x79,0xB0, 
  0x32,0x7A,0xCF, 
  0x32,0x7B,0xE1, 
  0x32,0x7C,0xEB, 
  0x32,0x7D,0xEF, 
  0x32,0x7E,0xF8,   
  0x32,0xB0,0x55,  //AE win
  0x32,0xB1,0x69,  //AE win
  0x32,0xB2,0xaa,  //AE win
  0x32,0xB3,0x55,  //AE win
	0x33,0x02,0x00,           
	0x33,0x03,0x4C,           
	0x33,0x04,0x00,           
	0x33,0x05,0x96,           
	0x33,0x06,0x00,           
	0x33,0x07,0x1D,           
	0x33,0x08,0x07,           
	0x33,0x09,0xC0,           
	0x33,0x0a,0x06,           
	0x33,0x0b,0xD6,           
	0x33,0x0c,0x01,           
	0x33,0x0d,0x6A,           
	0x33,0x0e,0x01,           
	0x33,0x0f,0x61,           
	0x33,0x10,0x06,           
	0x33,0x11,0xEA,           
	0x33,0x12,0x07,           
	0x33,0x13,0xB5,           
  0x33,0x26,0x02,
	0x32,0xf6,0x0f,
	0x32,0xf9,0x42,
	0x32,0xfa,0x24,
	0x33,0x25,0x4a,
	0x33,0x30,0x00,
	0x33,0x31,0x09,
	0x33,0x32,0x4f,//0x8f		//???1y????????????????2?????
	0x33,0x38,0x30,
	0x33,0x39,0x84,
	0x33,0x3a,0x48,
	0x33,0x3f,0x07,
  0x33,0x60,0x0b, //IQ_Param_Sel_0
  0x33,0x61,0x18, //IQ_Param_Sel_1
  0x33,0x62,0x1f, //IQ_Param_Sel_2
  0x33,0x63,0x37, //IQ_Auto_Control
  0x33,0x64,0x80, // CC_Ctrl_0 
  0x33,0x65,0x78, // CC_Ctrl_1 
  0x33,0x66,0x70, // CC_Ctrl_2 
  0x33,0x67,0x60, // CC_Ctrl_3 
  0x33,0x68,0x80, //Edge_Enhance_L_0
  0x33,0x69,0x78, //Edge_Enhance_L_1
  0x33,0x6A,0x70, //Edge_Enhance_L_2
  0x33,0x6B,0x60, //Edge_Enhance_L_3
  0x33,0x6C,0x00, //EE_Weight_H
  0x33,0x6D,0x20, //NR_DPC_Ratio_0
  0x33,0x6E,0x1C, //NR_DPC_Ratio_1
  0x33,0x6F,0x16, //NR_DPC_Ratio_2
  0x33,0x70,0x0E, //NR_DPC_Ratio_3
  0x33,0x71,0x32,  // NR_Weight_0 
  0x33,0x72,0x38, //NR_Weight_1
  0x33,0x73,0x3F, //NR_Weight_2
  0x33,0x74,0x3F, //NR_Weight_3
  0x33,0x75,0x0c, //NR_Thr_0
  0x33,0x76,0x10, //NR_Thr_1
  0x33,0x77,0x14, //NR_Thr_2
  0x33,0x78,0x1a, //NR_Thr_3
  0x33,0x8A,0x34, //GFilter_Ctrl_0
  0x33,0x8B,0x7F, //GF_Dark_Level_0
  0x33,0x8C,0x10, //GF_Comp_Max_0
  0x33,0x8D,0x23, //GFilter_Ctrl_1
  0x33,0x8E,0x7F, //GF_Dark_Level_1
  0x33,0x8F,0x14, //GF_Comp_Max_1
	0x33,0x75,0x10,
	0x33,0x76,0x14,
	0x33,0x77,0x18,
	0x33,0x78,0x20,
	0x30,0x12,0x02,
	0x30,0x13,0xd0,
	0x30,0x69,0x01,
	0x30,0x6a,0x02,
	0x32,0xBF,0x60, //[50Hz] 
	0x32,0xC0,0x60, 
	0x32,0xC1,0x60, 
	0x32,0xC2,0x60, 
	0x32,0xC3,0x00, 
	0x32,0xC4,0x2B, 
	0x32,0xC5,0x13, 
	0x32,0xC6,0x1F, 
	0x32,0xC7,0x00, 
	0x32,0xC8,0xE2, 
	0x32,0xC9,0x60, 
	0x32,0xCA,0x73, 
	0x32,0xCB,0x73, 
	0x32,0xCC,0x7F, 
	0x32,0xCD,0x7F, 
	0x32,0xDB,0x7C, 
	0x32,0x00,0x3E, 
	0x32,0x01,0x0F, 
	0x30,0x28,0x0E, 
	0x30,0x29,0x10, 
	0x30,0x2A,0x04, 
	0x30,0x22,0x24, 
	0x30,0x23,0x24, 
	0x30,0x02,0x00, 
	0x30,0x03,0x04, 
	0x30,0x04,0x00, 
	0x30,0x05,0x04, 
	0x30,0x06,0x05, 
	0x30,0x07,0x03, 
	0x30,0x08,0x02, 
	0x30,0x09,0xD3, 
	0x30,0x0A,0x06, 
	0x30,0x0B,0x7C, 
	0x30,0x0C,0x02, 
	0x30,0x0D,0xF1, 
	0x30,0x0E,0x05, 
	0x30,0x0F,0x00, 
	0x30,0x10,0x02, 
	0x30,0x11,0xD0, 	
	0x32,0xBB,0xa7, 	
	0x32,0xB8,0x3F, 
	0x32,0xB9,0x31, 
	0x32,0xBC,0x38, 
	0x32,0xBD,0x3C, 
	0x32,0xBE,0x34, 
	0x32,0x01,0x3F, 
	0x30,0x21,0x06,	
	0x30,0x60,0x01, 

#else
	0x31,0x09,0x04,
	0x30,0x40,0x04,
	0x30,0x41,0x02,
	0x30,0x42,0xff,
	0x30,0x43,0x08,
	0x30,0x52,0xe0,
	0x30,0x53,0x0E,
	0x30,0x5f,0x33,
	0x31,0x00,0x07,
	0x31,0x06,0x03,
	0x31,0x05,0x01,
	0x31,0x08,0x05,
	0x31,0x10,0x22,
	0x31,0x11,0x57,
	0x31,0x12,0x22,
	0x31,0x13,0x55,
	0x31,0x14,0x05,
	0x31,0x35,0x00,
	0x32,0xf0,0x50,//0x58//output format
	0x32,0x90,0x01,
	0x32,0x91,0x80,
	0x32,0x96,0x01,
	0x32,0x97,0x73,
	  0x32,0x50,0xC0,  //CA
	  0x32,0x51,0x01,  //Top boundary of R/G
	  0x32,0x52,0x4F,  // 
	  0x32,0x53,0x86,  //Bottom boundary of R/G
	  0x32,0x54,0x00,  //Top boundary of B/G
	  0x32,0x55,0xC7,  // 
	  0x32,0x56,0x75,  //Bottom boundary of B/G
	  0x32,0x57,0x46,
	  0x32,0x58,0x0A,
	  0x32,0x9B,0x31,  
	  0x32,0xA1,0x00,  
	  0x32,0xA2,0xE8,  
	  0x32,0xA3,0x01,  
	  0x32,0xA4,0xa8,  
	  0x32,0xA5,0x01,  
	  0x32,0xA6,0x61,  
	  0x32,0xA7,0x01,  
	  0x32,0xA8,0xE0, 
	  
	  0x32,0x10,0x03, //LSC
	  0x32,0x11,0x03,
	  0x32,0x12,0x03,
	  0x32,0x13,0x03,
	  0x32,0x14,0x01,
	  0x32,0x15,0x01,
	  0x32,0x16,0x01,
	  0x32,0x17,0x01,
	  0x32,0x18,0x01,
	  0x32,0x19,0x01,
	  0x32,0x1A,0x01,
	  0x32,0x1B,0x01,       
	  0x32,0x1C,0x00,       
	  0x32,0x1D,0x00,       
	  0x32,0x1E,0x00,       
	  0x32,0x1F,0x00,
	  0x32,0x32,0xC6,
	  
	  0x32,0x70,0x00,  //[Gamma_DXWY] 
	  0x32,0x71,0x0A, 
	  0x32,0x72,0x14, 
	  0x32,0x73,0x28, 
	  0x32,0x74,0x3B, 
	  0x32,0x75,0x4C, 
	  0x32,0x76,0x6B, 
	  0x32,0x77,0x86, 
	  0x32,0x78,0x9D, 
	  0x32,0x79,0xB0, 
	  0x32,0x7A,0xCF, 
	  0x32,0x7B,0xE1, 
	  0x32,0x7C,0xEB, 
	  0x32,0x7D,0xEF, 
	  0x32,0x7E,0xF8, 
	  
	  0x32,0xB0,0x55,  //AE win
	  0x32,0xB1,0x69,  //AE win
	  0x32,0xB2,0xaa,  //AE win
	  0x32,0xB3,0x55,  //AE win

	0x33,0x02,0x00,           
	0x33,0x03,0x4C,           
	0x33,0x04,0x00,           
	0x33,0x05,0x96,           
	0x33,0x06,0x00,           
	0x33,0x07,0x1D,           
	0x33,0x08,0x07,           
	0x33,0x09,0xC0,           
	0x33,0x0a,0x06,           
	0x33,0x0b,0xD6,           
	0x33,0x0c,0x01,           
	0x33,0x0d,0x6A,           
	0x33,0x0e,0x01,           
	0x33,0x0f,0x61,           
	0x33,0x10,0x06,           
	0x33,0x11,0xEA,           
	0x33,0x12,0x07,           
	0x33,0x13,0xB5,           
    0x33,0x26,0x02,
	0x32,0xf6,0x0f,
	0x32,0xf9,0x42,
	0x32,0xfa,0x24,
	0x33,0x25,0x4a,
	0x33,0x30,0x00,
	0x33,0x31,0x09,
	
//	0x33,0x32,0xAf,
	0x33,0x32,0x4f,//0x8f		//??ì?1y?è￡?è?à?￡??μ??éù??ì?μ???àí??2??÷??￡?
	
	0x33,0x38,0x30,
	0x33,0x39,0x84,
	0x33,0x3a,0x48,
	0x33,0x3f,0x07,


  0x33,0x60,0x0b, //IQ_Param_Sel_0
  0x33,0x61,0x18, //IQ_Param_Sel_1
  0x33,0x62,0x1f, //IQ_Param_Sel_2
  0x33,0x63,0x37, //IQ_Auto_Control
  0x33,0x64,0x80, // CC_Ctrl_0 
  0x33,0x65,0x78, // CC_Ctrl_1 
  0x33,0x66,0x70, // CC_Ctrl_2 
  0x33,0x67,0x60, // CC_Ctrl_3 
//  0x33,0x68,0x84, //Edge_Enhance_L_0
  0x33,0x68,0x80, //Edge_Enhance_L_0
//  0x33,0x69,0x80, //Edge_Enhance_L_1
  0x33,0x69,0x78, //Edge_Enhance_L_1
  0x33,0x6A,0x70, //Edge_Enhance_L_2
  0x33,0x6B,0x60, //Edge_Enhance_L_3
  0x33,0x6C,0x00, //EE_Weight_H
  0x33,0x6D,0x20, //NR_DPC_Ratio_0
  0x33,0x6E,0x1C, //NR_DPC_Ratio_1
  0x33,0x6F,0x16, //NR_DPC_Ratio_2
  0x33,0x70,0x0E, //NR_DPC_Ratio_3
  0x33,0x71,0x32,  // NR_Weight_0 
  0x33,0x72,0x38, //NR_Weight_1
  0x33,0x73,0x3F, //NR_Weight_2
  0x33,0x74,0x3F, //NR_Weight_3
  0x33,0x75,0x0c, //NR_Thr_0
  0x33,0x76,0x10, //NR_Thr_1
  0x33,0x77,0x14, //NR_Thr_2
  0x33,0x78,0x1a, //NR_Thr_3
  0x33,0x8A,0x34, //GFilter_Ctrl_0
  0x33,0x8B,0x7F, //GF_Dark_Level_0
  0x33,0x8C,0x10, //GF_Comp_Max_0
  0x33,0x8D,0x23, //GFilter_Ctrl_1
  0x33,0x8E,0x7F, //GF_Dark_Level_1
  0x33,0x8F,0x14, //GF_Comp_Max_1
	0x33,0x75,0x10,
	0x33,0x76,0x14,
	0x33,0x77,0x18,
	0x33,0x78,0x20,
	0x30,0x12,0x02,
	0x30,0x13,0xd0,
	0x30,0x69,0x01,
	0x30,0x6a,0x02,


//[YUYV_1280x720_25.00_30.00_Fps]

//[50Hz] 
	0x32, 0xBF, 0x60, 
	0x32, 0xC0, 0x60, 
	0x32, 0xC1, 0x60, 
	0x32, 0xC2, 0x60, 
	0x32, 0xC3, 0x00, 
	0x32, 0xC4, 0x2B, 
	0x32, 0xC5, 0x13, 
	0x32, 0xC6, 0x1F, 
	0x32, 0xC7, 0x00, 
	0x32, 0xC8, 0xE2, 
	0x32, 0xC9, 0x60, 
	0x32, 0xCA, 0x73, 
	0x32, 0xCB, 0x73, 
	0x32, 0xCC, 0x7F, 
	0x32, 0xCD, 0x7F, 
	0x32, 0xDB, 0x7C, 

	/*[60Hz]     
				 
	0x32, 0xBF, 0x60, 
	0x32, 0xC0, 0x63, 
	0x32, 0xC1, 0x63, 
	0x32, 0xC2, 0x63, 
	0x32, 0xC3, 0x00, 
	0x32, 0xC4, 0x2B, 
	0x32, 0xC5, 0x13, 
	0x32, 0xC6, 0x1F, 
	0x32, 0xC7, 0x00, 
	0x32, 0xC8, 0xBC, 
	0x32, 0xC9, 0x63, 
	0x32, 0xCA, 0x76, 
	0x32, 0xCB, 0x76, 
	0x32, 0xCC, 0x82, 
	0x32, 0xCD, 0x82, 
	0x32, 0xDB, 0x77,*/

	0x32, 0x00, 0x3E, 
	0x32, 0x01, 0x0f, 
	0x30, 0x28, 0x0E, 
	0x30, 0x29, 0x10, 
	0x30, 0x2A, 0x04, //
	0x30, 0x22, 0x24, 
	0x30, 0x23, 0x24, 
	0x30, 0x02, 0x00, 
	0x30, 0x03, 0x04, 
	0x30, 0x04, 0x00, 
	0x30, 0x05, 0x04,
	
	0x30, 0x06, 0x05, 
	0x30, 0x07, 0x03, 
	0x30, 0x08, 0x02, 
	0x30, 0x09, 0xD3,/**/

	/*0x30, 0x06, 0x02, 
	0x30, 0x07, 0x83, 
	0x30, 0x08, 0x01, 
	0x30, 0x09, 0x6b, 
	0x30, 0x06, 0x02, 
	0x30, 0x07, 0x83, 
	0x30, 0x08, 0x01, 
	0x30, 0x09, 0xE3,*/

	0x30, 0x0A, 0x07, //0x06
	0x30, 0x0B, 0x80, //0x7c //0x10
	0x30, 0x0C, 0x02, //0x02
	0x30, 0x0D, 0xe6, //0xf1
	0x30, 0x0E, 0x05, 
	0x30, 0x0F, 0x00, 
	0x30, 0x10, 0x02, 
	0x30, 0x11, 0xD0, 

	0x32,0xBB,0xa7, 
	//=======light level setting====step to set all reg====


	0x32,0xB8,0x3F, 
	0x32,0xB9,0x31, 
	0x32,0xBC,0x38, 
	0x32,0xBD,0x3C, 
	0x32,0xBE,0x34, 

	/*
	0x32,0xB8,0x44, 
	0x32,0xB9,0x34, 
	0x32,0xBC,0x3c, 
	0x32,0xBD,0x40, 
	0x32,0xBE,0x38,*/
	//=======end light level==========

	0x32, 0x01, 0x3F, 
	
	
#ifdef __RAW_INTERFACE__
	0x30, 0x24, 0x02, //vsync = 0,hsync = 1
	0x32, 0x00, 0x00, 
	0x32, 0x01, 0x00, 
	0x30, 0x12, 0x02,
	0x30, 0x13, 0xd0,//exposure
	0x30, 0x40, 0x04,
	0x30, 0x41, 0x03,
	
	0x30, 0x15, 0x08, 
	0x30, 0x17, 0x06, 
	0x30, 0x19, 0x06, 
	0x30, 0x1b, 0x0d,//*/
	/*0x30, 0x15, 0x10, 
	0x30, 0x17, 0x10, 
	0x30, 0x19, 0x10, 
	0x30, 0x1b, 0x10,//Agaim*/
	0x30, 0x44, 0x02, 
	0x30, 0x45, 0x05, 
	0x30, 0x46, 0x02, 
	0x30, 0x47, 0x05,
	0x30, 0x48, 0x02, 
	0x30, 0x49, 0x05, 
	0x30, 0x4a, 0x02, 
	0x30, 0x4b, 0x02,//*/offset
	
	0x30,0x0E,0x05,
	0x30,0x0F,0x00,
	0x30,0x10,0x02,
	0x30,0x11,0xD0,//*/imagesize
#endif
	0x30, 0x21, 0x06, 
	0x30, 0x25, 0x00, //colour bar:0x02
	0x30, 0x60, 0x01, 
#endif
	0xff,0xff,0xff,
};
_SEN_YGAMA_TABLE_ const u8 nt99141_ygama[_SEN_YGAMA_CLASSES_][256]={
{0xb,0x10,0x16,0x19,0x1d,0x21,0x24,0x27,0x2a,0x2e,0x30,0x33,0x35,0x38,0x3a,0x3d,0x3f,0x41,0x43,0x45,0x47,0x49,0x4b,0x4e,0x4f,0x51,0x53,0x55,0x57,0x59,0x5b,0x5d,
0x5f,0x60,0x62,0x64,0x65,0x67,0x69,0x6a,0x6c,0x6e,0x6f,0x71,0x73,0x74,0x76,0x77,0x79,0x7a,0x7c,0x7d,0x7f,0x80,0x82,0x83,0x85,0x86,0x87,0x89,0x8a,0x8b,0x8d,0x8e,
0x8f,0x91,0x92,0x93,0x95,0x96,0x97,0x98,0x9a,0x9b,0x9c,0x9d,0x9f,0xa0,0xa1,0xa2,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xab,0xac,0xad,0xae,0xaf,0xb1,0xb2,0xb3,0xb4,0xb5,
0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0xc0,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,
0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf5,0xf6,0xf6,
0xf7,0xf7,0xf8,0xf8,0xf9,0xf9,0xfa,0xfa,0xfb,0xfb,0xfc,0xfc,0xfd,0xfd,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},

{0xd,0x13,0x19,0x1d,0x21,0x25,0x28,0x2b,0x2e,0x31,0x33,0x36,0x39,0x3b,0x3e,0x41,0x43,0x45,0x47,0x49,0x4b,0x4d,0x4f,0x51,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,0x60,
0x62,0x63,0x65,0x66,0x68,0x69,0x6b,0x6d,0x6e,0x70,0x71,0x73,0x75,0x76,0x77,0x79,0x7a,0x7b,0x7d,0x7e,0x7f,0x81,0x82,0x83,0x85,0x86,0x87,0x89,0x8a,0x8b,0x8d,0x8e,
0x8f,0x91,0x92,0x93,0x95,0x96,0x97,0x98,0x99,0x9a,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,
0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc9,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,
0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdc,0xdd,0xde,0xdf,0xe0,0xe1,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xed,0xee,0xef,
0xf0,0xf1,0xf2,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},

{0x10,0x16,0x1c,0x20,0x24,0x28,0x2b,0x2e,0x31,0x35,0x37,0x3a,0x3c,0x3f,0x41,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x55,0x56,0x58,0x5a,0x5b,0x5d,0x5f,0x60,0x62,
0x64,0x65,0x67,0x68,0x6a,0x6b,0x6d,0x6e,0x70,0x71,0x73,0x74,0x76,0x77,0x78,0x7a,0x7b,0x7c,0x7e,0x7f,0x80,0x82,0x83,0x84,0x86,0x87,0x88,0x89,0x8b,0x8c,0x8d,0x8e,
0x90,0x91,0x92,0x93,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,
0xb2,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xca,0xcb,0xcc,0xcd,0xce,
0xcf,0xd0,0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdb,0xdc,0xdd,0xde,0xdf,0xe0,0xe1,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe7,0xe8,0xe9,
0xea,0xea,0xeb,0xec,0xed,0xed,0xee,0xef,0xf0,0xf0,0xf1,0xf2,0xf3,0xf3,0xf4,0xf5,0xf6,0xf6,0xf6,0xf7,0xf7,0xf7,0xf8,0xf8,0xf9,0xf9,0xf9,0xfa,0xfa,0xfa,0xfb,0xfb,
0xfc,0xfc,0xfc,0xfd,0xfd,0xfd,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},

{0x13,0x19,0x1f,0x23,0x27,0x2c,0x2f,0x32,0x35,0x39,0x3b,0x3e,0x40,0x43,0x45,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x59,0x5b,0x5d,0x5e,0x60,0x62,0x63,0x65,
0x67,0x68,0x69,0x6b,0x6c,0x6e,0x6f,0x70,0x72,0x73,0x75,0x76,0x78,0x79,0x7a,0x7c,0x7d,0x7e,0x80,0x81,0x82,0x84,0x85,0x86,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
0x90,0x91,0x92,0x93,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa2,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,
0xb1,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbc,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc2,0xc3,0xc4,0xc5,0xc6,0xc6,0xc7,0xc8,0xc9,0xca,0xca,
0xcb,0xcc,0xcd,0xce,0xce,0xcf,0xd0,0xd1,0xd2,0xd2,0xd3,0xd4,0xd5,0xd5,0xd6,0xd7,0xd8,0xd8,0xd9,0xda,0xdb,0xdb,0xdc,0xdd,0xde,0xde,0xdf,0xe0,0xe1,0xe1,0xe2,0xe3,
0xe3,0xe4,0xe5,0xe5,0xe6,0xe7,0xe8,0xe8,0xe9,0xea,0xea,0xeb,0xec,0xec,0xed,0xee,0xef,0xef,0xf0,0xf1,0xf1,0xf2,0xf3,0xf3,0xf4,0xf5,0xf5,0xf6,0xf7,0xf7,0xf8,0xf9,
0xf9,0xfa,0xfb,0xfb,0xfc,0xfd,0xfd,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},

{0x16,0x1c,0x23,0x27,0x2b,0x30,0x33,0x36,0x39,0x3c,0x3e,0x41,0x43,0x46,0x48,0x4b,0x4d,0x4f,0x51,0x53,0x55,0x57,0x59,0x5b,0x5c,0x5e,0x60,0x61,0x63,0x65,0x66,0x68,
0x6a,0x6b,0x6c,0x6e,0x6f,0x70,0x72,0x73,0x74,0x76,0x77,0x78,0x7a,0x7b,0x7c,0x7d,0x7f,0x80,0x81,0x82,0x84,0x85,0x86,0x87,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,
0x91,0x92,0x93,0x94,0x96,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
0xb0,0xb0,0xb1,0xb2,0xb3,0xb4,0xb4,0xb5,0xb6,0xb7,0xb8,0xb8,0xb9,0xba,0xbb,0xbc,0xbc,0xbd,0xbe,0xbf,0xc0,0xc0,0xc1,0xc2,0xc3,0xc3,0xc4,0xc5,0xc6,0xc6,0xc7,0xc8,
0xc9,0xc9,0xca,0xcb,0xcc,0xcc,0xcd,0xce,0xcf,0xcf,0xd0,0xd0,0xd1,0xd2,0xd2,0xd3,0xd4,0xd4,0xd5,0xd6,0xd6,0xd7,0xd8,0xd8,0xd9,0xda,0xda,0xdb,0xdc,0xdc,0xdd,0xdd,
0xde,0xdf,0xdf,0xe0,0xe1,0xe1,0xe2,0xe3,0xe3,0xe4,0xe5,0xe5,0xe6,0xe7,0xe7,0xe8,0xe9,0xe9,0xea,0xea,0xeb,0xec,0xec,0xed,0xee,0xee,0xef,0xef,0xf0,0xf1,0xf1,0xf2,
0xf3,0xf3,0xf4,0xf4,0xf5,0xf6,0xf6,0xf7,0xf8,0xf8,0xf8,0xf8,0xf9,0xf9,0xf9,0xfa,0xfa,0xfa,0xfa,0xfb,0xfb,0xfb,0xfc,0xfc,0xfc,0xfc,0xfd,0xfd,0xfd,0xfe,0xfe,0xfe,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},

{0x19,0x1f,0x26,0x2a,0x2e,0x33,0x36,0x39,0x3c,0x40,0x42,0x45,0x47,0x4a,0x4c,0x4f,0x50,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,0x5f,0x61,0x62,0x64,0x65,0x67,0x68,0x6a,
0x6c,0x6d,0x6e,0x70,0x71,0x72,0x74,0x75,0x76,0x78,0x79,0x7a,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x83,0x84,0x85,0x86,0x87,0x88,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,
0x92,0x93,0x94,0x95,0x96,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,
0xaf,0xaf,0xb0,0xb1,0xb2,0xb2,0xb3,0xb4,0xb5,0xb5,0xb6,0xb7,0xb8,0xb8,0xb9,0xba,0xbb,0xbb,0xbc,0xbd,0xbe,0xbe,0xbf,0xc0,0xc0,0xc1,0xc2,0xc2,0xc3,0xc4,0xc5,0xc5,
0xc6,0xc7,0xc7,0xc8,0xc9,0xc9,0xca,0xcb,0xcc,0xcc,0xcd,0xcd,0xce,0xcf,0xcf,0xd0,0xd0,0xd1,0xd2,0xd2,0xd3,0xd3,0xd4,0xd5,0xd5,0xd6,0xd6,0xd7,0xd8,0xd8,0xd9,0xd9,
0xda,0xdb,0xdb,0xdc,0xdc,0xdd,0xde,0xde,0xdf,0xdf,0xe0,0xe1,0xe1,0xe2,0xe2,0xe3,0xe4,0xe4,0xe5,0xe5,0xe6,0xe6,0xe7,0xe7,0xe8,0xe8,0xe9,0xe9,0xea,0xeb,0xeb,0xec,
0xec,0xed,0xed,0xee,0xee,0xef,0xef,0xf0,0xf1,0xf1,0xf2,0xf2,0xf3,0xf3,0xf4,0xf4,0xf5,0xf5,0xf6,0xf6,0xf7,0xf8,0xf8,0xf9,0xf9,0xfa,0xfa,0xfb,0xfb,0xfc,0xfc,0xfd,
0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},

{0x1d,0x23,0x2a,0x2e,0x32,0x37,0x3a,0x3d,0x40,0x44,0x46,0x48,0x4b,0x4d,0x4f,0x52,0x53,0x55,0x57,0x59,0x5b,0x5d,0x5f,0x61,0x62,0x64,0x65,0x67,0x68,0x6a,0x6b,0x6d,
0x6f,0x70,0x71,0x72,0x74,0x75,0x76,0x77,0x79,0x7a,0x7b,0x7c,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,
0x93,0x94,0x95,0x96,0x97,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa1,0xa2,0xa3,0xa4,0xa5,0xa5,0xa6,0xa7,0xa8,0xa9,0xa9,0xaa,0xab,0xac,0xad,
0xae,0xae,0xaf,0xb0,0xb0,0xb1,0xb2,0xb2,0xb3,0xb4,0xb5,0xb5,0xb6,0xb7,0xb7,0xb8,0xb9,0xb9,0xba,0xbb,0xbc,0xbc,0xbd,0xbd,0xbe,0xbf,0xbf,0xc0,0xc1,0xc1,0xc2,0xc3,
0xc3,0xc4,0xc5,0xc5,0xc6,0xc7,0xc7,0xc8,0xc9,0xc9,0xca,0xca,0xcb,0xcc,0xcc,0xcd,0xcd,0xce,0xcf,0xcf,0xd0,0xd0,0xd1,0xd2,0xd2,0xd3,0xd3,0xd4,0xd5,0xd5,0xd6,0xd6,
0xd7,0xd7,0xd8,0xd8,0xd9,0xd9,0xda,0xdb,0xdb,0xdc,0xdc,0xdd,0xdd,0xde,0xde,0xdf,0xe0,0xe0,0xe1,0xe1,0xe2,0xe2,0xe3,0xe3,0xe4,0xe4,0xe5,0xe5,0xe6,0xe6,0xe7,0xe7,
0xe8,0xe8,0xe9,0xe9,0xea,0xea,0xeb,0xeb,0xec,0xec,0xec,0xed,0xed,0xee,0xee,0xef,0xef,0xf0,0xf0,0xf1,0xf1,0xf1,0xf2,0xf2,0xf3,0xf3,0xf4,0xf4,0xf5,0xf5,0xf6,0xf6,
0xf7,0xf7,0xf8,0xf8,0xf9,0xf9,0xfa,0xfa,0xfb,0xfb,0xfc,0xfc,0xfd,0xfd,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},

{0x21,0x27,0x2e,0x32,0x36,0x3b,0x3e,0x41,0x44,0x47,0x49,0x4c,0x4e,0x51,0x53,0x56,0x57,0x59,0x5b,0x5d,0x5e,0x60,0x62,0x64,0x65,0x67,0x68,0x6a,0x6b,0x6d,0x6e,0x70,
0x72,0x73,0x74,0x75,0x76,0x77,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8d,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,
0x94,0x95,0x96,0x97,0x98,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9d,0x9e,0x9f,0xa0,0xa1,0xa2,0xa2,0xa3,0xa4,0xa5,0xa5,0xa6,0xa7,0xa8,0xa8,0xa9,0xaa,0xab,0xab,0xac,0xad,
0xae,0xae,0xaf,0xaf,0xb0,0xb1,0xb1,0xb2,0xb3,0xb3,0xb4,0xb5,0xb5,0xb6,0xb7,0xb7,0xb8,0xb9,0xb9,0xba,0xbb,0xbb,0xbc,0xbc,0xbd,0xbe,0xbe,0xbf,0xbf,0xc0,0xc1,0xc1,
0xc2,0xc2,0xc3,0xc4,0xc4,0xc5,0xc5,0xc6,0xc7,0xc7,0xc8,0xc8,0xc9,0xc9,0xca,0xca,0xcb,0xcb,0xcc,0xcd,0xcd,0xce,0xce,0xcf,0xcf,0xd0,0xd0,0xd1,0xd2,0xd2,0xd3,0xd3,
0xd4,0xd4,0xd5,0xd5,0xd6,0xd6,0xd7,0xd7,0xd8,0xd8,0xd9,0xd9,0xda,0xda,0xdb,0xdb,0xdc,0xdc,0xdc,0xdd,0xdd,0xde,0xde,0xdf,0xdf,0xe0,0xe0,0xe1,0xe1,0xe1,0xe2,0xe2,
0xe3,0xe3,0xe4,0xe4,0xe5,0xe5,0xe6,0xe6,0xe7,0xe7,0xe7,0xe8,0xe8,0xe9,0xe9,0xea,0xea,0xeb,0xeb,0xec,0xec,0xec,0xed,0xed,0xee,0xee,0xef,0xef,0xf0,0xf0,0xf1,0xf1,
0xf2,0xf2,0xf2,0xf3,0xf3,0xf4,0xf4,0xf5,0xf5,0xf5,0xf6,0xf6,0xf7,0xf7,0xf8,0xf8,0xf9,0xf9,0xf9,0xfa,0xfa,0xfb,0xfb,0xfb,0xfc,0xfc,0xfd,0xfd,0xfd,0xfe,0xfe,0xff},
};//*/

_SEN_RGBGAMA_TABLE_ const u8 nt99141_rgbgama[_SEN_RGBGAMA_CLASSES_][256] = {
{0x0,0x0,0x0,0x0,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x9,0xa,0xa,0xb,0xc,0xd,0xd,0xe,0xf,0xf,0x10,0x11,0x11,0x12,
0x13,0x13,0x14,0x15,0x16,0x17,0x18,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x22,0x23,0x24,0x25,0x26,0x27,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2c,
0x2d,0x2e,0x2f,0x30,0x31,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,
0x4c,0x4d,0x4e,0x4f,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,
0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8b,0x8c,0x8d,0x8e,
0x8f,0x90,0x91,0x92,0x93,0x94,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xaf,0xb0,0xb1,0xb2,
0xb3,0xb4,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbd,0xbe,0xbf,0xc0,0xc1,0xc3,0xc4,0xc5,0xc6,0xc7,0xc9,0xca,0xcb,0xcc,0xcd,0xcf,0xd0,0xd1,0xd2,0xd3,0xd5,0xd6,0xd7,0xd8,
0xda,0xdb,0xdc,0xdd,0xde,0xdf,0xe1,0xe2,0xe3,0xe4,0xe5,0xe7,0xe8,0xe9,0xea,0xeb,0xed,0xee,0xef,0xf0,0xf1,0xf3,0xf4,0xf5,0xf6,0xf7,0xf9,0xfa,0xfb,0xfc,0xfd,0xff},
{0x0,0x0,0x1,0x1,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x7,0x8,0x9,0xa,0xa,0xb,0xc,0xd,0xd,0xe,0xf,0x10,0x10,0x11,0x12,0x13,0x13,0x14,0x15,0x16,
0x17,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,
0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,0x50,0x51,
0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,0x60,0x61,0x62,0x63,0x64,0x65,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,
0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x91,0x92,0x93,0x94,
0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa2,0xa3,0xa4,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,
0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,
0xdc,0xdd,0xde,0xdf,0xe0,0xe1,0xe2,0xe3,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xee,0xef,0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xff},

{0x0,0x0,0x1,0x2,0x3,0x4,0x4,0x5,0x6,0x7,0x7,0x8,0x9,0xa,0xb,0xc,0xc,0xd,0xe,0xf,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,
0x1c,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
0x3a,0x3b,0x3c,0x3d,0x3e,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,
0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0x95,0x97,0x98,0x99,0x9a,
0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,
0xbc,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc3,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,
0xde,0xdf,0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xef,0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xff},

{0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,
0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,
0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,0x60,
0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,
0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,
0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0xc0,
0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,0xe0,
0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,0xf0,0xf1,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff},

{0x1,0x4,0x7,0x9,0xc,0xf,0x11,0x14,0x16,0x19,0x1b,0x1d,0x20,0x22,0x24,0x27,0x29,0x2b,0x2e,0x30,0x32,0x35,0x37,0x3a,0x3c,0x3e,0x40,0x42,0x45,0x47,0x49,0x4b,
0x4e,0x50,0x52,0x54,0x56,0x58,0x5b,0x5d,0x5f,0x61,0x63,0x65,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x75,0x77,0x79,0x7b,0x7d,0x7f,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8f,0x91,
0x93,0x95,0x97,0x99,0x9c,0x9e,0xa0,0xa2,0xa4,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb2,0xb5,0xb7,0xb9,0xbb,0xbd,0xbf,0xc1,0xc3,0xc6,0xc8,0xca,0xcc,0xce,0xd0,0xd2,0xd4,
0xd7,0xd9,0xdb,0xdd,0xdf,0xe1,0xe3,0xe5,0xe7,0xe9,0xeb,0xed,0xef,0xf1,0xf3,0xf5,0xf7,0xf9,0xfb,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},


{0x2,0x5,0x9,0xb,0xe,0x11,0x13,0x16,0x19,0x1c,0x1e,0x21,0x23,0x26,0x28,0x2b,0x2d,0x2f,0x31,0x34,0x36,0x38,0x3a,0x3d,0x3f,0x41,0x43,0x45,0x48,0x4a,0x4c,0x4e,
0x51,0x53,0x55,0x57,0x59,0x5b,0x5d,0x5f,0x61,0x63,0x65,0x67,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,0x80,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8e,0x90,
0x92,0x94,0x96,0x98,0x9a,0x9b,0x9d,0x9f,0xa1,0xa3,0xa5,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb1,0xb3,0xb5,0xb7,0xb9,0xbb,0xbd,0xbf,0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,
0xce,0xcf,0xd1,0xd3,0xd5,0xd7,0xd8,0xda,0xdc,0xde,0xe0,0xe1,0xe3,0xe5,0xe7,0xe9,0xea,0xec,0xee,0xf0,0xf2,0xf2,0xf3,0xf3,0xf4,0xf5,0xf5,0xf6,0xf7,0xf7,0xf8,0xf9,
0xf9,0xfa,0xfb,0xfb,0xfc,0xfd,0xfd,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},

{0x3,0x7,0xb,0xe,0x11,0x14,0x16,0x19,0x1c,0x1f,0x21,0x24,0x26,0x29,0x2b,0x2e,0x30,0x32,0x34,0x37,0x39,0x3b,0x3d,0x40,0x42,0x44,0x46,0x48,0x4b,0x4d,0x4f,0x51,
0x54,0x55,0x57,0x59,0x5b,0x5d,0x5f,0x61,0x63,0x65,0x67,0x69,0x6b,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,0x80,0x82,0x83,0x85,0x87,0x89,0x8b,0x8d,0x8e,
0x90,0x92,0x94,0x96,0x98,0x99,0x9b,0x9d,0x9f,0xa0,0xa2,0xa4,0xa6,0xa7,0xa9,0xab,0xad,0xae,0xb0,0xb1,0xb3,0xb5,0xb6,0xb8,0xba,0xbb,0xbd,0xbe,0xc0,0xc2,0xc3,0xc5,
0xc7,0xc8,0xca,0xcb,0xcd,0xcf,0xd0,0xd2,0xd4,0xd5,0xd7,0xd9,0xda,0xdc,0xde,0xdf,0xe1,0xe3,0xe4,0xe6,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xf0,0xf1,0xf2,0xf3,0xf4,
0xf5,0xf6,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
{0x5,0x9,0xd,0x10,0x13,0x17,0x1a,0x1d,0x20,0x23,0x25,0x28,0x2a,0x2d,0x2f,0x32,0x34,0x36,0x38,0x3b,0x3d,0x3f,0x41,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,
0x56,0x57,0x59,0x5b,0x5d,0x5f,0x61,0x63,0x65,0x67,0x69,0x6b,0x6d,0x6e,0x70,0x72,0x74,0x75,0x77,0x79,0x7b,0x7c,0x7e,0x80,0x82,0x83,0x85,0x87,0x88,0x8a,0x8c,0x8d,
0x8f,0x91,0x92,0x94,0x96,0x97,0x99,0x9b,0x9c,0x9e,0xa0,0xa1,0xa3,0xa5,0xa6,0xa8,0xaa,0xab,0xad,0xae,0xb0,0xb1,0xb3,0xb4,0xb6,0xb7,0xb9,0xba,0xbc,0xbd,0xbf,0xc0,
0xc2,0xc3,0xc4,0xc6,0xc7,0xc9,0xca,0xcc,0xcd,0xcf,0xd0,0xd1,0xd3,0xd4,0xd6,0xd7,0xd9,0xda,0xdc,0xdd,0xdf,0xe0,0xe1,0xe3,0xe4,0xe6,0xe7,0xe8,0xea,0xeb,0xed,0xee,
0xef,0xf1,0xf2,0xf4,0xf5,0xf6,0xf8,0xf9,0xfb,0xfb,0xfb,0xfb,0xfb,0xfc,0xfc,0xfc,0xfc,0xfc,0xfd,0xfd,0xfd,0xfd,0xfd,0xfe,0xfe,0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}
};


/*******************************************************************************
* Function Name  : u8sensor_ReadID
* Description    : read sensor chip ID
* Input          : None
* Output         : None
* Return         : sensor chip ID
*******************************************************************************/

static void NT99141_rotate(u32 r)
{
//	sensor_iic_enable();
//	sensor_iic_info();		

	if(0 == r)
	{
		u8 rot_buf[3];
		rot_buf[0] = 0x30;
		rot_buf[1] = 0x22;
		rot_buf[2] = 0x24;
		sensor_iic_write(rot_buf);
//		deg_Printf("sensor_rotate 0 \n");
	}
	else if(1 == r)
	{
		u8 rot_buf[3];
		rot_buf[0] = 0x30;
		rot_buf[1] = 0x22;
		rot_buf[2] = 0x27;
		sensor_iic_write(rot_buf);
//		deg_Printf("sensor_rotate 180 \n");
	}

	if(0 == r)
	{
		u8 rot_buf[3];
		rot_buf[0] = 0x30;
		rot_buf[1] = 0x22;
		rot_buf[2] = 0x27;
		sensor_iic_write(rot_buf);
//		deg_Printf("sensor_rotate 0 \n");
	}
	else if(1 == r)
	{

		u8 rot_buf[3];
		rot_buf[0] = 0x30;
		rot_buf[1] = 0x22;
		rot_buf[2] = 0x24;
		sensor_iic_write(rot_buf);
//		deg_Printf("sensor_rotate 180 \n");
	}
	
//   sensor_iic_diable();
}
/*
static u32 sensor_NT99141_exp_rd(void)
{
	u8 iicbuf[9] = {0x30,0x12,0x00,0x30,0x13,0x00,0x30,0x60,0x01};
	u16 temp;

 //  sensor_iic_enable();
 //  sensor_iic_info();  
	 temp = sensor_iic_read(iicbuf)<<8;
	 temp|= sensor_iic_read(iicbuf+2);
 // sensor_iic_disable();
	 return temp;

}*/
static void sensor_NT99141_exp_wr(u32 EV)
{
	u8 iicbuf[9] = {0x30,0x12,0x00,0x30,0x13,0x00,0x30,0x60,0x01};
	iicbuf[1] = ((EV >> 8) & 0xff);
	iicbuf[3] = (EV & 0xff);
 //  sensor_iic_enable();
 //  sensor_iic_info();  	
	sensor_iic_write(iicbuf);
	sensor_iic_write(iicbuf+3);	
	sensor_iic_write(iicbuf+6);	
 // sensor_iic_disable();	
}
static void sensor_NT99141_gain_wr(u32 EV)
{
//	sensor_iic_enable();
//	sensor_iic_info();

// sensor_iic_disable();		
}
static void sensor_NT99141_exp_gain_wr(u32 exp,u32 gain)
{
	sensor_NT99141_exp_wr(exp);
	sensor_NT99141_gain_wr(gain);
}

SENSOR_OP_SECTION const Sensor_Op_t nt99141_cmd= 
{
	.typ =CSI_TYPE_RAW10,
	.pixelw = 1280,
	.pixelh= 720,
	.hsyn = 1,
	.vsyn = 0,
	.rduline = 0,//
	.colrarray = 0,//0:_RGRG_ 1:_GRGR_,2:_BGBG_,3:_GBGB_
	.rotate_adapt = {0},
	//.hvb_adapt = {0,0,0,0},
	. mclk = 16000000,
	.pclk_fir_en = 0,
	.pclk_inv_en = 0,
	.csi_tun = 0,
	.isp_all_mod = _ISP_MODE_DEFAULT_,
	//.hgrm_adapt = {256,0,8,240,480,800,1040,180,360,640,680,0x5a96a555,0x1a96a,0x1000000,0x0},//0x5a96a555,0x1a96a//0x2000000,0x0//0x0a815000,0x5
	.hgrm_adapt = {256,0,160,320,960,1120,200,400,640,680,0x4a86a444,0x446a,0x1000000,0x0,{8,9,10,11,12,13,14,15},{2,2,3,3,4,4,5,5}},//0.5,2,2
	.blc_adapt ={-4,0,0,-4},
	//.blc_adapt ={-8,-10,-10,-8},
	
	//.ddc_adapt = {1,1,7,3,2,16,1,0,0,35},
	.ddc_adapt = {1,{1,8,16,16,16,16,16,16},7,6,{1,4,8,8,8,8,8,8},16,1,{3,3,3,3,2,2,1,1},{2,2,2,2,1,1,0,0},{35,35,35,35,35,35,35,35}},//th 35
	.awb_adapt = {0x03,0x08,352,2977,1142,170,400,40,80,80,3,2,0xa,0xc0,0,{(265 << 20) | (256<< 10) | (360<< 0),
				 (281 << 20) | (256<< 10) | (341<< 0),(496 << 20) | (256<< 10) | (196<< 0),
				 (352 << 20) | (256<< 10) | (352<< 0),(352 << 20) | (256<< 10) | (352<< 0)}},//manual:0xff
	//.ccm_adapt = {0x38,0x00,0x04,0x04,0x44,-0x4,0x04,-0x4,0x40,0x00,0x00,0x00},
	.ccm_adapt = {0x38,0x00,0x04,
				  0x04,0x44,-0x4,
				  0x04,-0x4,0x40,0x0c,0x0c,0x0c},		 
	.ygama_adapt = {0,{11,14,17,17,17,17,17,17},0,0,0xff,144,208,96,144},
	.rgbgama_adapt = {0,{1,1,1,1,1,1,1,1},{20,12,12,12,12,12,12,12},0,0xff,0,0xff,0,0xff,64,224,4000},//2
	.ee_adapt = {0,{0x15,0x14,0x13,0x12,0x11,0x11,0x12,0x12},{8,8,8,8,8,8,8,8}},//1f,8
	.ccf_adapt = {1,4,0xb0,0x20,1,2,0xff},
	.lsc_adapt = {0xf9,0x280,0x168,0x80,0x80,0x80,0x80,0x80,0x80},
	.vde_adapt = {0x80,0x80,0x80,0x80,1,0,0,3,8,0,1,{0x50,0x48,0x40,0x40,0x40,0x40,0x40,0x40},
				  {0xa0,0x80,0x80,0x80,0x80,0x80,0x80,0x80},{0x50,0x80,0x80,0x80,0x80,0x80,0x80,0x80},
				  {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}},
	.md_adapt = {40,40,1,1,1280,180,720},
	.exp_adapt = {4,{24,40,60,80,80,80,100,136},3,16,320/*512*/,195*256,16,4,4000,0x4142},//
	.p_fun_adapt = {NT99141_rotate,NULL,sensor_NT99141_exp_gain_wr},
};

SENSOR_HEADER_ITEM_SECTION const Sensor_Init_t nt99141_init=
{
	.sensor_struct_addr =	(u32 *)&nt99141_cmd,  
	.sensor_struct_size = sizeof(Sensor_Op_t),
	.sensor_init_tab_adr =	(u32 *) NT99141InitTable,     
	.sensor_init_tab_size = sizeof(NT99141InitTable),
	.rgb_gamma_tab_adr =	(u32 *)nt99141_rgbgama,     
	.rgb_gamma_tab_size = sizeof(nt99141_rgbgama),
	.ygamma_tab_adr =	(u32 *)nt99141_ygama,     
	.ygamma_tab_size = sizeof(nt99141_ygama),
	.id               =	0x14,                 
	.w_cmd            =	0x54,                 
	.r_cmd            =	0x55,                 
	.addr_num         =	0x02,                 
	.data_num         =	0x01,                 
	.id_reg           =	0x3000                
};

#endif
