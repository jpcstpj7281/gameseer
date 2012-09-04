/******************************************************************************

******************************************************************************/

#include <semLib.h>
#include <logLib.h>

#include "sys_types.h"
#include "IicDev.h"

#define I2C_DEBUG 0

SEM_ID semI2cLock=NULL;                 /*i2cͬ���ź���*/

/*��ǰI2Cͨ����*/
I2CPORT sCurI2cPort;

/*��ΪI2C״̬�ļ��*/
BYTE ack1 = 1, ack2 = 1;        /*��ӦӦ��λ*/
BYTE i2c_ack_stat;              /*״̬��¼*/
LOCAL  I2Cisinit=0;

/*��ȡ���ݹܽ�״̬*/
LOCAL BYTE PinDataRead(void)
{
    DWORD dwPioPdsr;
    PIOB_ODR = DATA(sCurI2cPort.byDataPin);         /*�ر����*/
    dwPioPdsr = PIOB_PDSR;                        /*��ȡ��ǰ״̬*/
    PIOB_OER = DATA(sCurI2cPort.byDataPin);         /*ʹ�����*/
/*    return ( dwPioPdsr | DATA(sCurI2cPort.byDataPin) ? 1 : 0);*/
    return ( (dwPioPdsr & DATA(sCurI2cPort.byDataPin)) ? 1 : 0);    
}

/*д�����ݹܽ�״̬*/
LOCAL void PinDataWrite(BYTE byLevel)
{
    switch(byLevel)
    {
        case HIGH:
            PIOB_SODR = DATA(sCurI2cPort.byDataPin);   /*�øߵ�ƽ*/
            break;
        case LOW:
            PIOB_CODR = DATA(sCurI2cPort.byDataPin);   /*�õ͵�ƽ*/
            break;
        default:
            break;
    }
}

/*д��ʱ�ӹܽ�״̬*/
LOCAL void PinClkWrite(BYTE byLevel)
{
    switch(byLevel)
    {
        case HIGH:
            PIOB_SODR = DATA(sCurI2cPort.byClkPin);    /*�øߵ�ƽ*/
            break;
		case LOW:
            PIOB_CODR = DATA(sCurI2cPort.byClkPin);    /*�õ͵�ƽ*/
            break;
        default:
            break;
    }
}

/*I2Cʱ���ź��߿���*/
void I2cClk(BYTE x)
{
	FAST int iLocKey;

    iLocKey = intLock();
	
    PinClkWrite(x);

    intUnlock (iLocKey); 
}

/*I2C�����ź��߿���*/
void I2cData(BYTE x)
{
	int iLocKey;    

    iLocKey = intLock ();
	
    PinDataWrite(x);
    
    intUnlock (iLocKey); 
}

/*I2C��ʼλ*/
void i2cStart(void)
{	
	/*SDA=1, SCL=1 */
	I2cData(HIGH);
	I2cClk(HIGH);
    I2C_DELAY(CLOCK_HIGH_TIME);

	/*SCL=1, SDA=0*/
	I2cData(LOW);
	I2C_DELAY(START_CONDITION_HOLD_TIME+3);

	/*SCL=0 SDA=0*/
	I2cClk(LOW);
	I2C_DELAY(CLOCK_LOW_TIME);
}

/*I2Cֹͣλ*/
void I2cStop(void)
{
	/*SCL=0, SDA=0 */
	I2cData(LOW);
	I2C_DELAY(CLOCK_LOW_TIME*2);

	/*SCL=1, SDA=0*/
	I2cClk(HIGH);
	I2C_DELAY(CLOCK_HIGH_TIME*9);

	/*SCL=1 SDA=1*/
	I2cData(HIGH);
	I2C_DELAY(STOP_CONDITION_HOLD_TIME);
    I2C_DELAY(CLOCK_LOW_TIME*3);
}

/*I2C������λ*/
BYTE I2cReadBit(void)
{
	volatile BYTE x;
    FAST int iLocKey;

	I2cClk(LOW);
	I2C_DELAY(CLOCK_LOW_TIME );
	I2cClk(HIGH);
	I2C_DELAY(CLOCK_HIGH_TIME);

	iLocKey = intLock ();
    x = PinDataRead();
    intUnlock (iLocKey);

	I2cClk(LOW);
	I2C_DELAY(CLOCK_LOW_TIME);
	return x;
}

