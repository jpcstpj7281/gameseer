/*
 * entSetting.cpp
 *
 *  Created on: 2012-1-10
 *      Author: icecoffee
 */

#include "entSetting.h"
#include "common.h"

using namespace ent;



EntSetting* EntSetting::m_instance = 0;
EntSetting::EntSetting()
:m_windowNum(0)
{
	m_version = "1.0.0.1";

	m_ip = "192.168.1.190";


	for(int i=1;i<=6;i++)
	{
		setInputInfoFlg(i,USE_FLG_OFFLINE);
		setInputInfoType(i,VIDEO_TYPE_DEFAULT);
		setInputInfoSize(i,0,0);
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


	//test
//	setInputInfoFlg(6,USE_FLG_ONLINE);
//	setInputInfoType(6,VIDEO_TYPE_RGB);
//	setInputInfoSize(6,1024,768);
//
//	setChnSignalInput(3,6);

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

void EntSetting::setInputInfoSize(uint32_t chId,uint32_t width,uint32_t height)
{
	m_inputStatus[chId].width = width;
	m_inputStatus[chId].height = height;
}


uint32_t EntSetting::getInputInfoFlg(uint32_t chId)
{
	return m_inputStatus[chId].useFlg;
}

string EntSetting::getInputInfoType(uint32_t chId)
{
	return m_inputStatus[chId].type;
}

void EntSetting::getInputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height)
{
	width = m_inputStatus[chId].width;
	height = m_inputStatus[chId].height;

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

void EntSetting::setWindowInfo(uint32_t out,uint32_t winX,uint32_t winY,uint32_t width,uint32_t height)
{


	WindowInfo info;
	info.winX = winX;
	info.winY = winY;
	info.width = width;
	info.height = height;

	m_windowInfo.insert(make_pair(out,info));



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



void EntSetting::dumpAll()
{
	test_msg("Dump  inputStatus");
	for(map<uint32_t,ChannelInfo>::iterator it=m_inputStatus.begin();it!=m_inputStatus.end();it++)
	{
		test_msg("input  signal=%d,type=%s,useFlg=%d,width=%d,height=%d",it->first,it->second.type.c_str(),it->second.useFlg,it->second.width,it->second.height);
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


