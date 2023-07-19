/****************************************************************************
**
 **                         BUILDWIN HAL LAYER
  ** *   **                  THE APPOTECH HAL
   **** **                 MJPEG HAL LAYER DRIVER
  *** ***
 **  * **               (C) COPYRIGHT 2016 BUILDWIN 
**      **                         
         **         BuildWin SZ LTD.CO  ; VIDEO PROJECT TEAM
          **       
* File Name   : hal_mjpeg.h
* Author      : Mark.Douglas 
* Version     : V0200
* Date        : 05/25/2016
* Description : This file for BUILDWIN MJPEG HARDWARE LAYER.
*               
*               
* History     :
* 2017-02-27  : 
*      <1>.This is created by mark,set version as v0100.
*      <2>.Add basic functions.
******************************************************************************/
#include "../inc/hal.h"

//#define  MJPEG_ITEM_SIZE        HAL_CFG_MJPEG_BUFFER_SIZE
#define  MJPEG_ITEM_NUM         HAL_CFG_MJPEG_BUFFER_NUM
//#define  MJPEG_BUFF_SIZE       (HAL_CFG_MJPEG_BUFFER_SIZE*HAL_CFG_MJPEG_BUFFER_NUM)

#define  MJPEG_TYPE_VIDEO      0
#define  MJPEG_TYPE_PHOTO      1
#define  MJPEG_TYPE_UVC         2

#define  M(w,h)		        {(ROUND_UP(w,31) + 1) & ~1,(ROUND_UP(h,31) + 1) & ~1}
#define	LDB_WORD(ptr)		(WORD)(((WORD)*((BYTE*)(ptr))<<8)|(WORD)*(BYTE*)((ptr)+1))

static u32 HAL_CFG_MJPEG_HEIGHT,HAL_CFG_MJPEG_WIDTH;//,MJPEG_ITEM_SIZE;
typedef struct MJPEG_DEC_OP_S {
	u16 height;		/* Image height in unit of pixel */
	u16 width;		/* Image width in unit of pixel */
	u8  msx;		/* y sampling factor hor */
	u8  msy;		/* y sampling factor vert*/
    u8  yuvfmt;     /* yuv format,0:yuv420,1:yuv422*/
	u8  qtid[3];	/* dequantizer table ID for y component */
					/* dequantizer table ID for u component */
					/* dequantizer table ID for v component */
	u8  hfid[3][2]; /* [y/u/v][AC/DC],[0][0]:yAC,[0][1]:yDC*/
	u16 nrst;		/* DRI interval */
	u16 bs_ofs;		/* bit stream offset to jpeg start */
	u16 qt_ofs[3];  /* dequantizer table offset for id=0 component*/
                    /* dequantizer table offset for id=1 component*/
                    /* dequantizer table offset for id=2 component*/
    u32 comp_table_id;
    u32 qt_addr[3];
	u8 *bsptr;		/* bit stream start */

	u8 *dqt[4];
	u8 *dht[4];
	u8 *valptr[4];
	u16 *minicode[4];
} MJPEG_DEC_OP_T;
typedef struct MJPEG_ENC_OP_S
{
	u8 type;
	u8 drop;
	
#if HAL_CFG_MJPEG_QULITY_AUTO>0
	s8 qulity;
    u8 q_cnt;
	u8 q_auto;
	s8 q_dir;
	u32 q_csize;
#endif
	u16 csi_width;
	u16 csi_height;
    u16 mjpeg_width;
	u16 mjpeg_height;

	u32 jfcnt;
    u32 ybuffer;
	u32 uvbuffer;
	u32 mjpbuf;
	u32 mjpsize;

	u32 curBuffer;
	u32 curLen;
	Stream_Head_T vids;
	Stream_Node_T mjpegNode[MJPEG_ITEM_NUM];
}MJPEG_ENC_OP_T;
#define  MJPEG_Q_MAX       11
static MJPEG_ENC_OP_T  mjpegEncCtrl;
static MJPEG_DEC_OP_T  mjpegDecCtrl;
#if HAL_CFG_MJPEG_QULITY_AUTO>0	
static u8 mjpegQualityTable[MJPEG_Q_MAX] = {JPEG_Q_27,JPEG_Q_28,JPEG_Q_31,JPEG_Q_33,JPEG_Q_36,JPEG_Q_40,JPEG_Q_42,JPEG_Q_50,JPEG_Q_62,JPEG_Q_75,JPEG_Q_81};
#endif
/*******************************************************************************
* Function Name  : hal_mjpegQualityAjust
* Description    : hal layer .mjpeg quality ajust
* Input          : u32 len : current mjpeg size
* Output         : None
* Return         : s8
*******************************************************************************/
static void hal_mjpegQualityAjust(u32 len)
{
#if HAL_CFG_MJPEG_QULITY_AUTO>0	
	if(mjpegEncCtrl.q_auto!=JPEG_Q_AUTO)
		return ;
	
	if(mjpegEncCtrl.q_dir==0)
	{
		int mjpeg_throld = mjpegEncCtrl.q_csize*15/100;  // 40%
		if(len>(mjpegEncCtrl.q_csize+mjpeg_throld))
		{
			mjpegEncCtrl.q_dir = 1;
			mjpegEncCtrl.q_cnt = 0;
			//debg("HAL : [MJPEG]<INFO> size auto check %x,%x\n",len,mjpegEncCtrl.q_csize+mjpeg_throld);
		}
		else if(len<(mjpegEncCtrl.q_csize-mjpeg_throld))
		{
			mjpegEncCtrl.q_dir = -1;
			mjpegEncCtrl.q_cnt = 0;
			//debg("HAL : [MJPEG]<INFO> size auto check %x,%x\n",len,mjpegEncCtrl.q_csize-mjpeg_throld);
		}
	}
	else if(mjpegEncCtrl.q_dir>0)
	{
		if(len<mjpegEncCtrl.q_csize)
		{
			mjpegEncCtrl.q_dir = 0;
			mjpegEncCtrl.q_cnt = 0;
		}
		else
			mjpegEncCtrl.q_cnt++;
	}
	else if(mjpegEncCtrl.q_dir<0)
	{
		if(len>mjpegEncCtrl.q_csize)
		{
			mjpegEncCtrl.q_dir = 0;
			mjpegEncCtrl.q_cnt = 0;
		}
		else
			mjpegEncCtrl.q_cnt++;
	}

	if(mjpegEncCtrl.q_cnt>=10)
	{
		mjpegEncCtrl.qulity-=mjpegEncCtrl.q_dir;
		if(mjpegEncCtrl.qulity<0)
			mjpegEncCtrl.qulity = 0;
		else if(mjpegEncCtrl.qulity>=MJPEG_Q_MAX)
			mjpegEncCtrl.qulity=MJPEG_Q_MAX-1; 
		
		
//		mjpegEncCtrl.q_csize=hal_mjpegSizecalculate(mjpegQualityTable[mjpegEncCtrl.qulity],mjpegEncCtrl.mjpeg_width,mjpegEncCtrl.mjpeg_height)-20480;
		ax32xx_mjpegEncodeQuilitySet(mjpegQualityTable[mjpegEncCtrl.qulity]);

		//debg("HAL : [MJPEG]<INFO> quality auto check[%d] ->%d\n",mjpegEncCtrl.q_dir,mjpegEncCtrl.qulity);
		mjpegEncCtrl.q_dir = 0;
		mjpegEncCtrl.q_cnt = 0;
	}
#endif	
}
/*******************************************************************************
* Function Name  : hal_mjpegQualityCheck
* Description    : hal layer .mjpeg quality check
* Input          : u8 quality : user set quality
* Output         : None
* Return         : s8
*******************************************************************************/
static s8 hal_mjpegQualityCheck(u8 quality)
{
#if HAL_CFG_MJPEG_QULITY_AUTO>0
    mjpegEncCtrl.q_auto = quality;
    if(quality == JPEG_Q_AUTO)
		quality = JPEG_Q_40;
	int i;
	for(i=0;i<MJPEG_Q_MAX;i++)
	{
		if(mjpegQualityTable[i] == quality)
			break;
	}
	if(i>=MJPEG_Q_MAX)
		i = MJPEG_Q_MAX-1;
	mjpegEncCtrl.qulity = i;
	mjpegEncCtrl.q_cnt = 0;	
	mjpegEncCtrl.q_dir = 0;
    mjpegEncCtrl.q_csize = hal_mjpegSizecalculate(quality,mjpegEncCtrl.mjpeg_width,mjpegEncCtrl.mjpeg_height);
	mjpegEncCtrl.q_csize = mjpegEncCtrl.q_csize*55/100;
#endif	
    if(quality == JPEG_Q_AUTO)
		quality = JPEG_Q_40;	
	deg("video record Q = %x\n",quality);
	return quality;
}

