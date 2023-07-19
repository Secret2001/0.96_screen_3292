#include "application.h"

static uint32 usbOutPowerOffCnt=0;
static uint32 batlowPowerOffCnt=0;

static int unshieldedKeyMsgOk(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		deamon_auto_poweroff(1);
		deamon_screen_save(1);
	}
	return 0;
}
static int unshieldedKeyMsgUp(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		deamon_auto_poweroff(1);
		deamon_screen_save(1);
	}
	return 0;
}
static int unshieldedKeyMsgDown(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		deamon_auto_poweroff(1);
		deamon_screen_save(1);
	}
	return 0;
}
static int unshieldedKeyMsgMenu(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		deamon_auto_poweroff(1);
		deamon_screen_save(1);
	}
	return 0;
}
static int unshieldedKeyMsgMode(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		deamon_auto_poweroff(1);
		deamon_screen_save(1);
	}
	return 0;
}
extern void setKeyEn(bool en);
static int unshieldedKeyMsgPower(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 lcdOn=0,irState=0; 
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		deamon_auto_poweroff(1);
		#if IR_MENU_EN>0
		boardIoctrl(SysCtrl.bfd_ir,IOGET_IR_GET,&irState);
		if(irState==0)
		{
			boardIoctrl(SysCtrl.bfd_ir,IOCTRL_IR_SET,1);
			configSet(CONFIG_ID_IR_LED,R_ID_STR_COM_ON);
		}
		else
		{
		  	boardIoctrl(SysCtrl.bfd_ir,IOCTRL_IR_SET,0);
		  	configSet(CONFIG_ID_IR_LED,R_ID_STR_COM_OFF);
		}
		#else
		boardIoctrl(SysCtrl.bfd_lcd,IOGET_LCD_BKLIGHT,(u32)&lcdOn);
		if(lcdOn&&SysCtrl.astern == ASTERN_OFF)
			boardIoctrl(SysCtrl.bfd_lcd,IOCTRL_LCD_BKLIGHT,0);
		else
		{
			deamon_screen_save(1);
			setKeyEn(true);
		}
		#endif
		deg_Printf("sys deal:powerkey\n");
	}
	return 0;
}
static int unshieldedKeyMsgPowerOff(winHandle handle,uint32 parameNum,uint32* parame)
{
//	uint32 lcdOn=0;
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		taskStart(TASK_POWER_OFF,0);
		deg_Printf("sys deal:power off\n");
	}
	return 0;
}
extern void setSoftwareDetachUsensor(BOOL en);
static int unshieldedMsgUSB(winHandle handle,uint32 parameNum,uint32* parame)
{
	deamon_screen_save(1);
	setKeyEn(true);
	if((SysCtrl.usb != USB_STAT_NULL))  // DC IN
	{
		setSoftwareDetachUsensor(FALSE);
		usbOutPowerOffCnt=0;
		batlowPowerOffCnt=0;
	}
	else
		usbOutPowerOffCnt=BAT_SAVE_POWER;
	if((SysCtrl.usb == USB_STAT_PC)) 
		uiOpenWindow(&menuUsbWindow,0);
	return 0;
}
static int unshieldedMsgSD(winHandle handle,uint32 parameNum,uint32* parame)
{      
	int ret;
	deamon_screen_save(1);
	setKeyEn(true);
	if(SysCtrl.sdcard == SDC_STAT_NORMAL)
	{
		ret = open((const char *)"SELFTEST.bin",FA_READ);
		if(ret>=0)
		{
			close(ret);
			uiOpenWindow(&selfTestWindow,0);
		}
	}
	return 0;
}
static int unshieldedMsgBattery(winHandle handle,uint32 parameNum,uint32* parame)
{
	if(SysCtrl.battery <= BATTERY_STAT_2)
	{
		setSoftwareDetachUsensor(TRUE);
		if(backrec_adpt())
		{
			backrec_stop();
			deg_Printf("software detach Usensor!!!\n\n\n\n");
			if(SysCtrl.battery < BATTERY_STAT_2)
				uiOpenWindow(&tips1Window,2,TIPS_POWER_LOW,TIPS_KEEP_SHOWING);
			else
				uiOpenWindow(&tips1Window,2,TIPS_USENSOR_POWER_LOW,TIPS_KEEP_SHOWING);
		}
	}
	if(SysCtrl.battery <= BATTERY_STAT_1)
	{
		if(batlowPowerOffCnt==0)
			batlowPowerOffCnt=5;
		uiOpenWindow(&tips1Window,2,TIPS_POWER_LOW,TIPS_KEEP_SHOWING);
	}
	return 0;
}
extern uint32 uvcIntCnt;
static int unshieldedMsg1S(winHandle handle,uint32 parameNum,uint32* parame)
{

	if(usbOutPowerOffCnt)
	{
		usbOutPowerOffCnt--;
		if(usbOutPowerOffCnt==0)
		{
			deg_Printf("sys deal:usb out,auto power off\n");
			taskStart(TASK_POWER_OFF,0);
		}
	}
	if(batlowPowerOffCnt)
	{
		batlowPowerOffCnt--;
		if(batlowPowerOffCnt==0)
		{
			deg_Printf("sys deal:battery low,auto power off\n");
			taskStart(TASK_POWER_OFF,0);
		}
	}
	return 0;
}

msgDealInfor sysUnshieldedMsgDeal[]=
{
	{KEY_EVENT_OK,unshieldedKeyMsgOk},
	{KEY_EVENT_UP,unshieldedKeyMsgUp},
	{KEY_EVENT_DOWN,unshieldedKeyMsgDown},
	{KEY_EVENT_MENU,unshieldedKeyMsgMenu},
	{KEY_EVENT_MODE,unshieldedKeyMsgMode},
	{KEY_EVENT_POWER,unshieldedKeyMsgPower},
	{KEY_EVENT_POWEROFF,unshieldedKeyMsgPowerOff},
	{SYS_EVENT_SDC,unshieldedMsgSD},
	{SYS_EVENT_USB,unshieldedMsgUSB},
	{SYS_EVENT_BAT,unshieldedMsgBattery},
	{SYS_EVENT_1S,unshieldedMsg1S},
	{EVENT_MAX,NULL},
};




