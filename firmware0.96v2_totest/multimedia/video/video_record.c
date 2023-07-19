/****************************************************************************
**
 **                              MULTIMEDIA
  ** *   **             THE APPOTECH MULTIMEDIA PROCESSOR
   **** **                  MULTIMEDIA video record
  *** ***
 **  * **               (C) COPYRIGHT 2016 BUILDWIN 
**      **                         
         **         BuildWin SZ LTD.CO  ; VIDEO PROJECT TEAM
          **   
* File Name   : video_record.c
* Author      : Mark.Douglas 
* Version     : V100
* Date        : 09/22/2016
* Description : This file is video record  file
*               
* History     : 
* 2016-09-22  : mark
*      <1>.This is created by mark,set version as v100.
*      <2>.Add basic functions & information
* 2017-07-13  : mark
*      <1>.modify sync timer when fps is lower than 20hz.The timer min-frq is 20hz
*      <2>.add option for insert vids frame.insert a old frame width real data or idx1 only 
******************************************************************************/
#include "../media.h"
#include "../multimedia.h"

#if  MEDIA_CFG_VIDEO_RECORD_EN > 0


/*******************************************************************************
* Function Name  : videoRecordTimeService
* Description    : for avi fps sync,irq call back function
* Input          : none
* Output         : none
* Return         : none
*******************************************************************************/
static void videoRecordTimeService(void)
{
//	videor_print("!");
	if(mediaVideoCtrl.stat == MEDIA_STAT_START)
	{
		mediaVideoCtrl.syncCounter++;
		if(mediaVideoCtrl.syncCounter<mediaVideoCtrl.syncValue)
			return ;
		mediaVideoCtrl.syncCounter = 0;
		mediaVideoCtrl.videoRecordSync++;
		mediaVideoCtrl.videoRecordTimeCounter+=mediaVideoCtrl.ftime;
		mediaVideoCtrl.tCounter+=mediaVideoCtrl.ftime;
		if(mediaVideoCtrl.ftime == 33){   //mdf videoRecordTimeCounter
			if((mediaVideoCtrl.videoRecordTimeCounter%100)==99)
				mediaVideoCtrl.videoRecordTimeCounter++;
		}
		if(mediaVideoCtrl.tCounter>=999)
		{
			mediaVideoCtrl.tCounter = 0;
			//mediaVideoCtrl.fCounter = 0;
		}
#if VIDEO_DBG_REC_EN >0
		mediaVideoCtrl.dbg_fps_c_time+=mediaVideoCtrl.ftime;
#endif
	}
	if(mediaVideoCtrlB.stat == MEDIA_STAT_START)
	{
		mediaVideoCtrlB.syncCounter++;
		if(mediaVideoCtrlB.syncCounter<mediaVideoCtrlB.syncValue)
			return ;
		mediaVideoCtrlB.syncCounter = 0;
		mediaVideoCtrlB.videoRecordSync++;
		mediaVideoCtrlB.videoRecordTimeCounter+=mediaVideoCtrlB.ftime;
		mediaVideoCtrlB.tCounter+=mediaVideoCtrlB.ftime;
		if(mediaVideoCtrlB.tCounter>=999)
		{
			mediaVideoCtrlB.tCounter = 0;
			//mediaVideoCtrlB.fCounter = 0;
		}
#if VIDEO_DBG_REC_EN >0
		mediaVideoCtrlB.dbg_fps_c_time+=mediaVideoCtrlB.ftime;
#endif
	}
}




static void videoRecordWatermark(void)
{
    INT8U *buffer;
	INT16U w,h;	
	
	char string[20];

	
	buffer = (INT8U *)hal_watermarkRam(mediaVideoCtrl.tinfo,&w,&h);
//	debg("LAYER=%d\n",mediaVideoCtrl.tinfo);
	//debg("-----width=%d height=%d------\n",w,h);
	

    if(buffer && w && h)
    {
		DATE_TIME_T *rtcTime = hal_rtcTimeGet();
		
		hal_rtcTime2StringExt(string,rtcTime);
	    string[19] = 0;


	    streamSprintf(string,buffer,w,mediaVideoCtrl.tfont);
//		debgbuf(string,20);
    }

}
void videoRecordImageWatermark(INT16U width,INT16U height,INT8U en)
{
	INT32U value,inv;
    if(en)
    {
		value = streamFont(width,height);
        if(mediaVideoCtrl.tfont!=(value&0xff));//change font,
		    hal_watermarkClear(mediaVideoCtrl.tinfo);
		mediaVideoCtrl.tfont = value&0xff;
		inv = 300;//((height*10)/240)*8/10;
		//deg_Printf("watermark pos : %d,%d,%d\n",height-(value>>8)-inv,value,inv);
		hal_watermarkPosition(mediaVideoCtrl.tinfo,150,height-(value>>8)-inv-20);
		videoRecordWatermark(); // update frame
		hal_watermarkEnable(mediaVideoCtrl.tinfo,1);
    }
	else
		hal_watermarkEnable(mediaVideoCtrl.tinfo,0);
}
int video_avi_write(int fd,void *buffer,INT32U len)
{
	int cnt;

	cnt = write(fd,buffer,len);

	if(cnt<0)
		return -1;

	return cnt;
}

