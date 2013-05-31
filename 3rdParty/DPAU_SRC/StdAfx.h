// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__7BDE8654_27AE_47A1_A3E2_3539E67F9B22__INCLUDED_)
#define AFX_STDAFX_H__7BDE8654_27AE_47A1_A3E2_3539E67F9B22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include<math.h>

#define EDIT_DB_WIDTH		40
#define EDIT_FREQ_WIDTH		40
#define SLIDER_FREQ_WIDTH	40

typedef struct _stYPos
{
	int mPosition;
	int mPosValue;
}STPOSITION,*PSTPOSITION;

typedef struct _stPoint
{
	int x;
	int y;
}STPOINT;

typedef struct _stDPG
{
	int mTotal;			//总节点
	int mCarrys;		//进位节点
	int mCarryVal[32];	//进位节点数值
	int mElements[64];	//元素个数
}STDPG,*PSTDPG;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

CString NumOfFreqStr(int freq);
int BitsOfNumber(int val);
int NodesOfFreqRange(int start,int end,STDPG *stDpg);
void InsertSort(STPOSITION a[]);
int CalcXPos(int sFreq,int eFreq,int freq,CRect *rect);
int CalcFreq(int x,int sFreq,int eFreq,CRect *rect);

#endif // !defined(AFX_STDAFX_H__7BDE8654_27AE_47A1_A3E2_3539E67F9B22__INCLUDED_)
