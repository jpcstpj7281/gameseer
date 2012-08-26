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



using namespace chip;


I2CBus::I2CBus()
{

}

I2CBus::~I2CBus()
{

}



void I2CBus::dev_I2C_WriteMult(uint32_t chn,uint32_t chipType,list<map<uint8_t,uint8_t> > value)
{
	for(list<map<uint8_t,uint8_t> >::iterator itList = value.begin();itList!=value.end();itList++)
	{
		for(map<uint8_t,uint8_t>::iterator itMap = itList->begin();itMap!=itList->end();itMap++)
		{
			I2C_Write(chn,chipType,itMap->first,itMap->second);
		}
	}

}

void I2CBus::I2C_Write(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t value)
{
	dev_I2C_Write(chn,chipType,addr,value);
}

void I2CBus::I2C_Read(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t &value)
{
	dev_I2C_Read(chn,chipType,addr,&value);
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
			dev_SPI_Write(chn,itMap->first,itMap->second);
		}
	}

}

void SPIBus::SPI_Write(uint32_t chn,uint8_t addr,uint8_t value)
{
//	printf("dev_SPI_Write value=%02x\n",value);
	if(chn == TYPE_CHIP_C753)
	{
		dev_SPI_Write(DEV_SPI_C753_CHANNEL,addr,value);
	}
	else if(chn == TYPE_CHIP_C772)
	{
		dev_SPI_Write(DEV_SPI_C722_CHANNEL,addr,value);
	}
}

void SPIBus::SPI_Read(uint32_t chn,uint8_t addr,uint8_t &value)
{
	if(chn == TYPE_CHIP_C753)
	{
		dev_SPI_Read(DEV_SPI_C753_CHANNEL,addr,&value);
	}
	else if(chn == TYPE_CHIP_C772)
	{
		dev_SPI_Read(DEV_SPI_C722_CHANNEL,addr,&value);
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