/*******************************************************************************
* Function Name  : videoRecordInit
* Description    : initial video record 
* Input          : VIDEO_ARG_T *arg : video initial argument
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordInit(VIDEO_ARG_T *arg)
{		
	if(arg == NULL)
		return STATUS_FAIL;

    if(arg->fps ==  0)
		arg->fps = 25;  // default using 30fps 
	if(arg->fps == 25)
		mediaVideoCtrl.arg.sync_fps = 7;
	else if(arg->fps == 30)
		mediaVideoCtrl.arg.sync_fps = 8;
	//-------------------------video information-------------------------------------------
	mediaVideoCtrl.arg.audio = arg->audio;
	mediaVideoCtrl.arg.callback= arg->callback;
	mediaVideoCtrl.arg.fps = arg->fps;
	mediaVideoCtrl.arg.looprecord = arg->looprecord;
	mediaVideoCtrl.arg.rectime = arg->rectime*1000;  // change to ms
	mediaVideoCtrl.arg.resolution.width= arg->resolution.width;
	mediaVideoCtrl.arg.resolution.height=arg->resolution.height;
	mediaVideoCtrl.arg.quality = arg->quality;
	mediaVideoCtrl.arg.timestramp = arg->timestramp;
	mediaVideoCtrl.arg.ftype = arg->ftype;
	mediaVideoCtrl.arg.syncwr = arg->syncwr;
	mediaVideoCtrl.stat = MEDIA_STAT_STOP;

	//mediaVideoCtrl.tinfo = -1;
	mediaVideoCtrl.ftime = 1000/arg->fps;
	mediaVideoCtrl.space=0;
	mediaVideoCtrl.aviFd = -1;
	mediaVideoCtrl.idxFd = -1;
		
//-----------initial sensor-----------------------------		
//	sensor_actech_to_csi(); // initial cmos sensor
//-----------initial timestramp------------------------
	hal_watermarkClose(mediaVideoCtrl.tinfo);
	mediaVideoCtrl.tinfo = -1;
    mediaVideoCtrl.tinfo = hal_watermarkOpen();
    if(mediaVideoCtrl.tinfo<0)
		videor_print("video record : watermark open fail\n");
	else
		hal_watermarkCallbackRegister(mediaVideoCtrl.tinfo,videoRecordWatermark);
    

    hal_mjpegEncodeInit();
	
//	ax32xx_csi_only_FrameSet();

    hal_csiEnable(1);
	mediaVideoCtrl.mjpbuff_full=false;
	mediaVideoCtrl.jframe_cnt=0;
	memset(audiobuff,0,audioframesizeB*4);
	return STATUS_OK;
}
/*******************************************************************************
* Function Name  : videoRecordUninit
* Description    : uninitial video record 
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordUninit(void)
{
#if MEDIA_CFG_SYNC_TIMER_EN == 0
    XWorkDestory(mediaVideoCtrl.videoSync);
#else
	hal_timerStop(MEDIA_CFG_TIMER);
#endif
	
	mediaVideoCtrl.videoSync = NULL;
    hal_watermarkClose(mediaVideoCtrl.tinfo);
	mediaVideoCtrl.tinfo = -1;
	if(mediaVideoCtrl.idx1)
		hal_sysMemFree(mediaVideoCtrl.idx1);
	mediaVideoCtrl.idx1 = NULL;


    hal_auadcStop();
	hal_mjpegEncodeUninit();
    hal_csiEnable(0);
    
	return STATUS_OK;
}
/*******************************************************************************
* Function Name  : videoRecordFileStart
* Description    : start video record start for file handler
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordFileStart(Video_Ctrl_T *ctrl,int channel)
{
	int ret;
	FHANDLE fd[4];

	MEDIA_NULL_CHECK(ctrl,STATUS_FAIL);
    MEDIA_NULL_CHECK(ctrl->arg.callback,STATUS_FAIL);

	ctrl->stat = MEDIA_STAT_START;
    hal_sdLock();
	ret = ctrl->arg.callback(channel,CMD_VIDEO_RECORD_START,(INT32U)&fd[0]); // user create file

	if(ret<0)
	{
		hal_sdUnlock();
		return STATUS_FAIL;   // start fail
	}
    ctrl->space = ret; // kb 
   // deg_Printf("space:%d\n",ctrl->space);
	ctrl->aviFd = fd[0];

    if(ctrl->arg.ftype == AVI_TYPE_OPENDML)
    {
		ctrl->idxFd = fd[0]; // using the same file when fast write enable
		videor_print("video record : AVI TYPE OPEN DML.\n");

    }
    else if(ctrl->arg.ftype == AVI_TYPE_STANDARD)
    {
	     ctrl->idxFd = fd[1];
		 if(ctrl->idx1==NULL)
			 ctrl->idx1 = hal_sysMemMalloc(AVI_CFG_IDX1_BUFF_SIZE,64);
		 videor_print("video record : AVI type->STANDARD.\n");

    }
	else
	{
		videor_print("video record : unknow AVI type.%d\n",ctrl->arg.ftype);
		hal_sdUnlock();
		return STATUS_FAIL;   // start fail
	}
	//ctrl->fencoder = aviEncodeInit(ctrl->arg.ftype,video_avi_write);
	ret = aviEncodeInit(ctrl->arg.ftype,video_avi_write);
	if(ret < 0)
	{
		aviEncodeUninit(ctrl->fencoder);
		ret = aviEncodeInit(ctrl->arg.ftype,video_avi_write);
	}
	ctrl->fencoder = ret;
	ret = aviEncodeParse(ctrl->fencoder,ctrl->aviFd,ctrl->arg.resolution.width,ctrl->arg.resolution.height,ctrl->arg.fps,1,MEDIA_CFG_AVI_SAMPLERATE); // audio always on

	if(ret<0)
	{
		videor_print("video record : encode parse fail.%d\n",ret);
		ctrl->arg.callback(channel,CMD_COM_ERROR,(INT32U)&fd[0]); // video start fail
		hal_sdUnlock();
		return STATUS_FAIL;
	}
	ctrl->avihead = ret;

    ctrl->videoRecordTimeCounter = 0;
    ctrl->videoRecordSync = 0;// sync clear
    ctrl->fCounter = 0;
	ctrl->tCounter = 0;
	ctrl->fStart = 0;
	ctrl->videoRecordAudioCnt = 0;
	ctrl->videoFrameSize = 0;
	ctrl->syncCounter = 0;
	ctrl->filesize = 0;
	ctrl->photo = MEDIA_STAT_STOP;
#if VIDEO_DBG_REC_EN >0    
    ctrl->dbg_fps_c_time = 0;
	ctrl->dbg_fps_n_cnt  = 0;
	ctrl->dbg_fps_e_cnt = 0;
	ctrl->dbg_fps_s_cnt = 0;
#endif

	ctrl->mjpA_write_first=false;
	ctrl->mjpbuff_full=false;
	ctrl->mjp_last_write=false;
	//ctrl->jframe_cnt=0;
	ctrl->abchangetime=0;
	ctrl->write_flag=false;
	/*if(backrec_adpt())
	{
		mediaVideoCtrlB.restart_flag=false;	
	}
	 */
	ctrl->looptime=false;
    return STATUS_OK;
}
/*******************************************************************************
* Function Name  : videoRecordFileStop
* Description    : stop video record 
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordFileStop(Video_Ctrl_T *ctrl,int channel)
{
	INT32U length;
    FHANDLE fd[2];

    MEDIA_NULL_CHECK(ctrl,STATUS_FAIL);
	MEDIA_NULL_CHECK(ctrl->arg.callback,STATUS_FAIL);
	
	videor_print("video record : ready to stop\n");
	//ctrl->stat = MEDIA_STAT_STOP;
    if(ctrl->arg.ftype == AVI_TYPE_OPENDML)
    {
	     aviEncodeEnd(ctrl->fencoder,NULL,0,0);  // 
    }
    else
    {
	//---------------finish index file & update idx1 length
	    length = aviEncodeGetIdx1Length(ctrl->fencoder)%AVI_CFG_IDX1_BUFF_SIZE;
		write(ctrl->idxFd,ctrl->idx1,length);  // write remainning idx1 data

		fs_readsector(ctrl->idxFd,ctrl->idx1,1);  // read 1-secotor from first sector
	    aviEncodeSetIdx1(ctrl->fencoder,ctrl->idx1);  // update idx1 length
		fs_writesector(ctrl->idxFd,ctrl->idx1,1);

	//--------------merge avi file & index file
		fs_merge(ctrl->aviFd,ctrl->idxFd);  

	    lseek(ctrl->aviFd,0,0);
	    read(ctrl->aviFd,ctrl->idx1,ctrl->avihead);

		length = fs_size(ctrl->aviFd);

		aviEncodeEnd(ctrl->fencoder,ctrl->idx1,length,length-aviEncodeGetIdx1Length(ctrl->fencoder));

		lseek(ctrl->aviFd,0,0);
	    write(ctrl->aviFd,ctrl->idx1,ctrl->avihead);
	}

    if(ctrl->arg.callback)
    {
		fd[0] = ctrl->aviFd;
		fd[1] = ctrl->idxFd;
		ctrl->arg.callback(channel,CMD_VIDEO_RECORD_STOP,(INT32U)&fd[0]); 
    }
	aviEncodeUninit(ctrl->fencoder);
	
	ctrl->aviFd = -1;
	ctrl->idxFd = -1;
	ctrl->stat = MEDIA_STAT_STOP;
	videor_print("video record : stop.total frame = %d\n",aviEncodeGetFrameCount(ctrl->fencoder));
	videor_print("video record : audio time = %dms,video time = %dms,timer = %dms\n",ctrl->videoRecordAudioCnt/32,(aviEncodeGetFrameCount(ctrl->fencoder)*1000)/30,ctrl->videoRecordTimeCounter);

	
	
	
	
	//hal_sdStop();
	
   // hal_sdUnlock();
	return STATUS_OK;
}
/*******************************************************************************
* Function Name  : videoRecordFileError
* Description    : start video record error for file handler
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordFileError(Video_Ctrl_T *ctrl,int channel)
{
	FHANDLE fd[2];
	
	MEDIA_NULL_CHECK(ctrl,STATUS_FAIL);
	MEDIA_NULL_CHECK(ctrl->arg.callback,STATUS_FAIL);
	
	fd[0] = ctrl->aviFd;
	fd[1] = ctrl->idxFd;
	ctrl->arg.callback(channel,CMD_COM_ERROR,(INT32U)&fd[0]);   // close file & release file handle
	aviEncodeUninit(ctrl->fencoder);
	ctrl->stat = MEDIA_STAT_STOP;
	return STATUS_FAIL;
}
/*******************************************************************************
* Function Name  : videoRecordStart
* Description    : start video record
* Input          : AUDIO_RECORD_ARG_T *arg : video record argument
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
const u32 pic_size[][2]  =
{
	{640,  360},
	{640,  480},
	{1280, 720},
	{1280, 960},
	{1920, 1080},
	{2560, 1440},
	//{3840, 2160},
	//{4000, 3000},
};
const u32 picB_size[][2] =
{
	{640, 480},
	{1280, 720},
	{1280, 960},
};
int videoRecordStart(void)
{
	#if 0
	static int sel = 0, selB=0;
	mediaVideoCtrl.arg.resolution.width = pic_size[sel][0];
	mediaVideoCtrl.arg.resolution.height = pic_size[sel][1];
	mediaVideoCtrlB.arg.resolution.width = picB_size[selB][0];
	mediaVideoCtrlB.arg.resolution.height = picB_size[selB][1];
	sel++;
	selB++;
	if(sel>5)
		sel = 0;
	if(selB>2)
		selB = 0;
	#endif	 
    int ret;	
	mediaVideoCtrl.stat = MEDIA_STAT_START;
    if(videoRecordFileStart(&mediaVideoCtrl,VIDEO_CH_A)!=STATUS_OK)
    {
		mediaVideoCtrl.stat = MEDIA_STAT_STOP;
		goto VIDEO_REC_ERROR;
    }
	mediaVideoCtrlB.restart_flag=true;
	if (backrec_sensor_stat())  //when unsensor in
	{
		if(videoRecordFileStartB()!=STATUS_OK)  
		{
			//mediaVideoCtrlB.error = true;
			//videoRecordErrorB(0);
			videor_print("video record B : file start fail.\n");
			goto VIDEO_REC_ERROR;
		}
		mediaVideoCtrlB.restart_flag=false;
		mediaVideoCtrlB.usensor_in=true;
		videor_print("usensor in, video B file start.\n");
	}
#if MEDIA_CFG_SYNC_TIMER_EN == 0
    if(mediaVideoCtrl.videoSync == NULL)
        mediaVideoCtrl.videoSync = XWorkCreate(mediaVideoCtrl.ftime,videoRecordTimeService);  // register video time sync service
#else
    if(TIMER_FRQ_MIN>mediaVideoCtrl.arg.fps)
    {
		ret = TIMER_FRQ_MIN/mediaVideoCtrl.arg.fps;
		if((ret*mediaVideoCtrl.arg.fps)<TIMER_FRQ_MIN)
			ret++;
		mediaVideoCtrl.syncValue = ret;
		mediaVideoCtrlB.syncValue = ret;
		ret = ret*mediaVideoCtrl.arg.fps;
    }
	else
	{
		ret = mediaVideoCtrl.arg.fps;
		mediaVideoCtrl.syncValue = 1;
		mediaVideoCtrlB.syncValue = 1;
	}
    if(hal_timerStart(MEDIA_CFG_TIMER,ret,videoRecordTimeService)<0)  // 1000 hz  
    {
		videor_print("video record : sync timer start fail.\n",ret);
		goto VIDEO_REC_ERROR;
    }
#endif
    hal_mjpegEncodeResolution(mediaVideoCtrl.arg.resolution.width,mediaVideoCtrl.arg.resolution.height);

    ret = hal_auadcMemInit();  // auadc memory malloc 
    if(ret<0)
    {
		videor_print("video record : auadc memory malloc fail.\n");
		goto VIDEO_REC_ERROR;
    }
    ret = hal_mjpegMemInit();  // mjpeg memory malloc
    if(ret<0)
    {
		videor_print("video record : mjpeg memory malloc fail.\n");
		goto VIDEO_REC_ERROR;
    }

   // hal_ispFrameCnt(1);
   hal_watermarkBPos_Adjust(mediaVideoCtrlB.arg.resolution.height);
    ret = hal_mjpegAVIStart(mediaVideoCtrl.arg.resolution.width,mediaVideoCtrl.arg.resolution.height,mediaVideoCtrl.arg.quality,mediaVideoCtrl.arg.timestramp);
	if(ret<0)
	{
		videor_print("video record : mjpeg start fail\n");
		goto VIDEO_REC_ERROR;
	}
    //videoRecordImageWatermark(mediaVideoCtrl.arg.resolution.width,mediaVideoCtrl.arg.resolution.height,mediaVideoCtrl.arg.timestramp);

	ret = hal_auadcStartForAVI(MEDIA_CFG_AVI_SAMPLERATE,mediaVideoCtrl.arg.audio*100); // set adc for audio sample rate
	if(ret<0)
	{
		videor_print("video record : auadc start fail\n");
		goto VIDEO_REC_ERROR;
	} 
	if (backrec_adpt()&&mediaVideoCtrlB.usensor_in)
	{
		ret = hal_auadcMemInitB();  // auadc memory malloc 
		if(ret<0)
		{
			videor_print("video record B: auadc memory malloc fail.\n");
			goto VIDEO_REC_ERROR;
		}
		if(hal_mjpB_actech_as_avi(mediaVideoCtrlB.arg.resolution.width,mediaVideoCtrlB.arg.resolution.height,0)<0)
		{
			videor_print("video record B : mjpegB start fail\n");
			goto VIDEO_REC_ERROR;
		}
		hal_auadcStartForAVIB(MEDIA_CFG_AVI_SAMPLERATE,mediaVideoCtrlB.arg.audio*100); // set adc for audio sample rate
		mediaVideoCtrlB.mjpBStart=true;
		mediaVideoCtrlB.stat = MEDIA_STAT_START;
		videor_print("video record B : [%d:%d]start\n",mediaVideoCtrlB.arg.resolution.width,mediaVideoCtrlB.arg.resolution.height);

	}
	mediaVideoCtrl.stat = MEDIA_STAT_START;
	mediaVideoCtrl.jframe_cnt=0;
	mediaVideoCtrlB.jframe_cnt=0;
	videor_print("video record : [%d:%d]start\n",mediaVideoCtrl.arg.resolution.width,mediaVideoCtrl.arg.resolution.height);

	return STATUS_OK;
VIDEO_REC_ERROR:
	hal_mjpegEncodeStop();
	hal_auadcStop();
	if (backrec_adpt()&&(mediaVideoCtrlB.usensor_in))
	{
		api_mjp_avi_stop();
		videoRecordFileErrorB();
	}else {
		if(mediaVideoCtrlB.usensor_in)
			videoRecordFileErrorB();
	}
	
	videoRecordFileError(&mediaVideoCtrl,VIDEO_CH_A);
	hal_sdStop();
	hal_sdUnlock();
	videor_print("video record : video record start fail\n");
	return STATUS_FAIL;	
}
/*******************************************************************************
* Function Name  : videoRecordStop
* Description    : stop video record 
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordStop(void)
{
#if MEDIA_CFG_SYNC_TIMER_EN == 0
    XWorkDestory(mediaVideoCtrl.videoSync);
#else
	hal_timerStop(MEDIA_CFG_TIMER);
#endif

    hal_mjpegEncodeStop();

	hal_auadcStop();

	videoRecordImageWatermark(0,0,0);
	if(videoRecordStopB() != STATUS_OK)
	{
		hal_sdStop();
		hal_sdUnlock();
		return STATUS_FAIL;
	}
	if(videoRecordFileStop(&mediaVideoCtrl,VIDEO_CH_A) != STATUS_OK)
	{
		hal_sdStop();
		hal_sdUnlock();
		return STATUS_FAIL;
	}
	
	hal_sdStop();
	
    hal_sdUnlock();
	
	mediaVideoCtrl.stat = MEDIA_STAT_STOP;
	return STATUS_OK;
	//return videoRecordFileStop(&mediaVideoCtrl,VIDEO_CH_A);
}

uint32 videoRecordGetTimeSec(void)
{
	return aviEncodeGetFrameCount(mediaVideoCtrl.fencoder)/mediaVideoCtrl.arg.fps+1;
}

/*******************************************************************************
* Function Name  : videoRecordError
* Description    : video record error handler
* Input          : none
* Output         : none
* Return         : none
*******************************************************************************/
void videoRecordError(u8 err)
{
//if(err<5)  // sdc read /write error
    {
#if MEDIA_CFG_SYNC_TIMER_EN == 0
    XWorkDestory(mediaVideoCtrl.videoSync);
#else
	hal_timerStop(MEDIA_CFG_TIMER);
#endif		
		hal_mjpegEncodeStop();
		
		hal_auadcStop();
		
		api_mjp_avi_stop();
		
		videoRecordImageWatermark(0,0,0);

		videoRecordFileError(&mediaVideoCtrl,VIDEO_CH_A);
		mediaVideoCtrl.stat = MEDIA_STAT_STOP;
		if(mediaVideoCtrlB.stat == MEDIA_STAT_START)
		{
			videoRecordErrorB(0);
		}
		aviEncodeUninit(mediaVideoCtrl.fencoder);

		hal_sdStop();
		
	    hal_sdUnlock();

		
    }
   /* else
	videoRecordStop();
 
    videoRecordFileError(&mediaVideoCtrl,VIDEO_CH_A);
	
	//videoRecordStopB();
	 */

	videor_print("video record : error %d\n",err);
}
/*******************************************************************************
* Function Name  : videoRecordRestart
* Description    : pause video record restart for loop recording
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordRestart(void)
{
	int stime=0;  
	stime++;
#if 1	
	stime = XOSTimeGet();
	//videoRecordRestartB();
	
	if(mediaVideoCtrlB.mjpBStart)
	{
		videoRecordFileStopB();
	}
	videoRecordFileStop(&mediaVideoCtrl,VIDEO_CH_A);   // end current file
	hal_sdStop();
	
    hal_sdUnlock();
    videor_print("video record : restart stop time.%dms\n",XOSTimeGet()-stime);
	if(videoRecordFileStart(&mediaVideoCtrl,VIDEO_CH_A)<0)
	{
		videoRecordError(0); // stop
		videor_print("video record : file start fail.\n");
		return STATUS_FAIL;
	}
	mediaVideoCtrl.stat = MEDIA_STAT_START;
	if(backrec_adpt())
	{
		if(videoRecordFileStartB()!=STATUS_OK)  
		{
			//mediaVideoCtrlB.error = true;
			videoRecordErrorB(0);
			videor_print("video record B : file start fail.\n");
			return STATUS_FAIL;
		}
		mediaVideoCtrlB.stat = MEDIA_STAT_START;
		mediaVideoCtrlB.mjpBStart = true;
	}
    videor_print("video record : restart.%dms\n",XOSTimeGet()-stime);
#else
    stime = XOSTimeGet();
	videoRecordStop();
	//videoRecordFileStopB();
	videoRecordStart();
	//videoRecordFileStartB();
	videor_print("video record : restart.%dms\n",XOSTimeGet()-stime);
#endif
	return STATUS_OK;
}
int videoRecordRestart2(void)
{
	int stime=0;
	stime++;

	stime = XOSTimeGet();
	videoRecordStop();
	//videoRecordFileStopB();
	videoRecordStart();
	//videoRecordFileStartB();
	videor_print("[video record : restart.%dms]\n",XOSTimeGet()-stime);
	return STATUS_OK;
}
/*******************************************************************************
* Function Name  : videoRecordPuase
* Description    : pause video record 
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordPuase(void)
{
	return STATUS_OK;
}
/*******************************************************************************
* Function Name  : videoRecordResume
* Description    : resume video record 
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordResume(void)
{
	return STATUS_OK;
}
/*******************************************************************************
* Function Name  : videoRecordGetStatus
* Description    : get video record 
* Input          : none
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordGetStatus(void)
{
	return mediaVideoCtrl.stat;
}
/*******************************************************************************
* Function Name  : videoRecordGetTime
* Description    : get video record time in ms
* Input          : none
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordGetTime(void)
{
	return ((aviEncodeGetFrameCount(mediaVideoCtrl.fencoder)/mediaVideoCtrl.arg.fps)*1000);
//	return mediaVideoCtrl.videoRecordTimeCounter;
}
/*******************************************************************************
* Function Name  : videoRecordUpdateAviIdx1
* Description    : video update avi file idx1 to fs
* Input          : INT8U type : idx type,wb,dc,db
                      INT32U len : frame length
* Output         : none
* Return         : int 
                      
*******************************************************************************/
static int videoRecordUpdateAviIdx1(Video_Ctrl_T *ctrl,INT8U type,INT32U len,INT8U key)
{
	INT32S ret;

	MEDIA_NULL_CHECK(ctrl,STATUS_FAIL);

	ret = aviEncodeAddIdx(ctrl->fencoder,ctrl->idx1,type,key,len,AVI_CFG_IDX1_BUFF_SIZE);
	if(ret<=0)
		return ret;
	if(ctrl->arg.ftype == AVI_TYPE_STANDARD)
	{
		ret = write(ctrl->idxFd,ctrl->idx1,AVI_CFG_IDX1_BUFF_SIZE);
		if(ret<0)
			return -2;
		if(ret!=AVI_CFG_IDX1_BUFF_SIZE)
			return -3;

		fs_bound(ctrl->aviFd,ctrl->idxFd);
        if(ctrl->arg.syncwr)
        {
		    u32 size,*ptemp;
		    ptemp = (u32 *)ctrl->idx1;
			
			fs_readsector(ctrl->idxFd,ctrl->idx1,1);  // read 1-secotor from first sector
		    ptemp[3] = fs_size(ctrl->idxFd)-16;
			fs_writesector(ctrl->idxFd,ctrl->idx1,1);
		    size = fs_size(ctrl->idxFd);
			
			size +=fs_size2(ctrl->aviFd);
		    fs_readsector(ctrl->aviFd,ctrl->idx1,ctrl->avihead>>9);
			aviEncodeEnd(ctrl->fencoder,ctrl->idx1,size,size-aviEncodeGetIdx1Length(ctrl->fencoder));
			fs_writesector(ctrl->aviFd,ctrl->idx1,ctrl->avihead>>9);
	    }
	}
	
	return 0;
}

