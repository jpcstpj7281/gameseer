/******************************************************************************


******************************************************************************/

#include "loadFPGA.h"

#define FPGA_FILE_MAX_LENGTH   0x300000

/* LATTICE 根据硬件连接，定义CPU 的IO脚*/
#define	FPGA_LATTICE_DIN            ((DWORD)0x01<<21)       /*PB21*/
#define	FPGA_LATTICE_CLK            ((DWORD)0x01<<22)       /*PB22*/
#define	FPGA_LATTICE_INIT           ((DWORD)0x01<<23)       /*PB23*/
/* ALTERA 据硬件连接，定义CPU 的IO脚*/
#define	FPGA_ALTERA_DIN             ((DWORD)(0x01<<26))      /*PB26*/  
#define	FPGA_ALTERA_CLK             ((DWORD)(0x01<<28))      /*PB28*/
#define	FPGA_ALTERA_INIT            ((DWORD)(0x01<<24))      /*PB24*/

/* LATTICE 根据硬件连接，定义CPU 的IO脚*/
#define	FPGA_DIN_LATTICE            21       /*PB21*/
#define	FPGA_DONE_LATTICE           11       /*PB11*/
#define	FPGA_CLK_LATTICE            22       /*PB22*/
#define	FPGA_INIT_LATTICE           23       /*PB23*/
#define	FPGA_PROG_LATTICE           20       /*PB20*/

#define FPGA_BUS_ENABLE             0		 /*P0*/

/* ALTERA 据硬件连接，定义CPU 的IO脚*/
#define	FPGA_DIN_ALTERA             26      /*PB26*/  
#define	FPGA_DONE_ALTERA            29      /*PB29*/
#define	FPGA_CLK_ALTERA             28      /*PB28*/
#define	FPGA_INIT_ALTERA            24      /*PB24*/
#define	FPGA_PROG_ALTERA            25      /*PB25*/
/**/
#define	FPGA_RESET		            2       /*PC2*/


#define ALTERA_PIN        (1<<FPGA_CLK_ALTERA | 1<<FPGA_DONE_ALTERA)

#define FPGA_CONFIG             0
#define FPGA_RST                2
LOCAL VOID mydelay(VOID);
SDWORD LoadFpga_ALTERA();
SDWORD LoadFpga_LATTICE();

/******************************************************************************
获得某个管脚的电平值

输入:MPP pin number
返回:获得的这个管脚的电平值0或者1
*/
LOCAL BYTE GpioValGet_ALTERA(BYTE pinNum)
{
        return BSP_AT91F_OR_PIO_GetInput(BSP_PIOB,pinNum);
}

/*把某个管脚设置为高或低电平
输入参数:pinNum  MPP pin number   
         state      电平状态
*/

LOCAL VOID GpioValSet_ALTERA(BYTE pinNum,BYTE state)
{
    if (state == 1)
    {
        
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,pinNum);
    }
    else
    {
        
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,pinNum);
    }
    
}

/*

---------------------------------------------------------------------
GPIO4	MDC					不初始化
GPIO5	MDIO
GPIO6	
GPIO7	
GPIO8
---------------------------------------------------------------------	
GPIO9	I2C_SDA				I2C总线
GPIO10	I2C_SCL
---------------------------------------------------------------------
GPIO11	RUN_LED				LED灯
GPIO12	ALAM_LED
---------------------------------------------------------------------
GPIO13	Cs8900中断			8900中断
---------------------------------------------------------------------
GPIO14	外设芯片其他中断	不初始化
*/

/*****************************************************************
功能:对FPGA芯片进行复位
输入:无
输出:无
返回:无
说明:CPLD里有对FPGA的复位
 *****************************************************************/

VOID ResetFpga_ALTERA()
{
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,FPGA_RESET);
        taskDelay(2);
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,FPGA_RESET);
}


/*****************************************************************
功能:把配置FPGA用到的5个信号线进行初始化
输入:无
输出:无
返回:无
硬件介绍:
GPIO0	FPGA_DIN			FPGA 加载
GPIO1	FPGA_DONE
GPIO2	FPGA_CLK
GPIO3	FPGA_INIT
 *****************************************************************/
LOCAL VOID InitFpgaPin_ALTERA()
{
    DWORD reg;
    /*对G4的5个IO脚进行初始化*/	
    /*把FPGA_DIN和FPGA_CCLK 和FPGA_PROG设置输出*/
    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_DIN_ALTERA);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_CLK_ALTERA);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_PROG_ALTERA);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,FPGA_RESET);    	
    /*把FPGA_INIT和FPGA_DONE设置输入*/
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_BUS_ENABLE); 
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_ALTERA);
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_INIT_ALTERA);
    /*输出脚初始值置为0*/
    /*BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_BUS_ENABLE);*/
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_PROG_ALTERA);

    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,FPGA_RESET);
	
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_DIN_ALTERA);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_CLK_ALTERA);
    mydelay();

}
/*****************************************************************
功能:设置FPGA的FPGA_CFG管脚的电平
输入:电平状态0或者1
输出:无
返回:无
说明:FPGA的CFG来自CPLD PIN14
 *****************************************************************/
LOCAL VOID SetCfgPin_ALTERA(SDWORD status)
{
    if(0 == status)
    {
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_PROG_ALTERA);
    }
    else if(1 == status)
    {
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_PROG_ALTERA);
    }
    
}

/*****************************************************************
功能:控制CFG脚，发起初始化操作
输入:无
输出:无
返回:无
 *****************************************************************/