/*I2Cд����λ*/
void I2cWriteBit(BYTE x)
{
	I2cClk(LOW);
	I2C_DELAY(CLOCK_LOW_TIME);

	if (x & 0x80) /* the MSB is sent out first*/
		I2cData(HIGH);
	else
		I2cData(LOW);

	I2C_DELAY(CLOCK_LOW_TIME);
	I2cClk(HIGH);
	I2C_DELAY(CLOCK_HIGH_TIME*15);
	I2cClk(LOW);
	I2C_DELAY(CLOCK_LOW_TIME);
/*	I2cData(HIGH);*/
}

/*I2Cдһ���ֽ�*/
void I2cWriteByte(BYTE data)
{
	int i;

	for(i=0;i<8;i++)
    {
		I2cWriteBit(data);
		data<<=1;
    }

	I2cData(HIGH);/*release SDA*/
}

/*I2C��һ���ֽ�*/
BYTE I2cReadByte(void)
{
	BYTE bit;
	BYTE data=0x0;
	
	/*The MSB is read first*/
	for(data=0,bit=0;bit<7;bit++)
		{
		data |= I2cReadBit();
		data <<= 1;
		}

	data |= I2cReadBit();
	return data;
}

/*���I2C�豸�Ƿ�æ*/
BYTE I2cDeviceBusy(BYTE bySlave)
{
	BYTE byBusy = 1;
	int i = 0;
	while((byBusy != 0) && (i < 100))
	{
		i2cStart();
		I2cWriteByte(bySlave);
		byBusy=I2cReadBit();
		if(byBusy)
			I2cStop();
		i++;
	}
#ifdef I2C_DEBUG    
	if(byBusy == 1)
		printf("\nThe device is busy\n");
	else
		printf("\nThe device is free\n");
#endif /* I2C_DEBUG */

	return byBusy;	
}

/***************************************************************

	��������: 	I2C ��ʼ���� ��ϵͳʹ��GPIO ģ��I2C ʱ��
	
	��������:
		��
	��������ֵ:
		��

***************************************************************/
void dev_I2cInit(void)
{
    FAST int iLocKey;
    DWORD dwPinMask;

    iLocKey = intLock ();
	/* initially at power up SDA has pull down because it is used as strap pin.
	 * the PCI_ARB strap pin which is GPIO 2 should be driven high inorder to 
     * have a pull up on SDA line. This is required by this board design
     */
	dwPinMask = DATA(IICDATA0) | DATA(IICDATA1)  | DATA(IICDATA2) | CLOCK(IICCLK0) | CLOCK(IICCLK1) | CLOCK(IICCLK2);

    PIOB_IDR = dwPinMask;                 /*���ж�*/

    PIOB_PUDR = dwPinMask;                /*���������*/

    PIOB_MDER = dwPinMask;                /*�迪©*/

    PIOB_SODR = dwPinMask;                /*��������Ĵ���*/

    PIOB_OER = dwPinMask;                 /*ʹ�����*/

    PIOB_PER = dwPinMask;                 /*IO��ʹ��*/

    PMC_PCER = (DWORD)(0x1 << 3);

	intUnlock (iLocKey);
	if(semI2cLock==NULL)
	{
   	 semI2cLock = semBCreate( SEM_Q_PRIORITY, SEM_FULL);
	}

    if(NULL == semI2cLock)
    {
        logMsg("i2c semBCreate Error!\n", 0, 0, 0, 0, 0, 0);
    }
	I2Cisinit =1;
}

/*I2Cʱ������,���ڲ���*/
void I2cClkCycles(int j)
{	
	dev_I2cInit();
    sCurI2cPort.byClkPin = IICCLK1;
    sCurI2cPort.byDataPin = IICDATA1;
	while(1)
		{
		I2cClk(HIGH);
		I2C_DELAY(j);
		I2cClk(LOW);
		I2C_DELAY(j);
		}
}

/*I2C������
//input :  byIicPort     I2C�˿ں�Ϊ 0 ~ 1
//         bySlave       �豸��
//         dwAddr        �����ַ
//output:  pbyData       ����ֵ
//return:  SYS_OK
           SYS_ERR      
*/

