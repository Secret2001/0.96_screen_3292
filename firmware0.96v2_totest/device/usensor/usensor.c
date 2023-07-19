/****************************************************************************
**
 **                              DEVICE
  ** *   **             THE APPOTECH MULTIMEDIA PROCESSOR
   **** **                  DEVICE G-SENSOR HEADER
  *** ***
 **  * **               (C) COPYRIGHT 2016 BUILDWIN 
**      **                         
         **         BuildWin SZ LTD.CO  ; VIDEO PROJECT TEAM
          **   
* File Name   : gsensor.c
* Author      : Mark.Douglas 
* Version     : V100
* Date        : 09/22/2016
* Description : This file is gsensor device file
*               
* History     : 
* 2016-09-22  : 
*      <1>.This is created by mark,set version as v100.
*      <2>.Add basic functions & information
******************************************************************************/
#include "usensor.h"


/*******************************************************************************
* Function Name  : gsensor_iic_read
* Description    : read gsensor data from iic bus
* Input          : INT8U sid : slave id
                     INT8U addr: read address
                     INT8U *data : data
* Output         : none                                            
* Return         : none
*******************************************************************************/





const u16 EX_SIV100BInitTable[][2]=
{
	{0x86,0xa1},//DPC EN
	{0x40,0x82},
	//EX_USB2IIC(13,0x25,0x00);
	//EX_USB2IIC(14,0x24,0x01);
	//EX_USB2IIC(15,0x35,0x64);
	{0x25,0xc8},
	{0x24,0xb3},
	{0x35,0x8c},
	
	{0x33,0x08},
	{0x41,0x78},
	{0x44,0x78},
	{0x45,0x22},
	{0x46,0x0c},
	{0x47,0x22},
	{0x80,0xaf},
	{0xa9,0x22},
	{0xaa,0x22},
	{0xaf,0xa1},
	{0xb0,0x81},
	{0xca,0x00},
	{0x04,0x01},
	{0xd7,0x10},
	{0xc8,0xc0},
	{-1,-1},
};



//sensor iic cmd(100b)
const u16 EX_7375SInitTable[][2]=
{
	0xf0,0x01,	  
	0xd4,0x11,	  
	0xf0,0x00,	  
	0x02,0x82,//dummy line
	0x04,0xF0,//dummy pixel
	
	0x0b,0x1c, // 0x0c 0' , 0x3c 180' (bit5 vflip ,bit4 mirror)
	
	0x30,0xa9,	  
	0x35,0xa8,	  
	0x68,0x55,	  
	0x69,0x55,	  
	0x71,0xde,	  
	0x72,0x40,//AE
	0x76,0x1c,//gl
	0x7a,0x70,//gl
	0x7c,0xf4,	  
	0x9e,0xb6,//D-
	0xb0,0x81, //A
	0xb1,0x21, //A
	0xb2,0x14,	  
	0xb3,0x25,	  
	0xb4,0x0b,	  
	0xb5,0x20,	  
	0xbc,0x1c,	  
	0xbd,0x11,	  
	0xc0,0x83,	  
	0xc1,0x66,	  
	0xc4,0x26,	  
	0xc7,0x00,	  
	0xe0,0x0f,	  
	0xe7,0x2f,	  
	0xe8,0x66,	  
	0xea,0xb0,	  
	0xd0,0x66, //e
	0xd4,0x4f, //ed
	0x41,0x10, //0x13,	//0x10,//	  
	0x42,0x20, //0x24,	//0x20,//	
	0x43,0x39, //0x41,	//0x39,//	
	0x44,0x5F, //0x6B,	//0x5F,//	
	0x45,0x7D, //0x8A,	//0x7D,//	
	0x46,0x93, //0xA0,	//0x93,//	
	0x47,0xA4, //0xB2,	//0xA4,//	
	0x48,0xB2, //0xC0,	//0xB2,//	
	0x49,0xBE, //0xCC,	//0xBE,//	
	0x4A,0xC8, //0xD5,	//0xC8,//	
	0x4B,0xD1, //0xDD,	//0xD1,//	
	0x4C,0xD9, //0xE4,	//0xD9,//	
	0x4D,0xE8, //0xF0,	//0xE8,//	
	0x4E,0xF4, //0xF8,	//0xF4,//	
	0x4F,0xFF, //0xFF,	//0xFF,//	
	0xf0,0x01,	 
	0x20,0x18,	  
	0x21,0xa0,	  
	0x22,0x08,	  
	0x23,0x94,	  
	0x24,0x28,	  
	0x25,0x94,	  
	0x26,0x18,	  
	0x27,0xc8,	  
	0x28,0x30,	  
	0x49,0xff,	  
	0x4a,0xef,	  
	0x4b,0x48,	  
	0x4f,0xcc,	  
	0x70,0x02,	  
	0x71,0x82,	  
	0x72,0x08,	  
	0x73,0x02,	  
	0x74,0xe2,	  
	0x75,0x10,	  
	0x77,0x00,	  
	0x79,0x04,
	0x7a,0x0e, //vb   
	0xd1,0x21,	  
	0xd2,0x00,	  
	0xd3,0x00,	  
	0xd6,0x10,	  
	0xd7,0x10,	  
	0xf0,0x00,	  
	0xff,0xff,

};


