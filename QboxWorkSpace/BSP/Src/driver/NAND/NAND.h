/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/


#ifndef __INSCCDRIVER
#define __INSCCDRIVER




#include "muxLib.h"
#include "stdio.h"
#include "taskLib.h"
#include <bootLib.h>
#include <ftpLib.h>
#include <config.h>


#include "vxWorks.h"
#include "intLib.h"
#include "errno.h"
#include "semLib.h" 
#include "msgQLib.h"
#include "logLib.h"
#include "drivererr.h"
#include "driverdebug.h"
#include "config.h"
#include "sys_include.h"
#include "BSPinclude.h"


/*FLASH 块相关参数*/
#define NAND_PAGE_SIZE 	                    (2*1024)
#define NAND_TOTAL_PAGE_BLOCK_NO 		    (128)
#define NAND_TOTAL_BLOCK_NO                   (2*1024)
#define NAND_LARGE_SPARE_SIZE                (64)
#define NAND_BLOCK_SIZE                       (NAND_PAGE_SIZE*NAND_TOTAL_PAGE_BLOCK_NO)
/*FLASH 操作地址相关参数*/
#define NAND_CMD_ADDRESS             (0x40200000)
#define NAND_ADD_ADDRESS             (0x40400000)
#define NAND_DAT_ADDRESS             (0x40000000)
#define NAND_CMD_REGISTER            (*((volatile UINT8 *)NAND_CMD_ADDRESS))
#define NAND_ADD_REGISTER            (*((volatile UINT8 *)NAND_ADD_ADDRESS))
#define NAND_DAT_REGISTER            (*((volatile UINT8 *)NAND_DAT_ADDRESS))

#define NAND_BLOCK_ADDR_MASK0        (0x00)         /*A0-A7  */
#define NAND_BLOCK_ADDR_MASK1        (0x00)         /*A8-A11*/
#define NAND_BLOCK_ADDR_MASK2        (0x80)         /*A12-A19*/
#define NAND_BLOCK_ADDR_MASK3        (0xFF)         /*A20-A27*/
#define NAND_BLOCK_ADDR_MASK4        (0x03)         /*A28-A29*/

#define NAND_PAGE_ADDR_MASK0        (0x00 )        /*A0-A7  */
#define NAND_PAGE_ADDR_MASK1        (0x00 )        /*A8-A11*/
#define NAND_PAGE_ADDR_MASK2        (0xFF )        /*A12-A19*/
#define NAND_PAGE_ADDR_MASK3        (0xFF )        /*A20-A27*/
#define NAND_PAGE_ADDR_MASK4        (0x03 )        /*A28-A29*/

#define BSP_FLASH_BUSY				(0x5)           /*PC5*/
#define BSP_FLASH_WP				(0x4)			/*PC4*/
#define BSP_FLASH_CE				(15)



/*FLASH 命令*/
#define NAND_READ1ST            (0x00)
#define NAND_READ2ND            (0x30)
#define NAND_WRITE1ST           (0x80)
#define NAND_WRITE2ND           (0x10)
#define NAND_ERASE1ST           (0x60)
#define NAND_ERASE2ND           (0xD0)
#define NAND_RESET1ST           (0xFF)
#define NAND_STATUS1ST          (0x70)
#define NAND_FLASHID			(0x90)




#define NAND_FILE_TABLE_INIT    (0x444E414E)


/*FLASH 地址封装*/

typedef union nand_flash_add
	{
    UINT32  ulPageAddr32;
	UINT8   pbPageAddr8[4];
 	} NAND_FLASH_ADD;

/******************页结构************************/






typedef struct nand_flash_file
	{
        DWORD dwFileBlock[89];
        DWORD dwFileLength;

 	} NAND_FLASH_FILE;


typedef struct nand_flash_block_status
	{
        DWORD dwBlock[4*1024];
        DWORD dwBlockNumber;
 	} NAND_FLASH_BLOCK_STATUS;


typedef struct nand_flash_file_table
	{
        NAND_FLASH_FILE sFlashFile[200];
        NAND_FLASH_BLOCK_STATUS sGoodBlock;
        NAND_FLASH_BLOCK_STATUS sBadBlock;
        DWORD dwNandFlashFormatFlg;           /* 格式化标记"NAND" 0x444E414E*/

 	} NAND_FLASH_FILE_TABLE;


#endif /*__INSCCDRIVER*/