/*******************************************************************************
* Function Name  : videoRecordService
* Description    : video record service
* Input          : none
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordService(void)
{
//	static INT8U errFlag = 0;
	INT32S res;/*icnt,fflag;*/
	INT32U insert;
	INT32U addr,size,addr1,size1,size2;
	void *buff_vids,*buff_auds;//,*tbuff;
	INT32S sync_vids,sync_auds,icnt,sync_vids_next, sync_auds_next;
	bool auds_flag=false;
	INT32U *temp;
	s32 alignsize=0;

	

	if(mediaVideoCtrl.stat != MEDIA_STAT_START)
		return mediaVideoCtrl.stat;
//	debg("6");
//----------------space check	
    if(mediaVideoCtrl.arg.ftype==AVI_TYPE_STANDARD)
    {
	    size = fs_size(mediaVideoCtrl.aviFd);
		if(mediaVideoCtrlB.mjpBStart)
			size+=fs_size(mediaVideoCtrlB.aviFd);
		 
	       size+= fs_size(mediaVideoCtrl.idxFd);
		if(mediaVideoCtrlB.mjpBStart)
			size+=fs_size(mediaVideoCtrlB.idxFd);
		 
		 size>>=10;/**/
	    if((mediaVideoCtrl.space-size)<(32<<10))
	    {
			//sysLog("requer space");
			videor_print("video record : requre space,%d,%d\r\n",mediaVideoCtrl.space,size);
			if(mediaVideoCtrl.arg.looprecord==0)
			{
				videoRecordStop();
				mediaVideoCtrl.arg.callback(VIDEO_CH_A,CMD_COM_CHECK,0);  // this will set sdc full show
				return mediaVideoCtrl.stat;
			}
			int ret = mediaVideoCtrl.arg.callback(VIDEO_CH_A,CMD_COM_CHECK,mediaVideoCtrl.space+(100<<10)); // 100M
			if(ret<0)
			{
				videor_print("video record : requre space fail.\r\n");
				res = 5;
				goto VIDEO_RECORD_ERROR;
			}
			ret<<=10;
			if((ret-size)<(32<<10)) // 20M
			{
				//sysLog("no more space");
				videor_print("video record : no more space,%dkb\r\n",ret-size);
				//videoRecordStop();
				//if(mediaVideoCtrl.arg.looprecord)
				//	videoRecordStart(); // restart
				videoRecordRestart(); // restart		
				return mediaVideoCtrl.stat;
			}
			else
			{
				//sysLog("get space ok");
				mediaVideoCtrl.space = ret;//-size;
			}
	    }
    }
	else if(mediaVideoCtrl.arg.ftype==AVI_TYPE_OPENDML)
	{
		size = fs_tell(mediaVideoCtrl.aviFd)>>10;
		if(mediaVideoCtrlB.mjpBStart)
			size2=fs_tell(mediaVideoCtrlB.aviFd)>>10;
		else
			size2 =0;
		if(((mediaVideoCtrl.space-size)<1024)||(size2 && ((mediaVideoCtrlB.space-size2)<1024)))
		{
			videor_print("video record :free=%dKB, size1 %dkb,size2 %dkb\n",mediaVideoCtrl.space,size,size,size2);
			//videor_print("video record : size1 %dkb,size2 %dkb\n",mediaVideoCtrl.space-size,mediaVideoCtrlB.space-size2);
			//videor_print("B:%d,%d\n",mediaVideoCtrlB.space,size2);
			//videoRecordStop();
			//if(mediaVideoCtrl.arg.looprecord)
				videoRecordRestart(); // restart
				return mediaVideoCtrl.stat;
		}
	}
