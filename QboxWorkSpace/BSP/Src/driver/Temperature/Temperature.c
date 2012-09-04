

/* includes */

#include "vxWorks.h"
#include "stdio.h"
#include "tasklib.h"
#include "Temperature.h"





/*
获取电压值
输入: 电压路数(1-6)
输出:电压值，单位0.01 MV
*/

DWORD getVoltage(BYTE VoltageNu)
{
		BYTE result[2] = {0};
		DWORD dwResult=0;
        DWORD dwExitCount=0;
        
		if(VoltageNu>16)
		{
			return 0xFFFFFFFF;
		}
        
	    VoltageNu=(VoltageNu|0x10);
        
		if ( OK !=  I2cWrite(0,BSP_POWER1014,9,VoltageNu))
		{
			return 0xFFFFFFFF;
		}
        
		while(0 == (result[0]&0x1))
		{
			if (OK !=  I2cRead1014(0,BSP_POWER1014,7,&result[0]))
			{
				return 0xFFFFFFFF;
			}
            dwExitCount++;
            taskDelay(10);
            
            if(10==dwExitCount)
            {
            	return 0xFFFFFFFF;
            }
            
		}
		
		if (OK !=  I2cRead1014(0,BSP_POWER1014,8,&result[1]))
		{
			return 0xFFFFFFFF;
		}
		result[0] >>= 4;
		
		dwResult= result[0] + (result[1]<<4);

		return  dwResult;
/*	SDWORD I2cRead(0, BYTE bySlave, DWORD dwAddr, BYTE *pbyData);*/
/*	SDWORD I2cWrite(0, BYTE bySlave, DWORD dwAddr, BYTE byData);*/
}


/* 读取LM73温度寄存器的温度值
------------------------------------------
    input: none
    output: val
    return: OK / ERROR 
*/

SDWORD  getTemperatureValue( BYTE   lM73No)
{
    SDWORD dwvalue = 0;
    BYTE abyval[2] ;

    SDWORD dwTempValue = 0;
    BYTE   byFlag      = 0;

    //计算平均值的滑动窗口，窗口为10
    static SDWORD dwTempWnd[10] = {0};
    
    static DWORD   index        = 0xff;      //用于区分初始化值
    DWORD  i;
    DWORD  dwAvarg              = 0;

    if ( OK !=  ReadLM73(LM73_TEMPERATURE_REG, abyval, 2))
    {
        dwvalue=-1;
        return dwvalue;
    }
    
    if( abyval[0] & 0x80 )
    {
        dwTempValue = (SDWORD)(abyval[0] << 8) + (SDWORD)(abyval[1] & 0xFF);
        dwTempValue = ~dwTempValue + 1;
        abyval[0]   = (BYTE)(dwTempValue >> 8);
        abyval[1]   = (BYTE)(dwTempValue & 0xFF);
        byFlag      = 1;
    }

    dwvalue = ((0x7f&abyval[0])<<1)+(abyval[1]>>7);
    
    dwvalue *= 100000;
    
    if( (abyval[1]>>2)&0x1 )
    {
        dwvalue += 3125 ;
    }

    if( (abyval[1]>>3)&0x1 )
    {
        dwvalue += 6250 ;
    }

    if( (abyval[1]>>4)&0x1 )
    {
        dwvalue += 12500;
    }

    if( (abyval[1]>>5)&0x1 )
    {
        dwvalue += 25000 ;
    }

    if( (abyval[1]>>6)&0x1 )
    {
        dwvalue += 50000 ;
    }

    if (0xff == index)
    {
        for (i = 0; i < 10; i ++)
        {
            dwTempWnd[i] = dwvalue;
        }  
    }
        
    if (9 < index)
    {
        index = 0;
    }

    dwTempWnd[index] = dwvalue;
    for (i = 0; i < 10; i ++)
    {
        dwAvarg += dwTempWnd[i];
    }    
    dwvalue = dwAvarg / 10;
    index ++;
    
    if( 1 == byFlag )
    {
        dwvalue= (~dwvalue) + 1;
    }

    return dwvalue;
}