SDWORD I2cRead(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData)
{
	BYTE byData = 0;
    volatile BYTE i2c_bw_ctrl; /* I2C write control */
    volatile BYTE i2c_br_ctrl; /* I2C read control */
    volatile BYTE i2c_addr_00; /* I2C address (0) */

    STATUS semStatus;                           /*i2cͬ���ź���*/

    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*����ź���*/
    
    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }
    
    if(0 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK0;
        sCurI2cPort.byDataPin = IICDATA0;
    }
    else if(1 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK1;
        sCurI2cPort.byDataPin = IICDATA1;
    }

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
		/*I2cWriteByte(i2c_addr_01);*/
		/*ack1=I2cReadBit();*/ /*read ack from slave*/
		/*if(ack1!=0)
			i2c_ack_stat |= 0x2; */
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
		byData = I2cReadByte();

		I2cStop();
    }

#ifdef I2C_DEBUG 
	if(i2c_ack_stat!=0)
		printf("\nError in read, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);
#endif
	*pbyData = byData;

    semGive(semI2cLock);    /*�ͷ��ź���*/

    if(0 != i2c_ack_stat)
    {
	    return SYS_ERROR;
    }
    return SYS_OK;
}

SDWORD I2cRead1014(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData)
{
	BYTE byData = 0;
    volatile BYTE i2c_bw_ctrl; /* I2C write control */
    volatile BYTE i2c_br_ctrl; /* I2C read control */
    volatile BYTE i2c_addr_00; /* I2C address (0) */

    STATUS semStatus;                           /*i2cͬ���ź���*/

    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*����ź���*/
    
    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }
    
    if(0 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK0;
        sCurI2cPort.byDataPin = IICDATA0;
    }
    else if(1 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK1;
        sCurI2cPort.byDataPin = IICDATA1;
    }

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
		/*I2cWriteByte(i2c_addr_01);*/
		/*ack1=I2cReadBit();*/ /*read ack from slave*/
		/*if(ack1!=0)
			i2c_ack_stat |= 0x2; */
		I2cWriteByte(i2c_addr_00);
		ack1=I2cReadBit(); /*read ack from slave*/
		if(ack1!=0)
			i2c_ack_stat |= 0x2; 
        I2cStop();
        I2C_DELAY(255);
        I2C_DELAY(255);
		i2cStart();
        I2C_DELAY(CLOCK_LOW_TIME*3);
		I2cWriteByte(i2c_br_ctrl);
		ack1=I2cReadBit(); /*read ack from slave*/
		if(ack1!=0)
			i2c_ack_stat |= 0x3; 
        I2C_DELAY(CLOCK_LOW_TIME*3);
		byData = I2cReadByte();

		I2cStop();
    }

#ifdef I2C_DEBUG 
	if(i2c_ack_stat!=0)
		printf("\nError in read, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);
#endif
	*pbyData = byData;

    semGive(semI2cLock);    /*�ͷ��ź���*/

    if(0 != i2c_ack_stat)
    {
	    return SYS_ERROR;
    }
    return SYS_OK;
}

/*I2C���ַ���   ������ʱ���ṩ
//input :  byIicPort     I2C�˿ں�Ϊ 0 ~ 1
//         bySlave       �豸��
//         dwAddr        �����ַ
//         dwCount       �����
//output:  pbyData       ����ֵ
  return:  SYS_OK
           SYS_ERR
*/
SDWORD I2cReadSeq(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData, DWORD dwCount)
{
    volatile BYTE i2c_bw_ctrl; /* I2C write control */
    volatile BYTE i2c_br_ctrl; /* I2C read control */
    volatile BYTE i2c_addr_00; /* I2C address (0) */
	int i;

    STATUS semStatus;                           /*i2cͬ���ź���*/

    if (0 == dwCount)
    {
        return SYS_ERROR;
    }
    
    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*����ź���*/

    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }

    if(0 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK0;
        sCurI2cPort.byDataPin = IICDATA0;
    }
    else if(1 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK1;
        sCurI2cPort.byDataPin = IICDATA1;
    }
    
