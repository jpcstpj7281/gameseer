/*
 * entSetting.h
 *
 *  Created on: 2012-1-10
 *      Author: icecoffee
 */

#ifndef ENTSETTING_H_
#define ENTSETTING_H_

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

namespace ent
{


struct BroadInfo
{
	uint32_t onlineFlg;
	string   type;

	BroadInfo& operator = (const BroadInfo& info)
	{
		if (this == &info)
			return *this;

		onlineFlg = info.onlineFlg;
		type = info.type;


		return *this;
	}
};


struct ChannelInfo
{
	uint32_t useFlg;
	uint32_t width;
	uint32_t height;
	string   type;

	ChannelInfo& operator = (const ChannelInfo& info)
	{
		if (this == &info)
			return *this;

		useFlg = info.useFlg;
		width = info.width;
		height = info.height;
		type = info.type;


		return *this;
	}


};

struct WindowInfo
{
	uint32_t winX;
	uint32_t winY;
	uint32_t width;
	uint32_t height;
	uint32_t channelIn;
	uint32_t channelOut;
	uint32_t layer;
	uint32_t showStatus;

	WindowInfo& operator = (const WindowInfo& info)
	{
		if (this == &info)
			return *this;


		winX = info.winX;
		winY = info.winY;
		width = info.width;
		height = info.height;
		channelIn = info.channelIn;
		channelOut = info.channelOut;
		layer = info.layer;

		return *this;
	}


};


class EntSetting
{

public:
	EntSetting();
	virtual ~EntSetting();

	static EntSetting* m_instance;
	static EntSetting* Instance();


	void setInputInfoFlg(uint32_t chId,uint32_t iFlg);
	void setInputInfoType(uint32_t chId,string sType);
	void setInputInfoSize(uint32_t chId,uint32_t width,uint32_t height);
	uint32_t getInputInfoFlg(uint32_t chId);
	string getInputInfoType(uint32_t chId);
	void getInputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height);
	uint32_t getInputTotal();

	void setOutputInfoFlg(uint32_t chId,uint32_t iFlg);
	void setOutputInfoType(uint32_t chId,string sType);
	void setOutputInfoSize(uint32_t chId,uint32_t width,uint32_t height);
	uint32_t getOutputInfoFlg(uint32_t chId);
	string getOutputInfoType(uint32_t chId);
	void getOutputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height);
	uint32_t getOutputTotal();

	void setVersion(string version);
	string getVersion();

	void setSysIp(string ip);
	string getSysIp();

	uint32_t getWindowsTotal();
	void getWindowsHandle(std::set<uint32_t> &handle);
	bool getWindowsInfo(uint32_t out,uint32_t &winX,uint32_t &winY,uint32_t &width,uint32_t &height);
	bool getWindowsInfo(uint32_t out,WindowInfo &info);

	void setWindowInfo(uint32_t out,uint32_t winX,uint32_t winY,uint32_t width,uint32_t height);
	bool delWindow(uint32_t winHandle);

	bool setLayer(uint32_t winHandle,uint32_t layer);
	bool getLayer(uint32_t winHandle,uint32_t &layer);

	bool setOutput(uint32_t winHandle,uint32_t channelOut);
	bool getOutput(uint32_t winHandle,uint32_t &channelOut);

	bool setInput(uint32_t winHandle,uint32_t channelIn);
	bool getInput(uint32_t winHandle,uint32_t &channelIn);

	bool setShowStatus(uint32_t winHandle,uint32_t status);
	bool getShowStatus(uint32_t winHandle,uint32_t &status);

	bool setWindowPosition(uint32_t winHandle,uint32_t winX,uint32_t winY,uint32_t width,uint32_t height);

	void setSlotStatusFlg(uint32_t slot,uint32_t iFlg);
	void setSlotStatusType(uint32_t slot,string sType);
	uint32_t getSlotStatusFlg(uint32_t slot);
	string getSlotStatusType(uint32_t slot);


	void dumpAll();

protected:

	uint32_t m_type;
private:

	string m_version;
	string m_ip;

	map<uint32_t,ChannelInfo> m_inputStatus;
	map<uint32_t,ChannelInfo> m_outputStatus;
	map<uint32_t,BroadInfo> m_slotStatus;

	uint32_t m_windowNum;
	map<uint32_t,WindowInfo> m_windowInfo;

};

};


#endif /* MSGHANDLER_H_ */
