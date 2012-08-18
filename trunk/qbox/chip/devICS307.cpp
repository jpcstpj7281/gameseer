/*
 * devFPGA.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "devICS307.h"


using namespace chip;


DriverChipICS307::DriverChipICS307()
{

}

DriverChipICS307::~DriverChipICS307()
{

}


void DriverChipICS307::setPOCLK(uint32_t sFreq)
{
	unsigned long  val=0;

	switch(sFreq)
	{
		case ICS307_FREQUENCY_32500KHZ:
			val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x03) | ICS307_VDW_VAL(0x12) | ICS307_RDW_VAL(0x02);
			break;

		case ICS307_FREQUENCY_54000KHZ:
			val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x03) | ICS307_VDW_VAL(0x2E) | ICS307_RDW_VAL(0x03);
			break;

        case ICS307_FREQUENCY_74250KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x03) | ICS307_VDW_VAL(0x121) | ICS307_RDW_VAL(0x12);
            break;

		case ICS307_FREQUENCY_81000KHZ:
			val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x03) | ICS307_VDW_VAL(0x49) | ICS307_RDW_VAL(0x03);
			break;

        case ICS307_FREQUENCY_60875KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x04) | ICS307_VDW_VAL(0x1DF) | ICS307_RDW_VAL(0x1E);
            break;

        case ICS307_FREQUENCY_42750KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x02) | ICS307_VDW_VAL(0xA3) | ICS307_RDW_VAL(0x08);
            break;

        case ICS307_FREQUENCY_35625KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x00) | ICS307_VDW_VAL(0x115) | ICS307_RDW_VAL(0x0E);
            break;

        case ICS307_FREQUENCY_65000KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x04) | ICS307_VDW_VAL(0x39) | ICS307_RDW_VAL(0x02);
            break;

        case ICS307_FREQUENCY_108000KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x06) | ICS307_VDW_VAL(0x49) | ICS307_RDW_VAL(0x03);
            break;

        case ICS307_FREQUENCY_148500KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x01) | ICS307_VDW_VAL(0x121) | ICS307_RDW_VAL(0x12);
            break;

        case ICS307_FREQUENCY_162000KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x01) | ICS307_VDW_VAL(0x49) | ICS307_RDW_VAL(0x03);
            break;

        case ICS307_FREQUENCY_121750KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x01) | ICS307_VDW_VAL(0x1DF) | ICS307_RDW_VAL(0x26);
            break;

        case ICS307_FREQUENCY_85500KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x03) | ICS307_VDW_VAL(0xA3) | ICS307_RDW_VAL(0x08);
            break;

        case ICS307_FREQUENCY_71250KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x04) | ICS307_VDW_VAL(0x115) | ICS307_RDW_VAL(0x0E);
            break;

        case ICS307_FREQUENCY_154000KHZ:
            val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x01) | ICS307_VDW_VAL(0x45) | ICS307_RDW_VAL(0x03);
            break;

        default:
			break;
	}

	printf("ics307=%x\n");
	ICS307_config(val);
}