#ifdef I2C_DEBUG    
	printf("\n i2cReadSeq() slave address is 0x%x", bySlave);
#endif /* I2C_DEBUG */
	i2c_ack_stat=0x0;
    i2c_bw_ctrl = bySlave | I2C_WRITE;
    i2c_br_ctrl = bySlave | I2C_READ;
    /*i2c_addr_01 = I2C_W1_ADDR(dwAddr);*/
    i2c_addr_00 = I2C_W0_ADDR(dwAddr);

	if(1)
	{
        i2cStart();
        I2cWriteByte(i2c_bw_ctrl);
        ack1=I2cReadBit(); /*read ack from slave*/
        if(ack1!=0)
            i2c_ack_stat |= 0x1; 
       
        I2cWriteByte(i2c_addr_00);
        ack1=I2cReadBit(); /*read ack from slave*/
        if(ack1!=0)
            i2c_ack_stat |= 0x2; 
        i2cStart();
        
        I2cWriteByte(i2c_br_ctrl);
        ack1=I2cReadBit(); /*read ack from slave*/
        if(ack1!=0)
            i2c_ack_stat |= 0x3; 
        for(i=0;i<dwCount;i++)
        {
            pbyData[i] = I2cReadByte();
            if(i != (dwCount-1))
                I2cWriteBit(0x0); /*send ack*/
            else
                I2cWriteBit(0x80); /*send nack after reading the last byte*/
            I2cData(HIGH);
        }
        
        I2cStop();
    }

	if(i2c_ack_stat!=0)
		printf("\nError in read, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);

    semGive(semI2cLock);       /*�ͷ��ź���*/

    if(0 != i2c_ack_stat)
    {
	    return SYS_ERROR;
    }
    return SYS_OK;
}

/*I2C����д
//input :  byIicPort     I2C�˿ں�Ϊ 0 ~ 1
//         bySlave       �豸��
//         dwAddr        �����ַ
//         byData        ����ֵ
//
  return:  SYS_OK
           SYS_ERR
*/

SDWORD I2cWrite(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE byData)
{
	
    volatile BYTE i2c_bw_ctrl; /* I2C write control */
    volatile BYTE i2c_addr_00; /* I2C address (0) */

    STATUS semStatus;                           /*i2cͬ���ź���*/

    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*����ź���*/

    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }

    if(0 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK0;
        sCurI2cPort.byDataPin = IICDATA0;
    }
    else if(1 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK1;
        sCurI2cPort.byDataPin = IICDATA1;
    }

	i2c_ack_stat=0x0;
    i2c_bw_ctrl = bySlave | I2C_WRITE;
    /*i2c_addr_01 = I2C_W1_ADDR(dwAddr);*/
    i2c_addr_00 = I2C_W0_ADDR(dwAddr);

	if(1)/*0 == I2cDeviceBusy(bySlave))*/
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

		I2cWriteByte(byData);
		ack2=I2cReadBit();
		if(ack2!=0)
			i2c_ack_stat |= 0x8;
        
        I2C_DELAY(CLOCK_LOW_TIME*3);
        
		I2cStop();
	}
    
    semGive(semI2cLock);       /*�ͷ��ź���*/

    if(0 != i2c_ack_stat)
    {
        printf("\nError in write, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);
	    return SYS_ERROR;
    }
    return SYS_OK;
}