bool hal_mjpegCallback_state(int flag)
{
	if(flag & BIT(MJPEG_IRQ_OUTPAUSE)){//ODMAPAUSE
		if(!(flag & BIT(MJPEG_IRQ_FRAMEEND))){
			debg("mallo j frame size err\n");
			return false;	
		}
	}	
	if((flag & BIT(MJPEG_IRQ_OUTERR))){
			return false;
	}
	return true;
}
u32 hal_jA_fcnt_get(void)
{
	u32 cnt = mjpegEncCtrl.jfcnt;
	mjpegEncCtrl.jfcnt = 0;
	debg("JA_fcnt:%d   ",cnt);
	return cnt;
}
/*******************************************************************************
* Function Name  : hal_mjpegCallback
* Description    : hal layer .mjpeg callback function for mjpeg irq encode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegCallback(int flag)
{
	#define _JPG_SIZE_MIN_DEF_		(100*1024)
		
	u32 addr,len;
	s32 mjp_sync;
	s32 mjp_sync_next;
	if(flag&((1<<MJPEG_IRQ_OUTPAUSE)|(1<<MJPEG_IRQ_FRAMEEND)))
	{
		mjpegEncCtrl.jfcnt++;
		mjp_sync=hal_audc_stamp_out();
		mjp_sync_next =hal_audc_stamp_next();
		if(mjpegEncCtrl.type== MJPEG_TYPE_UVC)
		{
			//if(flag&(1<<MJPEG_IRQ_OUTPAUSE))
			//	hal_mjpegUVCPackage();
			if(flag & (BIT (MJPEG_IRQ_FRAMEEND) | BIT(MJPEG_IRQ_OUTPAUSE)))
			{
				len = ax32xx_mjpegEncodeLoadAddrGet()-mjpegEncCtrl.curBuffer;
				
				if(!mjpegEncCtrl.drop){
					len = (hal_mjpegCallback_state(flag))?len:0; //MJPEC出错
					//debg("len:%d\n",len);
					hal_streamIn(&mjpegEncCtrl.vids,mjpegEncCtrl.curBuffer,len,mjp_sync,mjp_sync_next);
					
				}
				//debg("ulen:%dK\n",len/1024);
				mjpegEncCtrl.curLen = (len > _JPG_SIZE_MIN_DEF_)? (len*2) : (_JPG_SIZE_MIN_DEF_*2);
			#if HAL_CFG_MJPEG_QULITY_AUTO >0
	            if(mjpegEncCtrl.q_auto!=JPEG_Q_AUTO){
					if(mjpegEncCtrl.mjpeg_height <= 720){
						ax32xx_mjpegEncodeQadj(len,HAL_CFG_MJPEG_720_SIZE_MIN,HAL_CFG_MJPEG_720_SIZE_MAX);	
					}else{
						ax32xx_mjpegEncodeQadj(len,HAL_CFG_MJPEG_1080_SIZE_MIN,HAL_CFG_MJPEG_1080_SIZE_MAX);	
					}				
				}
				 hal_mjpegQualityAjust(len);	
			#endif 
			}
		
		}
		else
		{
			//if(flag&(1<<MJPEG_IRQ_OUTPAUSE))
			//	hal_mjpegPackage();
			if(flag & (BIT (MJPEG_IRQ_FRAMEEND) | BIT(MJPEG_IRQ_OUTPAUSE)))
			{
				
				len = ax32xx_mjpegEncodeLoadAddrGet()-mjpegEncCtrl.curBuffer;
				len = (len+0x1ff)&(~0x1ff);
				if(!mjpegEncCtrl.drop){
					len = (hal_mjpegCallback_state(flag))?len:0; //MJPEC出错
					//debg("[%d + %d ",hal_stream_size(&mjpegEncCtrl.vids),len);
					hal_streamIn(&mjpegEncCtrl.vids,mjpegEncCtrl.curBuffer,len,mjp_sync,mjp_sync_next);
					//debg("[+ %d]\n",hal_stream_size(&mjpegEncCtrl.vids));
					if(len&&(mjpegEncCtrl.type== MJPEG_TYPE_PHOTO))  // only need one frame
						ax32xx_mjpegEncodeEnable(0);
				}
				mjpegEncCtrl.curLen = (len > _JPG_SIZE_MIN_DEF_)? (len*2) : _JPG_SIZE_MIN_DEF_*2;
			#if HAL_CFG_MJPEG_QULITY_AUTO >0
	            if(mjpegEncCtrl.q_auto!=JPEG_Q_AUTO){
					if(mjpegEncCtrl.mjpeg_height <= 720){
						ax32xx_mjpegEncodeQadj(len,HAL_CFG_MJPEG_720_SIZE_MIN,HAL_CFG_MJPEG_720_SIZE_MAX);	
					}else{
						ax32xx_mjpegEncodeQadj(len,HAL_CFG_MJPEG_1080_SIZE_MIN,HAL_CFG_MJPEG_1080_SIZE_MAX);	
					}
				   
				}
				 hal_mjpegQualityAjust(len);	
			#endif 
			}
		}
		/*
		//JEOFULL
		if(hal_mjpegCallback_state(flag)){
			addr = hal_streamMalloc(&mjpegEncCtrl.vids,mjpegEncCtrl.curLen);	
		}else{
			debg("ulen:%dK\n",len/1024);
			addr = 0;
		}	
		*/
		//debg("%d\n",mjpegEncCtrl.curLen);
		addr = hal_streamMalloc(&mjpegEncCtrl.vids,mjpegEncCtrl.curLen);
		if(addr)
		{
			mjpegEncCtrl.curBuffer = addr;
			mjpegEncCtrl.drop = 0;
			
		}
		else
		{
			//mjpegEncCtrl.drop = 1;
			hal_streamIn_Drop(&mjpegEncCtrl.vids);
			deg_Printf("A");
			//deg_Printf("[A:%d,%d]",(hal_stream_size(&mjpegEncCtrl.vids)*100)/mjpegEncCtrl.mjpsize,mjpegEncCtrl.curLen);
			//sysLog("D:A");
		}
		ax32xx_mjpegEncodeBufferSet(mjpegEncCtrl.curBuffer,mjpegEncCtrl.curBuffer+mjpegEncCtrl.curLen);
	}	
}
u8 *hal_mjpeg_mallocbuf(void)
{
	return (u8 *)mjpegEncCtrl.curBuffer;	
}
/*******************************************************************************
* Function Name  : hal_mjpegStart
* Description    : hal layer .mjpeg start.for sync to frame,this function will be callback by csi frame end
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegStart(void)
{
	ax32xx_mjpegEncodeEnable(1);
	ax32xx_csiISRRegiser(CSI_IRQ_SEN_STATE_INT,NULL); // only need execute once
}
/*******************************************************************************
* Function Name  : hal_mjpegSrcCSI
* Description    : hal layer .mjpeg get data from csi
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegSrcCSI(void)
{
	_Sensor_Adpt_ *senradpt = hal_csiAdptGet();

    mjpegEncCtrl.csi_width = senradpt->pixelw;
	mjpegEncCtrl.csi_height= senradpt->pixelh; 

	ax32xx_csiInit();
	//raw
	
	ax32xx_csiModeSet(0xffffffff,0);  // clear
	ax32xx_csiSyncSet(senradpt->hsyn,senradpt->vsyn);
	ax32xx_csiSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height);
    if(senradpt->typ == CSI_TYPE_YUV422)
	{
		debg("HAL : <MJPEG>[INFO] _USE_YUV_INFTS\n");				
		ax32xx_csiPrioritySet(senradpt->colrarray);
		ax32xx_csiTypeSet(CSI_TYPE_YUV422);
		
	}
	else if((senradpt->typ == CSI_TYPE_RAW8) || (senradpt->typ == CSI_TYPE_RAW10) || (senradpt->typ == CSI_TYPE_RAW12))
	{
		debg("HAL : <MJPEG>[INFO] _USE_RAW_INFTS\n");
		//debg("CSIMODE:%x\n",CSIMODE);
		ax32xx_csiPrioritySet(senradpt->colrarray);				
		ax32xx_csiTypeSet(senradpt->typ);
		ax32xx_ispModeSet(ISP_MODE_CFAEN,1);
		ax32xx_csiModeSet(CSI_MODE_SAMPLE,1);
		ax32xx_pclk_fir_Set(senradpt->pclk_fir_en);
		ax32xx_pclk_analog_Set(senradpt->pclk_fir_class);
		ax32xx_pclk_inv_Set(senradpt->pclk_inv_en);
        ax32xx_csi_clk_tun_Set(senradpt->csi_tun);
	}
	else if (senradpt->typ == CSI_TYPE_COLOR_BAR)
	{
		debg("HAL : <MJPEG>[INFO] _TEST_IMAGE\n");
		/*ax32xx_csiPrioritySet(CSI_PRIORITY_CBY0CRY1);
		ax32xx_csiTypeSet(CSI_TYPE_YUVR422);
		ax32xx_csiModeSet(CSI_MODE_TEST_EN,1);
		ax32xx_csiTestModeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height,1028,512,8);// hbank must be divided 4*/
		ax32xx_csiPrioritySet(0);
		ax32xx_csiModeSet(CSI_MODE_SAMPLE,1);
		ax32xx_csiTypeSet(CSI_TYPE_RAW8);
		ax32xx_ispModeSet(ISP_MODE_CFAEN,1);
		ax32xx_csiModeSet(CSI_MODE_TEST_EN,1);
		ax32xx_csiTestModeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height,2046,1024,8);//10*/
	
	}	
}
/*******************************************************************************
* Function Name  : hal_mjpegSrcRam
* Description    : hal layer .mjpeg get data from sdram
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegSrcRam(void)
{
#if MJPEG_SRC	==  MJPEG_SRC_RAM
	
	//read raw data
	FIL Fil;
	UINT read,len;
	_Sensor_Adpt_ *senradpt = hal_csiAdptGet();
	char filename[18] = "DEBG/RAWD0000.raw";
	len = senradpt->pixelh*senradpt->pixelw*2;
	u8* sdr_data_buff = NULL; 
	deamon_sdc_check();
	FRESULT ret = f_mkdir("DEBG\0");
	if(ret != FR_OK){	
		if(ret != FR_EXIST){
			debg("DEBG mkdir err\n");
		}
	}
	if(FR_OK == f_open(&Fil,(char const *)filename, FA_READ)){
		sdr_data_buff = hal_sysMemMalloc(len,64);
		f_read (&Fil,sdr_data_buff, len, &read);
	}else{
		debg("GET RAW ERR!!!\n");
	}
	if(sdr_data_buff != NULL){
		debg("HAL : <MJPEG>[INFO] _USE_GENERATE_DVP\n");
		_Sensor_Adpt_ *senradpt = hal_csiAdptGet();
		mjpegEncCtrl.csi_width = senradpt->pixelw;
		mjpegEncCtrl.csi_height= senradpt->pixelh; 
		ax32xx_csiInit();
		ax32xx_csiModeSet(0xffffffff,0);  // clear
		ax32xx_csiSyncSet(senradpt->hsyn,senradpt->vsyn);
		ax32xx_csiSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height);
		ax32xx_csiPrioritySet(senradpt->colrarray);				
		ax32xx_csiTypeSet(senradpt->typ);
		ax32xx_ispModeSet(ISP_MODE_CFAEN,1);
		//ax32xx_csiModeSet(CSI_MODE_SAMPLE,1);
		ax32xx_csiTestModeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height,2048,1080,8);
        ax32xx_csiInputAddrSet((u32)sdr_data_buff);
		ax32xx_csiDvpClkDivSet(1);
		ax32xx_csiModeSet(CSI_MODE_DVP_EN,1);
	}
#endif		
}
/*******************************************************************************
* Function Name  : hal_mjpegSrcColorBar
* Description    : hal layer .mjpeg get data from mjpeg color bar
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegSrcColorBar(void)
{
	hal_mjpegSrcCSI();
	ax32xx_csiModeSet(0xffffffff,0);  // clear
	ax32xx_csiSyncSet(1,1);//(csiadpt.hsyn,csiadpt.vsyn);
	ax32xx_csiSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height);
	ax32xx_csiPrioritySet(CSI_PRIORITY_CBY0CRY1);
	ax32xx_csiTypeSet(CSI_TYPE_YUVR422);
	ax32xx_csiModeSet(CSI_MODE_TEST_EN,1);
	ax32xx_csiTestModeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height,1024,512,8);
}
/*******************************************************************************
* Function Name  : hal_mjpegStart
* Description    : hal layer .mjpeg start.for sync to frame,this function will be callback by csi frame end
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void hal_save_frame_isr(void)
{
	static u32 fnum = 0;
	if(fnum>0){
		ax32xx_csiEnable(0);
		ax32xx_csiOutputSet(CSI_OUTPUT_MJPGEN,0); 
		ax32xx_csiISRRegiser(CSI_IRQ_JPG_FRAME_END,NULL);
		extern bool cut_sdr_data_en;
		cut_sdr_data_en = 1;
		extern u32 ispmode_tmp;
		ISPMODE = ispmode_tmp;
		
	}
	fnum++;
}
/*******************************************************************************
* Function Name  : hal_Cut_RAW_SrcCSI
* Description    : cut raw  csi cfg
* Input          : void *sdr_buf : cut data to sdrbuf
* 				  u32 csi_save : 0: cut dma data  1:cut source data
* Output         : None
* Return         : None
*******************************************************************************/
u32 ispmode_tmp = 0;
void hal_Cut_SDR_SrcCSI(void *sdr_buf,bool csi_save)
{
	_Sensor_Adpt_ *senradpt = hal_csiAdptGet();
    mjpegEncCtrl.csi_width = senradpt->pixelw;
	mjpegEncCtrl.csi_height= senradpt->pixelh; 
	ispmode_tmp = ISPMODE;
	if(csi_save){
		
		ISPMODE = ISP_MODE_CSI_SAVEEN;//ISP_MODE_CSI_SAVEEN// save_en
	}else{
		ISPMODE = ISP_MODE_CFAEN;
	}
	//ax32xx_csiModeSet(CSI_MODE_TEST_EN,1);
	//ax32xx_csiTestModeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height,1024,512,8);
	if(sdr_buf!=NULL){
		ax32xx_csiISRRegiser(CSI_IRQ_JPG_FRAME_END,hal_save_frame_isr);
		mjpegEncCtrl.ybuffer = (u32)sdr_buf;
		mjpegEncCtrl.uvbuffer = mjpegEncCtrl.ybuffer + mjpegEncCtrl.csi_height*mjpegEncCtrl.csi_width;
		ax32xx_csiMJPEGFrameSet(mjpegEncCtrl.ybuffer,mjpegEncCtrl.uvbuffer,mjpegEncCtrl.csi_height,mjpegEncCtrl.csi_width*(csi_save+1));
		ax32xx_csiOutputSet(CSI_OUTPUT_MJPGEN,1); 
	} 
	ax32xx_csiEnable(1);
}
/*******************************************************************************
* Function Name  : hal_mjpegInit
* Description    : hal layer .mjpeg memory initial
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int hal_mjpegMemInit(void)
{
	s32 size;

	if(mjpegEncCtrl.ybuffer && mjpegEncCtrl.mjpbuf)
		return 0;
	if(mjpegEncCtrl.ybuffer==0)
	{
		mjpegEncCtrl.ybuffer = (u32)hal_sysMemMalloc(HAL_CFG_MJPEG_HEIGHT*HAL_CFG_MJPEG_WIDTH*3/2,64);
		if(mjpegEncCtrl.ybuffer==0)
			return -1;
		mjpegEncCtrl.uvbuffer = mjpegEncCtrl.ybuffer+HAL_CFG_MJPEG_HEIGHT*HAL_CFG_MJPEG_WIDTH;
	}
//	MJPEG_ITEM_SIZE = 32768;
    if(mjpegEncCtrl.mjpbuf==0)
    {
	#if SDRAM_SIZE == SDRAM_SIZE_8M	
	    size = hal_sysMemRemain()-128*1024-8*1024;
	   // if(backrec_sensor_stat())
		   size-=HAL_CFG_MJPEGB_BUFFER_SIZE;
		size-=HAL_CFG_PCM_BUFFER_SIZE*HAL_CFG_PCM_BUFFER_NUM ;
	#else
	    size = hal_sysMemRemain()-8*1024;
		if(size>1024*1024) // remain space for other using
		{
			size -= (size>>7);
		}/**/
	#endif	
		size &=~0x1ff;
		mjpegEncCtrl.mjpbuf = (u32)hal_sysMemMalloc(size,64);
		if(mjpegEncCtrl.mjpbuf == 0)
			return -2;
		mjpegEncCtrl.mjpsize = size;
		deg_Printf("HAL : [MJPEG]<INFO> mbuffer addr = 0x%x,size = 0x%x\n",mjpegEncCtrl.mjpbuf,size);
    }
	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegMemUninit
