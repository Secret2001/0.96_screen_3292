#include"taskAudioRecordRes.c"


//定义需要处理的消息
static int audioOpenWin(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}
static int audioCloseWin(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}
static int audioWinChildClose(winHandle handle,uint32 parameNum,uint32* parame)
{
	return 0;
}
static int audioKeyMsgOk(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		if(audioRecordGetStatus() == MEDIA_STAT_START)
			audioRecordStop();
		else
			audioRecordStart();
	}
	return 0;
}
static int audioKeyMsgMode(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		if(audioRecordGetStatus() != MEDIA_STAT_START)
			taskChange();
	}
	return 0;
}
static int audioRecSysMsgTimeUpdate(winHandle handle,uint32 parameNum,uint32* parame)
{
	audioRecTimeShow(handle,audioRecordGetTime());
	return 0;
}


msgDealInfor audioRecordeMsgDeal[]=
{
	{SYS_OPEN_WINDOW,audioOpenWin},
	{SYS_CLOSE_WINDOW,audioCloseWin},
	{SYS_CHILE_COLSE,audioWinChildClose},
	{KEY_EVENT_OK,audioKeyMsgOk},
	{KEY_EVENT_MODE,audioKeyMsgMode},
	{SYS_EVENT_TIME_UPDATE,audioRecSysMsgTimeUpdate},
	{EVENT_MAX,NULL},
};

WINDOW(audioRecordWindow,audioRecordeMsgDeal,audioRecordeWin)