void TempTest()
{
    SDWORD sdTemp[2] = {1,-2};

    SDWORD avrTemp = sdTemp[0] + sdTemp[1];

    printf("Temp = %d\n", avrTemp);
}    


void dispLM73reg( UINT8 lM73No, LM73_REG reg )
{
    UINT8 val[2] ;

    I2cRead( 0,BSP_LM73, reg, val ) ;
    
    printf( "reg is 0x%x\n", val[0] ) ;
}


/*************************************
 * AT24C32 EEPROM 驱动代码
 *************************************/
	/* eeprom 写
	 * 输入：offset 
	 *				   val
	 *				   len
	 * 输出：OK / ERROR
	 */
	int eepromRead( UINT32 offset, UINT8 *val, UINT32 len )
	{
		UINT32 temp=OK, i=0 ;
	
		//if(( offset >0x256 ) || ( len > 0x256 ) || (( offset + len ) > 0x256 ))
		if(( offset + len ) > 0x256 )
			return ERROR ;
	
		temp = I2cReadSeq(0, BSP_AT24C01, offset, val, len);
		
		return temp ;
	}
	
	/* eeprom 写
	 * 输入：offset 
	 *				   val
	 *				   len
	 * 输出：OK / ERROR

	
	int eepromWrite( UINT32 offset, UINT8 *val, int len )
	{
		int temp=OK, i ;
	
		if(( offset >0x256 ) || ( len > 0x256 ) || (( offset + len ) > 0x256 ))
			return ERROR ;
	
		(void)semTake( I2cUsedSemId, WAIT_FOREVER ) ;
		EnableEprom();
		for( i=0; i<len; i++,val++ )
		{
			i2cWrite(AT24C32_DEVICE_ADDR, i, *val) ;
			taskDelay(1) ;
		}
		
		DisableEprom();
		(void)semGive( I2cUsedSemId ) ;
	
		return temp ;
	}
	
	
*/


/*************************************
*
* toBCD - convert to binary coded decimal
*/
BYTE toBCD( BYTE intValue )
{
    BYTE bcdValue;

    bcdValue = intValue%10;
    intValue /= 10;
    intValue *= 0x10;
    bcdValue += intValue;

    return (bcdValue);
}



/*****************************************
*
* fromBCD - convert from binary coded decimal
*/
BYTE fromBCD( BYTE bcdValue )
{
    BYTE intValue;

    intValue = bcdValue&0xf;
    intValue += ((bcdValue&0xf0)/0x10)*10;

    return (intValue);
}


SDWORD GetRtc(DWORD *pdwYear, DWORD *pdwMonth, DWORD *pdwDay, 
    DWORD *pdwHours, DWORD *pdwMinutes, DWORD *pdwSecond)
{
    
    BYTE byTempBT;
    /* 02h seconds*/
    if (OK == I2cRead(0,BSP_PCF8563,0x02,&byTempBT))
        {
            byTempBT &= 0x7f;
            *pdwSecond = fromBCD(byTempBT); 
        }
        else
        {
            return ERROR;
        }
    /* 03h minutes*/
    
    if (OK == I2cRead(0,BSP_PCF8563,0x03,&byTempBT))
        {
            byTempBT &= 0x7f;
            *pdwMinutes = fromBCD(byTempBT); 
        }
        else
        {
            return ERROR;
        }
    
    /* 04h hours*/

    if (OK == I2cRead(0,BSP_PCF8563,0x04,&byTempBT))
        {
            byTempBT &= 0x3f;
            *pdwHours = fromBCD(byTempBT); 
        }
        else
        {
            return ERROR;
        }
    /* 05h days*/
    
    if (OK == I2cRead(0,BSP_PCF8563,0x05,&byTempBT))
        {
            byTempBT &= 0x3f;
            *pdwDay = fromBCD(byTempBT); 
        }
        else
        {
            return ERROR;
        }
    /*07h months/century*/
    
    if (OK == I2cRead(0,BSP_PCF8563,0x07,&byTempBT))
        {
            byTempBT &= 0x1f;
            *pdwMonth = fromBCD(byTempBT); 
        }
        else
        {
            return ERROR;
        }
    /* 08h years*/

    
    if (OK == I2cRead(0,BSP_PCF8563,0x08,&byTempBT))
        {
            *pdwYear = fromBCD(byTempBT); 
        }
        else
        {
            return ERROR;
        }

    return OK;
}



