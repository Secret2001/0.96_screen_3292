#include "application.h"
#include "taskPlayBackRes.c"
#define  VIDEO_PLAY_WAIT_KEYSOUND_END           while(audioPlaybackGetStatus() == MEDIA_STAT_PLAY){XOSTimeDly(10);}

extern int video_playback_start(int index);
static int playBackKeyMsgOk(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	//int ret;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		if(managerFileCount(SysCtrl.avi_list)>=1)
		{
			if(videoPlaybackGetStatus()== MEDIA_STAT_START)
			{
				videoPlaybackPuase();
				while(videoPlaybackGetStatus()==MEDIA_STAT_START);
				deamon_keysound_play();
			}
			else if(videoPlaybackGetStatus() == MEDIA_STAT_PAUSE)
			{
				deamon_keysound_play();
				VIDEO_PLAY_WAIT_KEYSOUND_END;
				videoPlaybackResume();
			}
			else
			{
				deamon_keysound_play();
				VIDEO_PLAY_WAIT_KEYSOUND_END;
				video_playback_start(SysCtrl.file_index);
			}
		}
	}
	return 0;
}
static int playBackKeyMsgUp(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		deg_Printf("avi num [%d]\n",managerFileCount(SysCtrl.avi_list));
		deg_Printf("jpg num [%d]\n",managerFileCount(SysCtrl.jpg_list));

		deg_Printf("avi list [%d]\n",(SysCtrl.avi_list));
		deg_Printf("jpg list [%d]\n",(SysCtrl.jpg_list));
		

		int i;
		// for(i=0;i<managerFileCount(SysCtrl.avi_list);i++)
		// {
		// 	deg_Printf("SysCtrl.avi_list [%d]\n",SysCtrl.avi_list);
		// 	SysCtrl.avi_list++;
		// }
		

		if(managerFileCount(SysCtrl.avi_list)>=1)
		{
		#if 0
			if(state == MEDIA_STAT_PLAY)
				videoPlaybackFastForward();
		#else						
			if(videoPlaybackGetStatus() != MEDIA_STAT_STOP)
			{
                  videoPlaybackStop();
			}
			deamon_keysound_play();
			SysCtrl.file_index--;
			if(SysCtrl.file_index<1)
				SysCtrl.file_index = managerFileCount(SysCtrl.avi_list);
			 video_playback_start(SysCtrl.file_index);
			 playbackResolutionShow(handle);
			playbackFileNameShow(handle);
			playbackLockShow(handle);
		#endif
		}
	}
	return 0;
}
static int playBackKeyMsgDown(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		if(managerFileCount(SysCtrl.avi_list)>=1)
		{
		#if 0
			if(state == MEDIA_STAT_PLAY)
				videoPlaybackFastBackward();

		#else				
			if(videoPlaybackGetStatus() != MEDIA_STAT_STOP)
			{
                  videoPlaybackStop();
			}
			deamon_keysound_play();
			SysCtrl.file_index++;
			if(SysCtrl.file_index>managerFileCount(SysCtrl.avi_list))
				SysCtrl.file_index = 1;
			video_playback_start(SysCtrl.file_index);
			playbackResolutionShow(handle);
			playbackFileNameShow(handle);
			playbackLockShow(handle);
		#endif
		}
	}
	return 0;
}
extern menu MENU(playBack);
static int playBackKeyMsgMenu(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
//	int ret;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		if((videoPlaybackGetStatus() != MEDIA_STAT_START)&&(managerFileCount(SysCtrl.avi_list)>0))
		{
			videoPlaybackStop();
			deamon_keysound_play();
            uiOpenWindow(&menuItemWindow,1,&MENU(playBack));						
			//layout_video_playback_name(manangerGetFileFullPathName(SysCtrl.avi_list,SysCtrl.file_index,NULL));
		}
	}
	return 0;
}
static int playBackKeyMsgMode(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		if(videoPlaybackGetStatus() != MEDIA_STAT_PLAY)
		{
			 taskChange();
			 deamon_keysound_play();
			 VIDEO_PLAY_WAIT_KEYSOUND_END;
		}
	}
	return 0;
}
static int playBackSysMsgSD(winHandle handle,uint32 parameNum,uint32* parame)
{
	deg_Printf("player : sdc stat ->%d\n",SysCtrl.sdcard);
	if((SysCtrl.sdcard != SDC_STAT_NORMAL)/* && (state == MEDIA_STAT_PLAY)*/) // sdc out when recording
	{
		if(videoPlaybackGetStatus() == MEDIA_STAT_PLAY)
		    videoPlaybackStop();
		uiOpenWindow(&noFileWindow,0);
	}
	else
	{
		SysCtrl.file_index = managerFileCount(SysCtrl.avi_list);
		if(SysCtrl.file_index>0)
		{
			video_playback_start(SysCtrl.file_index);
			playbackResolutionShow(handle);
			playbackFileNameShow(handle);
			playbackLockShow(handle);
		}
		else
			uiOpenWindow(&noFileWindow,0);
	}
	return 0;
}
static int playBackSysMsgUSB(winHandle handle,uint32 parameNum,uint32* parame)
{	
	playbackBaterryShow(handle);
	return 0;
}
static int playBackSysMsgBattery(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}
static int playBackSysMsgMD(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}
static int playBackOpenWin(winHandle handle,uint32 parameNum,uint32* parame)
{
	deg_Printf("playBack Open Win!!!\n");
	winSetName(handle,"play back");
	winSetResid(winItem(handle,PLAYBACK_MODE_ID),R_ID_ICON_MTPLAY2);
	#if SMALL_PANEL_SUPPORT==0
	playbackPoweOnTimeShow(handle,SysCtrl.powerOnTime);
	#endif
	playbackResolutionShow(handle);
	playbackFileNameShow(handle);
	playbackLockShow(handle);
	playbackMDShow(handle);
	playbackMonitorShow(handle);
	playbackIrLedShow(handle);
	playbackSDShow(handle);
	playbackMicShow(handle);
	playbackBaterryShow(handle);
	//playbackPlayTimeShow(handle,0,0);
	if(managerFileCount(SysCtrl.avi_list)<1)
	{
		uiOpenWindow(&noFileWindow,0);
	}
	return 0;
}
static int playBackCloseWin(winHandle handle,uint32 parameNum,uint32* parame)
{
	deg_Printf("playBack Close Win!!!\n");
	return 0;
}
static int playBackWinChildClose(winHandle handle,uint32 parameNum,uint32* parame)
{
	deg_Printf("playBack WinChild Close!!!\n");
	if(managerFileCount(SysCtrl.avi_list)<1)
	{
		uiOpenWindow(&noFileWindow,0);
		return 0;
	}
	else
	{
		video_playback_start(SysCtrl.file_index); 
	}
	#if SMALL_PANEL_SUPPORT==0
	playbackPoweOnTimeShow(handle,SysCtrl.powerOnTime);
	#endif
	playbackResolutionShow(handle);
	playbackFileNameShow(handle);
	playbackLockShow(handle);
	playbackMDShow(handle);
	playbackMonitorShow(handle);
	playbackIrLedShow(handle);
	playbackSDShow(handle);
	playbackMicShow(handle);
	playbackBaterryShow(handle);	
	return 0;
}
static int playBackSysMsgTimeUpdate(winHandle handle,uint32 parameNum,uint32* parame)
{
	INT32 playtime=0,totaltime = 0;
	videoPlaybackGetTime((u32*)&totaltime,(u32*)&playtime);
	if(playtime%1000 >500)
		playtime=playtime/1000;
	else
		playtime=playtime/1000;
	if(totaltime%1000 >500)
		totaltime = totaltime/1000 + 1;
	else 
		totaltime = totaltime/1000;
	playbackPlayTimeShow(handle,playtime,totaltime);
	return 0;
}