//-----------------mjpA write control----------------------------------- 
	if(mediaVideoCtrlB.mjpBStart){  //loop record control for A&B record
		if((mediaVideoCtrl.looptime)&&(!mediaVideoCtrlB.looptime))
			return mediaVideoCtrl.stat;
		if((!mediaVideoCtrl.looptime)&&(mediaVideoCtrlB.looptime))
			goto VIDEO_RECORD_VIDEO_FRAME;
		if((mediaVideoCtrl.looptime)&&(mediaVideoCtrlB.looptime)){
			if(mediaVideoCtrl.jframe_cnt<0x3dcc500)  //not stop mjpeg restart,time>25 days
				videoRecordRestart();
			else
				videoRecordRestart2();
			return mediaVideoCtrl.stat;
		}
	}
	//when mjpA and mjpB buff is pre full at the same time,write mjpA first,and not write mjpB until mjpA is not half full
	if(mediaVideoCtrlB.mjpBStart){
		if(!mediaVideoCtrl.mjpA_write_first){
			if(hal_mjpB_Buffer_prefull()&&(hal_mjpegRawBuffer_prefull()||hal_adcBuffer_prefull()))
			{
				mediaVideoCtrl.mjpA_write_first=true;
				//sysLog("A B Buff full");
				//videor_print("A B Buff full\n");
				if(mediaVideoCtrlB.write_flag){
					mediaVideoCtrlB.mjp_last_write=true;
					return mediaVideoCtrl.stat;
				}
			}
		}else{
			if(!(hal_mjpegRawBuffer_halffull()||hal_adcBuffer_halffull())){
				mediaVideoCtrl.mjpA_write_first=false;
				mediaVideoCtrl.mjp_last_write=true;//judge mjpA last write,have to align 32k
				mediaVideoCtrl.mjpbuff_full=false;
				mediaVideoCtrlB.mjpbuff_full=true;
			}
		}
	}
	if(mediaVideoCtrl.mjpA_write_first) //mjpA and mjpB buff are full at the same time,write mjpA first
	{
		
		goto VIDEO_RECORD_VIDEO_FRAME;
	}
	//before change to mjpB writing, align 32k to keep sd card write speed
	if((mediaVideoCtrl.mjp_last_write)&&(mediaVideoCtrl.arg.ftype == AVI_TYPE_OPENDML))
	{
		alignsize=hal_sdNextLBA()&(0x3f);
		if(alignsize)
		{
			temp = (INT32U *)audiobuff;
			temp[0]=0x4B4E554A;
			temp[1]=(64-alignsize)*512-8;
			size=(64-alignsize)*512;
			res = write(mediaVideoCtrl.aviFd,(void *)audiobuff,size);
			if(res!=size)
			{
				sysLog("error no 5");
				res = 4;
				goto VIDEO_RECORD_ERROR;
			}
			aviEncodeAddofs(mediaVideoCtrl.aviFd,size);
			//videor_print("Fill Junk:%x\n",size);
			alignsize=0;
			
		}
		mediaVideoCtrl.mjp_last_write=false;
		mediaVideoCtrl.write_flag=false;
		return mediaVideoCtrl.stat;
	}
	
	
	if(mediaVideoCtrlB.mjpBStart)
	{
		//when mjpA buff is not pre full, not write data,but check whether buff is pre full
		if(!mediaVideoCtrl.mjpbuff_full){
			if(!((hal_mjpegRawBuffer_prefull())||(hal_adcBuffer_prefull()))){
				mediaVideoCtrl.mjpbuff_full=false;
				mediaVideoCtrlB.mjpbuff_full=true;
				
				return mediaVideoCtrl.stat;
			}
			else{
				mediaVideoCtrl.mjpbuff_full=true;
				
				mediaVideoCtrlB.mjpbuff_full=false;
				if(mediaVideoCtrl.fStart){
					mediaVideoCtrlB.mjp_last_write=true;//judge mjpB last write,have to align 32k
					mediaVideoCtrl.abchangetime = XOSTimeGet();	
					//if(hal_mjpegRawBuffer_prefull()) deg_Printf("mjpegA buff full\n");
					//if(hal_adcBuffer_prefull()) deg_Printf("adc buff full\n");
					//videor_print("video A write,B->A change time:%dms\n",mediaVideoCtrl.abchangetime-mediaVideoCtrlB.abchangetime);	
				}
				else{
					mediaVideoCtrl.abchangetime = XOSTimeGet();	
				}
				return mediaVideoCtrl.stat;
			}
		}	
	}
