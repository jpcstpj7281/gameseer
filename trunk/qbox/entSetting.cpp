/*
 * entSetting.cpp
 *
 *  Created on: 2012-1-10
 *      Author: icecoffee
 */

#include "entSetting.h"
#include "common.h"
#include <iostream>
#include <sstream>

using namespace ent;
using namespace std;


EntSetting* EntSetting::m_instance = 0;
EntSetting::EntSetting()
:m_windowNum(0)
,m_DLPFanStatus(0)
{
	m_version = "1.0.0.1";

	m_ip = "192.168.1.190";


	for(int i=1;i<=6;i++)
	{
		setInputInfoFlg(i,USE_FLG_OFFLINE);
		setInputInfoType(i,VIDEO_TYPE_DEFAULT);
		setInputInfoSize(i,0,0,0);
	}

	for(int i=1;i<=4;i++)
	{
		setOutputInfoFlg(i,USE_FLG_OFFLINE);
		setOutputInfoType(i,VIDEO_TYPE_DEFAULT);
		setOutputInfoSize(i,0,0);
	}

	for(int i=1;i<5;i++)
	{
		setSlotStatusFlg(i,USE_FLG_OFFLINE);
		setSlotStatusType(i,VIDEO_TYPE_DEFAULT);

	}

	for(int i=1;i<=4;i++)
	{
		setOutputSwitch(i,1);
	}

//    TYPE_INPUT_SIZE_800_600_60 = 2,
//    TYPE_INPUT_SIZE_1024_768_60 = 3,
//    TYPE_INPUT_SIZE_1280_1024_60 = 4,
//    TYPE_INPUT_SIZE_1600_1200_60 = 5,
//    TYPE_INPUT_SIZE_1024_768_75 = 6,
//    TYPE_INPUT_SIZE_1280_1024_75 = 7,
//    TYPE_INPUT_SIZE_1440_900_60 = 8,
//    TYPE_INPUT_SIZE_1920_1080_60 = 9,
//    TYPE_INPUT_SIZE_1600_900_60 = 10,
//    TYPE_INPUT_SIZE_1280_960_60 = 11

	SignalInfo info;

	info.type = VIDEO_TYPE_CVBS;
	info.freq = 60;
	info.width = 702;
	info.height = 480;
	m_signalInfo[TYPE_INPUT_SIZE_702_480] = info;

	info.type = VIDEO_TYPE_CVBS;
	info.freq = 60;
	info.width = 720;
	info.height = 576;
	m_signalInfo[TYPE_INPUT_SIZE_720_576] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 60;
	info.width = 800;
	info.height = 600;
	m_signalInfo[TYPE_INPUT_SIZE_800_600_60] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 60;
	info.width = 1024;
	info.height = 768;
	m_signalInfo[TYPE_INPUT_SIZE_1024_768_60] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 60;
	info.width = 1280;
	info.height = 1024;
	m_signalInfo[TYPE_INPUT_SIZE_1280_1024_60] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 60;
	info.width = 1600;
	info.height = 1200;
	m_signalInfo[TYPE_INPUT_SIZE_1600_1200_60] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 75;
	info.width = 1024;
	info.height = 768;
	m_signalInfo[TYPE_INPUT_SIZE_1024_768_75] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 75;
	info.width = 1280;
	info.height = 1024;
	m_signalInfo[TYPE_INPUT_SIZE_1280_1024_75] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 60;
	info.width = 1440;
	info.height = 900;
	m_signalInfo[TYPE_INPUT_SIZE_1440_900_60] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 60;
	info.width = 1920;
	info.height = 1080;
	m_signalInfo[TYPE_INPUT_SIZE_1920_1080_60] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 60;
	info.width = 1600;
	info.height = 900;
	m_signalInfo[TYPE_INPUT_SIZE_1600_900_60] = info;

	info.type = VIDEO_TYPE_RGB;
	info.freq = 60;
	info.width = 1280;
	info.height = 960;
	m_signalInfo[TYPE_INPUT_SIZE_1280_960_60] = info;


}

EntSetting::~EntSetting()
{

}


EntSetting* EntSetting::Instance()
{
	if(m_instance == NULL)
	{
		m_instance = new EntSetting();
	}
	return m_instance;
}


