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

using namespace std;

namespace ent
{

#define USE_FLG_OFFLINE			0
#define USE_FLG_ONLINE			1

const string VIDEO_TYPE_DEFAULT	 = 	"default";
const string VIDEO_TYPE_CVBS	 = 	"cvbs";
const string VIDEO_TYPE_RGB		 = 	"rgb";

struct channelInfo
{
	uint32_t useFlg;
	uint32_t width;
	uint32_t height;
	string   type;

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



protected:

	uint32_t m_type;
private:

	string m_version;
	map<uint32_t,channelInfo> m_inputType;
	map<uint32_t,channelInfo> m_outputType;



};

};


#endif /* MSGHANDLER_H_ */