const u16 EX_OV2640InitTable[][2]=
{
	{0xff, 0x01},							  
    {0x12, 0x80},	 //com7 2017 0x80,
   // {SENSOR_WRITE_DELAY, 0x0a},//delay 10ms 	
 /* {0x0a,0x26}, //delay 10ms 
    {0x0a,0x26},
	{0x0a,0x26},
    {0x0a,0x26},
	{0x0a,0x26},
    {0x0a,0x26},
	{0x0a,0x26},
    {0x0a,0x26},
	{0x0a,0x26},
    {0x0a,0x26},*/
//	
    {0xff,0x00},		
	{0xc2,0x4c},		//2017		add	
    {0x2c,0xff},		//rsvd					  
    {0x2e,0xdf},		//rsvd					  
    {0xff,0x01},							  
    {0x3c,0x32},		//rsvd		
	//       
    {0x11,0x00},		//2017	  //pdf:0x01
    {0x09,0x02},	    //2x capability	
	{0x04,0x28},      //0x28
    {0x13,0xe5},		 //com8					  
    {0x14,0x48},		 //com9	2017			  
    {0x2c,0x0c},		 //rsvd					  
    {0x33,0x78},		 //rsvd						  
    {0x3a,0x33},		 //rsvd						  
    {0x3b,0xfB},		 //rsvd		
	//       
	{0x3e,0x00},		 //rsvd					  
    {0x43,0x11},		 //rsvd						  
    {0x16,0x10},		 //rsvd		
	//       
 	{0x39,0x92},
	//       
	{0x35,0xda},
	{0x22,0x1a},	
	{0x37,0xc3},
	{0x23,0x00},
	{0x34,0xc0},
	{0x36,0x1a},
	{0x06,0x88},
	{0x07,0xc0},
	{0x0d,0x87},
	{0x0e,0x41},
	{0x4c,0x00},
	{0x48,0x00},
	{0x5b,0x00},
	{0x42,0x03},
	//       
	{0x4a,0x81},
	{0x21,0x99},
	//       
	{0x24,0x40},
	{0x25,0x38},			//AEB	 			  						  
	{0x26,0x82},			 //2017 VV				  
    {0x5c,0x00},			//rsvd					  
    {0x63,0x00},			//rsvd					    
    {0x61,0x70},				//HISTO_L			  
    {0x62,0x80},				//HISTO_H			  
    {0x7c,0x05},	
    //       
    {0x20,0x80},				//rsvd				  
    {0x28,0x30},				//rsvd				  
    {0x6c,0x00},				//rsvd				  
    {0x6d,0x80},				//rsvd				  
    {0x6e,0x00},				//rsvd				  
    {0x70,0x02},				//rsvd				  
    {0x71,0x94},				//rsvd				  
    {0x73,0xc1},				//rsvd	
	//				
	{0x12,0x40},
    {0x17,0x11},			  //hrefst				  
    {0x18,0x43},			  //hrefend				  
    {0x19,0x00},			  //vstrt				  
    {0x1a,0x97},//0x4b,			   //vend	2017 int0x4b			  
    {0x32,0x09},				//reg32		  
    {0x37,0xc0},				//rsvd			  
    {0x4f,0x60},//banding 	50
    {0x50,0xa8},			    //BD60				  
    {0x6d,0x00},				 //rsvd			  
    {0x3d,0x38},				 //rsvd		
	//       
	{0x46,0x87},//25fps//2017 int 0x3f,   
	{0x47,0x00},
	{0x4f,0x60},
	{0x0c,0x3c},//2017 int 0x3c
	//       
	{0xff,0x00},
	{0xe5,0x7f},
	{0xf9,0xc0},
    {0x41,0x24},		         //rsvd					  
    {0xe0,0x14},							  
    {0x76,0xff},				//rsvd			  
    {0x33,0xa0},				//rsvd			  
    {0x42,0x20},				//rsvd			  
    {0x43,0x18},				//rsvd			  
    {0x4c,0x00},				//rsvd			  
    {0x87,0xd5},				//CTRL3	 2017 0xd0		  
    {0x88,0x3f},				//rsvd			  
    {0xd7,0x03},				//rsvd			  
    {0xd9,0x10},				//rsvd			  
    {0xd3,0x82},				//R_DVP_SP		
	//       
    {0xc8,0x08},				//rsvd			  
    {0xc9,0x80},				//rsvd	
	//	        
    {0x7c,0x00},				//BPADDR[3.0]			  
    {0x7d,0x00},				//BPDATA[7.0]			  
    {0x7c,0x03},				//BPADDR[3.0]			  
    {0x7d,0x48},							  
    {0x7d,0x48},	
    {0x7c,0x08},							  
    {0x7d,0x20},		
    {0x7d,0x10},							  
    {0x7d,0x0e},							  
    //       
    {0x90,0x00},							  
    {0x91,0x0e},							  
    {0x91,0x1a},							  
    {0x91,0x31},							  
    {0x91,0x5a},							  
    {0x91,0x69},							  
    {0x91,0x75},							  
    {0x91,0x7e},							  
    {0x91,0x88},							  
    {0x91,0x8f},							  
    {0x91,0x96},							  
    {0x91,0xa3},							  
    {0x91,0xaf},							  
    {0x91,0xc4},							  
    {0x91,0xd7},							  
    {0x91,0xe8},							  
    {0x91,0x20},							  
	//       
    {0x92,0x00},
    {0x93,0x06},  
    {0x93,0xe3},
    {0x93,0x05},
    {0x93,0x05},
    {0x93,0x00},	
    {0x93,0x04},  
    {0x93,0x00},	
    {0x93,0x00},	
    {0x93,0x00},	
    {0x93,0x00},
    {0x93,0x00},	
    {0x93,0x00}, 
    {0x93,0x00},	
    //	      
    {0x96,0x00},
    {0x97,0x08},
    {0x97,0x19}, 
    {0x97,0x02},
    {0x97,0x0c},
    {0x97,0x24},
    {0x97,0x30},
    {0x97,0x28},
    {0x97,0x26},
	{0x97,0x02},
    {0x97,0x98},
    {0x97,0x80},
    {0x97,0x00},
    {0x97,0x00},  
	//       
	{0xc3,0xed},
	{0xa4,0x00},
	{0xa8,0x00},
	{0xc5,0x11},
	{0xc6,0x51},								
	{0xbf,0x80},									
	{0xc7,0x10},
	{0xb6,0x66},
    {0xb8,0xa5},
    {0xb7,0x64},
    {0xb9,0x7c},
    {0xb3,0xaf},
    {0xb4,0x97},
    {0xb5,0xff},
    {0xb0,0xc5},
    {0xb1,0x94},
    {0xb2,0x0f},
    {0xc4,0x5c},											
	//       
	{0xc0,0x64},
    {0xc1,0x4b},
	{0x8c,0x00},
	{0x86,0x3d},
    {0x50,0x00},						
	{0x51,0xc8},//0xa0,   2017
    {0x52,0x96},//0x78,	2017					
	{0x53,0x00},		//0x00		offsetx[7.0]		
	{0x54,0x00},       //0x00offsetY[7.0]
    {0x55,0x00},						
	{0x5a,0xa0},//0xc8,//
    {0x5b,0x78},//0x96,
    {0x5c,0x00},
	{0xd3,0x82},
	//       
	{0xc3,0xed},
	{0x7f,0x00},
	//       
	{0xda,0x00},
	//       
	{0xe5,0x1f},
	{0xe1,0x67},
	{0xe0,0x00},
	{0xdd,0x7f},
	{0x05,0x00},
	//Auto band filter
	/*0xff,0x01,
	0x13,0xe5,
	0x0c,0x3a,
	0x4f,0x60,
	0x50,0x50,
	0x5a,0x67,*/
	//
	{-1,-1},       	
};
//
const u16 EX_OV7670InitTable[][2] = 
{
/*
	0x01,// [7:0]:driver type,0x01:sensor whith ISP; 0x02:ISP; 0x03:sensor whithout isp;	
	
	0x01,0x6E,0x36,0x00,// [7:0]:XCLK
	0x00,0x01,0x86,0xA0,// [7:0]:BAUDRATE(BE)
	
	0x00,//	[7:0]:chip_ID_addr>>8,when AddrByteNum == 2; 0 when  AddrByteNum == 1
	0x0a,// [7:0]:chip_ID_addr
	0x00,//
	0x76,// [7:0]:chip_ID 
	0x00,//	[7:0]:chip_ID_addr>>8,when AddrByteNum == 2; 0 when  AddrByteNum == 1
	0x00,// [7:0]:chip_ID_addr
	0x00,//
	0x00,// [7:0]:chip_ID 
	
	0x02,0x80,//image_width
	0x01,0xE0,//image_height
	0x43,// [7:0]:read ID
	0x42,// [7:0]:write ID
	0x01,//	[7:0]:AddrByteNum ; 
	0x01,// [7:0]:DataByteNum
	
	0x02,// [2:0]:ldo_config_para
	0x01,// [7:0]:ID nums
*/

/*0x2d,0xe0,*/
/*0x2e,0x02,*/
//0x13 exp 
	{0x01,0x90},
	{0x02,0x80},
	{0x3b,0xaa},//0xaa,//b7:night mod, bt(6-5):1,1/2,1/4,1/8 b4: 50HZ dis/en b1:exposure timing
	{0x3d,0x81},//gamma en  yvyu out
	{0x13,0xe7},//b7:fast AEC/AEC
	{0xaa,0x14},//b7: aec mode

	{0x1e,0x27},//mirror image
	{0x41,0x38},//b5:edge enhance, b4:denoise auto
	{0x4c,0x05}, //denoise strength
	{0x77,0x05}, //de-noise offset

//
	{0x4b,0x09},//0x09,h
	{0xc9,0x50}, //0x70,0x80(黑白)

	//edge enhancement
	{0x3f,0x00},//factor
	{0x75,0x03},//low
	{0x76,0xe1},//high
	

	{0x55,0x20},//brigghtness 
	{0x56,0x40},//0x30,//contras control
	{0x57,0x80},//0x80,//contrast center
	
	//25fps,24M
	{0x11,0x01},//0x80,
	{0x6b,0x4a},//0x0a,
	{0x92,0x50},//0x66,//0x00,//dummy line0x60
	{0xa4,0x00},//0x82,//auto frame rate//enter night mod gain = 2x

	//EXP    
	//0x04,0x}00,//AEC(0-1)
	//0x10,0x}00,//AEC(9-2)
	//0x07,0x}3f,//AEC(15-10)
	{0x14,0x2e},//0x4a,//0x3a,//0x38,//AGC max

	//AEC/AGC
	{0x24,0x95},//0x8f,//max light,
	{0x25,0x78},//0x7f,//min light,
	{0x26,0xe2},//0x94,//stable

	//AEC win
	{0x0d,0x00},//window = 1/2 bit(5-4):1,1/2,1/4,1/8
	{0x42,0x00},//window = 1/2 bit(7-6):1,1/2,1/4,1/8

	//blc    
	{0xb1,0x0c},
	{0xb3,0x7d},
	{0xb5,0x04},

//0x00,0xff,//AGC [7.0]
//0x03,0xca,//AGC [8.9]
//BLC
//0xb3,0x90,//0x8c,//0x82,ablc
//0xb5,0x0f,//stable range
//normal color
//0x67,0xc0,




//0x6b,0x1a,  //ext LDO 
//MTX1-6
/*0x4f,0x40,
0x50,0x34,
0x51,0x0c,
0x52,0x17,
0x53,0x78,
0x54,0x40,*/
//matrix
/*0x4f,0x8f,
0x50,0x8f,
0x51,0x04,
0x52,0x12,
0x53,0x8d,
0x54,0x9f,*/
//gamma
/*	
0x7a,0x20,
	0x7b,0x10,
	0x7c,0x28,
	0x7d,0x3c,
	0x7e,0x55,
	0x7f,0x68,
	0x80,0x76,
	0x81,0x80,
	0x82,0x88,
	0x83,0x8f,
	0x84,0x96,
	0x85,0xa3,
	0x86,0xaf,
	0x87,0xc4,
	0x88,0xd7,
	0x89,0xe8,
*/
	{0x7a, 0x15},//0x20,
	{0x7b, 0x10},
	{0x7c, 0x1e},
	{0x7d, 0x35},
	{0x7e, 0x5a},
	{0x7f, 0x69},
	{0x80, 0x76},
	{0x81, 0x80},
	{0x82, 0x8f},//0x88,
	{0x83, 0x96},//0x8f,
	{0x84, 0xa3},//0x96,
	{0x85, 0xaf},//0xa3,
	{0x86, 0xc4},//0xaf,
	{0x87, 0xd7},//0xc4,
	{0x88, 0xe8},//0xd7,
	{0x89, 0xf0},//0xe8,
//defaulat
/*
0x7a,0x24,
	0x7b,0x04,
	0x7c,0x07,
	0x7d,0x10,
	0x7e,0x28,
	0x7f,0x36,
	0x80,0x44,
	0x81,0x52,
	0x82,0x60,
	0x83,0x6c,
	0x84,0x78,
	0x85,0x8c,
	0x86,0x9e,
	0x87,0xbb,
	0x88,0xd2,
	0x89,0xe5,	
*/

	//AWB
	//0x43,0x14,
	//0x44,0xf0,
	//0x45,0x45,
	//0x46,0x61,
	//0x47,0x51,
	//0x48,0x79,
	//
	
	//0xa5,0x03,//0x07,
	//0xab,0x03,//0x07,
	//0x9d,0x98,//0xb7,//0xaf,//0x77,
	//0x9e,0x7f,//0xff,//0xff,
	//0x09,0x00, 
	
	//0x70,0x0a,
	//0x71,0x05, 
	{0x69,0xaa},
	//0x17,0x14,//0x11,
	//0x18,0x02,//0x61,
	//0x32,0x89,//0x80,
	
	//0x19,0x03,
	//0x1a,0x7b,
	//0x03,0x00,
	{0x00,0x10},
	{0x74,0x10},//Digitgl gain null, 1x, 2x, 4x
	//Saturation + 2
	/*
	0x4f,0xd0,
	0x50,0xd0,
	0x51,0x00,
	0x52,0x33,
	0x53,0x8d,
	0x54,0xc0,
	0x58,0x9e,
	*/
	//Saturation - 2
	/*
	0x4f, 0x40,
	0x50, 0x40,
	0x51, 0x00,
	0x52, 0x11,
	0x53, 0x2f,
	0x54, 0x40,
	0x58, 0x9e,
	*/
	/* */ 
	//0x13, 0xe7, //banding filter enable
	{0x9d, 0x99}, //50Hz banding filter
	{0x9e, 0x44}, //60Hz banding filter
	{0xa5, 0x02}, //7 step for 50hz
	{0xab, 0x07}, //8 step for 60hz
	//0x3b, 0x12, //Automatic detect banding filter
	
	//0x2d,0x10,
	//0x2e,0x00,
	//0x20,0x0f,
	//0xb1,0x0c,//bit(2) blc en/dis
	//0xb3,0x82,//target
	//0xb5,0x04,//stable
	//0xbe,0xa,
	//0xbf,0xa,
	//0xc0,0xa,
	//0xc1,0xa,
	{-1,-1},
};
const u16 EX_GC0307InitTable[][2]=
{

	0xf0,0x00,
	0x44,0xE3,
	0x68,0x30, //Global manual gain for every channel.
	0xd1,0x50,//0x60 Y target
	//0xba,0x30,
	
	//v/h bank
	0x01,0x6a,
	0x02,0xE0,//0x70,
	0x10,0x00,
	
	0x21,0xc0,//max post_gain
	0x22,0x60,//max pre_gain
	0x24,0x96,

	0xdd,0x22,
	0x47,0x20,//CbCr fixed en=0
	
	//contrast
	0x77, 0x80,
	0xa1, 0x30,
	
	//saturation
	0xa0,0x40,
	0xa2,0x30,
	0xa3,0x30,
	
	0x48,0xc0,
	0x80,0x10,
	0x81,0x10,
	0x82,0x99,
	0x7e,0x38,
	0x7f,0x88,
	
	0x8d,0x66,
	0x5c,0x78,
	0x5d,0x48,
	0x18,0x50,
	0x19,0x06,
	0x1a,0x06,
	0x61,0x80,
	0x63,0x80,
	0x65,0x80,
	0x67,0x80,
	
	0x0f,0x12,
	0x45,0x25,
	0x47,0x24,
	0x44,0xe2,
	
	
	//hue cos
	0x7b,0x30,
	
	//EV Level
	0x28,0x02,
	0x29,0x58,
	0x2a,0x04,
	0x2b,0xb0,
	0x2c,0x07,
	0x2d,0x08,
	0x2e,0x04,
	0x2f,0x00,
	-1,-1,

};
const u16 EX_OV3660InitTable[][2]=
{
	
	{0x3008,0x82},
	{0x3103,0x13},
	{0x3008,0x42},
	{0x3017,0xff},
	{0x3018,0xff}, 
	{0x302c,0xc3},
	{0x3032,0x00},
	{0x3901,0x13},
	{0x3704,0x80},
	{0x3717,0x00},
	{0x371b,0x60},
	{0x370b,0x10},
	{0x3611,0x01},  
	{0x3612,0x2d}, 
	{0x3624,0x03},
	{0x3622,0x80},
	{0x3614,0x80},
	{0x3630,0x52},
	{0x3632,0x07},
	{0x3633,0xd2},
	{0x3619,0x75},
	{0x371c,0x00},
	{0x370b,0x12},
	{0x3704,0x80},
	{0x3600,0x08},
	{0x3620,0x43},
	{0x3702,0x20},
	{0x3739,0x48},
	{0x3730,0x20},
	{0x370c,0x0c},
	{0x3a18,0x00},
	{0x3a19,0xf8},
	{0x3000,0x10},
	{0x3004,0xef},
	{0x6700,0x05},
	{0x6701,0x19},
	{0x6702,0xfd},
	{0x6703,0xd1},
	{0x6704,0xff},
	{0x6705,0xff},
	{0x3002,0x1c},
	{0x3006,0xc3},
/*
//==chop 1280*720
	{0x3800,0x01},		// windows ,  startx = 384,endx = 1695 , w = 1695-384 =1311
	{0x3801,0x80},		//			  starty = 408,endy = 1139 , h = 1139-408 =731
	{0x3802,0x01},
	{0x3803,0x98},
	{0x3804,0x06},
	{0x3805,0x9f},
	{0x3806,0x04},
	{0x3807,0x73},
	
	{0x3808,0x05},		//output w = 1280 , h = 720
	{0x3809,0x00},
	{0x380a,0x02},
	{0x380b,0xd0},
	
	{0x380c,0x08},			// total h pixel size = 2300
	{0x380d,0xfc},
	{0x380e,0x02},			// total v line size = 748
	{0x380f,0xec},
	{0x3810,0x00},		// isp offset h = 16, v = 6
	{0x3811,0x10},
	{0x3812,0x00},
	{0x3813,0x06},
*/

//===chop 1280*960 ,scale to vga===
	{0x3800,0x01},		// windows ,startx = 384,endx = 1695 , w = 1695-384 =1311
	{0x3801,0x80},		//			starty = 288,endy = 1259 , h = 1259-288 =971
	{0x3802,0x01},		// input 1280*960
	{0x3803,0x20},//0x98,
	{0x3804,0x06},
	{0x3805,0x9f},
	{0x3806,0x04},//0x05,
	{0x3807,0xeb},//0x63,
	{0x3808,0x02},		//output w = 640 , h = 480
	{0x3809,0x80},
	{0x380a,0x01},//0x01
	{0x380b,0xe0},//0xe0 
/*	{0x4602,0x02},
	{0x4603,0x80},
	{0x4604,0x01},
	{0x4605,0xe0},*/
   //{0x3818,0x01},
	//{0x3819,0xe0},//
//	{0x5600,0x00},//
//
/*	{0x5602,0x02},
	{0x5603,0x80},
	{0x5604,0x01},
	{0x5605,0xe0},*/
//	
	{0x380c,0x08},			// total h pixel size = 2300
	{0x380d,0xfc},
	{0x380e,0x03},//0x02,			// total v line size = 988
	{0x380f,0xDc},//0xec,
	{0x3810,0x00},		// isp offset h = 16, v = 6
	{0x3811,0x10},
	{0x3812,0x00},
	{0x3813,0x06},


	{0x3814,0x11},
	{0x3815,0x11},
	{0x3820,0x40},
	{0x3821,0x00},
	{0x3824,0x01},
	{0x3826,0x23},
	{0x3a02,0x30},
	{0x3a03,0xc0},
	{0x3a08,0x00},
	{0x3a09,0xe0},
	{0x3a0a,0x00},
	{0x3a0b,0xbb},
	{0x3a0d,0x04},
	{0x3a0e,0x03},
	{0x3a14,0x30},
	{0x3a15,0x72},
	{0x3618,0x78},
	{0x3623,0x00},
	{0x3708,0x63},
	{0x3709,0x12},
	{0x4300,0x30},
	{0x440e,0x09},
	{0x4514,0x00},
	{0x4520,0xb0},
	{0x460b,0x37},
	{0x460c,0x20},
	{0x4709,0x48},//		// 0x08, VS dummy line width
	{0x4713,0x02},
	{0x471c,0xd0},
	{0x4740,0x21},//0x01,		// VS 
	{0x471d,0x00},//

	{0x5086,0x00},
	{0x5000,0x07},
	
	{0x5001,0xf3},//0xf3,	//0x03,bit7 is scale en
	{0x5002,0x00},
	{0x501f,0x00},
	{0x3a00,0x38},//0x38,
	{0x303c,0x12},  //0x12,//15fps
	{0x440e,0x08},  //for MBIST
	{0x3821,0x06},  //mirror on
	{0x3008,0x02},
	////////////////IQ setting example
	/////////////////Sample_AWB
	{0x5180,0xff},
	{0x5181,0xf2},
	{0x5182,0x00}, 
	{0x5183,0x14},
	{0x5184,0x25},
	{0x5185,0x24},
	{0x5186,0x09}, 
	{0x5187,0x09}, 
	{0x5188,0x09}, 
	{0x5189,0x75},
	{0x518a,0x54},
	{0x518b,0xe0},
	{0x518c,0xb2},
	{0x518d,0x42},
	{0x518e,0x3d},
	{0x518f,0x56},
	{0x5190,0x46},
	{0x5191,0xf8},
	{0x5192,0x04}, 
	{0x5193,0x70},
	{0x5194,0xf0},
	{0x5195,0xf0},
	{0x5196,0x03}, 
	{0x5197,0x01}, 
	{0x5198,0x04}, 
	{0x5199,0x12},
	{0x519a,0x04}, 
	{0x519b,0x00}, 
	{0x519c,0x06}, 
	{0x519d,0x82},
	{0x519e,0x38},
	//////////////////////Sample_CMX
	{0x5381,0x1c},  
	{0x5382,0x5a},
	{0x5383,0x06}, 
	{0x5384,0x0a}, 
	{0x5385,0x7e},
	{0x5386,0x88},
	{0x5387,0x7c},
	{0x5388,0x6c},
	{0x5389,0x10},
	{0x538a,0x01}, 
	{0x538b,0x98},
	////////////////////////Sample_gamma
	{0x5000,0x27}, ///enable gamma====indoor====
	{0x5481,0x08}, 
	{0x5482,0x14},
	{0x5483,0x28},
	{0x5484,0x51},
	{0x5485,0x65},
	{0x5486,0x71},
	{0x5487,0x7d},
	{0x5488,0x87},
	{0x5489,0x91},
	{0x548a,0x9a},
	{0x548b,0xaa},
	{0x548c,0xb8},
	{0x548d,0xcd},
	{0x548e,0xdd},
	{0x548f,0xea},
	{0x5490,0x1d},
	//////////////////////////Example_EV
	{0x3a0f,0x48},
	{0x3a10,0x40},
	{0x3a1b,0x48},
	{0x3a1e,0x40},
	{0x3a11,0x70},
	{0x3a1f,0x14},
	{0x3a18,0x00}, 
	{0x5308,0x25},	//00 40
	{0x5300,0x08}, //8x
	{0x5301,0x30},
	{0x5302,0x10},
	{0x5303,0x00},
	{0x5309,0x08},
	{0x530a,0x30},
	{0x530b,0x04},
	{0x530c,0x06},
	{0x3a19,0x80},	//8x gain
	{0x5000,0xa7}, 
	{0x5800,0x20}, 
	{0x5801,0x0a}, 
	{0x5802,0x0a}, 
	{0x5803,0x0a}, 
	{0x5804,0x0e}, 
	{0x5805,0x19}, 
	{0x5806,0x07}, 
	{0x5807,0x05}, 
	{0x5808,0x04}, 
	{0x5809,0x04}, 
	{0x580a,0x06}, 
	{0x580b,0x0a}, 
	{0x580c,0x05}, 
	{0x580d,0x01}, 
	{0x580e,0x00}, 
	{0x580f,0x00}, 
	{0x5810,0x03}, 
	{0x5811,0x07}, 
	{0x5812,0x06}, 
	{0x5813,0x02}, 
	{0x5814,0x00}, 
	{0x5815,0x00}, 
	{0x5816,0x03}, 
	{0x5817,0x08}, 
	{0x5818,0x08}, 
	{0x5819,0x05}, 
	{0x581a,0x04}, 
	{0x581b,0x05}, 
	{0x581c,0x07}, 
	{0x581d,0x0a}, 
	{0x581e,0x38}, 
	{0x581f,0x0d}, 
	{0x5820,0x0b}, 
	{0x5821,0x0c}, 
	{0x5822,0x0f}, 
	{0x5823,0x36}, 
	{0x5824,0x37}, 
	{0x5825,0x17}, 
	{0x5826,0x07}, 
	{0x5827,0x17}, 
	{0x5828,0x27}, 
	{0x5829,0x26}, 
	{0x582a,0x25}, 
	{0x582b,0x33}, 
	{0x582c,0x25}, 
	{0x582d,0x17}, 
	{0x582e,0x16}, 
	{0x582f,0x42}, 
	{0x5830,0x50}, 
	{0x5831,0x42}, 
	{0x5832,0x27}, 
	{0x5833,0x27}, 
	{0x5834,0x36}, 
	{0x5835,0x35}, 
	{0x5836,0x36}, 
	{0x5837,0x28}, 
	{0x5838,0x47}, 
	{0x5839,0x18}, 
	{0x583a,0x19}, 
	{0x583b,0x27}, 
	{0x583c,0x58}, 
	{0x583d,0xce},

	{-1, -1},	
};