LOCAL VOID StartDownLoadFpga_ALTERA()
{
    SetCfgPin_ALTERA(0);
    taskDelay(1);
    SetCfgPin_ALTERA(1);
}
#if 1
/******************************************************************************
* 函数名称: ftpDownload
* 函数功能: 通过FTP从PC机下载文件到指定的地址
                        
* 创建日期: 2003-04-25
* 作    者: 邱文
* 输入参数: 
            CHAR *fileName: 要下载的文件名
            CHAR *TEMPBUFFER: 存放在系统内存的起始地址
* 输出参数: 无
* 返    回: fileLength(文件长度)，失败返回0
* 被调函数：ftpXfer() and ftpCommand()
* 调用函数：bsp_menu_ftpDownload()
*******************************************************************************/
LOCAL DWORD ftpDownload_ALTERA
(
BYTE *fileName,
BYTE *TEMPBUFFER
)
{
    BOOT_PARAMS  params;
    int dataSock;
    int ctrlSock;
    CHAR buf[1024];
    SDWORD nBytes;
    DWORD fileLength = 0;
    SDWORD status;
     
    BYTE *tempBuffer = TEMPBUFFER;

    if ( ( NULL == fileName ) || ( NULL == tempBuffer ) )
    {
        return 0; 
    }
    
    if (usrBootLineCrack (BOOT_LINE_ADRS, &params) != OK)
    {
        printf("根启动参数无效  \n");
        return (0);
    }
 
    if (ftpXfer (params.had, params.usr, params.passwd, "", "RETR %s", "", 
			fileName,&ctrlSock, &dataSock) == ERROR)
    {
        printf("下载文件 \"%s\" 出错 \n", fileName);
        return (0);
    }
  
    while ((nBytes = read (dataSock, buf, sizeof (buf))) > 0)
    {
         
        memcpy (tempBuffer, buf, nBytes);
        fileLength += nBytes;
        tempBuffer += nBytes;

    }
    /*   BSP_MENU_PRINT("     拷贝到缓冲区成功\n");*/

      close (dataSock);
    /*   BSP_MENU_PRINT("     关闭文件成功\n");*/
    if (fileLength > 0)
    {   
        status = OK;
        if (ftpCommand (ctrlSock, "QUIT", 0, 0, 0, 0, 0, 0) != FTP_COMPLETE)
             status = ERROR;
        close (ctrlSock);

        /*printf("\r\nFTP下载成功, 文件长度为 %d",fileLength);*/
        return fileLength;

    }
    else
    {    
        #if 0
        if (nBytes < 0)             /* read error? */
            status = 0;

        if (ftpReplyGet (ctrlSock, TRUE) != FTP_COMPLETE)
            status = 0;
        
        #endif
        if (ftpCommand (ctrlSock, "QUIT", 0, 0, 0, 0, 0, 0) != FTP_COMPLETE)
        {
            status = 0;
        }
        close (ctrlSock);
        printf("FTP下载失败\n");
        return 0;
    }
}

#endif
static DWORD OldHi, OldLo;
static DWORD NewHi, NewLo;
static DWORD TBmp;
/*############################################################
*加载fpga
return: OK  
           ERROR
*/
SDWORD load_fpga_ALTERA(DWORD  fileno)
{
	CHAR filename[4][80]={"host:./oplogic1.bit","host:./oplogic2.bit","host:./oplogic3.bit","host:./oplogic4.bit"};

	//BSP_AT91F_PIO_CfgPullupDisable(BSP_PIOB,ALTERA_PIN);
	//BSP_AT91F_PIO_MultiDriverEnable(BSP_PIOB,ALTERA_PIN);
	BSP_TimeGet(&OldHi, &OldLo);
	LoadFpga_ALTERA(filename,fileno);
	BSP_TimeGet(&NewHi, &NewLo);
	OldLo = (OldLo&0x0000ffff) | (OldHi&0x0000ffff)<<16;
	NewLo = (NewLo&0x0000ffff) | (NewHi&0x0000ffff)<<16;
	TBmp = (NewLo - OldLo);
	TBmp = TBmp*1000>>15;
    printf("load_fpga_ALTERA Total time %dms\n", TBmp);
	return 0;
	
}

/*****************************************************************
功能:从CF卡读取FPGA代码，然后加载到FPGA芯片中
输入:无
输出:无
返回:0         成功
            其他失败
 *****************************************************************/
SDWORD LoadFpga_ALTERA(CHAR filename[4][80],DWORD  fileno)
{

    BYTE *data  = NULL;
    DWORD bytes ;
    BYTE *bootrom_p1 ;
    FILE *bootrom_fd ;
    BYTE  *pFpgaFile = NULL;
    BYTE  dataTemp;
    DWORD  i = 0;
    DWORD  j = 0;
    DWORD  count = 0 ;
    DWORD  ulFileLength = 0;
	DWORD  tempfileno = 0;
	

    InitFpgaPin_ALTERA();
    StartDownLoadFpga_ALTERA();

    /*检测FPGA_INIT信号，如果变为1
    表示已经对FPGA里的memory清除完毕*/
    while(0 == GpioValGet_ALTERA(FPGA_INIT_ALTERA))
    {
        taskDelay(2) ;
        count++ ;
        if( 10 == count)
        {
            printf("\r\n  FPGA INIT Signal error !!") ; 
            return (2);
        }
    }

for(tempfileno=0;tempfileno<fileno;tempfileno++)
{
	
    pFpgaFile = (BYTE*)malloc(FPGA_FILE_MAX_LENGTH);
    if(NULL == pFpgaFile)
    {

        printf( "\nERROR: NO memory!\n" ) ;
        return (1);
    }

   bootrom_p1 = pFpgaFile ;
   
    if((bootrom_fd = fopen( filename[tempfileno], "rb" )) == NULL )
    {
        printf( "\nERROR: can not open file %s\n",filename ) ;
        free( pFpgaFile ) ;
        return (1);
    }

    bytes = 0 ;
    printf( "read FPGA file\n" ) ;
#if 0
    while( fscanf( bootrom_fd, "%c", &dataTemp ) != EOF )
    {
        *bootrom_p1++ = dataTemp ;
        bytes = bytes + 1 ;
        if( bytes >= FPGA_FILE_MAX_LENGTH )
        break ;
    }
#else
	fseek(bootrom_fd, 0, SEEK_END);
	bytes = ftell(bootrom_fd);
	fseek(bootrom_fd, 0, SEEK_SET);
    if(bytes <= FPGA_FILE_MAX_LENGTH)
	    fread(pFpgaFile, 1, bytes, bootrom_fd);
#endif
    fclose( bootrom_fd ) ;

    if( bytes > FPGA_FILE_MAX_LENGTH )
    {
        printf( "ERROR: bootrom file is too long!\n" ) ;
        return (1);
    }
	
	printf( "File %08x\n" ,bytes) ;
	ulFileLength=bytes;
    /*把文件存入到申请的内存块中*/
    /*ulFileLength = ftpDownload("nsp2000.bin", pFpgaFile);   */


    data = pFpgaFile;

	

	/* 启始点*/
    /*开始加载*/
#if 0    
    for(i = 0; i<ulFileLength; i++, data++)
    {
        for( j=0; j<8; j++)
        {    
            /*置FPGA_CLK为0*/
            GpioValSet_ALTERA(FPGA_CLK_ALTERA, 0);    
			
	     /*一个字节的最高bit先打入FPGA，
	     送到DIN脚上，在CLK上升沿打入*/
            /*if(((*data) << j) & 0x80 )*/
            if(((*data) >> j) & 0x01 )
            {
                GpioValSet_ALTERA(FPGA_DIN_ALTERA, 1);   
            }
            else 
            {
                GpioValSet_ALTERA(FPGA_DIN_ALTERA, 0);   
	     }
			
        mydelay();
            /*置FPGA_CLK为1，因为上升沿把DIN
            上的电平值打入FPGA，此时打入*/	
            GpioValSet_ALTERA(FPGA_CLK_ALTERA, 1);    
        mydelay();
        }
          
        if(0 == GpioValGet_ALTERA(FPGA_INIT_ALTERA))
        {
            free(pFpgaFile);
            printf("\r\n  FPGA_INIT_ALTERA in middle!\n") ; 

            return(3);
        }        
    }	
#else
    for(i = 0; i<ulFileLength; i++)
    {
        register DWORD dwTempValue;
        register BYTE val;
        val = *data++;
        dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;
        for( j=0; j<8; j++)
        {    
            if((val >> j) & 0x01)
            {
                /*置FPGA_CLK为0*/            
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_ALTERA_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;

        	    /*一个字节的最高bit先打入FPGA，
        	    送到DIN脚上，在CLK上升沿打入*/
                /*置FPGA_ALTERA_DIN为1*/
                /*GpioValSet_ALTERA(FPGA_DIN_ALTERA, 1);*/
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_ALTERA_DIN;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
    			
                mydelay();
                /*置FPGA_CLK为1，因为上升沿把DIN
                上的电平值打入FPGA，此时打入*/	
                /*GpioValSet_ALTERA(FPGA_CLK_ALTERA, 1); */
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = dwTempValue | FPGA_ALTERA_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
                mydelay();
            }
            else
            {
                /*置FPGA_CLK为0*/            
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_ALTERA_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;

        	    /*一个字节的最高bit先打入FPGA，
        	    送到DIN脚上，在CLK上升沿打入*/
                /*置FPGA_ALTERA_DIN为0*/
                /*GpioValSet_ALTERA(FPGA_DIN_ALTERA, 0);*/
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = dwTempValue | FPGA_ALTERA_DIN;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;
    			
                mydelay();
                /*置FPGA_CLK为1，因为上升沿把DIN
                上的电平值打入FPGA，此时打入*/	
                /*GpioValSet_ALTERA(FPGA_CLK_ALTERA, 1); */
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_ALTERA_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
                mydelay();
            }
        }
          
        dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_PDSR;
      	dwTempValue =  dwTempValue & FPGA_ALTERA_INIT;
        if(0 == dwTempValue)
        {
            free(pFpgaFile);
            printf("\r\n  FPGA_INIT_ALTERA in middle!\n") ; 
			
			free(pFpgaFile);
            return(3);
        }        
    }
#endif

    free(pFpgaFile);

 
    for(i = 0; i <100; i++)
    {
        GpioValSet_ALTERA(FPGA_CLK_ALTERA , 0 );
	 mydelay();
        GpioValSet_ALTERA(FPGA_CLK_ALTERA , 1 );
	 mydelay();
    }
	
}
    /*检测DONE信号是否变为1*/

    count = 0;
    while(0 == GpioValGet_ALTERA(FPGA_DONE_ALTERA))
    {
        taskDelay(10) ;
        count++ ;
        if( 10 == count)
        {
            printf("\n  FPGA DONE Signal Error \n") ; 
            return (2);
        }
    }

    /* 复位FPGA*/
    ResetFpga_ALTERA();
	
    printf("\nLoad FPGA OK\n");
    return (0);
}


