/*
 * devC772.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "devBus.h"
#include <stdio.h>
#include "chipCommon.h"


using namespace chip;


I2CBus::I2CBus()
{

}

I2CBus::~I2CBus()
{

}



void I2CBus::dev_5160_WriteMult(uint32_t chn,list<map<uint8_t,uint8_t> > value)
{
//	debug_msg("WriteMult chn=%d, size=%d\n",chn,value.size());

	for(list<map<uint8_t,uint8_t> >::iterator itList = value.begin();itList!=value.end();itList++)
	{
//		debug_msg("WriteMult map size=%d\n",itList->size());
		for(map<uint8_t,uint8_t>::iterator itMap = itList->begin();itMap!=itList->end();itMap++)
		{
			uint8_t addr=0;
			uint8_t value=0;
			addr=itMap->first;
			value = itMap->second;
			debug_msg("addr=%02x,value=%02x\n",addr,value);
			dev_5160_Write(chn,addr,value);
			for(int i=0;i<2000000;i++)
			{

			}
		}
	}

}

void I2CBus::I2C_5160_Write(uint32_t chn,uint8_t addr,uint8_t value)
{
	dev_5160_Write(chn,addr,value);
}

void I2CBus::I2C_5160_Read(uint32_t chn,uint8_t addr,uint8_t &value)
{
	dev_5160_Read(chn,addr,&value);
}


SPIBus::SPIBus()
{

}

SPIBus::~SPIBus()
{

}



void SPIBus::dev_SPI_WriteMult(uint32_t chn,list<map<uint8_t,uint8_t> > value)
{
	for(list<map<uint8_t,uint8_t> >::iterator itList = value.begin();itList!=value.end();itList++)
	{
		for(map<uint8_t,uint8_t>::iterator itMap = itList->begin();itMap!=itList->end();itMap++)
		{

			if(chn == DEV_SPI_C753_CHANNEL)
			{
				dev_SPI_Write(DEV_SPI_C753_CHANNEL,itMap->first,itMap->second);
			}
			else
			{
				printf("dev_SPI_Write 772 chn=%d addr=%02x,value=%02x\n",chn,itMap->first,itMap->second);
				switch(chn)
				{
					case 1:
						dev_SPI_Write(DEV_SPI_C772_CHANNEL_1,itMap->first,itMap->second);
						break;
					case 2:
						dev_SPI_Write(DEV_SPI_C772_CHANNEL_2,itMap->first,itMap->second);
						break;
					case 3:
						dev_SPI_Write(DEV_SPI_C772_CHANNEL_3,itMap->first,itMap->second);
						break;
					case 4:
						dev_SPI_Write(DEV_SPI_C772_CHANNEL_4,itMap->first,itMap->second);
						break;
					case 5:
						dev_SPI_Write(DEV_SPI_C772_CHANNEL_5,itMap->first,itMap->second);
						break;
					case 6:
						dev_SPI_Write(DEV_SPI_C772_CHANNEL_6,itMap->first,itMap->second);
						break;

				}

			}
		}
	}

}

void SPIBus::SPI_Write(uint32_t chn,uint8_t addr,uint8_t value)
{
	if(chn == 0)
	{
//		printf("dev_SPI_Write 753 addr=%02x,value=%02x\n",addr,value);
		dev_SPI_Write(DEV_SPI_C753_CHANNEL,addr,value);
	}
	else
	{
		printf("dev_SPI_Write 772 chn=%d addr=%02x,value=%02x\n",chn,addr,value);
		switch(chn)
		{
			case 1:
				dev_SPI_Write(DEV_SPI_C772_CHANNEL_1,addr,value);
				break;
			case 2:
				dev_SPI_Write(DEV_SPI_C772_CHANNEL_2,addr,value);
				break;
			case 3:
				dev_SPI_Write(DEV_SPI_C772_CHANNEL_3,addr,value);
				break;
			case 4:
				dev_SPI_Write(DEV_SPI_C772_CHANNEL_4,addr,value);
				break;
			case 5:
				dev_SPI_Write(DEV_SPI_C772_CHANNEL_5,addr,value);
				break;
			case 6:
				dev_SPI_Write(DEV_SPI_C772_CHANNEL_6,addr,value);
				break;

		}
	}
}

void SPIBus::SPI_Read(uint32_t chn,uint8_t addr,uint8_t &value)
{
//	printf("dev_SPI_Read addr=%02x,value=%02x\n",addr,value);
	if(chn == 0)
	{
		dev_SPI_Read(DEV_SPI_C753_CHANNEL,addr,&value);
	}
	else
	{
		switch(chn)
		{
			case 1:
				dev_SPI_Read(DEV_SPI_C772_CHANNEL_1,addr,&value);
				break;
			case 2:
				dev_SPI_Read(DEV_SPI_C772_CHANNEL_2,addr,&value);
				break;
			case 3:
				dev_SPI_Read(DEV_SPI_C772_CHANNEL_3,addr,&value);
				break;
			case 4:
				dev_SPI_Read(DEV_SPI_C772_CHANNEL_4,addr,&value);
				break;
			case 5:
				dev_SPI_Read(DEV_SPI_C772_CHANNEL_5,addr,&value);
				break;
			case 6:
				dev_SPI_Read(DEV_SPI_C772_CHANNEL_6,addr,&value);
				break;

		}

	}

//	printf("dev_SPI_Read value=%02x\n",value);
}


FPGABus::FPGABus()
{

}

FPGABus::~FPGABus()
{

}


void FPGABus::FPGA_Write(uint16_t addr,uint16_t value)
{
	dev_FPGA_Write(DEV_SPI_FPGA_CHANNEL,addr,value);
}

void FPGABus::FPGA_Read(uint16_t addr,uint16_t &value)
{
	dev_FPGA_Read(DEV_SPI_FPGA_CHANNEL,addr,&value);
}


