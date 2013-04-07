/*
 * pbgtest.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef PBGTEST_H_
#define PBGTEST_H_


#define BGTEST_MSGBASE  10


struct PWriteI2CReq
{
	enum{uri=(BGTEST_MSGBASE<<16|1)};
	//chn->??? | addr->???|value->???? //I2C 测试写入
};

struct PWriteI2CRsp
{
	enum{uri=(BGTEST_MSGBASE<<16|2)};
	//error->??? //I2C结果
};


struct PReadI2CReq
{
	enum{uri=(BGTEST_MSGBASE<<16|3)};
	//chn->??? | addr->??? //I2C 测试读取

};

struct PReadI2CRsp
{
	enum{uri=(BGTEST_MSGBASE<<16|4)};
	//error->???|value-> //I2C
};

struct PWriteSPIReq
{
	enum{uri=(BGTEST_MSGBASE<<16|5)};
	//chn->??? | addr->???|value->???? //SPI 测试写入
};

struct PWriteSPIRsp
{
	enum{uri=(BGTEST_MSGBASE<<16|6)};
	//error->??? //SPI结果
};


struct PReadSPIReq
{
	enum{uri=(BGTEST_MSGBASE<<16|7)};
	//chn->??? | addr->??? //SPI 测试读取

};

struct PReadSPIRsp
{
	enum{uri=(BGTEST_MSGBASE<<16|8)};
	//error->???|value-> //SPI
};


#endif /* PROTOCOL_H_ */
