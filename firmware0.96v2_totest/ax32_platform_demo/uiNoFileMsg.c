#include "uiNoFileRes.c"

static int noFileKeyMsgMode(winHandle handle,uint32 parameNum,uint32* parame)
{
	uint32 keyState=KEY_STATE_INVALID;
	if(parameNum==1)
		keyState=parame[0];
	if(keyState==KEY_PRESSED)
	{
		deamon_keysound_play();
		taskChange();
	}
	return 0;
}

static int noFileSysMsgSD(winHandle handle,uint32 parameNum,uint32* parame)
{
	if(SysCtrl.sdcard == SDC_STAT_NORMAL)
	{
		//if(managerFileCount(SysCtrl.avi_list)>0)
			winDestroy(&handle);
	}
	return 0;
}
static int noFileOpenWin(winHandle handle,uint32 parameNum,uint32* parame)
{
	deg_Printf("noFile open Win!!!\n");
	if(parameNum==1)
		winSetResid(winItem(handle,NO_FILE_TIP),parame[0]);
	return 0;
}
static int noFileCloseWin(winHandle handle,uint32 parameNum,uint32* parame)
{
	deg_Printf("noFile Close Win!!!\n");
	return 0;
}
static int noFileWinChildClose(winHandle handle,uint32 parameNum,uint32* parame)
{
	deg_Printf("noFile WinChild Close!!!\n");
	return 0;
}

msgDealInfor noFileMsgDeal[]=
{
	{KEY_EVENT_MODE,noFileKeyMsgMode},
	{SYS_OPEN_WINDOW,noFileOpenWin},
	{SYS_CLOSE_WINDOW,noFileCloseWin},
	{SYS_CHILE_COLSE,noFileWinChildClose},
	{SYS_EVENT_SDC,noFileSysMsgSD},
	{EVENT_MAX,NULL},
};

WINDOW(noFileWindow,noFileMsgDeal,noFileWin)