//----------------frame sync--------------------------------------------------------------

//-----------------video frame----------------------------------- if system bus is enough,user can add one more functions to take photo when recording
//    buff = hal_mjpegRawDataGet(&tbuff,&addr,&size);   // get jpeg frame addr & jpeg size.a total frame contains some of small buffers.here is the total size & start buffer addr
 //   icnt = 0;
	
VIDEO_RECORD_VIDEO_FRAME:
	mediaVideoCtrl.write_flag=true;
//	deg_Printf("video frame\n");
   buff_vids = hal_mjpegRawBufferGet(NULL,&addr,&size,&sync_vids, &sync_vids_next);
   buff_auds = hal_auadcBufferGet(&addr1,&size1,&sync_auds, &sync_auds_next);


/*   if((sync_vids>sync_auds)&&(sync_auds!=0)&&(sync_vids!=0)&&(!mediaVideoCtrl.fStart )) //err: auds start when there is not vids 
   {
		videor_print("<warning!>auds start when there is not vids\n");
		if(buff_auds)
		{
			hal_auadcBufferRelease(buff_auds);
			mediaVideoCtrl.jframe_cnt=sync_auds;
			return mediaVideoCtrl.stat;
		}
	}
	 */
	//case1: ex. file fisrt write, sync_vids = 7, sync_auds = 7 ; or not sync_vids but has sync_auds
	if ((!mediaVideoCtrl.fStart)&&(sync_auds!=0)&&((sync_vids>=sync_auds)||(!buff_vids)))//err: auds start before vids 
	{
		videor_print("<warning!>auds start before vids\n");
		if(buff_auds)
			hal_auadcBufferRelease(buff_auds);
		mediaVideoCtrl.jframe_cnt=sync_auds;
		mediaVideoCtrl.u_tsync_old=sync_auds;
		mediaVideoCtrl.iframe_ctr=0;
		return mediaVideoCtrl.stat;
	}
	//case 2:ex. sync_vids = 15, sync_auds = 7 ; or sync_vids = 15, sync_auds = 7, mediaVideoCtrl.jframe_cnt = 7
	if (((sync_vids>=sync_auds+mediaVideoCtrl.arg.sync_fps)||((sync_vids>=mediaVideoCtrl.jframe_cnt+mediaVideoCtrl.arg.sync_fps)&&(sync_vids>=sync_auds)))\
		&&(buff_vids)&&(buff_auds)) //when drop too many vids frame
	{
		deg_Printf("vids:%d,auds:%d,fc:%d\n",sync_vids,sync_auds,mediaVideoCtrl.jframe_cnt);
		if(buff_auds)
		{
			videor_print("<warning!>drop too many vids\n");
			hal_auadcBufferRelease(buff_auds);
			mediaVideoCtrl.jframe_cnt=sync_auds;
			mediaVideoCtrl.u_tsync_old=sync_auds;
			mediaVideoCtrl.iframe_ctr=0;
			return mediaVideoCtrl.stat;
		}
	}
    //case 3 :ex. not buff_auds, and  sync_vids = 23, mediaVideoCtrl.jframe_cnt = 15
	if ((buff_vids)&&(sync_vids>=mediaVideoCtrl.jframe_cnt+mediaVideoCtrl.arg.sync_fps))
	{
		deg_Printf("vids:%d,auds:%d,fc:%d\n",sync_vids,sync_auds,mediaVideoCtrl.jframe_cnt);
		mediaVideoCtrl.jframe_cnt=sync_vids;
		mediaVideoCtrl.iframe_ctr=0;
		
	}
	//case 4: ex. sync_vids = 23, sync_auds = 23 ,but the sync_vids 15 had not writen at least once 
	if((sync_vids==sync_auds)&&(buff_auds)&&(mediaVideoCtrl.iframe_ctr == 0)){ 
		deg_Printf("[case 4 : drop the auds frame:%d]\n",sync_auds);
		hal_auadcBufferRelease(buff_auds);
		mediaVideoCtrl.u_tsync_old=sync_auds;
		mediaVideoCtrl.jframe_cnt=sync_auds;
		return mediaVideoCtrl.stat;
	}
	if((!mediaVideoCtrl.fStart)&&(buff_vids))
	{
		mediaVideoCtrl.u_tsync_old=sync_vids;
		//mediaVideoCtrl.jframe_cnt = sync_vids;
		mediaVideoCtrl.iframe_ctr=0;
	}
	if((!buff_vids)&&(buff_auds))//write auds frame
		auds_flag=true;
	/*if((sync_vids==sync_auds)&&(buff_auds))
		auds_flag=true;
	if(auds_flag)
		goto VIDEO_RECORD_AUDIO_FRAME;
	if((sync_vids!=0)||(sync_auds!=0))
		deg_Printf("vids:%d,auds:%d,fc:%d\n",sync_vids,sync_auds,mediaVideoCtrl.jframe_cnt);*/

