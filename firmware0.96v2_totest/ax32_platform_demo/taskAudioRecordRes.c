#include"uiWin.h"

enum
{
	AUDIO_REC_TIME_ID=0,

};


static widgetCreateInfor audioRecordeWin[] =
{
	createFrameWin( Rx(0),Ry(0), Rw(320),Rh(240),R_COLOR_GRAY,WIN_ABS_POS),
	createStringIcon(INVALID_WIDGET_ID,Rx(100), Ry(70), Rw(120), Rh(25),strToResId("Audio Record"),ALIGNMENT_CENTER, R_COLOR_RED,0),
	createStringIcon(AUDIO_REC_TIME_ID,Rx(100), Ry(105), Rw(120), Rh(25),strToResId("00:00:00"),ALIGNMENT_CENTER, R_COLOR_RED,0),
	widgetEnd(),
};


static void audioRecTimeShow(winHandle handle,INT32U secodes)
{
	static char TimeStr[9];
	INT32U Minutes;
	Minutes=secodes/60;
	secodes=secodes%60;
	TimeStr[0]='0';
	TimeStr[1]='0';
	TimeStr[2]=':';
	TimeStr[3]=(Minutes/10)+'0';
	TimeStr[4]=(Minutes%10)+'0';
	TimeStr[5]=':';
	TimeStr[6]=(secodes/10)+'0';
	TimeStr[7]=(secodes%10)+'0';
	TimeStr[8]=0;
	winSetResid(winItem(handle,AUDIO_REC_TIME_ID),strToResId(TimeStr));
}