/*I2C����д�ַ���*/
/*input :  byIicPort     I2C�˿ں�Ϊ 0 ~ 1*/
/*         bySlave       �豸��*/
/*         dwAddr        �����ַ*/
/*         pbyData       ����ֵ*/
/*         dwCount       �����*/
/*return:  SYS_OK
           SYS_ERR
*/
SDWORD I2cWritePage(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData, DWORD dwCount)
{
	int i;
    volatile BYTE i2c_bw_ctrl; /* I2C write control */
    volatile BYTE i2c_addr_00; /* I2C address (0) */

    STATUS semStatus;                            /*i2cͬ���ź���*/

    semStatus = semTake(semI2cLock, WAIT_FOREVER);  /*����ź���*/

    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }

    if(0 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK0;
        sCurI2cPort.byDataPin = IICDATA0;
    }
    else if(1 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK1;
        sCurI2cPort.byDataPin = IICDATA1;
    }

	i2c_ack_stat=0x0;
    i2c_bw_ctrl = bySlave | I2C_WRITE;
    /*i2c_addr_01 = I2C_W1_ADDR(dwAddr);*/
    i2c_addr_00 = I2C_W0_ADDR(dwAddr);

    for(i=0;i<dwCount;i++)
	if(dwCount>16)
			dwCount=16;

	if(0 == I2cDeviceBusy(bySlave))
	{
		i2cStart();
		I2cWriteByte(i2c_bw_ctrl);
		ack1=I2cReadBit(); 
		if(ack1!=0)
			i2c_ack_stat |= 0x2;
		/*I2cWriteByte(i2c_addr_01);
		ack1=I2cReadBit();
		if(ack1!=0)
			i2c_ack_stat |= 0x2;*/
		I2cWriteByte(i2c_addr_00);
		ack1=I2cReadBit();
		if(ack1!=0)
			i2c_ack_stat |= 0x2;
		for(i=0;i<dwCount;i++)
		{
			I2cWriteByte(pbyData[i]);
			ack2=I2cReadBit();
			if(ack2!=0)
				i2c_ack_stat |= 0x8;
		}
		I2cStop();
	}
    
    semGive(semI2cLock);       /*�ͷ��ź���*/
    
    if(0 != i2c_ack_stat)
    {
	    return SYS_ERROR;
    }
    return SYS_OK;
}

/*ϵͳ��ʱʱ�� ����ʵ���������*/
void delayUSec(int iN)
{
    BYTE byBase;             /*��ʱѭ������*/
/*    while(iN --)
    {
*/        byBase = iN;
        while(byBase --);
/*    }*/
}

void i2cReadWrite(void)
{
    DWORD slaveId = 0x98;
    BYTE byData;

    logMsg("i2cTest star\n", 0, 0, 0, 0, 0, 0);

    dev_I2cInit();
	logMsg("i2cTest init\n", 0, 0, 0, 0, 0, 0);
 
    I2cWrite(0, slaveId, 0x09, 0x61);
	byData = 0;
    I2cRead(0, slaveId, 0x09, &byData);
    logMsg("i2cTest byData%d\n", byData, 0, 0, 0, 0, 0);
}

SDWORD I2cReadCpld(BYTE *pbyData, BYTE byDataNum)
{
    BYTE bySlave = I2C_CPLDID;
    BYTE i2c_br_ctrl = 0; /* I2C read control */
    BYTE byIicPort = I2C_CPLDPORT;

    static BYTE *pCpldData = (BYTE *)0x20000020;
    
    STATUS semStatus;                           /*i2cͬ���ź���*/
	if (0==I2Cisinit)
	{
		dev_I2cInit( );
	}

    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*����ź���*/
    
    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }
    
    if(0 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK0;
        sCurI2cPort.byDataPin = IICDATA0;
    }
    else if(1 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK1;
        sCurI2cPort.byDataPin = IICDATA1;
    }

#ifdef I2C_DEBUG    
/*	printf("\n i2cRead() slave address is 0x%08x, addr: 0x%08x", bySlave, dwAddr);*/
#endif /* I2C_DEBUG */
	i2c_ack_stat=0x0;
    i2c_br_ctrl = bySlave | I2C_READ;
 
	if(1)
    {
		i2cStart();
		I2cWriteByte(i2c_br_ctrl);
		ack1=I2cReadBit(); /*read ack from slave*/
		if(ack1!=0)
			i2c_ack_stat |= 0x3; 
        I2C_DELAY(CLOCK_LOW_TIME*3);
		pbyData[0] = I2cReadByte();
        I2cWriteBit(0x0); /*send ack*/
        I2cData(HIGH);
        pbyData[1] = I2cReadByte();
        I2cWriteBit(0x0); /*send ack*/
        I2cData(HIGH);
        pbyData[2] = I2cReadByte();
        I2cWriteBit(0x80); /*send ack*/
        I2cData(HIGH);
		I2cStop();
    }