//---------------------video frame ------------------------------------------------------------
	if(buff_vids)
	{
		//fflag = 1;
		if(size==0){
			debg("size error\n");
		} 
		//videor_print("-");
		
		/*if(mediaVideoCtrl.videoRecordSync<aviEncodeGetFrameCount(mediaVideoCtrl.fencoder))
		{
			hal_mjpegRawDataSet(buff);	
			goto VIDEO_RECORD_AUDIO_FRAME;
		}
		*/
		if(mediaVideoCtrl.u_tsync_old==sync_vids)
		{
			mediaVideoCtrl.iframe_ctr++;	
		}else{
			mediaVideoCtrl.iframe_ctr = 0;
			mediaVideoCtrl.icnt_control = sync_vids-mediaVideoCtrl.u_tsync_old;
			if(mediaVideoCtrl.icnt_control>mediaVideoCtrl.arg.sync_fps)  mediaVideoCtrl.icnt_control = mediaVideoCtrl.arg.sync_fps;
			mediaVideoCtrl.u_tsync_old = sync_vids;
		}	
		icnt=0;
VIDEO_RECORD_SYNC_FPS:		
		if(size>mediaVideoCtrl.videoFrameSize)
			mediaVideoCtrl.videoFrameSize = size;
		aviEncodeFrameTag(mediaVideoCtrl.fencoder,(INT32U *)addr,AVI_FRAME_DC_VIDEO,size-8);
	//	deg_Printf("addr:%x,size:%x\n",addr,size);
	//	mediaVideoCtrl.space-=size>>10;
		
		
		insert = 0;	
		if(mediaVideoCtrl.arg.ftype == AVI_TYPE_OPENDML){
			res = write(mediaVideoCtrl.aviFd,(void *)addr,size);
		//	debg("1");
		}
		else
			res = write(mediaVideoCtrl.aviFd,(void *)addr,size);	
			
		if(res!=size)
		{
			hal_mjpegRawDataSet(buff_vids);
			sysLog("error no 1");
		//	deg_Printf("addr:%x,size:%x\n",addr,size);
			res = 1;
			goto VIDEO_RECORD_ERROR;
		}
        if((mediaVideoCtrl.photo == MEDIA_STAT_START)&&(size>0))
        {
			write(mediaVideoCtrl.photoFd,(void *)(addr+8),size-8);
			mediaVideoCtrl.photo = MEDIA_STAT_STOP;
        }
		insert+=size;

		mediaVideoCtrl.fStart |= 1;  // set video start flag
		if(videoRecordUpdateAviIdx1(&mediaVideoCtrl,AVI_FRAME_DC_VIDEO,insert,1)<0)
		{
			sysLog("error no 2");
			res = 2;
			hal_mjpegRawDataSet(buff_vids);	
			goto VIDEO_RECORD_ERROR;
		}
		/*if(backrec_adpt())
			alignsize+=size/512;
			 */
		mediaVideoCtrl.jframe_cnt++;
		if (sync_vids_next-sync_vids==mediaVideoCtrl.arg.sync_fps){
			if(mediaVideoCtrl.iframe_ctr==3)
			{
				//videor_print("|");
				mediaVideoCtrl.iframe_ctr++;
				goto VIDEO_RECORD_SYNC_FPS;
			}
		}
		 
		while(((mediaVideoCtrl.jframe_cnt)<=sync_vids)&&((sync_auds==0)||((mediaVideoCtrl.jframe_cnt)<=sync_auds)))//insert frame
		{
			if(sync_auds){ // need to write auds frame
				auds_flag=true;
			}
			
			//videor_print("|");
			//videor_print("vids:%d,auds:%d,fc:%d\n",sync_vids,sync_auds,mediaVideoCtrl.jframe_cnt);
			//videor_print("fc:%d,vids:%d,auds:%d,jc:%d\n",mediaVideoCtrl.jframe_cnt,sync_vids,sync_auds,icnt);
			if(icnt>3){ //insert 8 frame max
				//videor_print("vids:%d,auds:%d,fc:%d\n",sync_vids,sync_auds,mediaVideoCtrl.jframe_cnt);
				deg_Printf("<warning!>insert too many vids frame\n");
				break;
			}
			
			#if 0//VIDEO_DBG_REC_EN >0			
				mediaVideoCtrl.dbg_fps_n_cnt++;
			#endif
			icnt++;
			mediaVideoCtrl.iframe_ctr++;
				goto VIDEO_RECORD_SYNC_FPS;
			
		}
		if((sync_vids==sync_auds)&&(sync_auds!=0)) 
			auds_flag=true;
/*
#if MEDIA_CFG_VIDEO_SYNC_FPS>0
        while(mediaVideoCtrl.videoRecordSync>(aviEncodeGetFrameCount(mediaVideoCtrl.fencoder)+1))
        {
			if(icnt>=2)  // 2-frame max
				break;
		#if VIDEO_DBG_REC_EN >0			
			mediaVideoCtrl.dbg_fps_n_cnt++;
		#endif
		    icnt++;
			goto VIDEO_RECORD_SYNC_FPS;
        }

#endif	
*/
		hal_mjpegRawDataSet(buff_vids);		
	}

	icnt=0;
