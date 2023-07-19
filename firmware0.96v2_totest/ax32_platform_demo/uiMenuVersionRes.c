#include"uiWin.h"
#if SMALL_PANEL_SUPPORT>0
enum
{
	VERSION_TIPS_ID=0,
	VERSION_LOG1_ID,
	VERSION_LOG2_ID,
};
static widgetCreateInfor versionWin[] =
{
	createFrameWin(Rx(70),Ry(50), Rw(180),Rh(140),R_COLOR_BLACK,WIN_ABS_POS),
	createStringIcon(VERSION_TIPS_ID,Rx(0),Ry(10), Rw(180),Rh(40),R_ID_STR_SET_VERSION,ALIGNMENT_CENTER, R_COLOR_WHITE,0),
	createStringIcon(VERSION_LOG1_ID,Rx(0),Ry(50), Rw(180),Rh(40),"AX3282S_CAR",ALIGNMENT_CENTER, R_COLOR_WHITE,0),
	createStringIcon(VERSION_LOG2_ID,Rx(0),Ry(90), Rw(180),Rh(40),"20181010",ALIGNMENT_CENTER, R_COLOR_WHITE,0),
	widgetEnd(),
};
#endif

