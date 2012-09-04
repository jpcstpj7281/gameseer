/******************************************************************************


******************************************************************************/

#include "loadFPGA.h"

#define FPGA_FILE_MAX_LENGTH   0x100000

/* LATTICE ����Ӳ�����ӣ�����CPU ��IO��*/
#define	FPGA_DIN_LATTICE            21       /*PB21*/
#define	FPGA_DONE_LATTICE           11       /*PB11*/
#define	FPGA_CLK_LATTICE            22       /*PB22*/
#define	FPGA_INIT_LATTICE           23       /*PB23*/
#define	FPGA_PROG_LATTICE           20       /*PB20*/

#define FPGA_BUS_ENABLE             0		 /*PB20*/

/* ALTERA ��Ӳ�����ӣ�����CPU ��IO��*/
#define	FPGA_DIN_ALTERA             26      /*PB26*/  
#define	FPGA_DONE_ALTERA            29      /*PB29*/
#define	FPGA_CLK_ALTERA             28      /*PB28*/
#define	FPGA_INIT_ALTERA            24      /*PB24*/
#define	FPGA_PROG_ALTERA            25      /*PB25*/
/**/
#define	FPGA_RESET		            2       /*PC2*/



#define FPGA_CONFIG             0
#define FPGA_RST                2
LOCAL void mydelay(void);
int LoadFpga_ALTERA();
int LoadFpga_LATTICE();

/*���ĳ���ܽŵĵ�ƽֵ*/
/*
����:MPP pin number
����:��õ�����ܽŵĵ�ƽֵ0����1
*/
LOCAL UCHAR GpioValGet_ALTERA(UCHAR pinNum)
{
        return BSP_AT91F_OR_PIO_GetInput(BSP_PIOB,pinNum);
}

/*��ĳ���ܽ�����Ϊ�߻�͵�ƽ
�������:pinNum  MPP pin number   
         state      ��ƽ״̬
*/

LOCAL void GpioValSet_ALTERA(UCHAR pinNum,UCHAR state)
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
GPIO4	MDC					����ʼ��
GPIO5	MDIO
GPIO6	
GPIO7	
GPIO8
---------------------------------------------------------------------	
GPIO9	I2C_SDA				I2C����
GPIO10	I2C_SCL
---------------------------------------------------------------------
GPIO11	RUN_LED				LED��
GPIO12	ALAM_LED
---------------------------------------------------------------------
GPIO13	Cs8900�ж�			8900�ж�
---------------------------------------------------------------------
GPIO14	����оƬ�����ж�	����ʼ��
*/

/*****************************************************************
����:��FPGAоƬ���и�λ
����:��
���:��
����:��
˵��:CPLD���ж�FPGA�ĸ�λ
 *****************************************************************/

LOCAL void ResetFpga_ALTERA()
{
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,FPGA_RESET);
        taskDelay(2);
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,FPGA_RESET);
}


/*****************************************************************
����:������FPGA�õ���5���ź��߽��г�ʼ��
����:��
���:��
����:��
Ӳ������:
GPIO0	FPGA_DIN			FPGA ����
GPIO1	FPGA_DONE
GPIO2	FPGA_CLK
GPIO3	FPGA_INIT
 *****************************************************************/
LOCAL void InitFpgaPin_ALTERA()
{
    UINT32 reg;
    /*��G4��5��IO�Ž��г�ʼ��*/	
    /*��FPGA_DIN��FPGA_CCLK ��FPGA_PROG�������*/
    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_DIN_ALTERA);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_CLK_ALTERA);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_PROG_ALTERA);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,FPGA_RESET);    	
    /*��FPGA_INIT��FPGA_DONE��������*/
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_ALTERA);
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_INIT_ALTERA);
    /*����ų�ʼֵ��Ϊ0*/
    
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_PROG_ALTERA);

    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,FPGA_RESET);
	
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_DIN_ALTERA);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_CLK_ALTERA);
    mydelay();

}
/*****************************************************************
����:����FPGA��FPGA_CFG�ܽŵĵ�ƽ
����:��ƽ״̬0����1
���:��
����:��
˵��:FPGA��CFG����CPLD PIN14
 *****************************************************************/
