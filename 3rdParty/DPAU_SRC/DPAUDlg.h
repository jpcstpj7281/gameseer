// DPAUDlg.h : header file
//

#if !defined(AFX_DPAUDLG_H__8D9E9828_5A43_4A69_BB07_74E9CA060F17__INCLUDED_)
#define AFX_DPAUDLG_H__8D9E9828_5A43_4A69_BB07_74E9CA060F17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDPAUDlg dialog

class CDPAUDlg : public CDialog
{
// Construction
public:
	CDPAUDlg(CWnd* pParent = NULL);	// standard constructor
	void InitGraphics();
	void CalcYGridPos();
	void DrawXYGrid(CDC *pDC);
	void DrawDempWave(CDC *pDC);
	void DrawShelvingWave(CDC *pDC);
	void DrawFreqGrid(CDC *pDC,int m_sFreq,int m_eFreq);

// Dialog Data
	//{{AFX_DATA(CDPAUDlg)
	enum { IDD = IDD_DPAU_DIALOG };
	CComboBox	m_ComboSlope;
	CComboBox	m_ComboType;
	CSpinButtonCtrl	m_SpinQValue;
	CSliderCtrl	m_SilderFreq10;
	CSliderCtrl	m_SilderFreq9;
	CSliderCtrl	m_SilderFreq8;
	CSliderCtrl	m_SilderFreq7;
	CSliderCtrl	m_SilderFreq6;
	CSliderCtrl	m_SilderFreq5;
	CSliderCtrl	m_SilderFreq4;
	CSliderCtrl	m_SilderFreq3;
	CSliderCtrl	m_SilderFreq2;
	CSliderCtrl	m_SilderFreq1;
	CStatic	m_CtlWave;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDPAUDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	HANDLE hRealSerial;
	HWND hStatusWindow;

	CDC *pDC;             //屏幕绘图设备
	CDC memDC;            //内存绘图设备
	CDC *pWaveDC;
	BOOL bLDown;
	BOOL bShow;

	TCHAR cQText[16];
	STPOSITION m_stYPos[128];

    CBitmap memBitmap;
	CRect WaveRect;
	CRect MouseMoveRect;

	CRgn rgnWave;
	CRgn rgnValid;

	CBrush brushBack;
	CBrush brushRed;
	CBrush brushGreen;

	CFont mWaveFont;

	int m_dBValue[10];
	double m_QValue;

	CPoint m_MousePoint;
	int m_Type;
	int m_Slope;
	int mZeroPos;
	int mXStep;

	int m_TopdB;		//分贝上限
	int m_BottomdB;		//分贝下限

	int m_StartFreq;	//开始频率
	int m_EndFreq;		//结束频率
	float m_FreqStep;	//步进
	float m_CurFreq;	//当前频率

	CPen *pPenGreenWeight;
	CPen *pPenRedWeight;
	CPen *pPenGreenLight;
	CPen *pPenBlueLight;

	CRect ValidRect;

	// Generated message map functions
	//{{AFX_MSG(CDPAUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCustomdrawSliderFreq1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq10(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq7(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq8(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderFreq9(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillfocusEditFreq10();
	afx_msg void OnKillfocusEditFreq9();
	afx_msg void OnKillfocusEditFreq8();
	afx_msg void OnKillfocusEditFreq7();
	afx_msg void OnKillfocusEditFreq6();
	afx_msg void OnKillfocusEditFreq5();
	afx_msg void OnKillfocusEditFreq4();
	afx_msg void OnKillfocusEditFreq3();
	afx_msg void OnKillfocusEditFreq2();
	afx_msg void OnKillfocusEditFreq1();
	afx_msg void OnButtonShow();
	afx_msg void OnButtonFlateq();
	afx_msg void OnDeltaposSpinValue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboType();
	afx_msg void OnSelchangeComboSlope();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPAUDLG_H__8D9E9828_5A43_4A69_BB07_74E9CA060F17__INCLUDED_)