/****************************************************以下为LATICE 加载代码***************************************************************/

/*获得某个管脚的电平值*/
/*
输入:MPP pin number
返回:获得的这个管脚的电平值0或者1
*/
LOCAL BYTE GpioValGet_LATTICE(BYTE pinNum)
{
       return  BSP_AT91F_OR_PIO_GetInput(BSP_PIOB,pinNum);
}

/*把某个管脚设置为高或低电平
输入参数:pinNum  MPP pin number   
         state      电平状态
*/

LOCAL VOID GpioValSet_LATTICE(BYTE pinNum,BYTE state)
{
    if (state == 1)
    {
        
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,pinNum);
    }
    else
    {
        
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,pinNum);
    }
    
}


/*****************************************************************
功能:对FPGA芯片进行复位
输入:无
输出:无
返回:无
说明:CPLD里有对FPGA的复位
 *****************************************************************/

VOID ResetFpga_LATTICE()
{
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_PROG_LATTICE);
        taskDelay(2);
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_PROG_LATTICE);
}


/*****************************************************************
功能:把配置FPGA用到的5个信号线进行初始化
输入:无
输出:无
返回:无
硬件介绍:
GPIO0	FPGA_DIN			FPGA 加载
GPIO1	FPGA_DONE
GPIO2	FPGA_CLK
GPIO3	FPGA_INIT
 *****************************************************************/
LOCAL VOID InitFpgaPin_LATTICE()
{
    DWORD reg;
    /*对G4的5个IO脚进行初始化*/	
    /*把FPGA_DIN和FPGA_CCLK 和FPGA_PROG设置输出*/
    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_DIN_LATTICE);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_CLK_LATTICE);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_PROG_LATTICE);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_BUS_ENABLE); 
    /*把FPGA_INIT和FPGA_DONE设置输入*/
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_LATTICE);
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_INIT_LATTICE);
    /*输出脚初始值置为0*/
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_BUS_ENABLE);
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_PROG_LATTICE);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_DIN_LATTICE);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_CLK_LATTICE);
    mydelay();

}
/*****************************************************************
功能:设置FPGA的FPGA_CFG管脚的电平
输入:电平状态0或者1
输出:无
返回:无
说明:FPGA的CFG来自CPLD PIN14
 *****************************************************************/
LOCAL VOID SetCfgPin_LATTICE(SDWORD status)
{
    if(0 == status)
    {
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_PROG_LATTICE);
    }
    else if(1 == status)
    {
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_PROG_LATTICE);
    }
    
}

/*****************************************************************
功能:控制CFG脚，发起初始化操作
输入:无
输出:无
返回:无
 *****************************************************************/
