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
#include "dev.h"


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
			dev_I2C_Write(chn,chipType,itMap->first,itMap->second);
		}
	}

}

void I2CBus::dev_I2C_Write(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t value)
{

}

void I2CBus::dev_I2C_Read(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t &value)
{

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
	printf("dev_SPI_Write\n");
	dev_SPI_Write(DEV_SPI_C753_CHANNEL,addr,value);
}

void SPIBus::SPI_Read(uint32_t chn,uint8_t addr,uint8_t &value)
{
	printf("dev_SPI_Read\n");
	dev_SPI_Read(DEV_SPI_C753_CHANNEL,addr,&value);
}


FPGABus::FPGABus()
{

}

FPGABus::~FPGABus()
{

}


void FPGABus::dev_FPGA_Write(uint32_t chn,uint16_t addr,uint16_t value)
{

}

void FPGABus::dev_FPGA_Read(uint32_t chn,uint16_t addr,uint16_t &value)
{

}


