#include"uiWin.h"
enum
{
	NO_FILE_TIP=0,
};
static widgetCreateInfor noFileWin[] =
{
	createFrameWin(Rx(0),Ry(0), Rw(320),Rh(240),R_COLOR_GRAY3,WIN_ABS_POS),
	createStringIcon(NO_FILE_TIP, Rx(0),Ry(105),Rw(320),Rh(30),R_ID_STR_FIL_NULL,ALIGNMENT_CENTER, R_COLOR_WHITE,0),
	widgetEnd(),
};