void EntSetting::setInputInfoFlg(uint32_t chId,uint32_t iFlg)
{
	m_inputStatus[chId].useFlg = iFlg;
}

void EntSetting::setInputInfoType(uint32_t chId,string sType)
{
	m_inputStatus[chId].type = sType;
}

void EntSetting::setInputInfoSize(uint32_t chId,uint32_t width,uint32_t height,uint32_t freq)
{
	m_inputStatus[chId].width = width;
	m_inputStatus[chId].height = height;
	m_inputStatus[chId].freq = freq;
}

void EntSetting::setInputModel(uint32_t chId,uint32_t model)
{
	m_inputStatus[chId].model = model;

	setInputInfoSize(chId,m_signalInfo[model].width,m_signalInfo[model].height,m_signalInfo[model].freq);
	setInputInfoType(chId,m_signalInfo[model].type);

}

uint32_t EntSetting::getInputModel(uint32_t chId)
{
	return m_inputStatus[chId].model;
}

uint32_t EntSetting::getInputInfoFlg(uint32_t chId)
{
	return m_inputStatus[chId].useFlg;
}

string EntSetting::getInputInfoType(uint32_t chId)
{
	return m_inputStatus[chId].type;
}

void EntSetting::getInputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height,uint32_t &freq)
{
	width = m_inputStatus[chId].width;
	height = m_inputStatus[chId].height;
	freq = m_inputStatus[chId].freq;

}


void EntSetting::setOutputInfoFlg(uint32_t chId,uint32_t iFlg)
{
	m_outputStatus[chId].useFlg = iFlg;
}

void EntSetting::setOutputInfoType(uint32_t chId,string sType)
{
	m_outputStatus[chId].type = sType;
}


void EntSetting::setOutputInfoSize(uint32_t chId,uint32_t width,uint32_t height)
{
	m_outputStatus[chId].width = width;
	m_outputStatus[chId].height = height;

}


uint32_t EntSetting::getOutputInfoFlg(uint32_t chId)
{
	return m_outputStatus[chId].useFlg;
}

string EntSetting::getOutputInfoType(uint32_t chId)
{
	return m_outputStatus[chId].type;
}

void EntSetting::getOutputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height)
{
	width = m_outputStatus[chId].width;
	height = m_outputStatus[chId].height;
}


uint32_t EntSetting::getInputTotal()
{
	uint32_t total = 0;
	for(map<uint32_t,ChannelInfo>::iterator it = m_inputStatus.begin();it !=  m_inputStatus.end();it++)
	{
		if(it->second.useFlg == USE_FLG_ONLINE)
		{
			total++;
		}
	}


	return total;
}

uint32_t EntSetting::getOutputTotal()
{

	uint32_t total=0;

	for(map<uint32_t,ChannelInfo>::iterator it = m_outputStatus.begin();it !=  m_outputStatus.end();it++)
	{
		if(it->second.useFlg == USE_FLG_ONLINE)
		{
			total++;
		}
	}


	return total;

}

void EntSetting::setVersion(string version)
{
	m_version = version;
}


string EntSetting::getVersion()
{
	return m_version;
}


void EntSetting::setSysIp(string ip)
{
	m_ip = ip;
}


string EntSetting::getSysIp()
{
	return m_ip;
}

uint32_t EntSetting::getWindowsTotal()
{
	return m_windowInfo.size();
}


void EntSetting::getWindowsHandle(std::set<uint32_t> &handle)
{
	for(map<uint32_t,WindowInfo>::iterator it=m_windowInfo.begin();it!=m_windowInfo.end();it++)
	{
		handle.insert(it->first);
	}
}

bool EntSetting::getWindowsInfo(uint32_t out,uint32_t &winX,uint32_t &winY,uint32_t &width,uint32_t &height)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(out);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		winX = it->second.winX;
		winY = it->second.winY;
		width = it->second.width;
		height = it->second.height;
	}

	return true;
}

bool EntSetting::getWindowsInfo(uint32_t out,WindowInfo &info)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(out);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		info.winX = it->second.winX;
		info.winY = it->second.winY;
		info.width = it->second.width;
		info.height = it->second.height;
		info.channelIn = it->second.channelIn;
		info.channelOut = it->second.channelOut;
		info.layer = it->second.layer;
		info.showStatus = it->second.showStatus;



	}

	return true;
}