LOCAL VOID StartDownLoadFpga_LATTICE()
{
    SetCfgPin_LATTICE(0);
    taskDelay(1);
    SetCfgPin_LATTICE(1);
}
#if 1
/******************************************************************************
* 函数名称: ftpDownload
* 函数功能: 通过FTP从PC机下载文件到指定的地址
                        
* 创建日期: 2003-04-25
* 作    者: 邱文
* 输入参数: 
            CHAR *fileName: 要下载的文件名
            CHAR *TEMPBUFFER: 存放在系统内存的起始地址
* 输出参数: 无
* 返    回: fileLength(文件长度)，失败返回0
* 被调函数：ftpXfer() and ftpCommand()
* 调用函数：bsp_menu_ftpDownload()
*******************************************************************************/
LOCAL DWORD ftpDownload_LATTICE
(
BYTE *fileName,
BYTE *TEMPBUFFER
)
{
    BOOT_PARAMS  params;
    int dataSock;
    int ctrlSock;
    CHAR buf[1024];
    SDWORD nBytes;
    DWORD fileLength = 0;
    SDWORD status;
     
    BYTE *tempBuffer = TEMPBUFFER;

    if ( ( NULL == fileName ) || ( NULL == tempBuffer ) )
    {
        return 0; 
    }
    
    if (usrBootLineCrack (BOOT_LINE_ADRS, &params) != OK)
    {
        printf("根启动参数无效  \n");
        return (0);
    }
 
    if (ftpXfer (params.had, params.usr, params.passwd, "", "RETR %s", "",fileName,
                 &ctrlSock, &dataSock) == ERROR)
    {
        printf("下载文件 \"%s\" 出错 \n", fileName);
        return (0);
    }
  
    while ((nBytes = read (dataSock, buf, sizeof (buf))) > 0)
    {
         
        memcpy (tempBuffer, buf, nBytes);
        fileLength += nBytes;
        tempBuffer += nBytes;

    }
    /*   BSP_MENU_PRINT("     拷贝到缓冲区成功\n");*/

      close (dataSock);
    /*   BSP_MENU_PRINT("     关闭文件成功\n");*/
    if (fileLength > 0)
    {   
        status = OK;
        if (ftpCommand (ctrlSock, "QUIT", 0, 0, 0, 0, 0, 0) != FTP_COMPLETE)
             status = ERROR;
        close (ctrlSock);

        /*printf("\r\nFTP下载成功, 文件长度为 %d",fileLength);*/
        return fileLength;

    }
    else
    {    
        #if 0
        if (nBytes < 0)             /* read error? */
            status = 0;

        if (ftpReplyGet (ctrlSock, TRUE) != FTP_COMPLETE)
            status = 0;
        
        #endif
        if (ftpCommand (ctrlSock, "QUIT", 0, 0, 0, 0, 0, 0) != FTP_COMPLETE)
        {
            status = 0;
        }
        close (ctrlSock);
        printf("FTP下载失败\n");
        return 0;
    }
}

#endif

/*############################################################
*加载fpga
return: OK  
           ERROR
*/
SDWORD load_fpga_LATTICE(DWORD  fileno)
{
	CHAR filename[4][80]={"host:./hdlogic1.bit","host:./hdlogic2.bit","host:./hdlogic3.bit","host:./hdlogic4.bit"};

    BSP_TimeGet(&OldHi, &OldLo);
    LoadFpga_LATTICE(filename,fileno);
	BSP_TimeGet(&NewHi, &NewLo);
	OldLo = (OldLo&0x0000ffff) | (OldHi&0x0000ffff)<<16;
	NewLo = (NewLo&0x0000ffff) | (NewHi&0x0000ffff)<<16;
	TBmp = (NewLo - OldLo);
	TBmp = TBmp*1000>>15;
    printf("load_fpga_LATTICE Total time %dms\n", TBmp);	
	return 0;
	
}


/*****************************************************************
功能:从CF卡读取FPGA代码，然后加载到FPGA芯片中
输入:无
输出:无
返回:0         成功
            其他失败
 *****************************************************************/
