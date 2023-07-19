/****************************************************************************
       ***             ***                      MAXLIB-GRAPHC                  
      ** **           ** **                                                    
     **   **         **   **            THE MAXLIB FOR IMAGE SHOW PROCESS      
    **     **       **     **                                                  
   **       **     **       **              MAX ROURCE ICON MANAGEMENT         
  **         **   **         **                                                
 **           ** **           **              (C) COPYRIGHT 2016 MAX           
**             ***             **                                              
                                                                               
* File Name   : user_icon.c                                                    
* Author      : Mark.Douglas                                                   
* Version     : V0100                                                          
* Date        : 05/25/2016                                                     
* Description : This file for maxlib resource icon managemant                  
*                                                                              
* History     :                                                                
* 2016-05-25  :                                                                
*      <1>.This is created by mark,set version as v0103.                       
*      <2>.Add basic functions.                                                
******************************************************************************/

#include "../application.h"
#include "user_icon.h"
R_ICON_T User_Icon_Table[R_ICON_MAX&0xffff]=
{
   {R_ID_ICON_BARNSEL                       ,	(void *)0,0,178, 24,0xFFFFFFFF,0x00000000},
   {R_ID_ICON_BARSEL                        ,	(void *)0,0,181, 28,0x00000010,0x00000001},
   {R_ID_ICON_MENUAUDIO                     ,	(void *)0,0, 24, 24,0x00000010,0x00000002},
   {R_ID_ICON_MENUBATTERY                   ,	(void *)0,0, 24, 24,0x00000010,0x00000003},
   {R_ID_ICON_MENUCLOCK                     ,	(void *)0,0, 24, 24,0x00000010,0x00000004},
   {R_ID_ICON_MENUDELALL                    ,	(void *)0,0, 24, 24,0x00000010,0x00000005},
   {R_ID_ICON_MENUDELONE                    ,	(void *)0,0, 24, 24,0x00000010,0x00000006},
   {R_ID_ICON_MENUEV                        ,	(void *)0,0, 24, 24,0x00000010,0x00000007},
   {R_ID_ICON_MENUFORMAT                    ,	(void *)0,0, 24, 24,0x00000010,0x00000008},
   {R_ID_ICON_MENUGSENSOR                   ,	(void *)0,0, 24, 24,0x00000010,0x00000009},
   {R_ID_ICON_MENUHZ                        ,	(void *)0,0, 24, 24,0x00000010,0x0000000a},
   {R_ID_ICON_MENUIMAGEQ                    ,	(void *)0,0, 24, 24,0x00000010,0x0000000b},
   {R_ID_ICON_MENULANGUAGE                  ,	(void *)0,0, 24, 24,0x00000010,0x0000000c},
   {R_ID_ICON_MENULIGHTNORMAL               ,	(void *)0,0, 24, 24,0x00000010,0x0000000d},
   {R_ID_ICON_MENULOCK                      ,	(void *)0,0, 24, 24,0x00000010,0x0000000e},
   {R_ID_ICON_MENULOOPRECORD                ,	(void *)0,0, 24, 24,0x00000010,0x0000000f},
   {R_ID_ICON_MENUMONITOR                   ,	(void *)0,0, 24, 24,0x00000010,0x00000010},
   {R_ID_ICON_MENUMOON                      ,	(void *)0,0, 24, 24,0x00000010,0x00000011},
   {R_ID_ICON_MENUMOTION                    ,	(void *)0,0, 24, 24,0x00000010,0x00000012},
   {R_ID_ICON_MENUPOWEROFF                  ,	(void *)0,0, 24, 24,0x00000010,0x00000013},
   {R_ID_ICON_MENURESET                     ,	(void *)0,0, 24, 24,0x00000010,0x00000014},
   {R_ID_ICON_MENURESOLUTION                ,	(void *)0,0, 24, 24,0x00000010,0x00000015},
   {R_ID_ICON_MENUSCRENNOFF                 ,	(void *)0,0, 24, 24,0x00000010,0x00000016},
   {R_ID_ICON_MENUSTRAMP                    ,	(void *)0,0, 24, 24,0x00000010,0x00000017},
   {R_ID_ICON_MENUTV                        ,	(void *)0,0, 24, 24,0x00000010,0x00000018},
   {R_ID_ICON_MENUUNLOCK                    ,	(void *)0,0, 24, 24,0x00000010,0x00000019},
   {R_ID_ICON_MENUVERSION                   ,	(void *)0,0, 24, 24,0x00000010,0x0000001a},
   {R_ID_ICON_MENUVOLUME                    ,	(void *)0,0, 24, 24,0x00000010,0x0000001b},
   {R_ID_ICON_MTBACK                        ,	(void *)0,0, 24, 24,0x00000010,0x0000001c},
   {R_ID_ICON_MTBATTERY0                    ,	(void *)0,0, 16, 16,0x00000010,0x0000001d},
   {R_ID_ICON_MTBATTERY1                    ,	(void *)0,0, 16, 16,0x00000010,0x0000001e},
   {R_ID_ICON_MTBATTERY2                    ,	(void *)0,0, 16, 16,0x00000010,0x0000001f},
   {R_ID_ICON_MTBATTERY3                    ,	(void *)0,0, 16, 16,0x00000010,0x00000020},
   {R_ID_ICON_MTBATTERY4                    ,	(void *)0,0, 16, 16,0x00000010,0x00000021},
   {R_ID_ICON_MTBATTERY5                    ,	(void *)0,0, 16, 16,0x00000010,0x00000022},
   {R_ID_ICON_MTFORWARD                     ,	(void *)0,0, 24, 24,0x00000010,0x00000023},
   {R_ID_ICON_MTIROFF                       ,	(void *)0,0, 16, 16,0x00000010,0x00000024},
   {R_ID_ICON_MTIRON                        ,	(void *)0,0, 16, 16,0x00000010,0x00000025},
   {R_ID_ICON_MTLOCK                        ,	(void *)0,0, 16, 16,0x00000010,0x00000026},
   {R_ID_ICON_MTMENU                        ,	(void *)0,0, 16, 16,0x00000010,0x00000027},
   {R_ID_ICON_MTMICOFF                      ,	(void *)0,0, 16, 16,0x00000010,0x00000028},
   {R_ID_ICON_MTMICON                       ,	(void *)0,0, 16, 16,0x00000010,0x00000029},
   {R_ID_ICON_MTMORE                        ,	(void *)0,0, 20, 20,0x00000010,0x0000002a},
   {R_ID_ICON_MTMOTION                      ,	(void *)0,0, 16, 16,0x00000010,0x0000002b},
   {R_ID_ICON_MTOFF                         ,	(void *)0,0, 20, 20,0x00000010,0x0000002c},
   {R_ID_ICON_MTON                          ,	(void *)0,0, 20, 20,0x00000010,0x0000002d},
   {R_ID_ICON_MTON1                         ,	(void *)0,0, 20, 20,0x00000010,0x0000002e},
   {R_ID_ICON_MTON2                         ,	(void *)0,0, 20, 20,0x00000010,0x0000002f},
   {R_ID_ICON_MTPARKOFF                     ,	(void *)0,0, 16, 16,0x00000010,0x00000030},
   {R_ID_ICON_MTPARKON                      ,	(void *)0,0, 16, 16,0x00000010,0x00000031},
   {R_ID_ICON_MTPAUSE                       ,	(void *)0,0, 24, 24,0x00000010,0x00000032},
   {R_ID_ICON_MTPAUSE1                      ,	(void *)0,0, 64, 64,0x00000010,0x00000033},
   {R_ID_ICON_MTPHOTO                       ,	(void *)0,0, 16, 16,0x00000010,0x00000034},
   {R_ID_ICON_MTPLAY                        ,	(void *)0,0, 24, 24,0x00000010,0x00000035},
   {R_ID_ICON_MTPLAY1                       ,	(void *)0,0, 64, 64,0x00000010,0x00000036},
   {R_ID_ICON_MTPLAY2                       ,	(void *)0,0, 16, 16,0x00000010,0x00000037},
   {R_ID_ICON_MTRECORD                      ,	(void *)0,0, 16, 16,0x00000010,0x00000038},
   {R_ID_ICON_MTSDCNORMAL                   ,	(void *)0,0, 16, 16,0x00000010,0x00000039},
   {R_ID_ICON_MTSDCNULL                     ,	(void *)0,0, 16, 16,0x00000010,0x0000003a},
};
