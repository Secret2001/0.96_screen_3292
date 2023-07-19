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
* File Name   : video_record.h
* Author      : Mark.Douglas 
* Version     : V100
* Date        : 09/22/2016
* Description : This file is video record  file
*               
* History     : 
* 2016-09-22  : 
*      <1>.This is created by mark,set version as v100.
*      <2>.Add basic functions & information
******************************************************************************/
#ifndef  VIDEO_RECORD_H
    #define  VIDEO_RECORD_H

typedef struct VIDEO_ARG_S
{	
	INT8U  fps;                    // frame rate
	INT8U  sync_fps;				//insert frame cal
	INT8U  audio;                  // audio enable
	INT8U  timestramp; 	       // timestramp flag
	INT8U  looprecord;          // loop record flag
	INT8U  quality;             // jpeg quality
	INT8U  fastwr;              // fast write
	INT8U  syncwr;             // sync write
	INT8U  ftype;
	

	INT32U rectime;             //record time

	Media_Res_T resolution; // lcd show resolution

	int (*callback)(INT32U channel,INT32U cmd,INT32U para);   // >=0 success,<0 fail
	

}VIDEO_ARG_T;

typedef struct Video_Ctrl_S
{
	INT8U  stat; 	
	INT8S  tinfo;
	INT8U  tfont;
	INT8U  fCounter;
	
	INT8U  fStart;
	INT8U  fastwr;   // fs fast write
	INT8U  syncValue;
	INT8U  syncCounter;
	
    INT16U  ftime;
	INT16U tCounter;
	
	
	INT32U avihead;

	INT32S space;
	INT32S filesize;
	INT32U videoRecordAudioCnt;
	INT32U videoRecordSync;
	INT32U videoRecordTimeCounter;
	INT32U videoFrameSize;
#if VIDEO_DBG_REC_EN >0
	INT32U dbg_fps_n_cnt;   // insert cnt in 10second
	INT32U dbg_fps_c_time;
	INT32U dbg_fps_e_cnt;   // error cnt in 10second
	INT32U dbg_fps_s_cnt;   // csi frame cnt
#endif

	FHANDLE aviFd;
	FHANDLE idxFd;

	int fencoder;  // avi encoder handler

	INT8U *idx1;
	INT8U *audio;
	
	XWork_T *videoSync;

	VIDEO_ARG_T arg;	
	bool mjpBStart;
	bool insertframe;
	bool restart_flag;
//	bool stop_flag;
//	bool error;
	bool firstframe;
	int dropframecount;
	
	bool mjpbuff_full;      //true:mjp buff is pre full
	bool mjpA_write_first; //true: when mjpA and mjpB buffer is prefull at the same time, first write mjpA
	bool mjp_last_write;   //true: to fill 32k align junk
	bool write_flag;       //true: this record service is writing
	bool looptime;         //true: it's time to restart record for loop recording
	bool usensor_in;
	INT32U jframe_cnt;
	INT32S u_tsync_old;
	INT32U abchangetime;
	INT32U iframe_ctr;
	INT32U icnt_control;

    INT32S photo;  // take photo when recording
    INT32S photoFd;
}Video_Ctrl_T;

Video_Ctrl_T mediaVideoCtrl;
Video_Ctrl_T mediaVideoCtrlB;
#define Framedrop_back 20
#define audioframesizeB (8*1024)
u8 audiobuff[audioframesizeB*4];
#if VIDEO_DBG_REC_EN
    #define  videor_print     deg_Printf
#else
    #define  videor_print(...)
#endif
//-----------------cmd table-------------------------
enum
{
	VIDEO_CMD_NULL,
	VIDEO_CMD_START=1,
	VIDEO_CMD_STOP,

	VIDEO_CMD_SET_LOOPTIME,


	VIDEO_CMD_MAX
};
	