void EntSetting::setWindowInfo(uint32_t out,uint32_t winX,uint32_t winY,uint32_t width,uint32_t height)
{




	m_windowInfo[out].winX = winX;
	m_windowInfo[out].winY = winY;
	m_windowInfo[out].width = width;
	m_windowInfo[out].height = height;




}

bool EntSetting::delWindow(uint32_t winHandle)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo.erase(winHandle);
		m_windowNum--;
	}
	return true;
}


bool EntSetting::setLayer(uint32_t winHandle,uint32_t layer)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].layer = layer;
	}
	return true;
}


bool EntSetting::getLayer(uint32_t winHandle,uint32_t &layer)
{

	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		layer = m_windowInfo[winHandle].layer;
	}

	return true;

}

bool EntSetting::setOutput(uint32_t winHandle,uint32_t channelOut)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].channelOut = channelOut;
	}
	return true;
}


bool EntSetting::getOutput(uint32_t winHandle,uint32_t &channelOut)
{

	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		channelOut = m_windowInfo[winHandle].channelOut;
	}

	return true;

}

bool EntSetting::setInput(uint32_t out,uint32_t channelIn)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(out);
	if(it == m_windowInfo.end())
	{
		test_msg("EntSetting  setInput false winHandle=%d not find!",out);
		return false;
	}
	else
	{
		m_windowInfo[out].channelIn = channelIn;
	}
	return true;
}


bool EntSetting::getInput(uint32_t out,uint32_t &channelIn)
{

	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(out);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		channelIn = m_windowInfo[out].channelIn;
	}

	return true;

}

bool EntSetting::setShowStatus(uint32_t winHandle,uint32_t status)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].showStatus = status;
	}
	return true;
}


bool EntSetting::getShowStatus(uint32_t winHandle,uint32_t &status)
{

	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		status = m_windowInfo[winHandle].showStatus;
	}

	return true;

}


bool EntSetting::setWindowPosition(uint32_t winHandle,uint32_t winX,uint32_t winY,uint32_t width,uint32_t height)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].winX = winX;
		m_windowInfo[winHandle].winY = winY;
		m_windowInfo[winHandle].width = width;
		m_windowInfo[winHandle].height = height;

	}

	return true;
}


void EntSetting::setSlotStatusFlg(uint32_t slot,uint32_t iFlg)
{
	m_slotStatus[slot].onlineFlg = iFlg;
}

void EntSetting::setSlotStatusType(uint32_t slot,string sType)
{
	m_slotStatus[slot].type = sType;
}

uint32_t EntSetting::getSlotStatusFlg(uint32_t slot)
{
	return m_slotStatus[slot].onlineFlg;
}

string EntSetting::getSlotStatusType(uint32_t slot)
{
	return m_slotStatus[slot].type;
}

uint32_t EntSetting::getDLPFanStatus()
{
	return m_DLPFanStatus;
}

void EntSetting::setDLPFanStatus(uint32_t status)
{
	m_DLPFanStatus = status;
}



void EntSetting::dumpAll()
{
	test_msg("Dump  inputStatus");
	for(map<uint32_t,ChannelInfo>::iterator it=m_inputStatus.begin();it!=m_inputStatus.end();it++)
	{
		test_msg("input  signal=%d,type=%s,useFlg=%d,width=%d,height=%d,model=%d",it->first,it->second.type.c_str(),it->second.useFlg,it->second.width,it->second.height,it->second.model);
	}

	test_msg("Dump  outputStatus");
	for(map<uint32_t,ChannelInfo>::iterator it=m_outputStatus.begin();it!=m_outputStatus.end();it++)
	{

	}

	test_msg("Dump  slotStatus");
	for(map<uint32_t,BroadInfo>::iterator it=m_slotStatus.begin();it!=m_slotStatus.end();it++)
	{

	}

}


void EntSetting::setOutputSwitch(uint32_t out,uint32_t inputSignal)
{
	m_outputSwitch[out] = inputSignal;
}

uint32_t EntSetting::getOutputSwitch(uint32_t out)
{
	return m_outputSwitch[out];
}

string EntSetting::dumpModelInfo(uint32_t model)
{
	stringstream ss;

	ss<<"Signal:"<<m_signalInfo[model].width<<"X"<<m_signalInfo[model].height<<"@"<<m_signalInfo[model].freq<<endl;

	return ss.str();
}

