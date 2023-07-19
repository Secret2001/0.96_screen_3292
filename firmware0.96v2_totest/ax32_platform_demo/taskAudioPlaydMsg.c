#include"taskAudioPlayRes.c"

extern int audio_play_start(int idx);
static uint32 getAudioPlayResInfor(uint32 item,uint32* image,uint32* str)
{
	if(image)
		*image=INVALID_RES_ID;
	if(str)
		*str=WAV_ID(item+1);
}

static int audioPlayOpenWin(winHandle handle,uint32 parameNum,uint32* parame)
{
	int sum;
	sum=managerFileCount(SysCtrl.wav_list);
	if(sum<0)
		sum=0;
	itemManageSetHeightAvgGap(winItem(handle,AUDIO_REC_SELECT_ID),R1h(33));
	itemManageCreateItem(winItem(handle,AUDIO_REC_SELECT_ID),itemCreatemenuOption,getAudioPlayResInfor,sum);
	itemManageSetCharInfor(winItem(handle,AUDIO_REC_SELECT_ID),0,ALIGNMENT_LEFT,R_COLOR_WHITE);
	itemManageSetSelectColor(winItem(handle,AUDIO_REC_SELECT_ID),R_COLOR_BLUE1);
	itemManageSetUnselectColor(winItem(handle,AUDIO_REC_SELECT_ID),R_COLOR_GRAY);
	itemManageSetCurItem(winItem(handle,AUDIO_REC_SELECT_ID),SysCtrl.file_index-1);
	if(sum==0)
		uiOpenWindow(&noFileWindow,1,"no audio file");
	return 0;
}
static int audioPlayCloseWin(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}
static int audioPlayWinChildClose(winHandle handle,uint32 parameNum,uint32* parame)
{
	int sum;
	sum=managerFileCount(SysCtrl.wav_list);
	if(sum<=0)
	{
		uiOpenWindow(&noFileWindow,1,"no audio file");
		return 0;
	}
	if(SysCtrl.file_index>sum)
			SysCtrl.file_index = 1;
	itemManageUpdateRes(winItem(handle,AUDIO_REC_SELECT_ID),sum,SysCtrl.file_index-1);
	return 0;
}
static int audioPlayKeyMsgOk(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	uint32 item;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		item=itemManageGetCurrentItem(winItem(handle,AUDIO_REC_SELECT_ID));
		if(SysCtrl.file_index!=item+1)
		{
			if(audioPlaybackGetStatus() != MEDIA_STAT_STOP)
				audioPlaybackStop();
		}
		SysCtrl.file_index=item+1;
		deg_Printf("audio play state ->%d\n",audioPlaybackGetStatus());
		if(audioPlaybackGetStatus() == MEDIA_STAT_STOP)
		{
			audio_play_start(SysCtrl.file_index);
		}
		else if(audioPlaybackGetStatus() == MEDIA_STAT_START)
		{
			audioPlaybackPuase();
		}
		else if(audioPlaybackGetStatus() == MEDIA_STAT_PAUSE)
		{
			audioPlaybackResume();
		}
	}
	return 0;
}
static int audioPlayKeyMsgUp(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED||keyState==KEY_CONTINUE)
	{
		itemManagePreItem(winItem(handle,AUDIO_REC_SELECT_ID));
	}
	return 0;
}
static int audioPlayKeyMsgDown(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED||keyState==KEY_CONTINUE)
	{
		itemManageNextItem(winItem(handle,AUDIO_REC_SELECT_ID));
	}
	return 0;
}
static int audioPlayKeyMsgMode(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		if(audioPlaybackGetStatus() != MEDIA_STAT_START)
			taskChange();
	}
	return 0;
}
static int audioPlaySysMsgSD(winHandle handle,uint32 parameNum,uint32* parame)
{
	int sum;
	deg_Printf("player : sdc stat ->%d\n",SysCtrl.sdcard);
	if((SysCtrl.sdcard != SDC_STAT_NORMAL)) // sdc out when recording
	{
		if(audioPlaybackGetStatus() != MEDIA_STAT_STOP)
			audioPlaybackStop();
		uiOpenWindow(&noFileWindow,1,"no audio file");
	}
	else
	{
		
		sum=managerFileCount(SysCtrl.wav_list);
		if(sum<=0)
		{
			uiOpenWindow(&noFileWindow,1,"no audio file");
			return 0;
		}
		if(SysCtrl.file_index>sum)
				SysCtrl.file_index = 1;
		itemManageUpdateRes(winItem(handle,AUDIO_REC_SELECT_ID),sum,SysCtrl.file_index-1);
	}
	return 0;
}

static int audioPlaySysMsgTimeUpdate(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}


msgDealInfor audioPlayMsgDeal[]=
{
	{SYS_OPEN_WINDOW,audioPlayOpenWin},
	{SYS_CLOSE_WINDOW,audioPlayCloseWin},
	{SYS_CHILE_COLSE,audioPlayWinChildClose},
	{KEY_EVENT_OK,audioPlayKeyMsgOk},
	{KEY_EVENT_UP,audioPlayKeyMsgUp},
	{KEY_EVENT_DOWN,audioPlayKeyMsgDown},
	{KEY_EVENT_MODE,audioPlayKeyMsgMode},
	{SYS_EVENT_SDC,audioPlaySysMsgSD},
	{SYS_EVENT_TIME_UPDATE,audioPlaySysMsgTimeUpdate},
	{EVENT_MAX,NULL},
};

WINDOW(audioPlayWindow,audioPlayMsgDeal,audioPlayWin)