SDWORD LoadFpga_LATTICE(CHAR filename[4][80],DWORD  fileno)
{

    BYTE *data  = NULL;
    DWORD bytes ;
    BYTE *bootrom_p1 ;
    FILE *bootrom_fd ;
    BYTE  *pFpgaFile = NULL;
    BYTE  dataTemp;
    DWORD  i = 0;
    DWORD  j = 0;
    DWORD  count = 0 ;
    DWORD  ulFileLength = 0;
	DWORD  tempfileno = 0;
	

    InitFpgaPin_LATTICE();
    StartDownLoadFpga_LATTICE();

    /*检测FPGA_INIT信号，如果变为1
    表示已经对FPGA里的memory清除完毕*/
    while(0 == GpioValGet_LATTICE(FPGA_INIT_LATTICE))
    {
        taskDelay(2) ;
        count++ ;
        if( 10 == count)
        {
            printf("\r\n  FPGA INIT Signal error") ; 
            return (2);
        }
    }

for(tempfileno=0;tempfileno<fileno;tempfileno++)
{
	
    pFpgaFile = (BYTE*)malloc(FPGA_FILE_MAX_LENGTH);
    if(NULL == pFpgaFile)
    {

        printf( "\nERROR: NO memory!\n" ) ;
        return (1);
    }

   bootrom_p1 = pFpgaFile ;
   
    if((bootrom_fd = fopen( filename[tempfileno], "rb" )) == NULL )
    {
        printf( "\nERROR: can not open file %s\n",filename ) ;
        free( pFpgaFile ) ;
        return (1);
    }

    bytes = 0 ;
    printf( "read FPGA file\n" ) ;
#if 0
    while( fscanf( bootrom_fd, "%c", &dataTemp ) != EOF )
    {
        *bootrom_p1++ = dataTemp ;
        bytes = bytes + 1 ;
        if( bytes >= FPGA_FILE_MAX_LENGTH )
        break ;
    } 
#else
	fseek(bootrom_fd, 0, SEEK_END);
	bytes = ftell(bootrom_fd);
	fseek(bootrom_fd, 0, SEEK_SET);
    if(bytes <= FPGA_FILE_MAX_LENGTH)
	    fread(pFpgaFile, 1, bytes, bootrom_fd);
#endif
    fclose( bootrom_fd ) ;

    if( bytes > FPGA_FILE_MAX_LENGTH )
    {
        printf( "ERROR: bootrom file is too long!\n" ) ;
        return (1);
    }
	
	printf( "File %08x\n" ,bytes) ;
	ulFileLength=bytes;
    /*把文件存入到申请的内存块中*/
    /*ulFileLength = ftpDownload("nsp2000.bin", pFpgaFile);   */


    data = pFpgaFile;



	/* 启始点*/
    /*开始加载*/
#if 0    
    for(i = 0; i<ulFileLength; i++, data++)
    {
        for( j=0; j<8; j++)
        {    
            /*置FPGA_CLK为0*/
            GpioValSet_ALTERA(FPGA_CLK_LATTICE, 0);    
			
	     /*一个字节的最高bit先打入FPGA，
	     送到DIN脚上，在CLK上升沿打入*/
			 if(((*data) << j) & 0x80 )
			 /*if(((*data) >> j) & 0x01 )*/
            {
                GpioValSet_ALTERA(FPGA_DIN_LATTICE, 1);   
            }
            else 
            {
                GpioValSet_ALTERA(FPGA_DIN_LATTICE, 0);   
	     }
			
        mydelay();
            /*置FPGA_CLK为1，因为上升沿把DIN
            上的电平值打入FPGA，此时打入*/	
            GpioValSet_ALTERA(FPGA_CLK_LATTICE, 1);    
        mydelay();
        }
          
        if(0 == GpioValGet_ALTERA(FPGA_INIT_LATTICE))
        {
            printf( "FPGA_INIT_LATTICE!\n" ) ;
	    	free(pFpgaFile);
            return(3);
        }        
    }	
#else
    for(i = 0; i<ulFileLength; i++)
    {
        register DWORD dwTempValue;
        register BYTE val;
        val = *data++;
        dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;
        for( j=0; j<8; j++)
        {            
            if((val << j) & 0x80)
            {
                /*置FPGA_CLK为0*/
                /*GpioValSet_ALTERA(FPGA_CLK_LATTICE, 0);*/    
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_LATTICE_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;
                /*一个字节的最高bit先打入FPGA，
                送到DIN脚上，在CLK上升沿打入*/
                /*置FPGA_LATTICE_DIN为1*/
                /*GpioValSet_ALTERA(FPGA_DIN_LATTICE, 1); */  
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_LATTICE_DIN;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;

                mydelay();
                /*置FPGA_CLK为1，因为上升沿把DIN
                上的电平值打入FPGA，此时打入*/	
                /*GpioValSet_ALTERA(FPGA_CLK_LATTICE, 1); */   
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = dwTempValue | FPGA_LATTICE_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
                mydelay();
            }
            else
            {
                /*置FPGA_CLK为0*/
                /*GpioValSet_ALTERA(FPGA_CLK_LATTICE, 0);*/    
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_LATTICE_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;
        	     /*一个字节的最高bit先打入FPGA，
        	     送到DIN脚上，在CLK上升沿打入*/
                /*置FPGA_LATTICE_DIN为0*/
                /*GpioValSet_ALTERA(FPGA_DIN_LATTICE, 0); */  
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = dwTempValue | FPGA_LATTICE_DIN;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;	
			
                mydelay();
                /*置FPGA_CLK为1，因为上升沿把DIN
                上的电平值打入FPGA，此时打入*/	
                /*GpioValSet_ALTERA(FPGA_CLK_LATTICE, 1); */   
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_LATTICE_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
                mydelay();
            }
        }
          
        dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_PDSR;
      	dwTempValue =  dwTempValue & FPGA_LATTICE_INIT;
        if(0 == dwTempValue)
        {
            printf( "FPGA_INIT_LATTICE!\n" ) ;
	        free(pFpgaFile);
            return(3);
        }        
    }
#endif

	free(pFpgaFile);


	for(i = 0; i <100; i++)
	{
		GpioValSet_ALTERA(FPGA_CLK_LATTICE , 0 );
		mydelay();
		GpioValSet_ALTERA(FPGA_CLK_LATTICE , 1 );
		mydelay();
	}
        printf( "\nfile %d done!\n",tempfileno) ;

}
	/* 终止点*/
	
    /*检测DONE信号是否变为1*/
    count = 0;
    while(0 == GpioValGet_ALTERA(FPGA_DONE_LATTICE))
    {
        taskDelay(10) ;
        count++ ;
        if( 10 == count)
        {
            printf("\n  FPGA DONE Signal Error \n ") ; 
            return (2);
        }
    }

    /* 复位FPGA*/
    ResetFpga_ALTERA();
	
    printf("\nLoad FPGA OK\n");
    return (0);
}

LOCAL VOID mydelay()
{
/*
	volatile DWORD x=0;
	DWORD val=10;
	for(x=0;x<val;x++);
*/
}

OpenBus()
{
	
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_BUS_ENABLE); 
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_BUS_ENABLE);    
}


CloseBus()
{
	
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_BUS_ENABLE); 
	BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_BUS_ENABLE);
}



/*
#define	FPGA_DIN_ALTERA             26    PB26  
#define	FPGA_DONE_ALTERA          	29    PB29
#define	FPGA_CLK_ALTERA             28    PB28
#define	FPGA_INIT_ALTERA            24    PB24
#define	FPGA_PROG_ALTERA          	25    PB25

*/
VOID testio(BYTE Abcd,BYTE pin,BYTE state)
{

	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_DIN_ALTERA);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_CLK_ALTERA);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_PROG_ALTERA);    
    /*把FPGA_INIT和FPGA_DONE设置输入*/
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_ALTERA);
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOC,FPGA_INIT_ALTERA);
	if(state==1)
	{
		switch (Abcd)
			{
				case 1:;
					BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,pin);
					break;
				case 2:;
					BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,pin);
					break;
				case 3:;
					BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,pin);
					break;
				case 4:;
					BSP_AT91F_OR_PIO_SetOutput(BSP_PIOD,pin);
					break;
			}
	}
	else
	{
		switch (Abcd)
			{

				case 1:;
				BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,pin);
				break;
				case 2:;
				BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,pin);
				break;
				case 3:;
				BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,pin);
				break;
				case 4:;
				BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOD,pin);
				break;

			}
	}
}
SDWORD testioRd(BYTE pin)
{

	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_DIN_ALTERA);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_CLK_ALTERA);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_PROG_ALTERA);    

	/*把FPGA_INIT和FPGA_DONE设置输入*/
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_ALTERA);
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_INIT_ALTERA);
	
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_LATTICE);
	
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,23);
	return	GpioValGet_ALTERA(pin);
}


/*****************************BSP代码*********************************************************/



/*****************************************************************
功能:从CF卡读取FPGA代码，然后加载到FPGA芯片中
输入:无
输出:无
返回:0         成功
            其他失败
 *****************************************************************/
