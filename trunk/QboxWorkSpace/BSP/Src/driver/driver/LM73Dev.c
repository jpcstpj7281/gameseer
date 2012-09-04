/******************************************************************************

******************************************************************************/
#include <semLib.h>
#include <logLib.h>
 
#include "sys_types.h"
#include "IicDev.h"

#define LM73DEVID    0x90

/*I2C读数据
//input :  byIicPort     I2C端口号为 0 ~ 1
//         bySlave       设备号
//         dwAddr        命令地址
//output:  pbyData       命令值
//return:  SYS_OK
           SYS_ERR      
*/
SDWORD ReadLM73(DWORD dwAddr, BYTE *pbyData, BYTE byDataNum)
{
    BYTE bySlave = LM73DEVID; 
    BYTE byData  = 0;
    
    volatile BYTE i2c_bw_ctrl; /* I2C write control */
    volatile BYTE i2c_br_ctrl; /* I2C read control */
    volatile BYTE i2c_addr_00; /* I2C address (0) */

    STATUS semStatus;                           /*i2c同步信号量*/

    if ((1 > byDataNum) | (2 < byDataNum))
    {
        return SYS_ERROR;
    }
    
    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*获得信号量*/
    
    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }
    
    sCurI2cPort.byClkPin = IICCLK0;
    sCurI2cPort.byDataPin = IICDATA0;

#ifdef I2C_DEBUG    
    printf("\n i2cRead() slave address is 0x%08x, addr: 0x%08x", bySlave, dwAddr);
#endif /* I2C_DEBUG */
    i2c_ack_stat=0x0;
    i2c_bw_ctrl = bySlave | I2C_WRITE;
    i2c_br_ctrl = bySlave | I2C_READ;
    /*i2c_addr_01 = I2C_W1_ADDR(addr);*/
    i2c_addr_00 = I2C_W0_ADDR(dwAddr);

    if(1)
    {
        i2cStart();
        I2cWriteByte(i2c_bw_ctrl);
        ack1=I2cReadBit(); /*read ack from slave*/
        if(ack1!=0)
            i2c_ack_stat |= 0x1; 
        I2C_DELAY(CLOCK_LOW_TIME*3);

        I2cWriteByte(i2c_addr_00);
        ack1=I2cReadBit(); /*read ack from slave*/
        if(ack1!=0)
            i2c_ack_stat |= 0x2; 
        i2cStart();
        I2C_DELAY(CLOCK_LOW_TIME*3);
        I2cWriteByte(i2c_br_ctrl);
        ack1=I2cReadBit(); /*read ack from slave*/
        if(ack1!=0)
            i2c_ack_stat |= 0x3; 
        I2C_DELAY(CLOCK_LOW_TIME*3);
        
        while(byDataNum--)
        {
            *pbyData++ = I2cReadByte();
            if(1 == byDataNum)
                I2cWriteBit(0x0); /*send ack*/
            else
                I2cWriteBit(0x80); /*send nack after reading the last byte*/
            I2cData(HIGH);
        }

        I2cStop();
    }

#ifdef I2C_DEBUG 
    if(i2c_ack_stat!=0)
        printf("\nError in read, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);
#endif

    semGive(semI2cLock);    /*释放信号量*/

    if(0 != i2c_ack_stat)
    {
        return SYS_ERROR;
    }
    return SYS_OK;
}

/*I2C命令写
//input :  byIicPort     I2C端口号为 0 ~ 1
//         bySlave       设备号
//         dwAddr        命令地址
//         byData        命令值
//
/*return:  SYS_OK
           SYS_ERR
*/

SDWORD WriteLM73(DWORD dwAddr, BYTE *pbyData, BYTE byDataNum)
{
    BYTE bySlave = 0x90;
    volatile BYTE i2c_bw_ctrl; /* I2C write control */
    volatile BYTE i2c_addr_00; /* I2C address (0) */

    STATUS semStatus;                           /*i2c同步信号量*/

    if ((1 > byDataNum) | (2 < byDataNum))
    {
        return SYS_ERROR;
    }

    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*获得信号量*/

    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }

    sCurI2cPort.byClkPin = IICCLK0;
    sCurI2cPort.byDataPin = IICDATA0;

    i2c_ack_stat=0x0;
    i2c_bw_ctrl = bySlave | I2C_WRITE;
    /*i2c_addr_01 = I2C_W1_ADDR(dwAddr);*/
    i2c_addr_00 = I2C_W0_ADDR(dwAddr);

    if(1)
    {
        i2cStart();
        I2cWriteByte(i2c_bw_ctrl);
        ack1=I2cReadBit();
        if(ack1!=0)
            i2c_ack_stat |= 0x2;
        I2C_DELAY(CLOCK_LOW_TIME*3);
        /*I2cWriteByte(i2c_addr_01);
        ack1=I2cReadBit();
        if(ack1!=0)
            i2c_ack_stat |= 0x2;*/
        I2cWriteByte(i2c_addr_00);
        ack1=I2cReadBit();
        if(ack1!=0)
            i2c_ack_stat |= 0x2;

        I2C_DELAY(CLOCK_LOW_TIME*3);

        while(byDataNum --)
        {
            I2cWriteByte(*pbyData);
            ack2=I2cReadBit();
            if(ack2!=0)
                i2c_ack_stat |= 0x8;
            pbyData ++;
            I2C_DELAY(CLOCK_LOW_TIME*3);
        }
        
        I2cStop();
    }
    
    semGive(semI2cLock);       /*释放信号量*/

    if(0 != i2c_ack_stat)
    {
        printf("\nError in write, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);
        return SYS_ERROR;
    }
    return SYS_OK;
}

void TestLm73(void)
{
    BYTE byData[3] = {0};

    /*WriteLM73(0x02, byData, 2);*/
    byData[1] = 0;
    /*WriteLM73(0x03, 0x1, 1);*/
    ReadLM73(0x00, byData, 2);

    printf("\nbyData[0]=%d, byData[1]=%d, byData[2]=%d\n", byData[0], byData[1], byData[2]);
}