enum
{
	PCLK_24M = 24,	
	PCLK_27M = 27,
};
static const sensor_cmd_t ex_ov7670_cmd = {
	.w_cmd = 0x42,
	.r_cmd = 0x43,
	.id_reg = 0x0a,
	.addr_num = 0x01,
	.data_num = 0x01,
	.id = 0x76,
	.init = EX_OV7670InitTable,
	.mclk = 192/PCLK_24M-1,

};
static const sensor_cmd_t ex_7375s_cmd = {
	.w_cmd = (0x68 << 1) | 0,
	.r_cmd = (0x68 << 1) | 1,
	.id_reg = 0xfd,
	.addr_num = 0x01,
	.data_num = 0x01,
	.id = 0x03 ,
	.init = EX_7375SInitTable,
	.mclk = 192/PCLK_24M-1,
};
static const sensor_cmd_t ex_siv100b_cmd = {
	.w_cmd = 0x66,
	.r_cmd = 0x67,
	.id_reg = 0x01,
	.addr_num = 0x01,
	.data_num = 0x01,
	.id = 0x0c,
	.init = EX_SIV100BInitTable,
	.mclk = 192/PCLK_27M-1,
};
const sensor_cmd_t ex_OV2640_cmd = {
	.w_cmd = 0x60,
	.r_cmd = 0x61,
	.id_reg = 0x0a,
	.addr_num = 0x01,
	.data_num = 0x01,
	.id = 0x26,
	.init = EX_OV2640InitTable,
	.mclk = 192/PCLK_24M-1,
};
const sensor_cmd_t ex_GC0307_cmd = {
	.w_cmd = 0x42,
	.r_cmd = 0x43,
	.id_reg = 0x00,
	.addr_num = 0x01,
	.data_num = 0x01,
	.id = 0x99,
	.init = EX_GC0307InitTable,
	.mclk = 192/PCLK_24M-1,
};

const sensor_cmd_t ex_OV3660_cmd = {
	.w_cmd = 0x78,
	.r_cmd = 0x79,
	.id_reg = 0x300a,
	.addr_num = 0x02,
	.data_num = 0x01,
	.id = 0x36,
	.init = EX_OV3660InitTable,
	.mclk = 192/PCLK_24M-1,
};
const sensor_cmd_t * sensor_cmd_tab[] = {
	&ex_OV3660_cmd,	
	&ex_siv100b_cmd,
	&ex_7375s_cmd,
	&ex_OV2640_cmd,
	&ex_ov7670_cmd,
	&ex_GC0307_cmd,
	NULL,
	};