/*******************************************************************************
* Function Name  : videoRecordInit
* Description	 : initial video record 
* Input 		 : none
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordInit(VIDEO_ARG_T *arg);
/*******************************************************************************
* Function Name  : videoRecordUninit
* Description	 : uninitial video record 
* Input 		 : none
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordUninit(void);
/*******************************************************************************
* Function Name  : videoRecordStart
* Description	 : start video record
* Input 		 : AUDIO_RECORD_ARG_T *arg : video record argument
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordStart(void);
/*******************************************************************************
* Function Name  : videoRecordStop
* Description	 : stop video record 
* Input 		 : none
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordStop(void);
/*******************************************************************************
* Function Name  : videoRecordPuase
* Description	 : pause video record 
* Input 		 : none
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordPuase(void);
/*******************************************************************************
* Function Name  : videoRecordRestart
* Description    : pause video record restart for loop recording
* Input          : none
* Output         : none
* Return         : int 0 : success
                      <0 : fail
*******************************************************************************/
int videoRecordRestart(void);
/*******************************************************************************
* Function Name  : videoRecordResume
* Description	 : resume video record 
* Input 		 : none
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordResume(void);
/*******************************************************************************
* Function Name  : videoRecordGetStatus
* Description	 : get video record 
* Input 		 : none
* Output		 : none
* Return		 : int 
					  
*******************************************************************************/
int videoRecordGetStatus(void);
/*******************************************************************************
* Function Name  : videoRecordGetTime
* Description    : get video record time in ms
* Input          : none
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordGetTime(void);
/*******************************************************************************
* Function Name  : videoRecordService
* Description    : video record service
* Input          : none
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordService(void);	
/*******************************************************************************
* Function Name  : videoRecordCmdSet
* Description    : video record set paramater
* Input          : INT32U cmd : command
                      INT32U para : paramater 
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordCmdSet(INT32U cmd,INT32U para);
/*******************************************************************************
* Function Name  : videoRecordSizePreSec
* Description    : video record size pre second
* Input          : INT32U time_s : time,second
                      int channel : video channel ,A,B
* Output         : none
* Return         : int   kb
                      
*******************************************************************************/
int videoRecordSizePreSec(int channel,INT32U time_s);






/*******************************************************************************
* Function Name  : videoRecordInit
* Description	 : initial video record 
* Input 		 : none
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordInitB(VIDEO_ARG_T *arg);
/*******************************************************************************
* Function Name  : videoRecordUninit
* Description	 : uninitial video record 
* Input 		 : none
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordUninitB(void);
/*******************************************************************************
* Function Name  : videoRecordStart
* Description	 : start video record
* Input 		 : AUDIO_RECORD_ARG_T *arg : video record argument
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordStartB(void);
/*******************************************************************************
* Function Name  : videoRecordStop
* Description	 : stop video record 
* Input 		 : none
* Output		 : none
* Return		 : int 0 : success
					  <0 : fail
*******************************************************************************/
int videoRecordStopB(void);

/*******************************************************************************
* Function Name  : videoRecordGetStatus
* Description	 : get video record 
* Input 		 : none
* Output		 : none
* Return		 : int 
					  
*******************************************************************************/
int videoRecordGetStatusB(void);

/*******************************************************************************
* Function Name  : videoRecordGetTime
* Description    : get video record time in ms
* Input          : none
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordGetTimeB(void);
/*******************************************************************************
* Function Name  : videoRecordService
* Description    : video record service
* Input          : none
* Output         : none
* Return         : int 
                      
*******************************************************************************/
int videoRecordServiceB(void);	
/*******************************************************************************
* Function Name  : videoRecordTakePhoto
* Description    : video record take photo when recording
* Input          : int fd : file handle
* Output         : none
* Return         : int : status
                      
*******************************************************************************/
int videoRecordTakePhoto(int fd);
/*******************************************************************************
* Function Name  : videoRecordTakePhotoStatus
* Description    : video record tabke photo status
* Input          : none
* Output         : none
* Return         : int : status
                      
*******************************************************************************/
int videoRecordTakePhotoStatus(void);
void videoRecordSetPhotoStatus(INT32S status);
int videoRecordRestartB(void);
void videoRecordErrorB(u8 err);
void videoRecordError(u8 err);
int videoRecordFileStartB(void);
int videoRecordFileStopB(void);
int videoRecordFileErrorB(void);
int videoRecordUpdateAviIdx1B(INT8U type,INT32U len,INT8U key);

extern bool backrec_adpt(void);
extern void api_mjp_avi_stop(void);
extern int hal_mjpB_actech_as_avi(u16 win_w, u16 win_h, u8 quality);
extern bool hal_mjpB_usensor_fram_rd(u8 **p, u32 *len, u32 *id,s32 *u_sync, s32 *u_sync_next);
extern bool hal_mjpB_usensor_fram_free(void);
extern u32 hal_get_fBcnt(void);

void videoRecordImageWatermark(INT16U width,INT16U height,INT8U en);

void videotime_mdf(u8 force);





#endif