#if 0
SDWORD BSP_LoadFpga_ALTERA(DWORD  fileno)
{

    BYTE *data  = NULL;
    DWORD bytes ;
    BYTE *bootrom_p1 ;
    FILE *bootrom_fd ;
    BYTE  *pFpgaFile = NULL;
    BYTE  dataTemp;
    DWORD  i = 0;
    DWORD  j = 0;
    DWORD  count = 0 ;
    DWORD  ulFileLength = 0;
	DWORD  tempfileno = 0;
	

    InitFpgaPin_ALTERA();
    StartDownLoadFpga_ALTERA();

    /*检测FPGA_INIT信号，如果变为1
    表示已经对FPGA里的memory清除完毕*/
    while(0 == GpioValGet_ALTERA(FPGA_INIT_ALTERA))
    {
        taskDelay(2) ;
        count++ ;
        if( 10 == count)
        {
            printf("\r\n  FPGA INIT Signal error !!") ; 
            return (2);
        }
    }

for(tempfileno=0;tempfileno<fileno;tempfileno++)
{
	
    pFpgaFile = (BYTE*)malloc(FPGA_FILE_MAX_LENGTH);
	
    if(NULL == pFpgaFile)
    {

        printf( "\nERROR: NO memory!\n" ) ;
		return (1);
    }
	if(0==tempfileno)
		{
			if (OK!=BSPGetSoft(BSP_MAINLOGSOFT3,pFpgaFile,&bytes))
				{
					if (OK!=BSPGetSoft(BSP_BACKLOGSOFT3,pFpgaFile,&bytes))
					{
						free(pFpgaFile);
						return (5);
					}
				}
		}
	if(1==tempfileno)
		{
			if (OK!=BSPGetSoft(BSP_MAINLOGSOFT4,pFpgaFile,&bytes))
				{
					if (OK!=BSPGetSoft(BSP_BACKLOGSOFT4,pFpgaFile,&bytes))
					{
						free(pFpgaFile);
						return (5);
					}
				}
		}
	if(tempfileno>1)
		{
		
	    free(pFpgaFile);
		return (4);
		}

    if( bytes > FPGA_FILE_MAX_LENGTH )
    {
        printf( "ERROR: bootrom file is too long!\n" ) ;
	    free(pFpgaFile);
        return (1);
    }
	
	printf( "File %08x\n" ,bytes) ;
	ulFileLength=bytes;
    /*把文件存入到申请的内存块中*/
    /*ulFileLength = ftpDownload("nsp2000.bin", pFpgaFile);   */


    data = pFpgaFile;

	

	/* 启始点*/
    /*开始加载*/	
    for(i = 0; i<ulFileLength; i++, data++)
    {
        for( j=0; j<8; j++)
        {    
            /*置FPGA_CLK为0*/
            GpioValSet_ALTERA(FPGA_CLK_ALTERA, 0);    
			
	     /*一个字节的最高bit先打入FPGA，
	     送到DIN脚上，在CLK上升沿打入*/
            /*if(((*data) << j) & 0x80 )*/
            if(((*data) >> j) & 0x01 )
            {
                GpioValSet_ALTERA(FPGA_DIN_ALTERA, 1);   
            }
            else 
            {
                GpioValSet_ALTERA(FPGA_DIN_ALTERA, 0);   
	     }
			
        mydelay();
            /*置FPGA_CLK为1，因为上升沿把DIN
            上的电平值打入FPGA，此时打入*/	
            GpioValSet_ALTERA(FPGA_CLK_ALTERA, 1);    
        mydelay();
        }
          
        if(0 == GpioValGet_ALTERA(FPGA_INIT_ALTERA))
        {
            free(pFpgaFile);
            printf("\r\n  FPGA_INIT_ALTERA in middle!\n") ; 
			
			free(pFpgaFile);
            return(3);
        }        
    }	


    free(pFpgaFile);

 
    for(i = 0; i <100; i++)
    {
        GpioValSet_ALTERA(FPGA_CLK_ALTERA , 0 );
	 	mydelay();
        GpioValSet_ALTERA(FPGA_CLK_ALTERA , 1 );
	 	mydelay();
    }
	
}
    /*检测DONE信号是否变为1*/

    count = 0;
    while(0 == GpioValGet_ALTERA(FPGA_DONE_ALTERA))
    {
        taskDelay(10) ;
        count++ ;
        if( 10 == count)
        {
            printf("\n  FPGA DONE Signal Error \n") ; 
            return (2);
        }
    }

    /* 复位FPGA*/
    ResetFpga_ALTERA();
	
    printf("\nLoad FPGA OK\n");
    return (0);
}
#else
SDWORD BSP_LoadFpga_ALTERA(DWORD  fileno)
{

    BYTE *data  = NULL;
    DWORD bytes ;
    BYTE *bootrom_p1 ;
    FILE *bootrom_fd ;
    BYTE  *pFpgaFile = NULL;
    BYTE  dataTemp;
    DWORD  i = 0;
    DWORD  j = 0;
    DWORD  count = 0 ;
    DWORD  ulFileLength = 0;
	DWORD  tempfileno = 0;
	

    InitFpgaPin_ALTERA();
    StartDownLoadFpga_ALTERA();

    /*检测FPGA_INIT信号，如果变为1
    表示已经对FPGA里的memory清除完毕*/
    while(0 == GpioValGet_ALTERA(FPGA_INIT_ALTERA))
    {
        taskDelay(2) ;
        count++ ;
        if( 10 == count)
        {
            printf("\r\n  FPGA INIT Signal error !!") ; 
            return (2);
        }
    }

for(tempfileno=0;tempfileno<fileno;tempfileno++)
{
	
    pFpgaFile = (BYTE*)malloc(FPGA_FILE_MAX_LENGTH);
	
    if(NULL == pFpgaFile)
    {

        printf( "\nERROR: NO memory!\n" ) ;
		return (1);
    }
	if(0==tempfileno)
		{
			if (OK!=BSPGetSoft(BSP_MAINLOGSOFT3,pFpgaFile,&bytes))
				{
					if (OK!=BSPGetSoft(BSP_BACKLOGSOFT3,pFpgaFile,&bytes))
					{
						free(pFpgaFile);
						return (5);
					}
				}
		}
	if(1==tempfileno)
		{
			if (OK!=BSPGetSoft(BSP_MAINLOGSOFT4,pFpgaFile,&bytes))
				{
					if (OK!=BSPGetSoft(BSP_BACKLOGSOFT4,pFpgaFile,&bytes))
					{
						free(pFpgaFile);
						return (5);
					}
				}
		}
	if(tempfileno>1)
		{
		
	    free(pFpgaFile);
		return (4);
		}

    if( bytes > FPGA_FILE_MAX_LENGTH )
    {
        printf( "ERROR: bootrom file is too long!\n" ) ;
	    free(pFpgaFile);
        return (1);
    }
	
	printf( "File %08x\n" ,bytes) ;
	ulFileLength=bytes;
    /*把文件存入到申请的内存块中*/
    /*ulFileLength = ftpDownload("nsp2000.bin", pFpgaFile);   */


    data = pFpgaFile;

	

	/* 启始点*/
    /*开始加载*/	
    for(i = 0; i<ulFileLength; i++)
    {
        register DWORD dwTempValue;
        register BYTE val;
        val = *data++;
        dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;
        for( j=0; j<8; j++)
        {    
            if((val >> j) & 0x01)
            {
                /*置FPGA_CLK为0*/            
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_ALTERA_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;

        	    /*一个字节的最高bit先打入FPGA，
        	    送到DIN脚上，在CLK上升沿打入*/
                /*置FPGA_ALTERA_DIN为1*/
                /*GpioValSet_ALTERA(FPGA_DIN_ALTERA, 1);*/
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_ALTERA_DIN;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
    			
                //mydelay();
                /*置FPGA_CLK为1，因为上升沿把DIN
                上的电平值打入FPGA，此时打入*/	
                /*GpioValSet_ALTERA(FPGA_CLK_ALTERA, 1); */
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = dwTempValue | FPGA_ALTERA_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
                //mydelay();
            }
            else
            {
                /*置FPGA_CLK为0*/            
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_ALTERA_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;

        	    /*一个字节的最高bit先打入FPGA，
        	    送到DIN脚上，在CLK上升沿打入*/
                /*置FPGA_ALTERA_DIN为0*/
                /*GpioValSet_ALTERA(FPGA_DIN_ALTERA, 0);*/
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = dwTempValue | FPGA_ALTERA_DIN;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;
    			
                //mydelay();
                /*置FPGA_CLK为1，因为上升沿把DIN
                上的电平值打入FPGA，此时打入*/	
                /*GpioValSet_ALTERA(FPGA_CLK_ALTERA, 1); */
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_ALTERA_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
                //mydelay();
            }
        }
          
        dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_PDSR;
      	dwTempValue =  dwTempValue & FPGA_ALTERA_INIT;
        if(0 == dwTempValue)
        {
            free(pFpgaFile);
            printf("\r\n  FPGA_INIT_ALTERA in middle!\n") ; 
			
            return(3);
        }        
    }	


    free(pFpgaFile);

 
    for(i = 0; i <100; i++)
    {
        GpioValSet_ALTERA(FPGA_CLK_ALTERA , 0 );
	 	mydelay();
        GpioValSet_ALTERA(FPGA_CLK_ALTERA , 1 );
	 	mydelay();
    }
	
}
    /*检测DONE信号是否变为1*/

    count = 0;
    while(0 == GpioValGet_ALTERA(FPGA_DONE_ALTERA))
    {
        taskDelay(10) ;
        count++ ;
        if( 10 == count)
        {
            printf("\n  FPGA DONE Signal Error \n") ; 
            return (2);
        }
    }

    /* 复位FPGA*/
    ResetFpga_ALTERA();
	
    printf("\nLoad FPGA OK\n");
    return (0);
}
#endif