* Description    : hal layer .mjpeg memory uninitial
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegMemUninit(void)
{
	if(mjpegEncCtrl.mjpbuf)
		hal_sysMemFree((void *)mjpegEncCtrl.mjpbuf);
	mjpegEncCtrl.mjpbuf = 0;

	if(mjpegEncCtrl.ybuffer)
		hal_sysMemFree((void *)mjpegEncCtrl.ybuffer);
	mjpegEncCtrl.ybuffer = 0;
	mjpegEncCtrl.uvbuffer = 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegInit
* Description    : hal layer .mjpeg initial
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegEncodeInit(void)
{
	static u8 cfged=0;
	
	if(cfged) 
		return;
	cfged = 1;
	
    mjpegEncCtrl.type = 0;
	mjpegEncCtrl.uvbuffer = 0;//(u32)halSysMemMJPEGBuffer.uv_buffer;
	mjpegEncCtrl.ybuffer  = 0;//(u32)halSysMemMJPEGBuffer.y_buffer;
	mjpegEncCtrl.mjpbuf   = 0;//&halSysMemMJPEGBuffer.mjpeg_buffer;
	
#if (MJPEG_SRC	==  MJPEG_SRC_CSI)
	hal_mjpegSrcCSI();
#elif MJPEG_SRC	==  MJPEG_SRC_BAR
	hal_mjpegSrcColorBar();
#elif MJPEG_SRC	==  MJPEG_SRC_RAM
	hal_mjpegSrcRam();
#endif
	isp_init();
}
/*******************************************************************************
* Function Name  : hal_mjpegEncodeUninit
* Description    : hal layer .mjpeg uninitial 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegEncodeUninit(void)
{
	if(mjpegEncCtrl.mjpbuf == 0)
		return;
	ax32xx_mjpegEncodeEnable(0);
	ax32xx_mjpegEA_ncodeISRRegister(NULL);
	hal_mjpegMemUninit();
}
/*******************************************************************************
* Function Name  : hal_mjpegEncodeResolution
* Description    : hal layer .mjpeg line scaler cal
* Input          : u16 width : target width
                      u16 height: target height
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegEncodeResolution(u16 width,u16 height)
{
	HAL_CFG_MJPEG_WIDTH = mjpegEncCtrl.csi_width;
#if SDRAM_SIZE == SDRAM_SIZE_8M
    HAL_CFG_MJPEG_HEIGHT = 360;
#else
    if(height<1440)//mjpegEncCtrl.csi_height)
		HAL_CFG_MJPEG_HEIGHT = 192;
	else
		HAL_CFG_MJPEG_HEIGHT = 320;//120*(2<<(height/mjpegEncCtrl.csi_height-1));	
#endif		
}

/*******************************************************************************
* Function Name  : hal_mjpegEncodeResolutionImage
* Description    : hal layer .mjpeg line scaler cal for pic 
* Input          : u16 width : target width
                      u16 height: target height
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegEncodeResolutionImage(u16 width,u16 height)
{
	HAL_CFG_MJPEG_WIDTH = mjpegEncCtrl.csi_width;
    HAL_CFG_MJPEG_HEIGHT = mjpegEncCtrl.csi_height;
}


/*******************************************************************************
* Function Name  : hal_mjpegSizecalculate
* Description    : hal layer .mjpeg output jpeg size
* Input          : u8 quailty : quality
                      u16 width : output width
                      u16 height: output height
* Output         : None
* Return         : int : size
*******************************************************************************/
int hal_mjpegSizecalculate(u8 quailty,u16 width,u16 height)
{
#if HAL_CFG_MJPEG_QULITY_AUTO>0
	if(height <= 720)   // mark modify,2017/11/30.change mjpegEncCtrl.mjpeg_height -> height.when resolution changed,the size calulated is wrong
		return HAL_CFG_MJPEG_720_SIZE_MAX;
	else
		return HAL_CFG_MJPEG_1080_SIZE_MAX;
#else		
	INT32U quli;
	switch(quailty)
	{
		case JPEG_Q_27 : quli = 40;break;
		case JPEG_Q_28 : quli = 45;break;
		case JPEG_Q_31 : quli = 50;break;
		case JPEG_Q_33 : quli = 65;break;
		case JPEG_Q_36 : quli = 70;break;
		case JPEG_Q_AUTO :
		case JPEG_Q_40 : quli = 80;break;
		case JPEG_Q_42 : quli = 80;break;
		case JPEG_Q_50 : quli = 90;break;
		case JPEG_Q_62 : quli = 100;break;
		case JPEG_Q_75 : quli = 110;break;
		case JPEG_Q_81 : quli = 120;break;
		default : quli = 100;break;
	}
//    quli+=20;
	return (((width*height/100)*quli)/10); // byte
#endif	
}
void hal_mjpeg_manual_fdown(int flag)
{
	
	if(flag & (BIT (MJPEG_IRQ_FRAMEEND) | BIT(MJPEG_IRQ_OUTPAUSE))){
		u32 /*addr,*/len;
		s32 mjp_sync;
		s32 mjp_sync_next;
		//debg("J");
		mjpegEncCtrl.jfcnt++;
		mjp_sync=hal_audc_stamp_out();
		mjp_sync_next =hal_audc_stamp_next();
		
		if(mjpegEncCtrl.type== MJPEG_TYPE_UVC)
		{
			len = ax32xx_mjpegEncodeLoadAddrGet()-mjpegEncCtrl.curBuffer;
			
			if(!mjpegEncCtrl.drop){
				len = (hal_mjpegCallback_state(flag))?len:0; //MJPEC出错
				hal_streamIn(&mjpegEncCtrl.vids,mjpegEncCtrl.curBuffer,len,mjp_sync,mjp_sync_next);
			}
			//debg("ulen:%dK\n",len/1024);
			mjpegEncCtrl.curLen = (len > _JPG_SIZE_MIN_DEF_)? (len*2) : (_JPG_SIZE_MIN_DEF_*2);
		
		}
		else
		{
			len = ax32xx_mjpegEncodeLoadAddrGet()-mjpegEncCtrl.curBuffer;
			len = (len+0x1ff)&(~0x1ff);
			if(!mjpegEncCtrl.drop){
				len = (hal_mjpegCallback_state(flag))?len:0; //MJPEC出错
				//debg("len:%d\n",len);
				hal_streamIn(&mjpegEncCtrl.vids,mjpegEncCtrl.curBuffer,len,mjp_sync,mjp_sync_next);
				if(len&&(mjpegEncCtrl.type== MJPEG_TYPE_PHOTO))  // only need one frame
					ax32xx_mjpegEncodeEnable(0);
			}
			mjpegEncCtrl.curLen = (len > _JPG_SIZE_MIN_DEF_)? (len*2) : _JPG_SIZE_MIN_DEF_*2;
		}	
		mjpegEncCtrl.curBuffer =(u32) NULL;		
	}

}
bool hal_mjpeg_manual_on(void)
{
	//debg("m");
	
	mjpegEncCtrl.curBuffer = hal_streamMalloc(&mjpegEncCtrl.vids,mjpegEncCtrl.curLen);
	//debg("mbuff:%x\n",mjpegEncCtrl.curBuffer);
	if(mjpegEncCtrl.curBuffer==0)
		return -1;
	
	ax32xx_mjpegEncodeBufferSet(mjpegEncCtrl.curBuffer,mjpegEncCtrl.curBuffer+mjpegEncCtrl.curLen);	
		
	CSIMODE  |= BIT(31);//CSI_DCEN
	//PRE_JPCON1 |= BIT(10);
	//SetIntSrc(_CSI_INT_);	
	
	PRE_JPCON1 |= BIT(8); //JERUN
	PRE_JPELINECNT = 8;
	//Delay_MS(10);
	//debg("j -mon:%x,%x\n",PRE_JPCON1,PRE_JPINTCON);
	PRE_JPELINECNT = 800;	
	//SetIntSrc(_JPG_INT_);
	ax32xx_intEnable(IRQ_JPGA,1); // enable jpegirq
	//debg("mjpA: <manual on>\n");	
	//debg("M");
	return 1;
}

/*******************************************************************************
* Function Name  : hal_mjpegUVCInit
* Description    : hal layer .mjpeg initial for uvc
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern void videoRecordImageWatermark(INT16U width,INT16U height,INT8U en);
int hal_mjpegUVCStart(u16 win_w, u16 win_h, u8 quality)
{
	hal_mjpegEncodeInit();
	//hal_mjpegEncodeResolution(win_w,win_h);
	hal_mjpegEncodeResolutionImage(win_w,win_h);
	if(hal_mjpegMemInit()<0)
	{
		debg("HAL : [MJPEG]<ERROR> memory malloc fail\n");
		return -1;
	}
	if((mjpegEncCtrl.csi_width  > win_w) || (mjpegEncCtrl.csi_height > win_h)){
		//hal_mjpegEncodeResolution(win_w,win_h);
		//if(hal_mjpegMemInit()<0)
		//{
		//	debg("HAL : [MJPEG]<ERROR> memory malloc fail\n");
		//	return -1;
		//}	
		
		mjpegEncCtrl.type = MJPEG_TYPE_UVC;	
		mjpegEncCtrl.mjpeg_width = win_w;
		mjpegEncCtrl.mjpeg_height = win_h;
		quality = hal_mjpegQualityCheck(quality);

		if(!ax32xx_hvScaler(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h)){
			return -1;	
		}
		ax32xx_csihv_tomjp_dma_cfg((u8*)mjpegEncCtrl.ybuffer,(u8*)mjpegEncCtrl.uvbuffer,win_h,win_w);	
		
		hal_streamInit(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpegNode,MJPEG_ITEM_NUM,(u32)mjpegEncCtrl.mjpbuf,mjpegEncCtrl.mjpsize);
		mjpegEncCtrl.curLen = mjpegEncCtrl.mjpsize;	
		
		ax32xx_mjpegEncodeInit(1,0);
		ax32xx_mjpeg_inlinebuf_init((u8*)mjpegEncCtrl.ybuffer,(u8*)mjpegEncCtrl.uvbuffer);
		ax32xx_mjpegEncodeSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, mjpegEncCtrl.mjpeg_width, mjpegEncCtrl.mjpeg_height);
		ax32xx_mjpegEncodeQuilitySet(quality);
		ax32xx_mjpegEncodeInfoSet(0);
		videoRecordImageWatermark(win_w,win_h,false);
	
		ax32xx_csiISRRegiser(CSI_IRQ_JPG_FRAME_END,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_SEN_STATE_INT,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_VXY_FRAME_EN,(void *)hal_mjpeg_manual_on);
		ax32xx_mjpegEA_ncodeISRRegister(hal_mjpeg_manual_fdown);
		ax32xx_csiOutputSet(CSI_OUTPUT_WIFIEN,1);  
		ax32xx_csiEnable(1);
		mjpegEncCtrl.drop = 0;	
	}
	else{
		mjpegEncCtrl.mjpeg_width = win_w;
		mjpegEncCtrl.mjpeg_height = win_h;
		quality = hal_mjpegQualityCheck(quality);
		ax32xx_csiScaler(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h,0,0,mjpegEncCtrl.csi_width, mjpegEncCtrl.csi_height);
		u32 line;
		if((mjpegEncCtrl.csi_width  > win_w) || (mjpegEncCtrl.csi_height > win_h)){
			line = win_h;
		}else{
			line = HAL_CFG_MJPEG_HEIGHT	;	
		}
		ax32xx_csiMJPEGFrameSet(mjpegEncCtrl.ybuffer,mjpegEncCtrl.uvbuffer,line,win_w);			
		
		ax32xx_mjpegEncodeInit(0,1);
		ax32xx_mjpegEncodeSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h);
		ax32xx_mjpegEncodeQuilitySet(quality);
		ax32xx_mjpegEncodeInfoSet(0);
		videoRecordImageWatermark(win_w,win_h,false);
		
		mjpegEncCtrl.type = MJPEG_TYPE_UVC;
		hal_streamInit(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpegNode,MJPEG_ITEM_NUM,(u32)mjpegEncCtrl.mjpbuf,mjpegEncCtrl.mjpsize);
		mjpegEncCtrl.curBuffer = hal_streamMalloc(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpsize);
		if(mjpegEncCtrl.curBuffer==0)
			return -1;
		mjpegEncCtrl.curLen = mjpegEncCtrl.mjpsize;
		
		ax32xx_mjpegEncodeBufferSet(mjpegEncCtrl.curBuffer,mjpegEncCtrl.curBuffer+mjpegEncCtrl.curLen);

		ax32xx_csiISRRegiser(CSI_IRQ_JPG_FRAME_END,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_SEN_STATE_INT,hal_mjpegStart);

		ax32xx_mjpegEA_ncodeISRRegister(hal_mjpegCallback);

		ax32xx_csiEnable(1);
		mjpegEncCtrl.drop = 0;
	}
    return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegPhotoInit
* Description    : hal layer .mjpeg initial for photo
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int hal_mjpegPhotoStart(u16 win_w, u16 win_h, u8 quality, u8 timestramp)
{  
	hal_mjpegEncodeInit();
	if((mjpegEncCtrl.csi_width  > win_w) || (mjpegEncCtrl.csi_height > win_h)){
		//hal_mjpegEncodeResolution(win_w,win_h);
		//if(hal_mjpegMemInit()<0)
		//{
		//	debg("HAL : [MJPEG]<ERROR> memory malloc fail\n");
		//	return -1;
		//}	
		
		mjpegEncCtrl.type = MJPEG_TYPE_PHOTO;	
		mjpegEncCtrl.mjpeg_width = win_w;
		mjpegEncCtrl.mjpeg_height = win_h;
		mjpegEncCtrl.qulity = hal_mjpegQualityCheck(quality);

		if(!ax32xx_hvScaler(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h)){
			return -1;	
		}
		ax32xx_csihv_tomjp_dma_cfg((u8*)mjpegEncCtrl.ybuffer,(u8*)mjpegEncCtrl.uvbuffer,win_h,win_w);	
		
		hal_streamInit(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpegNode,MJPEG_ITEM_NUM,(u32)mjpegEncCtrl.mjpbuf,mjpegEncCtrl.mjpsize);
		mjpegEncCtrl.curLen = mjpegEncCtrl.mjpsize;	
		
		ax32xx_mjpegEncodeInit(1,0);
		ax32xx_mjpeg_inlinebuf_init((u8*)mjpegEncCtrl.ybuffer,(u8*)mjpegEncCtrl.uvbuffer);
		ax32xx_mjpegEncodeSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, mjpegEncCtrl.mjpeg_width, mjpegEncCtrl.mjpeg_height);
		ax32xx_mjpegEncodeQuilitySet(mjpegEncCtrl.qulity);
		ax32xx_mjpegEncodeInfoSet(0);
		videoRecordImageWatermark(win_w,win_h,timestramp);
	
		ax32xx_csiISRRegiser(CSI_IRQ_JPG_FRAME_END,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_SEN_STATE_INT,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_VXY_FRAME_EN,(void *)hal_mjpeg_manual_on);
		ax32xx_mjpegEA_ncodeISRRegister(hal_mjpeg_manual_fdown);
		ax32xx_csiOutputSet(CSI_OUTPUT_WIFIEN,1);  
		ax32xx_csiEnable(1);
		mjpegEncCtrl.drop = 0;	
	}else{
	
		/* if(hal_mjpegMemInit()<0)
		{
			debg("HAL : [MJPEG]<ERROR> memory malloc fail\n");
			return -1;
		}*/
		mjpegEncCtrl.type = MJPEG_TYPE_PHOTO;
		mjpegEncCtrl.mjpeg_width = win_w;
		mjpegEncCtrl.mjpeg_height = win_h;
		quality = hal_mjpegQualityCheck(quality);
		
		ax32xx_csiScaler(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h,0,0,mjpegEncCtrl.csi_width, mjpegEncCtrl.csi_height);
		ax32xx_csiMJPEGFrameSet(mjpegEncCtrl.ybuffer,mjpegEncCtrl.uvbuffer,HAL_CFG_MJPEG_HEIGHT,HAL_CFG_MJPEG_WIDTH);//mjpegEncCtrl.csi_height,mjpegEncCtrl.csi_width);
		
		ax32xx_mjpegEncodeInit(0,0);
		ax32xx_mjpegEncodeSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h);
		ax32xx_mjpegEncodeQuilitySet(quality);
		ax32xx_mjpegEncodeInfoSet(0);
		videoRecordImageWatermark(win_w,win_h,timestramp);

		hal_streamInit(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpegNode,MJPEG_ITEM_NUM,(u32)mjpegEncCtrl.mjpbuf,mjpegEncCtrl.mjpsize);
		mjpegEncCtrl.curBuffer = hal_streamMalloc(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpsize);
		if(mjpegEncCtrl.curBuffer==0)
			return -1;
		mjpegEncCtrl.curLen = mjpegEncCtrl.mjpsize;
		ax32xx_mjpegEncodeBufferSet(mjpegEncCtrl.curBuffer,mjpegEncCtrl.curBuffer+mjpegEncCtrl.curLen);
		
		ax32xx_csiISRRegiser(CSI_IRQ_JPG_FRAME_END,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_SEN_STATE_INT,hal_mjpegStart);
		ax32xx_csiISRRegiser(CSI_IRQ_VXY_FRAME_EN,NULL);
		ax32xx_mjpegEA_ncodeISRRegister(hal_mjpegCallback);

		mjpegEncCtrl.drop = 0;
	
	}

	debg("PRE_JPCON1:%x,%x\n",quality,(PRE_JPCON1 >> 23)&0x0f);
	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegAVIInit
