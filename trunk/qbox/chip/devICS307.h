/*
 * devC772.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _DEV_ICS307_H_
#define _DEV_ICS307_H_

#include <map>
#include <list>

#include "devBus.h"

using namespace std;

namespace chip
{

#define ICS307_OTHER_VAL(x)	((unsigned long)(x & 0x001F) << 19)		/*C1 C0 TTL F1 F0*/
#define ICS307_OD_VAL(x)	((unsigned long)(x & 0x0007) << 16)		/*S2-S0*/
#define	ICS307_VDW_VAL(x)	((unsigned long)(x & 0x01FF) << 7)		/*V8-V0*/
#define ICS307_RDW_VAL(x)	((unsigned long)(x & 0x007F))			/*R6-R0*/

enum FREQ_TYPE
{
	ICS307_FREQUENCY_32500KHZ = 1,
	ICS307_FREQUENCY_54000KHZ,
	ICS307_FREQUENCY_74250KHZ,
	ICS307_FREQUENCY_81000KHZ,
	ICS307_FREQUENCY_60875KHZ,
    ICS307_FREQUENCY_42750KHZ,
    ICS307_FREQUENCY_35625KHZ,
    ICS307_FREQUENCY_65000KHZ,
    ICS307_FREQUENCY_108000KHZ,
    ICS307_FREQUENCY_148500KHZ,
    ICS307_FREQUENCY_162000KHZ,
    ICS307_FREQUENCY_121750KHZ,
    ICS307_FREQUENCY_85500KHZ,
    ICS307_FREQUENCY_71250KHZ,
    ICS307_FREQUENCY_154000KHZ,
};


class DriverChipICS307
{

public:
	DriverChipICS307();
	virtual ~DriverChipICS307();

	void setPOCLK(uint32_t wVal);



private:




};

};

#endif /* USER_H_ */