SDWORD SetRtc(DWORD dwYear, DWORD dwMonth, DWORD dwDay,
    DWORD dwHours, DWORD dwMinutes, DWORD dwSecond)
{

    BYTE byTempBT;
    DWORD dwTmpYear; 
    DWORD dwTmpMonth; 
    DWORD dwTmpDay;
    DWORD dwTmpHours; 
    DWORD dwTmpMinutes; 
    DWORD dwTmpSecond;

    BYTE byCentury = 0;

    if(99 < dwYear)
    {
        dwYear -= 100;
        byCentury = 1;
    }
    
    byTempBT = toBCD(dwSecond);
    /* 02h seconds*/
    if (OK != I2cWrite(0,BSP_PCF8563,0x02,byTempBT))
        {
            return ERROR;
        }

     byTempBT = toBCD(dwMinutes);
    /* 03h minutes*/
    
    if (OK != I2cWrite(0,BSP_PCF8563,0x03,byTempBT))
        {
            return ERROR;
        }
    
    /* 04h hours*/
    
    byTempBT = toBCD(dwHours);
    if (OK != I2cWrite(0,BSP_PCF8563,0x04,byTempBT))
        {
            return ERROR;
        }
    /* 05h days*/

    byTempBT = toBCD(dwDay);
    if (OK != I2cWrite(0,BSP_PCF8563,0x05,byTempBT))
        {
            return ERROR;
        }
    /*07h months/century*/
    byTempBT = toBCD(dwMonth);

    if( 1 == byCentury )
    {
        byTempBT |= 0x80;
    }
    
    if (OK != I2cWrite(0,BSP_PCF8563,0x07,byTempBT))
        {
            return ERROR;
        }
    /* 08h years*/

    byTempBT = toBCD(dwYear);
    if (OK != I2cWrite(0,BSP_PCF8563,0x08,byTempBT))
        {
            return ERROR;
        }



       if(OK == GetRtc(&dwTmpYear,&dwTmpMonth,&dwTmpDay,&dwTmpHours,&dwTmpMinutes,&dwTmpSecond))
           {
            dwTmpMonth &= 0x1f;
            
            if ((dwTmpYear==dwYear)
                &&(dwTmpMonth ==dwMonth)
                &&(dwTmpDay   ==dwDay)
                &&(dwTmpHours ==dwHours)
                &&(dwTmpMinutes==dwMinutes)
                &&(dwTmpSecond ==dwSecond)
                )
                
            return OK;
               
           }

    return ERROR;

}


VOID BSP_RTCTEST(VOID)
{
    
    DWORD dwTmpYear; 
    DWORD dwTmpMonth; 
    DWORD dwTmpDay;
    DWORD dwTmpHours; 
    DWORD dwTmpMinutes; 
    DWORD dwTmpSecond;
    struct tm psCurTime;

 	

	if(OK != GetRtc(&dwTmpYear,&dwTmpMonth,&dwTmpDay,&dwTmpHours,&dwTmpMinutes,&dwTmpSecond))
    {
        return;
    }

	printf("year=%d,month=%d,day=%d,hours=%d,ninutes=%d,second=%d\n",dwTmpYear,dwTmpMonth,dwTmpDay,dwTmpHours,dwTmpMinutes,dwTmpSecond);

	
    psCurTime.tm_sec   = 0  ;
    psCurTime.tm_min   = 34  ;
    psCurTime.tm_hour  = 2 ;
    psCurTime.tm_mday  = 12;
    psCurTime.tm_mon   = 3  ;
    psCurTime.tm_year  = 1950 ;
    psCurTime.tm_wday  = 0 ;
    psCurTime.tm_yday  = 0  ;
    psCurTime.tm_isdst = 0 ;

    if(OK != (BSP_SetCurSysDateTime(&psCurTime)))
    {
        return;
    }

}