static int playBackSysMsg1S(winHandle handle,uint32 parameNum,uint32* parame)
{
	#if SMALL_PANEL_SUPPORT==0
	playbackPoweOnTimeShow(handle,SysCtrl.powerOnTime);
	#endif
	return 0;
}

msgDealInfor playBackMsgDeal[]=
{
	{SYS_OPEN_WINDOW,playBackOpenWin},
	{SYS_CLOSE_WINDOW,playBackCloseWin},
	{SYS_CHILE_COLSE,playBackWinChildClose},
	{KEY_EVENT_OK,playBackKeyMsgOk},
	{KEY_EVENT_UP,playBackKeyMsgUp},
	{KEY_EVENT_DOWN,playBackKeyMsgDown},
	{KEY_EVENT_MENU,playBackKeyMsgMenu},
	{KEY_EVENT_MODE,playBackKeyMsgMode},
	{SYS_EVENT_SDC,playBackSysMsgSD},
	{SYS_EVENT_USB,playBackSysMsgUSB},
	{SYS_EVENT_BAT,playBackSysMsgBattery},
	{SYS_EVENT_MD,playBackSysMsgMD},
	{SYS_EVENT_1S,playBackSysMsg1S},
	{SYS_EVENT_TIME_UPDATE,playBackSysMsgTimeUpdate},
	{EVENT_MAX,NULL},
};

WINDOW(playBackWindow,playBackMsgDeal,playBackWin)


