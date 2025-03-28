/*
 * devC772.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _DEV_BUS_H_
#define _DEV_BUS_H_

#include <map>
#include <list>
#include "dev.h"

using namespace std;

namespace chip
{




class I2CBus
{

public:
	I2CBus();
	virtual ~I2CBus();

	void dev_5160_WriteMult(uint32_t chn,list<map<uint8_t,uint8_t> > value);
	void I2C_5160_Write(uint32_t chn,uint8_t addr,uint8_t value);
	void I2C_5160_Read(uint32_t chn,uint8_t addr,uint8_t &value);



private:


};

class SPIBus
{

public:
	SPIBus();
	virtual ~SPIBus();

	void dev_SPI_WriteMult(uint32_t chn,list<map<uint8_t,uint8_t> > value);
	void SPI_Write(uint32_t chn,uint8_t addr,uint8_t value);

	void SPI_Read(uint32_t chn,uint8_t addr,uint8_t &value);

private:


};

class FPGABus
{

public:
	FPGABus();
	virtual ~FPGABus();


	void FPGA_Write(uint16_t addr,uint16_t value);

	void FPGA_Read(uint16_t addr,uint16_t &value);

private:


};

};

#endif /* USER_H_ */
