/****************************************************************************
**
 **                              TASK 
  ** *   **             THE APPOTECH MULTIMEDIA PROCESSOR
   **** **                 TASK USB
  *** ***
 **  * **               (C) COPYRIGHT 2016 BUILDWIN 
**      **                         
         **         BuildWin SZ LTD.CO  ; VIDEO PROJECT TEAM
          **   
* File Name   : task_usb.c
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
#include "application.h" 

#define  USB_ICON_MASS      RES_ICON_USB_MODE
#define  USB_ICON_CAM       RES_ICON_PCCAM_MODE
extern msgDealInfor usbDeviceMsgDeal[];
static void taskUsbDeviceOpen(uint32 arg)
{
	uint32 mode;
	deg_Printf("usb task enter.0x%x\n",arg);
	dispLayerUninit(DISP_LAYER_VIDEO);
	mode = 0;
	//set lcd video layer color
	hal_lcdSetBufYUV(hal_lcdGetShowingBuffer(),0,0x80,0x80);

	if(arg==USB_DEV_PCCAMERA) // pc-cam   
	{
		extern void setSoftwareDetachUsensor(BOOL en);
	   setSoftwareDetachUsensor(TRUE);
	   if(backrec_adpt())
	   {
			backrec_stop();
		}
	   VIDEO_ARG_T arg1;
	   arg1.resolution.width = 1280;
	   arg1.resolution.height= 720;
	   videoRecordInit(&arg1); // enable csi&mjpeg 
	   mode=1;
	}
	else
	{
		mode=0;
	}
	deg_Printf("mode:%d\n",mode);
	if(mode==0)
	 	logo_image_show(USB_ICON_MASS);
	else
		logo_image_show(USB_ICON_CAM);
	while(audioPlaybackGetStatus() == MEDIA_STAT_PLAY); 
	hal_usbdInit(mode);
	msgFuncRegister(usbDeviceMsgDeal);
}
static void taskUsbDeviceClose(uint32 arg)
{
	hal_usbdUninit();
	dispLayerInit(DISP_LAYER_OSD0);
}
static void taskUsbDeviceService(uint32 arg)
{
	if(false == hal_usbdProcess())
	{
		deg_Printf("usb update\n");
		boardIoctrl(SysCtrl.bfd_lcd,IOCTRL_LCD_BKLIGHT,0); // back light off
		taskStart(TASK_USB_UPDATE,0);
		//taskStart(TASK_POWER_OFF,0);
	}

}
sysTask taskUsbDevice=
{
	"usb device",
	NULL,
	taskUsbDeviceOpen,
	taskUsbDeviceClose,
	taskUsbDeviceService,
};


static int usbDeviceSysMsgSD(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}
static int usbDeviceSysMsgUSB(winHandle handle,uint32 parameNum,uint32* parame)
{
	if(SysCtrl.usb == USB_STAT_NULL)
		taskStart(TASK_POWER_OFF,0);
	return 0;
}
static int usbDeviceSysMsg1S(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}
static int usbDeviceKeyMsgMode(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}

msgDealInfor usbDeviceMsgDeal[]=
{
	{SYS_EVENT_SDC,usbDeviceSysMsgSD},
	{SYS_EVENT_USB,usbDeviceSysMsgUSB},
	{SYS_EVENT_1S,usbDeviceSysMsg1S},
	{KEY_EVENT_MODE,usbDeviceKeyMsgMode},
	{EVENT_MAX,NULL},
};