* Description    : hal layer .mjpeg initial for avi
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int hal_mjpegAVIStart(u16 win_w, u16 win_h, u8 quality, u8 timestramp)
{
	hal_mjpegEncodeInit();
	if((mjpegEncCtrl.csi_width  > win_w) || (mjpegEncCtrl.csi_height > win_h))
	{
		//hal_mjpegEncodeResolution(win_w,win_h);
		//if(hal_mjpegMemInit()<0)
		//{
		//	debg("HAL : [MJPEG]<ERROR> memory malloc fail\n");
		//	return -1;
		//}	
		
		mjpegEncCtrl.type = MJPEG_TYPE_VIDEO;	
		mjpegEncCtrl.mjpeg_width = win_w;
		mjpegEncCtrl.mjpeg_height = win_h;
		mjpegEncCtrl.qulity = hal_mjpegQualityCheck(quality);

		if(!ax32xx_hvScaler(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h)){
			return -1;	
		}
		ax32xx_csihv_tomjp_dma_cfg((u8*)mjpegEncCtrl.ybuffer,(u8*)mjpegEncCtrl.uvbuffer,win_h,win_w);	
		hal_streamInit(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpegNode,MJPEG_ITEM_NUM,(u32)mjpegEncCtrl.mjpbuf,mjpegEncCtrl.mjpsize);
		mjpegEncCtrl.curLen = mjpegEncCtrl.mjpsize;	
#if _DEBG_CUT_SDR_DATA_  ==  _DEBG_CUT_POST_YUV_INAVI_    
		extern u32 cut_sdr_data_addr;
		cut_sdr_data_addr = mjpegEncCtrl.ybuffer;
		extern bool cut_sdr_data_en;
		cut_sdr_data_en = 1;
#endif		
		ax32xx_mjpegEncodeInit(1,1);
		ax32xx_mjpeg_inlinebuf_init((u8*)mjpegEncCtrl.ybuffer,(u8*)mjpegEncCtrl.uvbuffer);
		ax32xx_mjpegEncodeSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, mjpegEncCtrl.mjpeg_width, mjpegEncCtrl.mjpeg_height);
		ax32xx_mjpegEncodeQuilitySet(mjpegEncCtrl.qulity);
		ax32xx_mjpegEncodeInfoSet(1);
		videoRecordImageWatermark(win_w,win_h,timestramp);
	
	
		ax32xx_csiISRRegiser(CSI_IRQ_JPG_FRAME_END,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_SEN_STATE_INT,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_VXY_FRAME_EN,(void *)hal_mjpeg_manual_on);
		ax32xx_mjpegEA_ncodeISRRegister(hal_mjpeg_manual_fdown);
		ax32xx_csiOutputSet(CSI_OUTPUT_WIFIEN,1);  
		ax32xx_csiEnable(1);
		mjpegEncCtrl.drop = 0;	
	}else{
		/* if(hal_mjpegMemInit()<0)
		{
			debg("HAL : [MJPEG]<ERROR> memory malloc fail\n");
			return -1;
		}*/
		mjpegEncCtrl.mjpeg_width = win_w;
		mjpegEncCtrl.mjpeg_height = win_h;
		quality = hal_mjpegQualityCheck(quality);

		ax32xx_csiScaler(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h,0,0,mjpegEncCtrl.csi_width, mjpegEncCtrl.csi_height);
		
		
		ax32xx_csiMJPEGFrameSet(mjpegEncCtrl.ybuffer,mjpegEncCtrl.uvbuffer,HAL_CFG_MJPEG_HEIGHT,HAL_CFG_MJPEG_WIDTH);// mjpegEncCtrl.csi_height,mjpegEncCtrl.csi_width);
		
		ax32xx_mjpegEncodeInit(0,1);
		ax32xx_mjpegEncodeSizeSet(mjpegEncCtrl.csi_width,mjpegEncCtrl.csi_height, win_w, win_h);
		ax32xx_mjpegEncodeQuilitySet(quality);
		ax32xx_mjpegEncodeInfoSet(1);
		videoRecordImageWatermark(win_w,win_h,timestramp);
		mjpegEncCtrl.type = MJPEG_TYPE_VIDEO;	
		
		hal_streamInit(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpegNode,MJPEG_ITEM_NUM,(u32)mjpegEncCtrl.mjpbuf,mjpegEncCtrl.mjpsize);
		mjpegEncCtrl.curBuffer = hal_streamMalloc(&mjpegEncCtrl.vids,mjpegEncCtrl.mjpsize);
		if(mjpegEncCtrl.curBuffer==0)
			return -1;
		mjpegEncCtrl.curLen = mjpegEncCtrl.mjpsize;
		
		ax32xx_mjpegEncodeBufferSet(mjpegEncCtrl.curBuffer,mjpegEncCtrl.curBuffer+mjpegEncCtrl.curLen);
		ax32xx_csiISRRegiser(CSI_IRQ_JPG_FRAME_END,NULL);
		ax32xx_csiISRRegiser(CSI_IRQ_SEN_STATE_INT,hal_mjpegStart);
		ax32xx_csiISRRegiser(CSI_IRQ_VXY_FRAME_EN,NULL);
		ax32xx_mjpegEA_ncodeISRRegister(hal_mjpegCallback);

		mjpegEncCtrl.drop = 0;
	}

    
    


	return 0;
}

