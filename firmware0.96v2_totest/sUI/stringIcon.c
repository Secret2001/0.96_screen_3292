#include "stringIcon.h"


static void stringIconCB(winMsg* msg)
{
	winHandle hWin=msg->hWin;
	stringIconObj* pstringIcon=(stringIconObj*)uiHandleToPtr(hWin);
	winObj* pWin=&(pstringIcon->widget.win);
	strInfor* stringInfor;
	if(widgetProc(msg))
		return;
	switch(msg->id)
	{
		case MSG_WIN_CREATE:
			//debug_msg("stringIcon win create\n");
			return;
		case MSG_WIN_PAINT:
			
			if(pstringIcon->visible==true&&pstringIcon->str!=INVALID_RES_ID)
			{
				//debug_msg("paint stringIcon [%d]:[%d %d %d %d]\n",pstringIcon->widget.id,pWin->invalidRect.x0,pWin->invalidRect.y0,pWin->invalidRect.x1,pWin->invalidRect.y1);
				drawString(&pWin->rect,(uiRect*)(msg->parameter.p),pstringIcon->str,pstringIcon->font,pstringIcon->strAlign,pstringIcon->fontColor,pWin->bgColor);
			}
			else if(pWin->bgColor!=INVALID_COLOR)
			{
				//debug_msg("paint stringIcon bgcolor [%d]:[%d %d %d %d]\n",pstringIcon->widget.id,pWin->invalidRect.x0,pWin->invalidRect.y0,pWin->invalidRect.x1,pWin->invalidRect.y1);
				drawRectangle((uiRect*)(msg->parameter.p),pWin->bgColor);
			}
			return;
		case MSG_WIN_UPDATE_RESID:
			if(winIsVisible(hWin))
			{
				if(pWin->bgColor==INVALID_COLOR)
					winChangeNotify(hWin);
				else
					winUpdate(hWin);
			}
			return;
		case MSG_WIN_CHANGE_RESID:
			if(resIdIsStr(pstringIcon->str)==0&&pstringIcon->str==msg->parameter.v)
				return;
			pstringIcon->str=msg->parameter.v;
			if(winIsVisible(hWin))
			{
				if(pWin->bgColor==INVALID_COLOR)
					winChangeNotify(hWin);
				else
					winUpdate(hWin);
			}
			return;
		case MSG_WIN_CHANGE_STRINFOR:
			stringInfor=(strInfor*)(msg->parameter.p);
			pstringIcon->fontColor=stringInfor->fontColor;
			pstringIcon->strAlign=stringInfor->strAlign;
			pstringIcon->font=stringInfor->font;
			return;
		case MSG_WIN_VISIBLE_SET:
			if(pWin->bgColor==INVALID_COLOR)
				break;
			if(msg->parameter.v)
				pstringIcon->visible=true;
			else
				pstringIcon->visible=false;
			winUpdate(hWin);
			return;
		case MSG_WIN_VISIBLE_GET:
			if(pWin->bgColor==INVALID_COLOR)
				break;
			if(pstringIcon->visible)
				msg->parameter.v=1;
			else
				msg->parameter.v=0;
			return;
		case MSG_WIN_TOUCH:
			break;
		default:
			break;
	}
	winDefaultProc(msg);
}

winHandle stringIconCreate(int16 x0,int16 y0,uint16 width,uint16 height,winHandle parent,uint16 style,uint16 id)
{
	winHandle hstringIcon;
	stringIconObj* pstringIcon;
	hstringIcon=winCreate(x0,y0,width,height,parent,stringIconCB,sizeof(stringIconObj),WIN_WIDGET|style);
	widgetSetId(hstringIcon,id);
	if(hstringIcon!=INVALID_HANDLE)
	{
		pstringIcon=(stringIconObj*)uiHandleToPtr(hstringIcon);
		pstringIcon->str=INVALID_RES_ID;
		pstringIcon->fontColor=DEFAULT_COLOR;
		winSetbgColor(hstringIcon, INVALID_COLOR);
		pstringIcon->visible=true;
	}
	return hstringIcon;
}

winHandle stringIconCreateIndirect(widgetCreateInfor* infor,winHandle parent,winCB cb)
{
	winHandle hstringIcon;
	stringIconObj* pstringIcon;
	hstringIcon = stringIconCreate(infor->x0,infor->y0,infor->width,infor->height,parent,infor->style|WIN_TOUCH_SUPPORT,infor->id);
	if(hstringIcon!=INVALID_HANDLE)
	{
		pstringIcon=(stringIconObj*)uiHandleToPtr(hstringIcon);
		pstringIcon->str=infor->str;
		pstringIcon->strAlign=infor->strAlign;
		pstringIcon->fontColor=infor->fontColor;
		pstringIcon->font=infor->font;
		winSetbgColor(hstringIcon, infor->bgColor);
		pstringIcon->visible=true;
	}
	return hstringIcon;
}