LOCAL void SetCfgPin_ALTERA(int status)
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
����:����CFG�ţ������ʼ������
����:��
���:��
����:��
 *****************************************************************/
LOCAL void StartDownLoadFpga_ALTERA()
{
    SetCfgPin_ALTERA(0);
    taskDelay(1);
    SetCfgPin_ALTERA(1);
}
#if 1
/******************************************************************************
* ��������: ftpDownload
* ��������: ͨ��FTP��PC�������ļ���ָ���ĵ�ַ
                        
* ��������: 2003-04-25
* ��    ��: ����
* �������: 
            char *fileName: Ҫ���ص��ļ���
            char *TEMPBUFFER: �����ϵͳ�ڴ����ʼ��ַ
* �������: ��
* ��    ��: fileLength(�ļ�����)��ʧ�ܷ���0
* ����������ftpXfer() and ftpCommand()
* ���ú�����bsp_menu_ftpDownload()
*******************************************************************************/
LOCAL UINT32 ftpDownload_ALTERA
(
UINT8 *fileName,
UINT8 *TEMPBUFFER
)
{
    BOOT_PARAMS  params;
    int dataSock;
    int ctrlSock;
    char buf[1024];
    int nBytes;
    UINT32 fileLength = 0;
    int status;
     
    UINT8 *tempBuffer = TEMPBUFFER;

    if ( ( NULL == fileName ) || ( NULL == tempBuffer ) )
    {
        return 0; 
    }
    
    if (usrBootLineCrack (BOOT_LINE_ADRS, &params) != OK)
    {
        printf("������������Ч  \n");
        return (0);
    }
 
    if (ftpXfer (params.had, params.usr, params.passwd, "", "RETR %s", "", 
fileName,
                 &ctrlSock, &dataSock) == ERROR)
    {
        printf("�����ļ� \"%s\" ���� \n", fileName);
        return (0);
    }
  
    while ((nBytes = read (dataSock, buf, sizeof (buf))) > 0)
    {
         
        memcpy (tempBuffer, buf, nBytes);
        fileLength += nBytes;
        tempBuffer += nBytes;

    }
    /*   BSP_MENU_PRINT("     �������������ɹ�\n");*/

      close (dataSock);
    /*   BSP_MENU_PRINT("     �ر��ļ��ɹ�\n");*/
    if (fileLength > 0)
    {   
        status = OK;
        if (ftpCommand (ctrlSock, "QUIT", 0, 0, 0, 0, 0, 0) != FTP_COMPLETE)
             status = ERROR;
        close (ctrlSock);

        /*printf("\r\nFTP���سɹ�, �ļ�����Ϊ %d",fileLength);*/
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
        printf("FTP����ʧ��\n");
        return 0;
    }
}

#endif

/*############################################################
*����fpga
return: OK  
           ERROR
*/
int load_fpga_ALTERA()
{
    return LoadFpga_ALTERA();
}

/*****************************************************************
����:��CF����ȡFPGA���룬Ȼ����ص�FPGAоƬ��
����:��
���:��
����:0         �ɹ�
            ����ʧ��
 *****************************************************************/