/*****************************************************************
功能:从CF卡读取FPGA代码，然后加载到FPGA芯片中
输入:无
输出:无
返回:0         成功
            其他失败
 *****************************************************************/
#if 0
SDWORD BSP_LoadFpga_LATTICE(DWORD  fileno)
{

    BYTE *data  = NULL;
    DWORD bytes ;
    BYTE *bootrom_p1 ;
    FILE *bootrom_fd ;
    BYTE  *pFpgaFile = NULL;
    BYTE  dataTemp;
    DWORD  i = 0;
    DWORD  j = 0;
    DWORD  count = 0 ;
    DWORD  ulFileLength = 0;
	DWORD  tempfileno = 0;
	

    InitFpgaPin_LATTICE();
    StartDownLoadFpga_LATTICE();

    /*检测FPGA_INIT信号，如果变为1
    表示已经对FPGA里的memory清除完毕*/
    while(0 == GpioValGet_LATTICE(FPGA_INIT_LATTICE))
    {
        taskDelay(2) ;
        count++ ;
        if( 10 == count)
        {
            printf("\r\n  FPGA INIT Signal error") ; 
            return (2);
        }
    }

for(tempfileno=0;tempfileno<fileno;tempfileno++)
{
	
	
    pFpgaFile = (BYTE*)malloc(FPGA_FILE_MAX_LENGTH);
	
    if(NULL == pFpgaFile)
    {

        printf( "\nERROR: NO memory!\n" ) ;
        return (1);
    }
	if(fileno-tempfileno >1)
		{
			if (OK!=BSPGetSoft(BSP_MAINLOGSOFT1,pFpgaFile,&bytes))
				{
					if (OK!=BSPGetSoft(BSP_BACKLOGSOFT1,pFpgaFile,&bytes))
					{
						free(pFpgaFile);
						return (5);
					}
				}
		}
	if(1==fileno-tempfileno)
		{
			if (OK!=BSPGetSoft(BSP_MAINLOGSOFT2,pFpgaFile,&bytes))
				{
					
					if (OK!=BSPGetSoft(BSP_BACKLOGSOFT2,pFpgaFile,&bytes))
					{
						free(pFpgaFile);
						return (5);
					}
				}
		}
	if(tempfileno>2)
		{
		
	    free(pFpgaFile);
		return (4);
		}

    if( bytes > FPGA_FILE_MAX_LENGTH )
    {
        printf( "ERROR: bootrom file is too long!\n" ) ;
		
	    free(pFpgaFile);
        return (1);
    }

	ulFileLength=bytes;
    /*把文件存入到申请的内存块中*/
    /*ulFileLength = ftpDownload("nsp2000.bin", pFpgaFile);   */


    data = pFpgaFile;



	/* 启始点*/
    /*开始加载*/	
    for(i = 0; i<ulFileLength; i++, data++)
    {
        for( j=0; j<8; j++)
        {    
            /*置FPGA_CLK为0*/
            GpioValSet_ALTERA(FPGA_CLK_LATTICE, 0);    
			
	     /*一个字节的最高bit先打入FPGA，
	     送到DIN脚上，在CLK上升沿打入*/
			 if(((*data) << j) & 0x80 )
			 /*if(((*data) >> j) & 0x01 )*/
            {
                GpioValSet_ALTERA(FPGA_DIN_LATTICE, 1);   
            }
            else 
            {
                GpioValSet_ALTERA(FPGA_DIN_LATTICE, 0);   
	     }
			
        mydelay();
            /*置FPGA_CLK为1，因为上升沿把DIN
            上的电平值打入FPGA，此时打入*/	
            GpioValSet_ALTERA(FPGA_CLK_LATTICE, 1);    
        mydelay();
        }
          
        if(0 == GpioValGet_ALTERA(FPGA_INIT_LATTICE))
        {
            printf( "FPGA_INIT_LATTICE!\n" ) ;
	    free(pFpgaFile);
            return(3);
        }        
    }	


	free(pFpgaFile);


	for(i = 0; i <100; i++)
	{
		GpioValSet_ALTERA(FPGA_CLK_LATTICE , 0 );
		mydelay();
		GpioValSet_ALTERA(FPGA_CLK_LATTICE , 1 );
		mydelay();
	}
        printf( "\nfile %d done!\n",tempfileno) ;

}
	/* 终止点*/
	
    /*检测DONE信号是否变为1*/
    count = 0;
    while(0 == GpioValGet_ALTERA(FPGA_DONE_LATTICE))
    {
        taskDelay(10) ;
        count++ ;
        if( 10 == count)
        {
            printf("\n  FPGA DONE Signal Error \n ") ; 
            return (2);
        }
    }

    /* 复位FPGA*/
    ResetFpga_ALTERA();
	
    printf("\nLoad FPGA OK\n");
    return (0);
}
#else
SDWORD BSP_LoadFpga_LATTICE(DWORD  fileno)
{

    BYTE *data  = NULL;
    DWORD bytes ;
    BYTE *bootrom_p1 ;
    FILE *bootrom_fd ;
    BYTE  *pFpgaFile = NULL;
    BYTE  dataTemp;
    DWORD  i = 0;
    DWORD  j = 0;
    DWORD  count = 0 ;
    DWORD  ulFileLength = 0;
	DWORD  tempfileno = 0;
	

    InitFpgaPin_LATTICE();
    StartDownLoadFpga_LATTICE();

    /*检测FPGA_INIT信号，如果变为1
    表示已经对FPGA里的memory清除完毕*/
    while(0 == GpioValGet_LATTICE(FPGA_INIT_LATTICE))
    {
        taskDelay(2) ;
        count++ ;
        if( 10 == count)
        {
            printf("\r\n  FPGA INIT Signal error") ; 
            return (2);
        }
    }

for(tempfileno=0;tempfileno<fileno;tempfileno++)
{
	
	
    pFpgaFile = (BYTE*)malloc(FPGA_FILE_MAX_LENGTH);
	
    if(NULL == pFpgaFile)
    {

        printf( "\nERROR: NO memory!\n" ) ;
        return (1);
    }
	if(fileno-tempfileno >1)
		{
			if (OK!=BSPGetSoft(BSP_MAINLOGSOFT1,pFpgaFile,&bytes))
				{
					if (OK!=BSPGetSoft(BSP_BACKLOGSOFT1,pFpgaFile,&bytes))
					{
						free(pFpgaFile);
						return (5);
					}
				}
		}
	if(1==fileno-tempfileno)
		{
			if (OK!=BSPGetSoft(BSP_MAINLOGSOFT2,pFpgaFile,&bytes))
				{
					
					if (OK!=BSPGetSoft(BSP_BACKLOGSOFT2,pFpgaFile,&bytes))
					{
						free(pFpgaFile);
						return (5);
					}
				}
		}
	if(tempfileno>2)
		{
		
	    free(pFpgaFile);
		return (4);
		}

    if( bytes > FPGA_FILE_MAX_LENGTH )
    {
        printf( "ERROR: bootrom file is too long!\n" ) ;
		
	    free(pFpgaFile);
        return (1);
    }

	ulFileLength=bytes;
    /*把文件存入到申请的内存块中*/
    /*ulFileLength = ftpDownload("nsp2000.bin", pFpgaFile);   */


    data = pFpgaFile;



	/* 启始点*/
    /*开始加载*/	
    for(i = 0; i<ulFileLength; i++)
    {
        register DWORD dwTempValue;
        register BYTE val;
        val = *data++;
        dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;
        for( j=0; j<8; j++)
        {            
            if((val << j) & 0x80)
            {
                /*置FPGA_CLK为0*/
                /*GpioValSet_ALTERA(FPGA_CLK_LATTICE, 0);*/    
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_LATTICE_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;
                /*一个字节的最高bit先打入FPGA，
                送到DIN脚上，在CLK上升沿打入*/
                /*置FPGA_LATTICE_DIN为1*/
                /*GpioValSet_ALTERA(FPGA_DIN_LATTICE, 1); */  
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_LATTICE_DIN;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;

                //mydelay();
                /*置FPGA_CLK为1，因为上升沿把DIN
                上的电平值打入FPGA，此时打入*/	
                /*GpioValSet_ALTERA(FPGA_CLK_LATTICE, 1); */   
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = dwTempValue | FPGA_LATTICE_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
                //mydelay();
            }
            else
            {
                /*置FPGA_CLK为0*/
                /*GpioValSet_ALTERA(FPGA_CLK_LATTICE, 0);*/    
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_LATTICE_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;
        	     /*一个字节的最高bit先打入FPGA，
        	     送到DIN脚上，在CLK上升沿打入*/
                /*置FPGA_LATTICE_DIN为0*/
                /*GpioValSet_ALTERA(FPGA_DIN_LATTICE, 0); */  
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = dwTempValue | FPGA_LATTICE_DIN;
                ((AT91PS_PIO)BSP_PIOB)->PIO_CODR = dwTempValue;	
			
                //mydelay();
                /*置FPGA_CLK为1，因为上升沿把DIN
                上的电平值打入FPGA，此时打入*/	
                /*GpioValSet_ALTERA(FPGA_CLK_LATTICE, 1); */   
                /*dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_ODSR;*/
                dwTempValue = ~dwTempValue | FPGA_LATTICE_CLK;
                ((AT91PS_PIO)BSP_PIOB)->PIO_SODR = dwTempValue;
                //mydelay();
            }
        }
          
        dwTempValue = ((AT91PS_PIO)BSP_PIOB)->PIO_PDSR;
      	dwTempValue =  dwTempValue & FPGA_LATTICE_INIT;
        if(0 == dwTempValue)
        {
            printf( "FPGA_INIT_LATTICE!\n" ) ;
	        free(pFpgaFile);
            return(3);
        }        
    }


	free(pFpgaFile);


	for(i = 0; i <100; i++)
	{
		GpioValSet_ALTERA(FPGA_CLK_LATTICE , 0 );
		mydelay();
		GpioValSet_ALTERA(FPGA_CLK_LATTICE , 1 );
		mydelay();
	}
        printf( "\nfile %d done!\n",tempfileno) ;

}
	/* 终止点*/
	
    /*检测DONE信号是否变为1*/
    count = 0;
    while(0 == GpioValGet_ALTERA(FPGA_DONE_LATTICE))
    {
        taskDelay(10) ;
        count++ ;
        if( 10 == count)
        {
            printf("\n  FPGA DONE Signal Error \n ") ; 
            return (2);
        }
    }

    /* 复位FPGA*/
    ResetFpga_ALTERA();
	
    printf("\nLoad FPGA OK\n");
    return (0);
}
#endif
