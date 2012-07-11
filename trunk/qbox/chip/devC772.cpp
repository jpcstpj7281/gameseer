/*
 * devC772.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "devC772.h"
#include "CPC772Addr.h"

using namespace chip;


DriverChip772::DriverChip772()
{

}

DriverChip772::~DriverChip772()
{

}



void DriverChip772::dev_C772_Set480(list<map<uint8_t,uint8_t> > &value)
{

	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR1] = 0x58;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR1] = 0x0b;
	bank0[CP_IP00C772_B0_OHSCT_ADDR] = 0x1e;
	bank0[CP_IP00C772_B0_OVSCT_ADDR] = 0x05;
	bank0[CP_IP00C772_B0_OACTHST_ADDR1] = 0x7b;
	bank0[CP_IP00C772_B0_OACTHST_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OACTVST_ADDR1] = 0x24;
	bank0[CP_IP00C772_B0_OACTVST_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OACTHW_ADDR1] = 0xc6;
	bank0[CP_IP00C772_B0_OACTHW_ADDR2] = 0x02;
	bank0[CP_IP00C772_B0_OACTVW_ADDR1] = 0xe7;
	bank0[CP_IP00C772_B0_OACTVW_ADDR2] = 0x01;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR1] = 0xea;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR2] = 0x01;
	bank0[CP_IP00C772_B0_OIMGCT_ADDR] = 0x00;

	value.push_back(bank0);

	map<uint8_t,uint8_t> bank1;
	bank1[CP_IP00C772_RGBNK_ADDR] = 0x01;
	bank1[CP_IP00C772_B1_IACTHST_ADDR1] = 0x49;
	bank1[CP_IP00C772_B1_IACTHST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTHW_ADDR1] = 0xd0;
	bank1[CP_IP00C772_B1_IACTHW_ADDR2] = 0x02;
	bank1[CP_IP00C772_B1_IACTVST_ADDR1] = 0x12;
	bank1[CP_IP00C772_B1_IACTVST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTVW_ADDR1] = 0xe4;
	bank1[CP_IP00C772_B1_IACTVW_ADDR2] = 0x01;


	value.push_back(bank1);


	map<uint8_t,uint8_t> bank2;
	bank2[CP_IP00C772_RGBNK_ADDR] = 0x02;
	bank2[CP_IP00C772_B2_OADJCT_ADDR] = 0x08;
	bank2[CP_IP00C772_B2_PDCTRL_ADDR] = 0xfd;
	bank2[CP_IP00C772_B2_PDMV22TH_ADDR] = 0x08;
	bank2[CP_IP00C772_B2_PD23RSTTH_ADDR] = 0x3c;
	bank2[CP_IP00C772_B2_PDSQTH_ADDR] = 0x41;
	bank2[CP_IP00C772_B2_MVACCSEL_ADDR] = 0x35;
	bank2[CP_IP00C772_B2_PDACTSEL_ADDR] = 0x03;
	bank2[CP_IP00C772_B2_PD22RSTCT_ADDR] = 0x61;
	bank2[CP_IP00C772_B2_PDMV23TH_ADDR] = 0x14;

	value.push_back(bank2);

	map<uint8_t,uint8_t> bank3;
	bank3[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank3[CP_IP00C772_MEMCT_ADDR] = 0x29;

	value.push_back(bank3);



}

void dev_C772_Set576(list<map<uint8_t,uint8_t> > &value)
{
	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR1] = 0x5e;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR1] = 0x6f;
	bank0[CP_IP00C772_B0_OHSCT_ADDR] = 0x1f;
	bank0[CP_IP00C772_B0_OVSCT_ADDR] = 0x04;
	bank0[CP_IP00C772_B0_OACTHST_ADDR1] = 0x82;
	bank0[CP_IP00C772_B0_OACTHST_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OACTVST_ADDR1] = 0x2a;
	bank0[CP_IP00C772_B0_OACTVST_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OACTHW_ADDR1] = 0xbc;
	bank0[CP_IP00C772_B0_OACTHW_ADDR2] = 0x02;
	bank0[CP_IP00C772_B0_OACTVW_ADDR1] = 0x43;
	bank0[CP_IP00C772_B0_OACTVW_ADDR2] = 0x02;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR1] = 0xea;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR2] = 0x01;
	bank0[CP_IP00C772_B0_OIMGCT_ADDR] = 0x00;

	value.push_back(bank0);

	map<uint8_t,uint8_t> bank1;
	bank1[CP_IP00C772_RGBNK_ADDR] = 0x01;
	bank1[CP_IP00C772_B1_IACTHST_ADDR1] = 0x51;
	bank1[CP_IP00C772_B1_IACTHST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTHW_ADDR1] = 0xd0;
	bank1[CP_IP00C772_B1_IACTHW_ADDR2] = 0x02;
	bank1[CP_IP00C772_B1_IACTVST_ADDR1] = 0x17;
	bank1[CP_IP00C772_B1_IACTVST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTVW_ADDR1] = 0x40;
	bank1[CP_IP00C772_B1_IACTVW_ADDR2] = 0x02;




	value.push_back(bank1);


	map<uint8_t,uint8_t> bank2;
	bank2[CP_IP00C772_RGBNK_ADDR] = 0x02;
	bank2[CP_IP00C772_B2_OADJCT_ADDR] = 0x09;
	bank2[CP_IP00C772_B2_PDCTRL_ADDR] = 0x7d;
	bank2[CP_IP00C772_B2_PDMV22TH_ADDR] = 0x0c;
	bank2[CP_IP00C772_B2_PD23RSTTH_ADDR] = 0x40;
	bank2[CP_IP00C772_B2_PDSQTH_ADDR] = 0x41;
	bank2[CP_IP00C772_B2_MVACCSEL_ADDR] = 0x45;
	bank2[CP_IP00C772_B2_PDACTSEL_ADDR] = 0x03;
	bank2[CP_IP00C772_B2_PD22RSTCT_ADDR] = 0x21;
	bank2[CP_IP00C772_B2_PDMV23TH_ADDR] = 0x16;


	value.push_back(bank2);

	map<uint8_t,uint8_t> bank3;
	bank3[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank3[CP_IP00C772_MEMCT_ADDR] = 0x29;

	value.push_back(bank3);




}

void DriverChip772::dev_InitIP00c772(list<map<uint8_t,uint8_t> > &value)
{
	map<uint8_t,uint8_t> bank;

	bank[CP_IP00C772_RGBNK_ADDR] = 0x03;
	bank[CP_IP00C772_RTCT_ADDR] = 	0x00;
	bank[CP_IP00C772_MISC_ADDR] = 	0x08;
	bank[CP_IP00C772_MEMCT_ADDR] = 0x29;
	bank[CP_IP00C772_RSTCT_ADDR] = 0x00;

	value.push_back(bank);


	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	bank0[CP_IP00C772_B0_OSYCT_ADDR] = 		0x41;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR1] =   	0x5e;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR2] =  	0x03;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR1] = 	0x6f;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR2] =	0x02;
	bank0[CP_IP00C772_B0_OHSCT_ADDR]   =   	0x1e;
	bank0[CP_IP00C772_B0_OVSCT_ADDR]   =   	0x05;
	bank0[CP_IP00C772_B0_SYRDLY_ADDR]  =   	0x20;
//	bank0[CP_IP00C772_B0_OVCYCLMIN_ADDR1] =   	0x00;
//	bank0[CP_IP00C772_B0_OVCYCLMIN_ADDR2] =   	0x00;
	bank0[CP_IP00C772_B0_OSWP_ADDR]      =   	0x00;
	bank0[CP_IP00C772_B0_OACTHST_ADDR1]   =   	0x79;
	bank0[CP_IP00C772_B0_OACTHST_ADDR2]   =   	0x00;
	bank0[CP_IP00C772_B0_OACTHW_ADDR1]    =   	0xd0;
	bank0[CP_IP00C772_B0_OACTHW_ADDR2]    =   	0x02;
	bank0[CP_IP00C772_B0_OACTVST_ADDR1]   =   	0x28;
	bank0[CP_IP00C772_B0_OACTVST_ADDR2]   =   	0x00;
	bank0[CP_IP00C772_B0_OACTVW_ADDR1]    =   	0xe3;
	bank0[CP_IP00C772_B0_OACTVW_ADDR2]    =   	0x01;

//	bank0[CP_IP00C772_B0_OAOI0HST_ADDR]   =   	0x00;
//	bank0[CP_IP00C772_B0_OAOI0HEND_ADDR]  =   	0x00;
//	bank0[CP_IP00C772_B0_OAOI0VST_ADDR]   =   	0x00;
//	bank0[CP_IP00C772_B0_OAOI0VEND_ADDR]  =   	0x00;
//	bank0[CP_IP00C772_B0_OAOI1HST_ADDR]   =   	0x00;
//	bank0[CP_IP00C772_B0_OAOI1HEND_ADDR]  =   	0x00;
//	bank0[CP_IP00C772_B0_OAOI1VST_ADDR]   =   	0x00;
//	bank0[CP_IP00C772_B0_OAOI1VEND_ADDR]  =   	0x00;

	bank0[CP_IP00C772_B0_OFILL_RED_ADDR]  =   	0x00;
	bank0[CP_IP00C772_B0_OFILL_GREEN_ADDR]  =   0x00;
	bank0[CP_IP00C772_B0_OFILL_BLUE_ADDR]  =   	0xff;

//	bank0[CP_IP00C772_B0_OBKGD0_ADDR]  =   	0x00;
//	bank0[CP_IP00C772_B0_OBKGD1_ADDR]  =   	0x00;

	bank0[CP_IP00C772_B0_OIMGCT_ADDR]  =   	0x00;
	bank0[CP_IP00C772_B0_OCCFTR_ADDR1]  =   0x9d;
	bank0[CP_IP00C772_B0_OCCFTR_ADDR2]  =   0x05;
	bank0[CP_IP00C772_B0_OCCFTB_ADDR1]  =   0x18;
	bank0[CP_IP00C772_B0_OCCFTB_ADDR2]  =   0x27;
	bank0[CP_IP00C772_B0_OCCFTGR_ADDR1]  =   0x25;
	bank0[CP_IP00C772_B0_OCCFTGR_ADDR2]  =   0x1d;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR1]  =   0xea;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR2]  =   0x01;

//	bank0[CP_IP00C772_B0_OCCFTRB_ADDR1]  =   0x11;
//	bank0[CP_IP00C772_B0_OCCFTRB_ADDR2]  =   0x05;
//	bank0[CP_IP00C772_B0_OCCFTBR_ADDR1]  =   0x05;
//	bank0[CP_IP00C772_B0_OCCFTBR_ADDR2]  =   0x05;
//	bank0[CP_IP00C772_B0_BGCT_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GAINR_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GAING_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GAINB_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_BIASR_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_BIASG_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_BIASB_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GAIN2R_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GAIN2G_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GAIN2B_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_BIAS2R_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_BIAS2G_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_BIAS2B_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GMCT_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GMBNKSEL_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GMAD_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_GMDT_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_ERDFCT_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_ACTCT_ADDR]  =   0x05;
//	bank0[CP_IP00C772_B0_HISTGRAMCT_ADDR]  =   0x05;

	bank0[CP_IP00C772_B0_POCLKOCT_ADDR]  =   0x11;
	bank0[CP_IP00C772_B0_POPLLCT_ADDR]  =   0x01;
	bank0[CP_IP00C772_B0_POREFDIV_ADDR]  =   0x02;
	bank0[CP_IP00C772_B0_POFBDIV_ADDR]  =   0x07;

	bank0[CP_IP00C772_B0_GIO1SEL_ADDR]  =   0x03;
//	bank0[CP_IP00C772_B0_GIO1DATA_ADDR]  =   0x05;

	value.push_back(bank0);


	map<uint8_t,uint8_t> bank1;
	bank1[CP_IP00C772_RGBNK_ADDR] = 0x01;
	bank1[CP_IP00C772_B1_IIMGCT_ADDR] = 0x41;
	bank1[CP_IP00C772_B1_ISYCT_ADDR] = 0x02;
	bank1[CP_IP00C772_B1_HVPHMSR_ADDR] = 0x00;
	bank1[CP_IP00C772_B1_IVLNDLY_ADDR1] = 0x00;
	bank1[CP_IP00C772_B1_IVLNDLY_ADDR2] = 0x01;
	bank1[CP_IP00C772_B1_IVSKDLY_ADDR1] = 0x01;
	bank1[CP_IP00C772_B1_IVSKDLY_ADDR2] = 0x01;
	bank1[CP_IP00C772_B1_IHSKDLY_ADDR1] = 0x01;
	bank1[CP_IP00C772_B1_IHSKDLY_ADDR2] = 0x01;
	bank1[CP_IP00C772_B1_AUTOFLD_ADDR] = 0x80;
	bank1[CP_IP00C772_B1_IACTHST_ADDR1] = 0x4e;
	bank1[CP_IP00C772_B1_IACTHST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTHW_ADDR1] = 0xd0;
	bank1[CP_IP00C772_B1_IACTHW_ADDR2] = 0x02;
	bank1[CP_IP00C772_B1_IACTVST_ADDR1] = 0x14;
	bank1[CP_IP00C772_B1_IACTVST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTVW_ADDR1] = 0xf3;
	bank1[CP_IP00C772_B1_IACTVW_ADDR2] = 0x00;

	value.push_back(bank1);


	map<uint8_t,uint8_t> bank2;
	bank1[CP_IP00C772_RGBNK_ADDR] = 0x02;

	bank2[CP_IP00C772_B2_TMPPXNRCT_ADDR]=0x03;
	bank2[CP_IP00C772_B2_TPXNRTH1_ADDR]=0x31;
	bank2[CP_IP00C772_B2_TPXNRTH2_ADDR]=0x75;
	bank2[CP_IP00C772_B2_TPXNRTH3_ADDR]=0xb9;
	bank2[CP_IP00C772_B2_TPXNRTH4_ADDR]=0xfd;
	bank2[CP_IP00C772_B2_TPXNRCF1_ADDR]=0x10;
	bank2[CP_IP00C772_B2_TPXNRCF2_ADDR]=0x12;
	bank2[CP_IP00C772_B2_TPXNRCF3_ADDR]=0x14;
	bank2[CP_IP00C772_B2_TPXNRCF4_ADDR]=0x16;
	bank2[CP_IP00C772_B2_TPXNRCF5_ADDR]=0x18;
	bank2[CP_IP00C772_B2_TPXNRCF6_ADDR]=0x1a;
	bank2[CP_IP00C772_B2_TPXNRCF7_ADDR]=0x1c;
	bank2[CP_IP00C772_B2_TPXNRCF8_ADDR]=0x1f;
	bank2[CP_IP00C772_B2_HVPXNRCT_ADDR]=0x00;
	bank2[CP_IP00C772_B2_VPXNRCF1_ADDR]=0x00;
	bank2[CP_IP00C772_B2_VPXNRCF2_ADDR]=0x00;
	bank2[CP_IP00C772_B2_HPXNRCF1_ADDR]=0x00;
	bank2[CP_IP00C772_B2_HPXNRCF2_ADDR]=0x00;
	bank2[CP_IP00C772_B2_MVNRCT_ADDR]=0x1f;
	bank2[CP_IP00C772_B2_HMVNRCFA_ADDR]=0x01;
	bank2[CP_IP00C772_B2_HMVNRCFB_ADDR]=0x01;
	bank2[CP_IP00C772_B2_HMVNRCFC_ADDR]=0x02;
	bank2[CP_IP00C772_B2_HMVNRCFD_ADDR]=0x08;
	bank2[CP_IP00C772_B2_VFILCFA_ADDR]=0x08;
	bank2[CP_IP00C772_B2_VFILCFB_ADDR]=0x08;
	bank2[CP_IP00C772_B2_VFILCFC_ADDR]=0x08;
	bank2[CP_IP00C772_B2_VFILCFD_ADDR]=0x10;
	bank2[CP_IP00C772_B2_HFILCFA_ADDR]=0x08;
	bank2[CP_IP00C772_B2_HFILCFB_ADDR]=0x08;
	bank2[CP_IP00C772_B2_HFILCFC_ADDR]=0x10;
	bank2[CP_IP00C772_B2_HFILCFD_ADDR]=0x18;
	bank2[CP_IP00C772_B2_XVFILMD_ADDR]=0x07;
	bank2[CP_IP00C772_B2_XNRCUT_ADDR]=0x01;
//	bank2[CP_IP00C772_B2_LUTWAD_ADDR]=0x02;
//	bank2[CP_IP00C772_B2_LUTCOEF_ADDR]=0x02;
//	bank2[CP_IP00C772_B2_LUTWR_ADDR]= 0x02;

	bank2[CP_IP00C772_B2_IPTEST_ADDR]=0x00;
	bank2[CP_IP00C772_B2_OADJCT_ADDR]=0x08;
	bank2[CP_IP00C772_B2_PDCTRL_ADDR]=0xfe;
	bank2[CP_IP00C772_B2_PDMV22TH_ADDR]=0x08;
	bank2[CP_IP00C772_B2_PD23RSTTH_ADDR]=0x3c;
	bank2[CP_IP00C772_B2_PDSQTH_ADDR]=0x41;
	bank2[CP_IP00C772_B2_MVACCSEL_ADDR]=0x35;
	bank2[CP_IP00C772_B2_PDACTSEL_ADDR]=0x03;
	bank2[CP_IP00C772_B2_PD22RSTCT_ADDR]=0x61;
	bank2[CP_IP00C772_B2_PDMV23TH_ADDR]=0x14;
	bank2[CP_IP00C772_B2_DIAGCT1_ADDR]=0x37;
	bank2[CP_IP00C772_B2_DIAGCT2_ADDR]=0xcf;
	bank2[CP_IP00C772_B2_DIAGCT3_ADDR]=0xe6;

	bank2[CP_IP00C772_B2_DIAGTH0_ADDR]=0x00;
	bank2[CP_IP00C772_B2_DIAGTH1_ADDR]=0x09;
	bank2[CP_IP00C772_B2_DIAGTH2_ADDR]=0x12;
	bank2[CP_IP00C772_B2_DIAGTH3_ADDR]=0x03;
	bank2[CP_IP00C772_B2_DIAGTH4_ADDR]=0x08;
	bank2[CP_IP00C772_B2_DIAGTH5_ADDR]=0x05;
	bank2[CP_IP00C772_B2_DIAGTH6_ADDR]=0x12;
	bank2[CP_IP00C772_B2_DIAGTH7_ADDR]=0x04;
	bank2[CP_IP00C772_B2_DIAGTH8_ADDR]=0x04;
	bank2[CP_IP00C772_B2_DIAGTH9_ADDR]=0x04;
	bank2[CP_IP00C772_B2_DIAGTH10_ADDR]=0x09;
	bank2[CP_IP00C772_B2_DIAGTH11_ADDR]=0x10;
	bank2[CP_IP00C772_B2_DIAGTH12_ADDR]=0x32;

	value.push_back(bank2);

	dev_C772_InitColorConversion(value);
	dev_C772_InitIPConversion(value);
	dev_C772_InitLUT(value);

	map<uint8_t,uint8_t> bank3;
	bank3[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank3[CP_IP00C772_B0_OVCYCLMIN_ADDR1] = 0x0b;
	bank3[CP_IP00C772_B0_OVCYCLMIN_ADDR2] = 0x02;

	value.push_back(bank3);


}

void DriverChip772::dev_C772_InitColorConversion(list<map<uint8_t,uint8_t> > &value)
{

	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OCCFTR_ADDR1] = 0x9d;
	bank0[CP_IP00C772_B0_OCCFTR_ADDR2] = 0x05;
	bank0[CP_IP00C772_B0_OCCFTB_ADDR1] = 0x18;
	bank0[CP_IP00C772_B0_OCCFTB_ADDR2] = 0x07;
	bank0[CP_IP00C772_B0_OCCFTGR_ADDR1] = 0x25;
	bank0[CP_IP00C772_B0_OCCFTGR_ADDR2] = 0x1d;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR1] = 0xea;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OCCFTRB_ADDR1] = 0x00;
	bank0[CP_IP00C772_B0_OCCFTRB_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OCCFTBR_ADDR1] = 0x00;
	bank0[CP_IP00C772_B0_OCCFTBR_ADDR2] = 0x00;

	value.push_back(bank0);

}

void DriverChip772::dev_C772_InitIPConversion(list<map<uint8_t,uint8_t> > &value)
{

	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x03;

	bank0[CP_IP00C772_B3_IPOSFLD1_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_IPOSFLD1_ADDR2] = 0x00;
	bank0[CP_IP00C772_B3_IPOSFLD1_ADDR3] = 0x18;

	bank0[CP_IP00C772_B3_IPISFLD0_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_IPISFLD0_ADDR2] = 0x08;
	bank0[CP_IP00C772_B3_IPISFLD0_ADDR3] = 0x00;

	bank0[CP_IP00C772_B3_IPISFLD2_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_IPISFLD2_ADDR2] = 0x08;
	bank0[CP_IP00C772_B3_IPISFLD2_ADDR3] = 0x18;

	bank0[CP_IP00C772_B3_IPISFLD3_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_IPISFLD3_ADDR2] = 0x00;
	bank0[CP_IP00C772_B3_IPISFLD3_ADDR3] = 0x18;

	bank0[CP_IP00C772_B3_IPMWI_ADDR] = 0x08;
	bank0[CP_IP00C772_B3_MVFLD_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_MVFLD_ADDR2] = 0x00;
	bank0[CP_IP00C772_B3_MVFLD_ADDR3] = 0x30;
	bank0[CP_IP00C772_B3_TMSASEL_ADDR] = 0x01;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x0;

	value.push_back(bank0);

}

void DriverChip772::dev_C772_InitLUT(list<map<uint8_t,uint8_t> > &value)
{

	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x02;

	// C772B2 LUTCOEF 00042000h
	bank0[CP_IP00C772_LUTCOEF_a] = 0x00;
	bank0[CP_IP00C772_LUTCOEF_b] = 0x20;
	bank0[CP_IP00C772_LUTCOEF_c] = 0x04;
	bank0[CP_IP00C772_LUTCOEF_d] = 0x00;

	bank0[CP_IP00C772_LUTWAD] =   0x00;
	bank0[CP_IP00C772_LUTWR] =    0xff;


    // C772B2 LUTCOEF 00139c01h
	bank0[CP_IP00C772_LUTCOEF_a] =  0x01;
	bank0[CP_IP00C772_LUTCOEF_b] = 0x9c;
	bank0[CP_IP00C772_LUTCOEF_c] = 0x13;
	bank0[CP_IP00C772_LUTCOEF_d] = 0x00;

	bank0[CP_IP00C772_LUTWAD]=0x01;
	bank0[CP_IP00C772_LUTWR ]=0xff;
	bank0[CP_IP00C772_LUTWAD]=0x02;
	bank0[CP_IP00C772_LUTWR ]=0xff;


    // C772B2 LUTCOEF 00231802h
	bank0[CP_IP00C772_LUTCOEF_a]=0x02;
	bank0[CP_IP00C772_LUTCOEF_b]=0x18;
	bank0[CP_IP00C772_LUTCOEF_c]=0x23;
	bank0[CP_IP00C772_LUTCOEF_d]=0x00;

	bank0[CP_IP00C772_LUTWAD]=0x03;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x04;
    bank0[CP_IP00C772_LUTWR ]=0xff;


    // C772B2 LUTCOEF 00329403h
    bank0[CP_IP00C772_LUTCOEF_a]=0x03;
    bank0[CP_IP00C772_LUTCOEF_b]=0x94;
    bank0[CP_IP00C772_LUTCOEF_c]=0x32;
    bank0[CP_IP00C772_LUTCOEF_d]=0x00;


    bank0[CP_IP00C772_LUTWAD]=0x05;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x06;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x07;
    bank0[CP_IP00C772_LUTWR ]=0xff;



    // C772B2 LUTCOEF 00421004h
    bank0[CP_IP00C772_LUTCOEF_a]=0x04;
    bank0[CP_IP00C772_LUTCOEF_b]=0x10;
    bank0[CP_IP00C772_LUTCOEF_c]=0x42;
    bank0[CP_IP00C772_LUTCOEF_d]=0x00;

    bank0[CP_IP00C772_LUTWAD]=0x08;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x09;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x0a;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x0b;
    bank0[CP_IP00C772_LUTWR ]=0xff;


    // C772B2 LUTCOEF 00518c05h
    bank0[CP_IP00C772_LUTCOEF_a]=0x05;
    bank0[CP_IP00C772_LUTCOEF_b]=0x8c;
    bank0[CP_IP00C772_LUTCOEF_c]=0x51;
    bank0[CP_IP00C772_LUTCOEF_d]=0x00;


    bank0[CP_IP00C772_LUTWAD]=0x0c;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x0d;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x0e;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x0f;
    bank0[CP_IP00C772_LUTWR]= 0xff;


    // C772B2 LUTCOEF 00610806h
    bank0[CP_IP00C772_LUTCOEF_a]=0x06;
    bank0[CP_IP00C772_LUTCOEF_b]=0x08;
    bank0[CP_IP00C772_LUTCOEF_c]=0x61;
    bank0[CP_IP00C772_LUTCOEF_d]=0x00;


    bank0[CP_IP00C772_LUTWAD]=0x10;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x11;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x12;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x13;
    bank0[CP_IP00C772_LUTWR ]=0xff;


    // C772B2 LUTCOEF 00708407h
    bank0[CP_IP00C772_LUTCOEF_a]=0x07;
    bank0[CP_IP00C772_LUTCOEF_b]=0x84;
    bank0[CP_IP00C772_LUTCOEF_c]=0x70;
    bank0[CP_IP00C772_LUTCOEF_d]=0x00;



    bank0[CP_IP00C772_LUTWAD]=0x14;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x15;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x16;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x17;
    bank0[CP_IP00C772_LUTWR ]=0xff;



   // C772B2 LUTCOEF 00800008h
    bank0[CP_IP00C772_LUTCOEF_a]= 0x08;
    bank0[CP_IP00C772_LUTCOEF_b]= 0x00;
    bank0[CP_IP00C772_LUTCOEF_c]= 0x80;
    bank0[CP_IP00C772_LUTCOEF_d]= 0x00;




    bank0[CP_IP00C772_LUTWAD]=0x18;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x19;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x1a;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x1b;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x1c;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x1d;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x1e;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x1f;
    bank0[CP_IP00C772_LUTWR ]=0xff;


    // C772B2 LUTCOEF 00004000h
    bank0[CP_IP00C772_LUTCOEF_a]=0x00;
    bank0[CP_IP00C772_LUTCOEF_b]= 0x40;
    bank0[CP_IP00C772_LUTCOEF_c]=0x00;
    bank0[CP_IP00C772_LUTCOEF_d]=0x00;


    bank0[CP_IP00C772_LUTWAD]=0x20;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x21;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x22;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x23;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x24;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x25;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x26;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x27;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x28;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x29;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x2a;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x2b;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x2c;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x2d;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x2e;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x2f;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x30;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x31;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x32;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x33;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x34;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x35;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x36;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x37;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x38;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x39;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x3a;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x3b;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x3c;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x3d;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x3e;
    bank0[CP_IP00C772_LUTWR ]=0xff;
    bank0[CP_IP00C772_LUTWAD]=0x3f;
    bank0[CP_IP00C772_LUTWR ]=0xff;

    value.push_back(bank0);

}

void DriverChip772::dev_C772_Reset(list<map<uint8_t,uint8_t> > &value)
{

}



void DriverChip772::dev_C772_ChangeModel(list<map<uint8_t,uint8_t> > &value,uint32_t byVideoModel)
{

}


void DriverChip772::dev_C772_SetInputSize(list<map<uint8_t,uint8_t> >&value,uint32_t wACTHStart,uint32_t wACTHWidth,uint32_t wACTVStart,uint32_t wACTVWidth)
{
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x01;

	uint8_t byValue = 0;

	byValue = wACTHStart & MASK_LOW8;
	bank0[CP_IP00C772_B1_IACTHST_ADDR1] = byValue;

	byValue = (wACTHStart & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B1_IACTHST_ADDR2] = byValue;

	byValue = wACTHWidth & MASK_LOW8;
	bank0[CP_IP00C772_B1_IACTHW_ADDR1] = byValue;

	byValue = (wACTHWidth & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B1_IACTHW_ADDR2] = byValue;


	byValue = wACTVStart & MASK_LOW8;
	bank0[CP_IP00C772_B1_IACTVST_ADDR1] = byValue;

	byValue = (wACTVStart & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B1_IACTVST_ADDR2] = byValue;

	byValue = wACTVWidth & MASK_LOW8;
	bank0[CP_IP00C772_B1_IACTVW_ADDR1] = byValue;

	byValue = (wACTVWidth & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B1_IACTVW_ADDR2] = byValue;

	value.push_back(bank0);
}

void DriverChip772::dev_C772_SetOutputSize(list<map<uint8_t,uint8_t> >&value,uint32_t wACTHStart,uint32_t wACTHWidth,uint32_t wACTVStart,uint32_t wACTVWidth)
{
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	uint8_t byValue = 0;

	byValue = wACTHStart & MASK_LOW8;
	bank0[CP_IP00C772_B0_OACTHST_ADDR1] = byValue;

	byValue = (wACTHStart & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OACTHST_ADDR2] = byValue;

	byValue = wACTHWidth & MASK_LOW8;
	bank0[CP_IP00C772_B0_OACTHW_ADDR1]  = byValue;

	byValue = (wACTHWidth & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OACTHW_ADDR2]  = byValue;


	byValue = wACTVStart & MASK_LOW8;
	bank0[CP_IP00C772_B0_OACTVST_ADDR1] = byValue;

	byValue = (wACTVStart & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OACTVST_ADDR2] = byValue;

	byValue = wACTVWidth & MASK_LOW8;
	bank0[CP_IP00C772_B0_OACTVW_ADDR1] = byValue;

	byValue = (wACTVWidth & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OACTVW_ADDR2] = byValue;

}


void DriverChip772::dev_C772_SetOutputSyncCycle(list<map<uint8_t,uint8_t> > &value,uint32_t wHSyncCycle,uint32_t wVSyncCycle)
{
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	uint8_t byValue = 0;


	byValue = wHSyncCycle & MASK_LOW8;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR1] = byValue;

	byValue = (wHSyncCycle & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR2] = byValue;

	byValue = wHSyncCycle & MASK_LOW8;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR1] = byValue;

	byValue = (wHSyncCycle & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR2] = byValue;

	value.push_back(bank0);
}

void DriverChip772::dev_C772_SetBlueScreen(list<map<uint8_t,uint8_t> > &value,uint32_t byFlg)
{
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	bank0[CP_IP00C772_B0_OFILL_RED_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OFILL_GREEN_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OFILL_BLUE_ADDR] = 0xff;


//	CHIP_ReadC772(byChannel,CP_IP00C772_B0_OIMGCT_ADDR,&byValue);
//
//	if(byFlg == CP_TRUE)
//	{
//		byValue = byValue | 0x01;
//		CHIP_WriteC772(byChannel,CP_IP00C772_B0_OIMGCT_ADDR,byValue);
//	}
//	else
//	{
//		byValue = byValue & 0xfe;
//		CHIP_WriteC772(byChannel,CP_IP00C772_B0_OIMGCT_ADDR,byValue);
//	}
//	CHIP_WriteC772(byChannel,CP_IP00C772_RGBNK_ADDR,0);


}

void DriverChip772::dev_C772_SetHorAndVerSyncCtrl(list<map<uint8_t,uint8_t> > &value,uint32_t byHorPolarity,uint32_t byHorWidth,uint32_t byVerPolarty,uint32_t byVerWidth)
{

	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	uint8_t byValue = 0;

	byValue = byValue | (byHorWidth & 0x7f);
	byValue = byValue | (byHorPolarity << 7);

	bank0[CP_IP00C772_B0_OHSCT_ADDR] = byValue;

	byValue = 0;
	byValue = byValue | (byVerWidth & 0x0f);
	byValue = byValue | (byVerPolarty << 4);

	bank0[CP_IP00C772_B0_OVSCT_ADDR] = byValue;


	value.push_back(bank0);
}





