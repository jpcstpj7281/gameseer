/*
 * pstatus.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef PDLP_H_
#define PDLP_H_


#define DLP_MSGBASE  32


struct PDLPCTRLReq
{
	enum{uri=(DLP_MSGBASE<<16|1)};

};

struct PDLPCTRLRsp
{
	enum{uri=(DLP_MSGBASE<<16|2)};

};

struct PDLPReadReq
{
	enum{uri=(DLP_MSGBASE<<16|3)};

};

struct PDLPReadRsp
{
	enum{uri=(DLP_MSGBASE<<16|4)};

};


#endif /* PROTOCOL_H_ */
