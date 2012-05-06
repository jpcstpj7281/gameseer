/*
 * protocol.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_


#define USER_MSGBASE  0x01


struct PUserLoginReq
{
	enum{uri=(1<<16|USER_MSGBASE)};
	//info["user"]
	//info["psw"]

};

struct PUserLoginRsp
{
	enum{uri=(2<<16|USER_MSGBASE)};
	//info["result"]
};


struct PUserPingReq
{
	enum{uri=(3<<16|USER_MSGBASE)};
	//info["ping"]
};

struct PUserPingRsp
{
	enum{uri=(4<<16|USER_MSGBASE)};
	//info["ping"]
};

struct PUserRegReq
{
    enum{uri=(5<<16|USER_MSGBASE)};
    //info["user"]
    //info["psw"]
};

struct PUserRegRsp
{
    enum{uri=(6<<16|USER_MSGBASE)};
    //info["user"]
    //info["psw"]
};

struct PUserSaveReq
{
    enum{uri=(7<<16|USER_MSGBASE)};
    //info["user"]
    //info["psw"]
};

struct PUserSaveRsp
{
    enum{uri=(8<<16|USER_MSGBASE)};
    //info["user"]
    //info["psw"]
};
struct PUserLoadReq
{
    enum{uri=(9<<16|USER_MSGBASE)};
    //info["user"]
    //info["psw"]
};

struct PUserLoadRsp
{
    enum{uri=(10<<16|USER_MSGBASE)};
    //info["user"]
    //info["psw"]
};
struct PUserOPReq
{
    enum{uri=(11<<16|USER_MSGBASE)};
    //info["user"]
    //info["psw"]
};
struct PUserOPRsp
{
    enum{uri=(12<<16|USER_MSGBASE)};
    //info["user"]
    //info["psw"]
};
#endif /* PROTOCOL_H_ */