#ifdef I2C_DEBUG 
	if(i2c_ack_stat!=0)
		printf("\nError in read, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);
#endif
/*    printf("\nbyData[0] =%d, byData[1] =%d,byData[2] =%d\n",pbyData[0], pbyData[1], pbyData[2]);*/

    if (0x20000030 > pCpldData)
    {        
        *pCpldData++ = pbyData[0];
        *pCpldData++ = pbyData[1];
        *pCpldData++ = pbyData[2];
    }
    
    semGive(semI2cLock);    /*�ͷ��ź���*/

    if(0 != i2c_ack_stat)
    {
	    return SYS_ERROR;
    }
    return SYS_OK;
}

SDWORD TestCpld(void)
{
    BYTE byData[5] = {0};
    BYTE bySlave = 0xca;
    BYTE i2c_br_ctrl = 0; /* I2C read control */
    BYTE byIicPort = 0;
    
    STATUS semStatus;                           /*i2cͬ���ź���*/

	if (0==I2Cisinit)
	{
		dev_I2cInit( );
	}
    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*����ź���*/
    
    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }
    
    if(0 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK0;
        sCurI2cPort.byDataPin = IICDATA0;
    }
    else if(1 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK1;
        sCurI2cPort.byDataPin = IICDATA1;
    }

#ifdef I2C_DEBUG    
/*	printf("\n i2cRead() slave address is 0x%08x, addr: 0x%08x", bySlave, dwAddr);*/
#endif /* I2C_DEBUG */
	i2c_ack_stat=0x0;
    i2c_br_ctrl = bySlave | I2C_READ;
 
	if(1)/*0 == I2cDeviceBusy(bySlave))*/
    {
		i2cStart();
		I2cWriteByte(i2c_br_ctrl);
		ack1=I2cReadBit(); /*read ack from slave*/
		if(ack1!=0)
			i2c_ack_stat |= 0x3; 
        I2C_DELAY(CLOCK_LOW_TIME*3);
		byData[0] = I2cReadByte();
        I2cWriteBit(0x0); /*send ack*/
        I2cData(HIGH);
        byData[1] = I2cReadByte();
        I2cWriteBit(0x0); /*send ack*/
        I2cData(HIGH);
        byData[2] = I2cReadByte();
        I2cWriteBit(0x00); /*send ack*/
        I2cData(HIGH);
        byData[3] = I2cReadByte();
        I2cWriteBit(0x00); /*send ack*/
        I2cData(HIGH);
        byData[4] = I2cReadByte();
        I2cWriteBit(0x80); /*send ack*/
        I2cData(HIGH);
		I2cStop();
    }

#ifdef I2C_DEBUG 
	if(i2c_ack_stat!=0)
		printf("\nError in read, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);
#endif
    printf("\Data[0] = 0x%2x, Data[1] = 0x%2x, Data[2] = 0x%2d, Data[3] = 0x%2d, Data[4] = 0x%2d\n", byData[0], byData[1], byData[2], byData[3], byData[4]);

    semGive(semI2cLock);    /*�ͷ��ź���*/

    if(0 != i2c_ack_stat)
    {
	    return SYS_ERROR;
    }
    return SYS_OK;
}

void I2cCpldReset(void)
{
    FAST int iLocKey;
    DWORD dwPinMask;

    iLocKey = intLock ();
	/* initially at power up SDA has pull down because it is used as strap pin.
	 * the PCI_ARB strap pin which is GPIO 2 should be driven high inorder to 
     * have a pull up on SDA line. This is required by this board design
     */
	dwPinMask = DATA(13);

    PIOC_IDR = dwPinMask;                 /*���ж�*/

    PIOC_PPUER = dwPinMask;                /*���������*/

    PIOC_SODR = dwPinMask;                /*��������Ĵ���*/

    PIOC_OER = dwPinMask;                 /*ʹ�����*/

    PIOC_PER = dwPinMask;                 /*IO��ʹ��*/

	intUnlock (iLocKey);

    semI2cLock = semBCreate( SEM_Q_PRIORITY, SEM_FULL);

    if(NULL == semI2cLock)
    {
        logMsg("i2c semBCreate Error!\n", 0, 0, 0, 0, 0, 0);
    }

    PIOC_CODR = DATA(13);   /*�õ͵�ƽ*/

    delayUSec(100);

    PIOC_SODR = DATA(13);   /*�øߵ�ƽ*/
}


