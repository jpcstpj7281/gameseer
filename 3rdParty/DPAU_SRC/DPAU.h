// DPAU.h : main header file for the DPAU application
//

#if !defined(AFX_DPAU_H__D125F57B_C62E_419A_BE9A_964A537C3C4A__INCLUDED_)
#define AFX_DPAU_H__D125F57B_C62E_419A_BE9A_964A537C3C4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDPAUApp:
// See DPAU.cpp for the implementation of this class
//

class CDPAUApp : public CWinApp
{
public:
	CDPAUApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDPAUApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDPAUApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPAU_H__D125F57B_C62E_419A_BE9A_964A537C3C4A__INCLUDED_)