int LoadFpga_ALTERA()
{

    UINT8 *data  = NULL;
    UINT32 bytes ;
    UINT8 *bootrom_p1 ;
    FILE *bootrom_fd ;
    UINT8  *pFpgaFile = NULL;
    UINT8  dataTemp;
    UINT32  i = 0;
    UINT32  j = 0;
    UINT32  count = 0 ;
    UINT32  ulFileLength = 0;
    /*��CF�����FPGA�ļ��������ļ�
    �ĺϷ��Ժ��ļ����Ƚ����ж�*/

    
    pFpgaFile = (UINT8*)malloc(FPGA_FILE_MAX_LENGTH);
    if(NULL == pFpgaFile)
    {
        printf( "\nERROR: no memory!\n" ) ;
        return (1);
    }

   bootrom_p1 = pFpgaFile ;
   
    if((bootrom_fd = fopen( "nsp2000.bin", "rb" )) == NULL )
    {
        printf( "\nERROR: can not open nsp2000.bin\n" ) ;
        free( pFpgaFile ) ;
        return (1);
    }

    bytes = 0 ;
    printf( "read FPGA file\n" ) ;
    taskDelay(1);
    while( fscanf( bootrom_fd, "%c", &dataTemp ) != EOF )
    {
        *bootrom_p1++ = dataTemp ;
        bytes = bytes + 1 ;
        if( bytes >= FPGA_FILE_MAX_LENGTH )
        break ;
    } 
    fclose( bootrom_fd ) ;

    if( bytes > FPGA_FILE_MAX_LENGTH )
    {
        printf( "ERROR: bootrom file is too long!\n" ) ;
        return (1);
    }
	ulFileLength=bytes;
    /*���ļ����뵽������ڴ����*/
    /*ulFileLength = ftpDownload("nsp2000.bin", pFpgaFile);   */

    InitFpgaPin_ALTERA();
    StartDownLoadFpga_ALTERA();

    /*���FPGA_INIT�źţ������Ϊ1
    ��ʾ�Ѿ���FPGA���memory������*/
    while(0 == GpioValGet_ALTERA(FPGA_INIT_ALTERA))
    {
        taskDelay(2) ;
        count++ ;
        if( 10 == count)
        {
            printf("\r\n  FPGA INIT Signal error") ; 
            free(pFpgaFile);
            return (2);
        }
    }

    data = pFpgaFile;

    taskDelay(2) ;   

    /*��ʼ����*/	
    for(i = 0; i<ulFileLength; i++, data++)
    {
        for( j=0; j<8; j++)
        {    
            /*��FPGA_CLKΪ0*/
            GpioValSet_ALTERA(FPGA_CLK_ALTERA, 0);    
			
	     /*һ���ֽڵ����bit�ȴ���FPGA��
	     �͵�DIN���ϣ���CLK�����ش���*/
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
            /*��FPGA_CLKΪ1����Ϊ�����ذ�DIN
            �ϵĵ�ƽֵ����FPGA����ʱ����*/	
            GpioValSet_ALTERA(FPGA_CLK_ALTERA, 1);    
        mydelay();
        }
          
        if(0 == GpioValGet_ALTERA(FPGA_INIT_ALTERA))
        {
            free(pFpgaFile);
            printf("\r\n  FPGA INIT Signal Error") ; 

            return(3);
        }        
    }	

    taskDelay(1);

    free(pFpgaFile);


    for(i = 0; i <100; i++)
    {
        GpioValSet_ALTERA(FPGA_CLK_ALTERA , 0 );
	 mydelay();
        GpioValSet_ALTERA(FPGA_CLK_ALTERA , 1 );
	 mydelay();
    }
	
	printf("\n  Waiting for   DONE Signal \n") ; 
    /*���DONE�ź��Ƿ��Ϊ1*/
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

    /* ��λFPGA*/
    ResetFpga_ALTERA();
	
    printf("\nLoad FPGA OK\n");
    taskDelay(10);
    return (0);
}


/****************************************************����ΪLATICE ���ش���***************************************************************/

/*���ĳ���ܽŵĵ�ƽֵ*/
/*
����:MPP pin number
����:��õ�����ܽŵĵ�ƽֵ0����1
*/
LOCAL UCHAR GpioValGet_LATTICE(UCHAR pinNum)
{
       return  BSP_AT91F_OR_PIO_GetInput(BSP_PIOB,pinNum);
}

/*��ĳ���ܽ�����Ϊ�߻�͵�ƽ
�������:pinNum  MPP pin number   
         state      ��ƽ״̬
*/

LOCAL void GpioValSet_LATTICE(UCHAR pinNum,UCHAR state)
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
����:��FPGAоƬ���и�λ
����:��
���:��
����:��
˵��:CPLD���ж�FPGA�ĸ�λ
 *****************************************************************/

LOCAL void ResetFpga_LATTICE()
{
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_PROG_LATTICE);
        taskDelay(2);
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_PROG_LATTICE);
}


