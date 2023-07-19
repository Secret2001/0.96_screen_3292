#include "rect.h"


static void rectCB(winMsg* msg)
{
	winHandle hWin=msg->hWin;
	rectObj* prect=(rectObj*)uiHandleToPtr(hWin);
	winObj* pWin=&(prect->widget.win);
	if(widgetProc(msg))
		return;
	switch(msg->id)
	{
		case MSG_WIN_CREATE:
			return;
		case MSG_WIN_PAINT:
			if(prect->select==false)
				drawRectangle((uiRect*)(msg->parameter.p),prect->color);
			else
				drawRectangle((uiRect*)(msg->parameter.p),prect->selectColor);
			return;
		case MSG_WIN_UNSELECT:
			if(prect->select==false)
				return;
			prect->select=false;
			if(winIsVisible(hWin))
				winChangeNotify(hWin);
			return;
		case MSG_WIN_SELECT:
			if(prect->select==true)
				return;
			prect->select=true;
			if(winIsVisible(hWin))
				winChangeNotify(hWin);
			return;
		case MSG_WIN_CHANGE_FG_COLOR:
			if(prect->color==msg->parameter.v)
				return;
			prect->color=msg->parameter.v;
			if(winIsVisible(hWin))
				winChangeNotify(hWin);
			return;
		case MSG_WIN_TOUCH:
			break;
		default:
			break;
	}
	winDefaultProc(msg);
}

winHandle rectCreate(int16 x0,int16 y0,uint16 width,uint16 height,winHandle parent,uint16 style,uint16 id)
{
	winHandle hrect;
	rectObj* prect;
	hrect=winCreate(x0,y0,width,height,parent,rectCB,sizeof(rectObj),WIN_WIDGET|style);
	widgetSetId(hrect,id);
	if(hrect!=INVALID_HANDLE)
	{
		prect=(rectObj*)uiHandleToPtr(hrect);
		prect->select=false;
	}
	return hrect;
}

winHandle rectCreateIndirect(widgetCreateInfor* infor,winHandle parent,winCB cb)
{
	winHandle hrect;
	rectObj* prect;
	hrect = rectCreate(infor->x0,infor->y0,infor->width,infor->height,parent,infor->style|WIN_TOUCH_SUPPORT,infor->id);
	if(hrect!=INVALID_HANDLE)
	{
		prect=(rectObj*)uiHandleToPtr(hrect);
		prect->color=infor->fontColor;
		winSetbgColor(hrect, infor->bgColor);
	}
	return hrect;
}





