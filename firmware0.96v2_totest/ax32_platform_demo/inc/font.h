/****************************************************************************
**
 **                              RESOURCE 
  ** *   **             THE APPOTECH MULTIMEDIA PROCESSOR
   **** **                  RESOURCE FONT
  *** ***
 **  * **               (C) COPYRIGHT 2016 BUILDWIN 
**      **                         
         **         BuildWin SZ LTD.CO  ; VIDEO PROJECT TEAM
          **   
* File Name   : font.h
* Author      : Mark.Douglas 
* Version     : V100
* Date        : 09/22/2016
* Description : 
*               
* History     : 
* 2016-09-22  : 
*      <1>.This is created by mark,set version as v100.
*      <2>.Add basic functions & information
******************************************************************************/
#ifndef  FONT_H  
    #define  FONT_H



/*******************************************************************************
* Function Name  : fontInit
* Description	 :	font initial
* Input 		 : 
* Output		 : none 										   
* Return		 : int : 
*******************************************************************************/
int fontInit(void);
/*******************************************************************************
* Function Name  : fontSetLanguage
* Description	 :	set current lanaguage
* Input 		 : INT8U num : lan index 
* Output		 : none 										   
* Return		 : int : 
*******************************************************************************/
int fontSetLanguage(INT8U num);
/*******************************************************************************
* Function Name  : fontGetStringInfo
* Description    :  get string info 
* Input          : INT8U num : string index
                      INT16U *width:string width
                      INT16U *height:string height
* Output         : none                                            
* Return         : int : 
*******************************************************************************/
int fontGetStringInfo(INT8U num,INT16U *width,INT16U *height);
/*******************************************************************************
* Function Name  : fontDrawString
* Description    :  draw string 
* Input          : INT8U *dest : destination buffer
                      INT8U num  : string index
                      INT16S x    : x position
                      INT16S y    : y position
                      INT16U width : buffer size
                      INT8U color : color
* Output         : none                                            
* Return         : int : 
*******************************************************************************/
int fontDrawString(INT8U *dest,INT8U num,INT16S x,INT16S y,INT16U width,INT8U color);

































#endif