/*****************************************************************
����:������FPGA�õ���5���ź��߽��г�ʼ��
����:��
���:��
����:��
Ӳ������:
GPIO0	FPGA_DIN			FPGA ����
GPIO1	FPGA_DONE
GPIO2	FPGA_CLK
GPIO3	FPGA_INIT
 *****************************************************************/
LOCAL void InitFpgaPin_LATTICE()
{
    UINT32 reg;
    /*��G4��5��IO�Ž��г�ʼ��*/	
    /*��FPGA_DIN��FPGA_CCLK ��FPGA_PROG�������*/
    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_DIN_LATTICE);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_CLK_LATTICE);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_PROG_LATTICE);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_BUS_ENABLE); 
    /*��FPGA_INIT��FPGA_DONE��������*/
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_LATTICE);
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_INIT_LATTICE);
    /*����ų�ʼֵ��Ϊ0*/
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_BUS_ENABLE);
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,FPGA_PROG_LATTICE);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_DIN_LATTICE);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,FPGA_CLK_LATTICE);
    mydelay();

}
/*****************************************************************
����:����FPGA��FPGA_CFG�ܽŵĵ�ƽ
����:��ƽ״̬0����1
���:��
����:��
˵��:FPGA��CFG����CPLD PIN14
 *****************************************************************/
LOCAL void SetCfgPin_LATTICE(int status)
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
����:����CFG�ţ������ʼ������
����:��
���:��
����:��
 *****************************************************************/
LOCAL void StartDownLoadFpga_LATTICE()
{
    SetCfgPin_LATTICE(0);
    taskDelay(1);
    SetCfgPin_LATTICE(1);
}
#if 1
/******************************************************************************
* ��������: ftpDownload
* ��������: ͨ��FTP��PC�������ļ���ָ���ĵ�ַ
                        
* ��������: 2003-04-25
* ��    ��: ����
* �������: 
            char *fileName: Ҫ���ص��ļ���
            char *TEMPBUFFER: �����ϵͳ�ڴ����ʼ��ַ
* �������: ��
* ��    ��: fileLength(�ļ�����)��ʧ�ܷ���0
* ����������ftpXfer() and ftpCommand()
* ���ú�����bsp_menu_ftpDownload()
*******************************************************************************/
LOCAL UINT32 ftpDownload_LATTICE
(
UINT8 *fileName,
UINT8 *TEMPBUFFER
)
{
    BOOT_PARAMS  params;
    int dataSock;
    int ctrlSock;
    char buf[1024];
    int nBytes;
    UINT32 fileLength = 0;
    int status;
     
    UINT8 *tempBuffer = TEMPBUFFER;

    if ( ( NULL == fileName ) || ( NULL == tempBuffer ) )
    {
        return 0; 
    }
    
    if (usrBootLineCrack (BOOT_LINE_ADRS, &params) != OK)
    {
        printf("������������Ч  \n");
        return (0);
    }
 
    if (ftpXfer (params.had, params.usr, params.passwd, "", "RETR %s", "",fileName,
                 &ctrlSock, &dataSock) == ERROR)
    {
        printf("�����ļ� \"%s\" ���� \n", fileName);
        return (0);
    }
  
    while ((nBytes = read (dataSock, buf, sizeof (buf))) > 0)
    {
         
        memcpy (tempBuffer, buf, nBytes);
        fileLength += nBytes;
        tempBuffer += nBytes;

    }
    /*   BSP_MENU_PRINT("     �������������ɹ�\n");*/

      close (dataSock);
    /*   BSP_MENU_PRINT("     �ر��ļ��ɹ�\n");*/
    if (fileLength > 0)
    {   
        status = OK;
        if (ftpCommand (ctrlSock, "QUIT", 0, 0, 0, 0, 0, 0) != FTP_COMPLETE)
             status = ERROR;
        close (ctrlSock);

        /*printf("\r\nFTP���سɹ�, �ļ�����Ϊ %d",fileLength);*/
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
        printf("FTP����ʧ��\n");
        return 0;
    }
}

#endif