//---------------------audio frame ------------------------------------------------------------
//VIDEO_RECORD_AUDIO_FRAME:	
	if(auds_flag&&(buff_auds))
	{
		if(size1==0) videor_print("<audio size error>\n");
		//	mediaVideoCtrl.space-=size>>10;		
		//videor_print("*");
		aviEncodeFrameTag(mediaVideoCtrl.fencoder,(INT32U *)addr1,AVI_FRAME_WD_AUDIO,size1-8);
		
		if(mediaVideoCtrl.arg.ftype == AVI_TYPE_OPENDML)
			res = write(mediaVideoCtrl.aviFd,(void *)addr1,size1);
		else
			res = write(mediaVideoCtrl.aviFd,(void *)addr1,(UINT)size1);
	
		//videor_print("auds:%d\n",sync_auds);
		hal_auadcBufferRelease(buff_auds);
		
		if(res!=size1)// write error
		{
			sysLog("error no 4");
			res = 4;
			goto VIDEO_RECORD_ERROR;
		}

		if(videoRecordUpdateAviIdx1(&mediaVideoCtrl,AVI_FRAME_WD_AUDIO,size1,1)<0)
		{
			sysLog("error no 2");
			res = 2;
			//hal_mjpegRawDataSet(buff);	
			goto VIDEO_RECORD_ERROR;
		}
		/*if(backrec_adpt())
			alignsize+=size1/512;
			 */
		mediaVideoCtrl.fStart|=2;  // audio frame ok
		mediaVideoCtrl.videoRecordAudioCnt+=size1-8;
		auds_flag=false;
			//mediaVideoCtrl.audioframewrite=true;

	}
	

//---------------------avi service-----------------------------------------------------------------
	aviEncodeService(mediaVideoCtrl.fencoder);
//-------------------video frame sync--------------------------------------------------------
#if 0//MEDIA_CFG_VIDEO_SYNC_FPS == 0
    icnt  = 0;
    if((mediaVideoCtrl.fStart&1)&&(fflag==0)) // video first frame ok
    {
		while(mediaVideoCtrl.videoRecordSync>(aviEncodeGetFrameCount(mediaVideoCtrl.fencoder)+1))
		//while((mediaVideoCtrl.videoRecordSync/33) >aviEncodeGetFrameCount())
		{	
			res = videoRecordUpdateAviIdx1(&mediaVideoCtrl,AVI_FRAME_DC_VIDEO,0,0);
			if(res<0)// insert repeat frame
			{
				sysLog("error no 3");
				//videor_print("video record : res = %d\n",res);
				res = 3;
				goto VIDEO_RECORD_ERROR;
			}
		#if VIDEO_DBG_REC_EN >0			
			mediaVideoCtrl.dbg_fps_n_cnt++;
		#endif
			icnt++;
		    //videor_print(".");
		   // mediaVideoCtrl.fCounter++;
			if(icnt>=1)
				break;
		}
    }

#endif	

//------------------------------time check---------------------------------------------------------
    /*if(mediaVideoCtrl.arg.looprecord==0)
	{
		if((fs_size(mediaVideoCtrl.aviFd)>>20)>=3886)
		{
		//	videoRecordStop();
		//	videoRecordStart();
			videoRecordRestart();
		}
	}
	else*/
	{
		/*if(mediaVideoCtrl.videoRecordTimeCounter >= mediaVideoCtrl.arg.rectime)*/
		{
			if((((mediaVideoCtrl.arg.rectime/1000)*mediaVideoCtrl.arg.fps)<=aviEncodeGetFrameCount(mediaVideoCtrl.fencoder))/*\
				||(mediaVideoCtrl.videoRecordTimeCounter >= mediaVideoCtrl.arg.rectime)*/)
			{
				//videoRecordStop();
				//videoRecordStart(); // restart
				//if(mediaVideoCtrl.mjp_last_write)//align 32k
				if(mediaVideoCtrlB.mjpBStart){
					mediaVideoCtrl.looptime=true;
					/*buff_vids = hal_mjpegRawBufferGet(NULL,&addr,&size,&sync_vids,&sync_vids_next);
					buff_auds = hal_auadcBufferGet(&addr1,&size1,&sync_auds,&sync_auds_next);
					if((buff_auds)&&((!buff_vids)||(sync_vids==sync_auds)))
					{
						if(icnt==0)
						{
							auds_flag=true;
							icnt++;
							goto VIDEO_RECORD_AUDIO_FRAME;
						}
					}*/
					alignsize=hal_sdNextLBA()&(0x3f);
					if(alignsize)
					{
						temp = (INT32U *)audiobuff;
						temp[0]=0x4B4E554A;
						temp[1]=(64-alignsize)*512-8;
						size=(64-alignsize)*512;
						res = write(mediaVideoCtrl.aviFd,(void *)audiobuff,size);
						if(res!=size)
						{
							sysLog("error no 5");
							res = 4;
							goto VIDEO_RECORD_ERROR;
						}
						aviEncodeAddofs(mediaVideoCtrl.aviFd,size);
						//videor_print("Fill Junk:%x\n",size);
						alignsize=0;
			
					}
					mediaVideoCtrl.mjp_last_write=false;
					mediaVideoCtrl.write_flag=false;
					videor_print("Video A ready to stop.\n");
				}
				else{
					if(mediaVideoCtrl.jframe_cnt<0x3dcc500)  //not stop mjpeg restart,time>25 days
						videoRecordRestart();
					else
						videoRecordRestart2();
					//videoRecordRestart();		
				}		
			
			}
		}
	}

	
