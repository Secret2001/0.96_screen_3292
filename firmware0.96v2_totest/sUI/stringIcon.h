#ifndef __STRING_ICON_H
#define __STRING_ICON_H
#include "widget.h"

typedef struct
{
	widgetObj widget;
	resID  str;
	charFont font;
	uint8 strAlign;
	uiColor fontColor;
	bool  visible;
}stringIconObj;

winHandle stringIconCreate(int16 x0,int16 y0,uint16 width,uint16 height,winHandle parent,uint16 style,uint16 id);
winHandle stringIconCreateIndirect(widgetCreateInfor* infor,winHandle parent,winCB cb);





#endif