/*******************************************************************************
* Function Name  : hal_mjpegRawDataGet
* Description    : hal layer.get mjpeg fram raw data
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void *hal_mjpegRawDataGet(void **hbuff,u32 *addr,u32 *len)
{
     return ((void *)1);	
}
/*******************************************************************************
* Function Name  : hal_mjpegRawBufferGet
* Description    : hal layer.check raw buffer addr &length
* Input          : u32 *addr : addr
                      u32 *len : length
* Output         : None
* Return         : int <0  : end
*******************************************************************************/
void *hal_mjpegRawBufferGet(void *buffer,u32 *addr,u32 *len,s32 *sync, s32 *sync_next)
{
	u32 buff,size;
	s32 syn_cnt, syn_cnt_next;
	*sync=0;
	*sync_next=0;

	if(hal_streamOut(&mjpegEncCtrl.vids,&buff,&size,&syn_cnt, &syn_cnt_next)<0)
		return NULL;
		
	if(size == 0){
		hal_mjpegRawBufferfree();
		debg("jlen=0\n");
		return NULL;
	}
	if(/*(mjpegEncCtrl.type != MJPEG_TYPE_PHOTO) && */((u32)hal_mjpeg_mallocbuf() == buff))
	{
		//debg("j conver\n");
		hal_mjpegRawBufferfree();
		debg("jbuf overlay\n");
		return NULL;
	}
	
	//check 0xffd8
	u8 *p = (u8*)buff;
	ax32xx_sysDcacheFlush((u32)p,16);
	if((p[0] != 0xff) || (p[1] != 0xd8)){
		if((p[8] != 0xff) || (p[9] != 0xd8)){
			hal_mjpegRawBufferfree();
			debg("jhead err:");debgbuf(p,16);
			return NULL;	
		}	
	}
	if(addr)
		*addr = buff;
	if(len)
		*len = size;
	if(sync)
		*sync = syn_cnt;
	if(sync_next)
		*sync_next = syn_cnt_next;
    
	return ((void *)buff);
}

