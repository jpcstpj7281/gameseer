#if !defined(AFX_BUTTONST_H__A3483D87_0905_4A27_96DE_68967096DD5C__INCLUDED_)
#define AFX_BUTTONST_H__A3483D87_0905_4A27_96DE_68967096DD5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonST.h : header file

#define RWIDTH(x)			x.right-x.left
#define RHIGHT(x)			x.bottom-x.top
#define MAX_PATHLEN			512

/////////////////////////////////////////////////////////////////////////////
// CButtonST window

class CButtonST : public CButton
{
// Construction
public:
	CButtonST();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonST)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CButtonST();
	void InitMemCDC(CDC *pDC,CRect bRect);
	void SetBitmapID(int nID,CDC *pParentDC);
	void SetFlat(BOOL bState);
	void SetOwnerStyle(LONG lStyle);
	void SetImageFile(char *szFilename);
	void ImageOpen(CDC *pDC,char *szFilename);
	void DrawTransparentBitmap(CDC *pDC,UINT IDImage,CRect &rect,COLORREF rgbMask);

	BOOL bInitialCDC;
	CDC *pBtnDC;
	int mBitmapID;

	CDC *pBKDC;			//±³¾°²ã
	CDC m_BuffDC;		//»º´æ²ã
	
	BOOL m_bIsFlat;
	BOOL m_bImage;
	LONG lBStyle;
	TCHAR szImageFileName[MAX_PATHLEN];
	CFont m_Font;

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonST)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONST_H__A3483D87_0905_4A27_96DE_68967096DD5C__INCLUDED_)
