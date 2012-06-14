/*
 * entSetting.cpp
 *
 *  Created on: 2012-1-10
 *      Author: icecoffee
 */

#include "entSetting.h"


using namespace ent;



EntSetting* EntSetting::m_instance = 0;
EntSetting::EntSetting()
{
	m_version = "1.0.0.1";
	for(int i=0;i<6;i++)
	{
		setInputInfoFlg(i,USE_FLG_OFFLINE);
		setInputInfoType(i,VIDEO_TYPE_DEFAULT);
		setInputInfoSize(i,0,0);
	}

	for(int i=0;i<3;i++)
	{
		setOutputInfoFlg(i,USE_FLG_OFFLINE);
		setOutputInfoType(i,VIDEO_TYPE_DEFAULT);
		setOutputInfoSize(i,0,0);
	}


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
	m_inputType[chId].useFlg = iFlg;
}

void EntSetting::setInputInfoType(uint32_t chId,string sType)
{
	m_inputType[chId].type = sType;
}

void EntSetting::setInputInfoSize(uint32_t chId,uint32_t width,uint32_t height)
{
	m_inputType[chId].width = width;
	m_inputType[chId].height = height;
}


uint32_t EntSetting::getInputInfoFlg(uint32_t chId)
{
	return m_inputType[chId].useFlg;
}

string EntSetting::getInputInfoType(uint32_t chId)
{
	return m_inputType[chId].type;
}

void EntSetting::getInputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height)
{
	width = m_inputType[chId].width;
	height = m_inputType[chId].height;

}


void EntSetting::setOutputInfoFlg(uint32_t chId,uint32_t iFlg)
{
	m_outputType[chId].useFlg = iFlg;
}

void EntSetting::setOutputInfoType(uint32_t chId,string sType)
{
	m_outputType[chId].type = sType;
}


void EntSetting::setOutputInfoSize(uint32_t chId,uint32_t width,uint32_t height)
{
	m_outputType[chId].width = width;
	m_outputType[chId].height = height;
}


uint32_t EntSetting::getOutputInfoFlg(uint32_t chId)
{
	return m_outputType[chId].useFlg;
}

string EntSetting::getOutputInfoType(uint32_t chId)
{
	return m_outputType[chId].type;
}

void EntSetting::getOutputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height)
{
	width = m_outputType[chId].width;
	height = m_outputType[chId].height;
}


uint32_t EntSetting::getInputTotal()
{
	uint32_t total = 0;
	for(map<uint32_t,channelInfo>::iterator it = m_inputType.begin();it !=  m_inputType.end();it++)
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

	for(map<uint32_t,channelInfo>::iterator it = m_outputType.begin();it !=  m_outputType.end();it++)
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