/*############################################################
*����fpga
return: OK  
           ERROR
*/
int load_fpga_LATTICE(UINT32  fileno)
{
	char filename[4][80]={"hdlogic1.bit","hdlogic2.bit","hdlogic3.bit","hdlogic4.bit"};

	LoadFpga_LATTICE(filename,fileno);
	
	return 0;
	
}


/*****************************************************************
����:��CF����ȡFPGA���룬Ȼ����ص�FPGAоƬ��
����:��
���:��
����:0         �ɹ�
            ����ʧ��
 *****************************************************************/
int LoadFpga_LATTICE(char filename[4][80],UINT32  fileno)
{

    UINT8 *data  = NULL;
    UINT32 bytes ;
    UINT8 *bootrom_p1 ;
    FILE *bootrom_fd ;
    UINT8  *pFpgaFile = NULL;
    UINT8  dataTemp;
    UINT32  i = 0;
    UINT32  j = 0;
    UINT32  count = 0 ;
    UINT32  ulFileLength = 0;
	UINT32  tempfileno = 0;
	

    InitFpgaPin_LATTICE();
    StartDownLoadFpga_LATTICE();

    /*���FPGA_INIT�źţ������Ϊ1
    ��ʾ�Ѿ���FPGA���memory������*/
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
	
    pFpgaFile = (UINT8*)malloc(FPGA_FILE_MAX_LENGTH);
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

    while( fscanf( bootrom_fd, "%c", &dataTemp ) != EOF )
    {
        *bootrom_p1++ = dataTemp ;
        bytes = bytes + 1 ;
        if( bytes >= FPGA_FILE_MAX_LENGTH )
        break ;
    } 
    fclose( bootrom_fd ) ;

    if( bytes > FPGA_FILE_MAX_LENGTH )
    {
        printf( "ERROR: bootrom file is too long!\n" ) ;
        return (1);
    }
	ulFileLength=bytes;
    /*���ļ����뵽������ڴ����*/
    /*ulFileLength = ftpDownload("nsp2000.bin", pFpgaFile);   */


    data = pFpgaFile;



	/* ��ʼ��*/
    /*��ʼ����*/	
    for(i = 0; i<ulFileLength; i++, data++)
    {
        for( j=0; j<8; j++)
        {    
            /*��FPGA_CLKΪ0*/
            GpioValSet_ALTERA(FPGA_CLK_LATTICE, 0);    
			
	     /*һ���ֽڵ����bit�ȴ���FPGA��
	     �͵�DIN���ϣ���CLK�����ش���*/
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
            /*��FPGA_CLKΪ1����Ϊ�����ذ�DIN
            �ϵĵ�ƽֵ����FPGA����ʱ����*/	
            GpioValSet_ALTERA(FPGA_CLK_LATTICE, 1);    
        mydelay();
        }
          
        if(0 == GpioValGet_ALTERA(FPGA_INIT_LATTICE))
        {
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

}
	/* ��ֹ��*/
	
    /*���DONE�ź��Ƿ��Ϊ1*/
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

    /* ��λFPGA*/
    ResetFpga_ALTERA();
	
    printf("\nLoad FPGA OK\n");
    return (0);
}

LOCAL void mydelay()
{

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
#define	FPGA_DIN_ALTERA             26      PB26  
#define	FPGA_DONE_ALTERA          	29    PB29
#define	FPGA_CLK_ALTERA             28      PB28
#define	FPGA_INIT_ALTERA            24      PB24
#define	FPGA_PROG_ALTERA          	25    PB25

*/
void testio(UINT8 Abcd,UINT8 pin,UINT8 state)
{

	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_DIN_ALTERA);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_CLK_ALTERA);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_PROG_ALTERA);    
    /*��FPGA_INIT��FPGA_DONE��������*/
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
int testioRd(UINT8 pin)
{

	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_DIN_ALTERA);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_CLK_ALTERA);    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,FPGA_PROG_ALTERA);    

	/*��FPGA_INIT��FPGA_DONE��������*/
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_ALTERA);
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_INIT_ALTERA);
	
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,FPGA_DONE_LATTICE);
	
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOB,23);
	return	GpioValGet_ALTERA(pin);
}