//------------------------------debug information print-----------------------------------------------	
#if 0//VIDEO_DBG_REC_EN >0
    
    mediaVideoCtrl.dbg_fps_s_cnt += hal_ispFrameCnt(1);
	if(mediaVideoCtrl.dbg_fps_c_time>=9999) // counting real time fps by 10-second
	{	
		INT32U fpsi,fpsf;		
		videor_print("video record : [%d:%d]{%x}-",mediaVideoCtrl.arg.resolution.width,mediaVideoCtrl.arg.resolution.height,mediaVideoCtrl.videoFrameSize);  // reslution
		fpsi = (mediaVideoCtrl.dbg_fps_s_cnt*1000)/10;
		fpsf = fpsi%1000;
		fpsi/=1000;
		videor_print("[sensor:%d",fpsi);
		if(fpsf)
            videor_print(".%dfps]",fpsf);   // sensor frame rate
        else
			videor_print(".000fps]");   // sensor frame rate
		if(mediaVideoCtrl.dbg_fps_n_cnt>300)
			mediaVideoCtrl.dbg_fps_n_cnt = 300;
        fpsi = (mediaVideoCtrl.dbg_fps_n_cnt*1000)/10;
		fpsf = fpsi%1000;
		fpsi/=1000;
		videor_print("<insert:%d",fpsi);
		if(fpsf)
			videor_print(".%dfps>",fpsf);     //insert frame rate
		else
			videor_print(".000fps>");     //insert frame rate
		res = mediaVideoCtrl.arg.fps*10-mediaVideoCtrl.dbg_fps_n_cnt;  // frame cnt in 10-second
		fpsi = (res*1000)/10;
		fpsf = fpsi%1000;
		fpsi/=1000;
		videor_print("frame rate = %d",fpsi);
		if(fpsf)
	        videor_print(".%dfps\n",fpsf);  // mjpeg frame rate
	    else
			videor_print(".000fps\n");  // mjpeg frame rate
       // if(mediaVideoCtrl.dbg_fps_n_cnt>=300)
		//	errFlag =1;
		mediaVideoCtrl.videoFrameSize = 0;
		mediaVideoCtrl.dbg_fps_c_time = 0;
        mediaVideoCtrl.dbg_fps_n_cnt = 0;
        mediaVideoCtrl.dbg_fps_e_cnt = 0;
		mediaVideoCtrl.dbg_fps_s_cnt = 0;
		//videor_print("remain space = %dKB\n",mediaVideoCtrl.space);
	//	debg("F:%d,f:%d\n",(mediaVideoCtrl.videoRecordSync/33),aviEncodeGetFrameCount());
	}
#endif
    return mediaVideoCtrl.stat;
	
VIDEO_RECORD_ERROR:
	videor_print("video record : error no %d.space=%dKB\n",res,mediaVideoCtrl.space);

    videoRecordError(res);  // recorder can not handler this error.only stop recording
    
	return mediaVideoCtrl.stat;
}
/*******************************************************************************
* Function Name  : videoRecordCmdSet
* Description    : video record set paramater
* Input          : INT32U cmd : command
                      INT32U para : paramater 
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordCmdSet(INT32U cmd,INT32U para)
{
	if(mediaVideoCtrl.stat != MEDIA_STAT_STOP)
		return STATUS_FAIL;
	if(cmd == CMD_COM_LOOPTIME)
	{
		mediaVideoCtrl.arg.rectime = para*1000;  // change to ms
		mediaVideoCtrlB.arg.rectime = para*1000;  // change to ms
	}
	else if(cmd == CMD_COM_LOOPREC)
	{
		mediaVideoCtrl.arg.looprecord = para;
		mediaVideoCtrlB.arg.looprecord = para;
	}
	else if(cmd == CMD_COM_TIMESTRAMP)
	{
		mediaVideoCtrl.arg.timestramp = para;
		mediaVideoCtrlB.arg.timestramp = para;
		//watermark_enable(mediaVideoCtrl.arg.timestramp);
	}
	else if(cmd == CMD_COM_AUDIOEN)
	{
		mediaVideoCtrl.arg.audio = para;
		mediaVideoCtrlB.arg.audio = para;
	}
	else if(cmd == CMD_COM_RESOLUTIONN)
	{
		mediaVideoCtrl.arg.resolution.width= para>>16;
		mediaVideoCtrl.arg.resolution.height=para&0xffff;
	}
	else if(cmd == CMD_COM_QUALITY)
	{
		mediaVideoCtrl.arg.quality = para;
	}
	else
		return STATUS_FAIL;
	
	return STATUS_OK;
}
/*******************************************************************************
* Function Name  : videoRecordSizePreSec
* Description    : video record size pre second
* Input          : INT32U time_s : time,second
                      int channel : video channel ,A,B
* Output         : none
* Return         : int   kb
                      
*******************************************************************************/
int videoRecordSizePreSec(int channel,INT32U time_s)
{
	INT32U res,size;

	if(channel == VIDEO_CH_B)
		res = 40;  // 30k
    else if(channel == VIDEO_CH_A)
    {
		res = hal_mjpegSizecalculate(mediaVideoCtrl.arg.quality,mediaVideoCtrl.arg.resolution.width,mediaVideoCtrl.arg.resolution.height)>>10;
    }
    else
		return 0;

	size = (res*mediaVideoCtrl.arg.fps)*time_s;
    
	res = (size>>10)/10;  // 10M bytes
	
	if(res == 0)
		return size;
	
	if(res&1)
		res+=1;
	else
		res+=2;

	if(channel == VIDEO_CH_A)	// add more size for save
	{
		u32 add_size = 0;
		if(time_s > 1)
		{
			add_size = 2*((time_s+59)/60);	//720P  add 20M / min for save
		}

		if(mediaVideoCtrl.arg.resolution.width == 720)
		{
			res+=add_size;
		}
		else if(mediaVideoCtrl.arg.resolution.width == 1920)
		{
			res+=add_size*2;
		}
    }

	size = (res*10)<<10;  //KB
	return size;
}
/*******************************************************************************
* Function Name  : videoRecordTakePhoto
* Description    : video record take photo when recording
* Input          : int fd : file handle
* Output         : none
* Return         : int : status
                      
*******************************************************************************/
int videoRecordTakePhoto(int fd)
{
	if(mediaVideoCtrl.stat == MEDIA_STAT_START)
	{
		mediaVideoCtrl.photo = MEDIA_STAT_START;
		mediaVideoCtrl.photoFd = fd;
	}
	if(fd == -2)
	{
		mediaVideoCtrl.photo = MEDIA_STAT_ERROR;
	}
	return mediaVideoCtrl.photo;
}
/*******************************************************************************
* Function Name  : videoRecordTakePhotoStatus
* Description    : video record tabke photo status
* Input          : none
* Output         : none
* Return         : int : status
                      
*******************************************************************************/
int videoRecordTakePhotoStatus(void)
{
	return mediaVideoCtrl.photo;
}
void videoRecordSetPhotoStatus(INT32S status)
{
	mediaVideoCtrl.photo = status;
}
void pt_javgsize(void)
{
#if 0
	u32 ja = cal_jA_1s_size()>>20;
	u32 jb = cal_jB_1s_size()>>20;
	u8  jaf = hal_jA_fcnt_get();
	u8  jbf = hal_jB_fcnt_get();
	u8 csif = hal_csi_fcnt_get();
	
	u8 sbuf[]={'0','0',' ','A',':','0','M','-','0','0',',','B',':','0','M','-','0','0','\n', '\0'};
	sbuf[0] = csif/10+'0';
	sbuf[1] = csif%10+'0';
	
	sbuf[5] = ja+'0';
	sbuf[8] = jaf/10+'0';
	sbuf[9] = jaf%10+'0';
	sbuf[13] = jb+'0';
	sbuf[16] = jbf/10+'0';
	sbuf[17] = jbf%10+'0';
	/*
	sbuf[2] = ja/1000+'0';
	sbuf[3] = (ja%1000)/100+'0';
	sbuf[4] = (ja%100)/10+'0';
	sbuf[5] = (ja%10)+'0';
	sbuf[7] = jaf/10+'0';
	sbuf[8] = jaf%10+'0';
	sbuf[9] = jb/1000+'0';
	sbuf[10] = (jb%1000)/100+'0';
	sbuf[11] = (jb%100)/10+'0';
	sbuf[12] = (jb%10)+'0';
	 */
	LogPrint((char *)sbuf,0);
#endif

}
void videotime_mdf(u8 force)
{
	static u32 timecounter = 0;
	if(force == 1)
		timecounter = mediaVideoCtrl.videoRecordTimeCounter;
	else
	{
		if(mediaVideoCtrl.videoRecordTimeCounter>(1000+timecounter))
		{	
			mediaVideoCtrl.videoRecordTimeCounter = timecounter + 1000;
		}
		timecounter = mediaVideoCtrl.videoRecordTimeCounter;
	}
	
	//debg("[Counter:%d %d ",mediaVideoCtrl.videoRecordTimeCounter/1000,mediaVideoCtrlB.videoRecordTimeCounter/1000);
}
#endif
