/****************************************************************************
**
 **                         BUILDWIN AX32XX MCU LAYER
  ** *   **                     THE APPOTECH HAL
   **** **                           AX32XX 
  *** ***
 **  * **               (C) COPYRIGHT 2016 BUILDWIN 
**      **                         
         **         BuildWin SZ LTD.CO  ; VIDEO PROJECT TEAM
          **       
* File Name   : ax32xx.h
* Author      : Mark.Douglas 
* Version     : V0200
* Date        : 05/25/2016
* Description : This file for BUILDWIN AX32XX HARDWARE LAYER.
*               
*               
* History     :
* 2017-02-27  : 
*      <1>.This is created by mark,set version as v0100.
*      <2>.Add basic functions.
******************************************************************************/
#ifndef  AX32XX_CFG_H
   #define  AX32XX_CFG_H

#define  CFG_DCACHE_EN       1
#define  CFG_ICACHE_EN       1



#define  CFG_WDT_EN          1   // watch dog



#define  CFG_MCU_DBG_EN      0
#define  CFG_MCU_TFDBG_EN    0
//------------CHIP VISION
#define THUNDERSE_A1		0x00000000
#define THUNDERSE_B1		0x00010000
#define THUNDERSE_B2		0x00030000

//----------ax32xx body define------------
#define  FPGA                0x0080
#define  AX3293A             0x4880
#define  AX3293B             0x4881
#define  AX3282S             0x6480
#define  AX3292              0x6481
//#define  AX3292B           0x6482
#define  AX3291A             0x8080
#define  AX3291B             0x8081

#define  AX32_PLATFORM       AX3292//AX3282S  //FPGA// AX3291A//AX3282S //AX3292    //  current body     

//-----------------------------------------
#define  SDRAM_SIZE_2M       0x200000
#define  SDRAM_SIZE_8M       0x800000

#if ((AX32_PLATFORM&0xf0)==0x20)
   #define  SDRAM_SIZE       SDRAM_SIZE_2M  // 2M
#elif ((AX32_PLATFORM&0xf0)==0x80)
   #define  SDRAM_SIZE       SDRAM_SIZE_8M  // 8M
#else
   #define  SDRAM_SIZE       SDRAM_SIZE_8M  // 8M
#endif

















#endif