SDWORD I2cReadTest(BYTE byIicPort, BYTE bySlave, DWORD dwAddr)
{
	BYTE byData = 0;
    volatile BYTE i2c_bw_ctrl; /* I2C write control */
    volatile BYTE i2c_br_ctrl; /* I2C read control */
    volatile BYTE i2c_addr_00; /* I2C address (0) */

    STATUS semStatus;                           /*i2cͬ���ź���*/

    semStatus = semTake(semI2cLock, WAIT_FOREVER); /*����ź���*/
    
    if(ERROR == semStatus)
    {
        logMsg("i2c semTake ERROR\n", 0, 0, 0, 0, 0, 0);
        return;
    }
    
    if(0 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK0;
        sCurI2cPort.byDataPin = IICDATA0;
    }
    else if(1 == byIicPort)
    {
        sCurI2cPort.byClkPin = IICCLK1;
        sCurI2cPort.byDataPin = IICDATA1;
    }

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
		/*I2cWriteByte(i2c_addr_01);*/
		/*ack1=I2cReadBit();*/ /*read ack from slave*/
		/*if(ack1!=0)
			i2c_ack_stat |= 0x2; */
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
		byData = I2cReadByte();

		I2cStop();
    }

#ifdef I2C_DEBUG 
	if(i2c_ack_stat!=0)
		printf("\nError in read, ack not recd, i2c_ack_stat=0x%x\n",i2c_ack_stat);
#endif
	printf("byData: %x \n", byData);
    semGive(semI2cLock);    /*�ͷ��ź���*/

    if(0 != i2c_ack_stat)
    {
	    return SYS_ERROR;
    }
    return SYS_OK;
}

/* I2cInit */
/* 5160 1011100 1011101 iic0 pb5/6 */
/* I2cReadTest 0x0, 0xb8, 0x80 */
/* I2cWrite 0x0, 0xb8,*/
/* I2cReadTest 0x0, 0xba, 0x80 */
/* I2cWrite 0x0, 0xba,*/

/* 9548 1110000 iic0 */
/* I2cWrite 0x0, 0xe0, 0x0, 0x2 */
/* I2cReadTest 0x0, 0xe0, 0x0 */


/******************************************************

	��������: 	I2C �豸д��������
	��������: 	
		chn:	
				I2C ͨ����, ϵͳʹ����·I2C ͨ��0 Ϊ���ذ�
				ͨ��1 ΪԶ��

		chipType:
				I2C �豸��ַ��I2CΪ�������ߣ�ÿһ��������
				���豸���ж�Ӧ�ĵ�ַ
		addr:
				��Ҫ���ʵļĴ���ƫ��
		value:
				д��Ĵ�����ֵ
	��������ֵ
		��


*******************************************************/
void dev_I2C_Write(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t value)
{
	if (chn > 1)
	{
		printf ("\r\n the I2C channel error ! channel = 0x%0x\n", chn);
		return;
	}		

	I2cWrite((unsigned char)chn, (unsigned char)chipType, (unsigned long)(addr & 0xFF), (unsigned char)value);
}


/*************************************************************

	��������:	I2C �豸����������
	��������:    
		chn:
				I2C ͨ���ţ�ϵͳ ʹ������ͨ��, ͨ��1Ϊ���ذ�
				ͨ����ͨ��1ΪԶ�˷���ͨ��
		chipType:
				I2C �豸��ַ��I2CΪ����ʽ���ߣ�ÿһ�������ϵ�
				�豸���ж�Ӧ�ĵ�ַ
		addr:
				I2C�豸�ļĴ���ƫ�Ƶ�ַ
		value:
				��ȡ�Ĵ�����ֵ
	��������ֵ:
		��

**************************************************************/
void dev_I2C_Read(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t *value)
{
	unsigned char r_value;
	
	if (chn > 1)
	{
		printf ("\r\n the I2C channel error ! channel = 0x%0x\n", chn);
		return;
	}		

	I2cRead((unsigned char)chn, (unsigned char)chipType, (unsigned long)(addr & 0xFF), &r_value);
	*value = r_value;
}