/*******************************************************************************
* Function Name  : hal_mjpegRawBuffer_prefull
* Description    : hal layer.mjpeg buffer pre full(2/3) just
* Input          : None
* Output         : None
* Return         : true:mjpeg buffer is pre_full
*******************************************************************************/
bool hal_mjpegRawBuffer_prefull(void)
{
	s32 size;
	size=hal_stream_size(&mjpegEncCtrl.vids);
	if(size<0)
		return false;
	if(size>((mjpegEncCtrl.mjpsize-200*1024)/2))
		return true;
	return false;
}
/*******************************************************************************
* Function Name  : hal_mjpegRawBuffer_prefull
* Description    : hal layer.mjpeg buffer pre full(2/3) just
* Input          : None
* Output         : None
* Return         : true:mjpeg buffer is pre_full
*******************************************************************************/
bool hal_mjpegRawBuffer_halffull(void)
{
	s32 size;
	size=hal_stream_size(&mjpegEncCtrl.vids);
	if(size<0)
		return false;
	if(size>((mjpegEncCtrl.mjpsize-200*1024)/4))
		return true;
	return false;
}
/*******************************************************************************
* Function Name  : hal_mjpegRawBufferfree
* Description    : hal layer.set mjpeg fram raw data
* Input          : void *buffer : frame buffer
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegRawBufferfree(void)
{
	hal_streamfree(&mjpegEncCtrl.vids);
}
/*******************************************************************************
* Function Name  : hal_mjpegRawDataSet
* Description    : hal layer.set mjpeg fram raw data
* Input          : void *buffer : frame buffer
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegRawDataSet(void *buffer)
{
	if(buffer)
	{
		hal_mjpegRawBufferfree();
		
	}
}
/*******************************************************************************
* Function Name  : hal_mjpegQTTable
* Description    : hal layer.mjpeg decode qt table caculation
* Input          : u8 * seg : buffer
                      u32 len  : length
* Output         : None
* Return         : None
*******************************************************************************/
static int hal_mjpegQTTable(u8 * seg,u32 len)
{
	u8 d, *p;
	while(len)
	{
		d = seg[0];
		if (d & 0xF0) 
			return -1;			/* Err: not 8-bit resolution */
		p = mjpegDecCtrl.dqt[d & 3];						/* Get table ID */
		
		memcpy(p,&seg[1],64);
		mjpegDecCtrl.qt_addr[d & 3] = (u32)&seg[1];
		seg += 65;
		len -= 65;
	}
    
    if(mjpegDecCtrl.qt_addr[2])
        return -1;
	
	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegHuffmanTable
* Description    : hal layer.mjpeg decode huffman table caculation
* Input          : u8 * seg : buffer
                      u32 len  : length
* Output         : None
* Return         : None
*******************************************************************************/
static void hal_mjpegHuffmanTable(u8 * seg,u32 len)
{
	int counter,i;
	u8  order,j;
	u16 code,d;
	while(len)
	{
		d = *seg++; len--;
		d = ((d & 0x10) >> 3) + (d & 0x01);

		counter = code = 0;

		for(i=0,order = 15; i<16; i++)
		{
			j = *seg++;
			mjpegDecCtrl.minicode[d][i] = ((code >> order) & 0xffff);
			mjpegDecCtrl.valptr[d][i]   = counter;
			counter += j;
			code += j << order;
			order--;
		}
		len -= 16;

		for(i=0; i < counter; i++)
		{
			mjpegDecCtrl.dht[d][i] = *seg++;
		}
		len -= counter;
	}	
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeSize
* Description    : hal layer.mjpeg decode get jpeg file header
* Input          : u8 * p_jpeg_header : buffer
* Output         : u16 *width
                       u16 *height
* Return         : None
*******************************************************************************/
static int hal_mjpegDecodeSize(u8 * p_jpeg_header,u16 *width,u16 *height)
{
	u8 *seg;
	u32 i;
	int res = -1;
	

	seg = p_jpeg_header;
	
	if (LDB_WORD(seg) != 0xFFD8) 
	   return -1;
	
	seg += 2;

	for(i = 512;i > 0;i -= 2)
	{
		if(LDB_WORD(seg) == 0xffc0)
		{
			seg += 4;
			*width = LDB_WORD(seg+3);
			*height = LDB_WORD(seg+1);
			res = 0;
			break;
		}
		seg += 2;
	}

	return res;
}
/*******************************************************************************
* Function Name  : hal_mjpegHeaderParse
* Description    : hal layer.mjpeg decode parse jpeg file 
* Input          : u8 * p_jpeg_header : buffer
* Output         : None
* Return         : None
*******************************************************************************/
int hal_mjpegHeaderParse (u8 * p_jpeg_header)
{
	u8 *seg, b;
	u16 marker;
	u32 ofs,i, len;
	int res=0;
	u8 *temp_buf=halSysMemLineCache+1024;

	
//	u8 * temp_buf = tempbuf_malloc(1024);
	mjpegDecCtrl.dqt[0] = &temp_buf[0];
	mjpegDecCtrl.dqt[1] = &temp_buf[0x40];
	mjpegDecCtrl.dqt[2] = &temp_buf[80];
	mjpegDecCtrl.dqt[3] = &temp_buf[0xc0];
	
	mjpegDecCtrl.minicode[0] = (u16 *)&temp_buf[0x100];
	mjpegDecCtrl.minicode[1] = (u16 *)&temp_buf[0x120];
	mjpegDecCtrl.minicode[2] = (u16 *)&temp_buf[0x140];
	mjpegDecCtrl.minicode[3] = (u16 *)&temp_buf[0x160];
	
	mjpegDecCtrl.valptr[0] = &temp_buf[0x180];
	mjpegDecCtrl.valptr[1] = &temp_buf[0x190];
	mjpegDecCtrl.valptr[2] = &temp_buf[0x1a0];
	mjpegDecCtrl.valptr[3] = &temp_buf[0x1b0];
	
	mjpegDecCtrl.dht[0] = &temp_buf[0x1c0];
	mjpegDecCtrl.dht[1] = &temp_buf[0x1cc];
	mjpegDecCtrl.dht[2] = &temp_buf[0x1d8];
	mjpegDecCtrl.dht[3] = &temp_buf[0x27a];

	seg = p_jpeg_header;
	if (LDB_WORD(seg) != 0xFFD8) 
	{
		res = -1;
		goto out;
	}	
	ofs = 2;

	for (;;) 
	{
		/* Get a JPEG marker */
		seg = p_jpeg_header + ofs;
		marker = LDB_WORD(seg);		/* Marker */
		if(marker == 0xffff){
			ofs += 1;
			continue;
		}
		len = LDB_WORD(seg + 2);	/* Length field */
		if (len <= 2 || (marker >> 8) != 0xFF) 
		{
			res = -2;
			goto out;
		}
		len -= 2;		/* Content size excluding length field */
		ofs += 4 + len;	/* Number of bytes loaded */
		seg += 4;
		
		switch (marker & 0xFF) 
		{
			case 0xC0:	/* SOF0 (baseline JPEG) */
				mjpegDecCtrl.width = LDB_WORD(seg+3);		/* Image width in unit of pixel */
				mjpegDecCtrl.height = LDB_WORD(seg+1);		/* Image height in unit of pixel */
				if (seg[5] != 3)
				{
					res = -3;
					goto out;
				}

				/* Check three image components */
				for (i = 0; i < 3; i++) 
				{	
					b = seg[7 + 3 * i];							/* Get sampling factor */
					if (!i) 
					{	/* Y component */
						if (/*b != 0x11 &&*/ b != 0x22 && b != 0x21)/* Check sampling factor */
						{
							res = -4;
							goto out;
						}
						mjpegDecCtrl.msx = b >> 4;			/* Size of MCU [blocks] */
						mjpegDecCtrl.msy = b & 15;
					} 
					else
					{	/* Cb/Cr component */
						if (b != 0x11)
						{
							res = -4;
							goto out;
						}
					}
					b = seg[8 + 3 * i];							/* Get dequantizer table ID for this component */
					if (b > 3)
					{
						res = -4;
						goto out;
					}
					mjpegDecCtrl.qtid[i] = b;
				}
				break;

			case 0xDD:	/* DRI */
				/* Get restart interval (MCUs) */
				mjpegDecCtrl.nrst = LDB_WORD(seg);
				break;

			case 0xC4:	/* DHT */
				/* Create huffman tables */
				hal_mjpegHuffmanTable(seg, len);
				break;

			case 0xDB:	/* DQT */
			/* Create de-quantizer tables */
				if (hal_mjpegQTTable(seg, len) <0) 
				{
					res = -7;
					goto out;
				}
				break;

			case 0xDA:	/* SOS */
				if (!mjpegDecCtrl.width || !mjpegDecCtrl.height)
				{
					res = -8;
					goto out;
				}

				if (*seg++ != 3)
				{
					res = -9;
					goto out;
				}

				/* Check if all tables corresponding to each components have been loaded */
				for (i = 0; i < 3; i++) 
				{
					mjpegDecCtrl.hfid[seg[0] - 1][0] = seg[1] & 0xf; /* AC */
					mjpegDecCtrl.hfid[seg[0] - 1][1] = seg[1] >> 4;  /* DC */
					seg += 2;
				}

				mjpegDecCtrl.bsptr = seg + len - 7;
				mjpegDecCtrl.bs_ofs = mjpegDecCtrl.bsptr - p_jpeg_header;
				for(i=0;i<2;i++)
				{
					mjpegDecCtrl.qt_ofs[i] = (u16)((u32)mjpegDecCtrl.qt_addr[i] - (u32)p_jpeg_header);
				}
				
			    ax32xx_mjpegDecodeInitTable((u32)temp_buf,0);
                
				goto out;		/* Initialization succeeded. Ready to decompress the JPEG image. */

			default:	/* Unknown segment (comment, exif or etc..) */
				break;
		}
	}
	
out:
//	tempbuf_free(temp_buf);
	return res;
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeInit
* Description    : hal layer.mjpeg decode initial
* Input          : u8 * p_jpeg_start : buffer
                      u8 * p_out_y : out ybuffer
                      u8 * p_out_uv: out uvbuffer
                      u16 dst_width: out size width
                      u16 dst_height:out size height
* Output         : None
* Return         : None
*******************************************************************************/
static int hal_mjpegDecodeInit(u8 * p_jpeg_start,u8 * p_out_y,u8 * p_out_uv,
                               u16 dst_width,u16 dst_height,u32 stride)
{
	static const u8 yuv_format_map[] = {0,0,2,1,0};
	int ret;
	u32 comp_table_id;
    
	memset(&mjpegDecCtrl,0,sizeof(MJPEG_DEC_OP_T));

	ret = hal_mjpegHeaderParse(p_jpeg_start);
	if(ret<0)
	{
		debg("HAL: <MJPEG>[ERROR] jpeg header parse fail.%d\n",ret);
		return ret;
	}
    mjpegDecCtrl.comp_table_id =
    comp_table_id = (mjpegDecCtrl.hfid[2][0]<<29)|//AC entropy coding table for comp 3
                    (mjpegDecCtrl.hfid[2][1]<<28)|//DC entropy coding table for comp 3
                    (mjpegDecCtrl.qtid[2]<<26)|//quant talbe for comp 3
                    (1<<23)|//vertical sampling for comp 3
                    (1<<20)|//horizontal sampling for comp 3
                    (mjpegDecCtrl.hfid[1][0]<<19)|//AC entropy coding table for comp 2
                    (mjpegDecCtrl.hfid[1][1]<<18)|//DC entropy coding table for comp 2
                    (mjpegDecCtrl.qtid[1]<<16)|//quant talbe for comp 2
                    (1<<13)|//vertical sampling for comp 2
                    (1<<10)|//horizontal sampling for comp 2
                    (mjpegDecCtrl.hfid[0][0]<<9)| //AC entropy coding table for comp 1
                    (mjpegDecCtrl.hfid[0][1]<<8)| //DC entropy coding table for comp 1
                    (mjpegDecCtrl.qtid[0]<<6)| //quant talbe for comp 1
                    (mjpegDecCtrl.msy<<3)| //vertical sampling for comp 1
                    (mjpegDecCtrl.msx<<0); //horizontal sampling for comp 1
    
    mjpegDecCtrl.yuvfmt = yuv_format_map[mjpegDecCtrl.msy+mjpegDecCtrl.msx];

    ax32xx_mjpegDecodeInit(mjpegDecCtrl.yuvfmt);
	ax32xx_mjpegDecodeDCTimeSet(1,mjpegDecCtrl.width,mjpegDecCtrl.height);
    ax32xx_mjpegDecodeSetSize(mjpegDecCtrl.width,mjpegDecCtrl.height,dst_width,dst_height,stride);
    ax32xx_mjpegDecodeOutputSet((u32)p_out_y,(u32)p_out_uv);
	ax32xx_mjpegDecodeInputSet((u32)mjpegDecCtrl.bsptr,0);
	ax32xx_mjpegDecodeDriSet(mjpegDecCtrl.nrst);
	ax32xx_mjpegDecodeCompressSet(comp_table_id);

	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeGetResolution
* Description    : hal layer.mjpeg decode get jpeg size
* Input          :  u16 width: out size width
                      u16 height:out size height
* Output         : None
* Return         : None
*******************************************************************************/
int hal_mjpegDecodeGetResolution(u16 *width,u16 *height)
{
	if(width)
		*width = mjpegDecCtrl.width;
	if(height)
		*height = mjpegDecCtrl.height;
	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeSetResolution
* Description    : hal layer.mjpeg decode Set jpeg size
* Input          :  u16 width: out size width
                      u16 height:out size height
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegDecodeSetResolution(u16 width,u16 height)
{
	mjpegDecCtrl.width = width;
	mjpegDecCtrl.height = height;
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodePicture
* Description    : hal layer.mjpeg decode one picture
* Input          : u8 * p_jpeg_start : buffer
                      u8 * p_out_y : out ybuffer
                      u8 * p_out_uv: out uvbuffer
                      u16 dst_width: out size width
                      u16 dst_height:out size height
* Output         : None
* Return         : int 0:success
                          <0: fail
*******************************************************************************/
//TODO:use stride
int hal_mjpegDecodePicture(u8 * p_jpeg_start,u8 * p_out_y,u8 * p_out_uv,u16 dst_width,u16 dst_height)
{
    hal_mjpegDecodeReset();
	if(hal_mjpegDecodeInit(p_jpeg_start,p_out_y,p_out_uv,dst_width,dst_height,0)<0)
		return -1;

    ax32xx_mjpegDecodeEnable(1);
	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodePicture2
* Description    : hal layer.mjpeg decode one picture without int
* Input          : u8 * p_jpeg_start : buffer
                      u8 * p_out_y : out ybuffer
                      u8 * p_out_uv: out uvbuffer
                      u16 dst_width: out size width
                      u16 dst_height:out size height
* Output         : None
* Return         : int 0:success
                          <0: fail
*******************************************************************************/
//TODO:use stride
int hal_mjpegDecodePicture_2(u8 * p_jpeg_start,u8 * p_out_y,u8 * p_out_uv,u16 dst_width,u16 dst_height)
{
    hal_mjpegDecodeReset();
	if(hal_mjpegDecodeInit(p_jpeg_start,p_out_y,p_out_uv,dst_width,dst_height,0)<0)
		return -1;

    ax32xx_mjpegDecodeKick();
	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeStatusCheck
* Description    : hal layer.mjpeg decode get status
* Input          :  
* Output         : None
* Return         : 1 : busy
                       0: idle
*******************************************************************************/
int hal_mjpegDecodeStatusCheck(void)
{
    return ax32xx_mjpegDecodeStatus();
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeErrorCheck
* Description    : hal layer.mjpeg decode get error
* Input          :  
* Output         : None
* Return         : 0 : no error
*******************************************************************************/
u32 hal_mjpegDecodeErrorCheck(void)
{
    return ax32xx_mjpegDecodeCheck();
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeMiniSize
* Description    : hal layer.mjpeg decode mini size caculation
* Input          :  
* Output         : None
* Return         : < 0 fail
*******************************************************************************/
int hal_mjpegDecodeMiniSize(u8 * p_jpeg_start,u16 *min_width,u16 *min_height)
{
	static u16 minsize[][2] = {M(640,480),M(1280,720),M(1920,1080),M(2560,1440),M(4000,3000)};
	u16 src_w;
	u16 src_h;
	if(hal_mjpegDecodeSize(p_jpeg_start,&src_w,&src_h)<0)
	{
		debg("HAL : <MJPEG>[ERROR] jpeg head parse err\n");
		return -1;
	}
	
	u32 check = (src_w<<16)|(src_h);
	switch(check)
	{
		case (640 << 16)|480   : *min_width = minsize[0][0];*min_height = minsize[0][1];break;
		case (1280 << 16)|720  : *min_width = minsize[1][0];*min_height = minsize[1][1];break;
		case (1920 << 16)|1080 : *min_width = minsize[2][0];*min_height = minsize[2][1];break;
		case (2560 << 16)|1440 : *min_width = minsize[3][0];*min_height = minsize[3][1];break;
		case (4000 << 16)|3000 : *min_width = minsize[4][0];*min_height = minsize[4][1];break;
		default: 
			*min_width  = (ROUND_UP(src_w,31) + 1) & ~1;
			*min_height = (ROUND_UP(src_h,31) + 1) & ~1;
			break;
	}
	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeStop
* Description    : hal layer.mjpeg decode stop
* Input          :  
* Output         : None
* Return         : 
*******************************************************************************/
void hal_mjpegDecodeStop(void)
{
    ax32xx_mjpegDecodeStop();
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeReset
* Description    : hal layer.mjpeg decoder reset
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int hal_mjpegDecodeReset(void)
{
    ax32xx_mjpB_reset();
    ax32xx_pipCounterReset(PIP_SRC_JPG);
    hal_mjpB_dcdown();
    hal_mjpB_ecdown();
	return 0;
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeParse
* Description    : hal layer.mjpeg decode stop
* Input          :  u8 * p_jpeg_start : buffer
                       u16 dst_width : out width
                       u16 dst_height: out height
* Output         : None
* Return         : 0 : success
                      <0 : fail
*******************************************************************************/
int hal_mjpegDecodeParse(u8 * p_jpeg_start,u16 dst_width,u16 dst_height)
{
	return hal_mjpegDecodeInit(p_jpeg_start,NULL,NULL,dst_width,dst_height,0);
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeOneFrame
* Description    : hal layer.mjpeg decode one frame,video file using
* Input          :  u8 * p_jpeg_start : buffer
                       u8 * p_out_y : out ybuffer
                       u8 * p_out_uv:out uvbuffer
* Output         : None
* Return         : 0 : success
                      <0 : fail
*******************************************************************************/
void hal_mjpegDecodeOneFrame(u8 * p_jpeg_start,u8 * p_out_y,u8 * p_out_uv)
{
	mjpegDecCtrl.bsptr = p_jpeg_start + mjpegDecCtrl.bs_ofs;

    ax32xx_mjpegDecodeOutputSet((u32)p_out_y,(u32)p_out_uv);
    ax32xx_mjpegDecodeInputSet((u32)mjpegDecCtrl.bsptr,0);
	ax32xx_mjpegDecodeEnable(1);	
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeOneFrame_ext
* Description    : hal layer.mjpeg decode one frame,
* Input          :  u8 * p_jpeg_start : buffer
                       u8 * p_out_y : out ybuffer
                       u8 * p_out_uv:out uvbuffer
* Output         : None
* Return         : 0 : success
                      <0 : fail
*******************************************************************************/
void hal_mjpegDecodeOneFrame_Ext(u8 * p_jpeg_start,u8 * p_out_y,u8 * p_out_uv)
{
	u8 *qt[3],i;
	for(i=0;i<2;i++)
	{
		qt[i] = p_jpeg_start+mjpegDecCtrl.qt_ofs[i];
	}
	mjpegDecCtrl.bsptr = p_jpeg_start + mjpegDecCtrl.bs_ofs;

    ax32xx_mjpegDecodeQDTCfg(qt);
    ax32xx_mjpegDecodeOutputSet((u32)p_out_y,(u32)p_out_uv);
    ax32xx_mjpegDecodeInputSet((u32)mjpegDecCtrl.bsptr,0);
	ax32xx_mjpegDecodeEnable(1);	
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeRestart_Ext
* Description    : hal layer.mjpeg decode one frame,use last configration.
* Input          :  u8 * p_jpeg_start : buffer
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegDecodeRestart_Ext(u8 * p_jpeg_start)
{
	u8 *qt[3],i;
	for(i=0;i<2;i++)
	{
		qt[i] = p_jpeg_start+mjpegDecCtrl.qt_ofs[i];
	}
	mjpegDecCtrl.bsptr = p_jpeg_start + mjpegDecCtrl.bs_ofs;

    ax32xx_mjpegDecodeQDTCfg(qt);
    ax32xx_mjpegDecodeInputSet((u32)mjpegDecCtrl.bsptr,0);
	ax32xx_mjpegDecodeEnable(1);	
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeOneFrame_Fast
* Description    : quickly mjpeg decoder initial and kick decoder run
*                  NEED call hal_mjpegDecodeInit before call this function
* Input          : u8 * p_jpeg_start : buffer
                   u8 * p_out_y : out ybuffer
                   u8 * p_out_uv: out uvbuffer
                   u16 dst_width: out size width
                   u16 dst_height:out size height
                   u16 stride :
* Output         : None
* Return         : None
*******************************************************************************/
void hal_mjpegDecodeOneFrame_Fast(u8 * p_jpeg_start,
                                  u8 * p_out_y,u8 * p_out_uv,
                                  u16 dst_width,u16 dst_height,
                                  u16 stride)
{
    ax32xx_mjpegDecodeInit(mjpegDecCtrl.yuvfmt);
	ax32xx_mjpegDecodeDCTimeSet(1,mjpegDecCtrl.width,mjpegDecCtrl.height);
    ax32xx_mjpegDecodeSetSize(mjpegDecCtrl.width,mjpegDecCtrl.height,dst_width,dst_height,stride);
	ax32xx_mjpegDecodeDriSet(mjpegDecCtrl.nrst);
    ax32xx_mjpegDecodeCompressSet(mjpegDecCtrl.comp_table_id);
    hal_mjpegDecodeOneFrame_Ext(p_jpeg_start,p_out_y,p_out_uv);
}
/*******************************************************************************
* Function Name  : hal_mjpegDecodeODma1Cfg
* Description    : config output dma1(no block-scaler),call this function before init jpeg-decoder
*                  hal_mjpegDecodeStop will disable DMA1
* Input          : u8 * y_addr
*                  u8 * uv_addr
*                  bool dma_en
* Output         : none
* Return         : none
*******************************************************************************/
void hal_mjpegDecodeODma1Cfg(u8 * y_addr,u8 * uv_addr,bool dma_en)
{
    ax32xx_mjpegDecodeODma1Cfg(y_addr,uv_addr,dma_en);
}

static u32 ftmout;
int hal_BackRecDecodeStatusCheck(void)
{
	int ret = ax32xx_mjpegDecodeStatus();
	if(ret){
		ftmout++;
		if(ftmout > 6){ //6frame time out
			ftmout = 0;
			hal_mjpegDecodeReset();
			ax32xx_mjpegDecodeStop();	
			huvc_dcod_down(1);
			debg("hal_mjpegDecodeStatusCheck: <time out>\n");
			sysLog("mjpegDecode time out\n");
		}
	}else{
		ftmout = 0;
	}
    return ret;
}
