//DPAUDlg.cpp : implementation file

#include "stdafx.h"
#include "DPAU.h"
#include "DPAUDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FREQ_STEP(x)	(int)((pow((double)10,BitsOfNumber(x)-1)+1)/2)

//对double型只取8位有效值,4舍5入
#define	dd2(x)	((double)(((int)(((x)+0.000000005)*100000000)))/100000000)  

int m_EditDBCtrlID[]=
{
	IDC_EDIT_DB1,IDC_EDIT_DB2,IDC_EDIT_DB3,IDC_EDIT_DB4,IDC_EDIT_DB5,
	IDC_EDIT_DB6,IDC_EDIT_DB7,IDC_EDIT_DB8,IDC_EDIT_DB9,IDC_EDIT_DB10
};

int m_EditFreqCtrlID[]=
{
	IDC_EDIT_FREQ1,IDC_EDIT_FREQ2,IDC_EDIT_FREQ3,IDC_EDIT_FREQ4,IDC_EDIT_FREQ5,
	IDC_EDIT_FREQ6,IDC_EDIT_FREQ7,IDC_EDIT_FREQ8,IDC_EDIT_FREQ9,IDC_EDIT_FREQ10
};

int m_SliderCtrlID[]=
{
	IDC_SLIDER_FREQ1,IDC_SLIDER_FREQ2,IDC_SLIDER_FREQ3,IDC_SLIDER_FREQ4,IDC_SLIDER_FREQ5,
	IDC_SLIDER_FREQ6,IDC_SLIDER_FREQ7,IDC_SLIDER_FREQ8,IDC_SLIDER_FREQ9,IDC_SLIDER_FREQ10
};

int m_MidFreq[]=
{
	30,60,100,200,500,1000,2000,5000,10000,15000
};

/////////////////////////////////////////////////////////////////////////////
//CDPAUDlg dialog

CDPAUDlg::CDPAUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDPAUDlg::IDD,pParent)
{
	//{{AFX_DATA_INIT(CDPAUDlg)
		//NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDPAUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDPAUDlg)
	DDX_Control(pDX, IDC_COMBO_SLOPE, m_ComboSlope);
	DDX_Control(pDX,IDC_COMBO_TYPE,m_ComboType);
	DDX_Control(pDX,IDC_SPIN_VALUE,m_SpinQValue);
	DDX_Control(pDX,IDC_SLIDER_FREQ10,m_SilderFreq10);
	DDX_Control(pDX,IDC_SLIDER_FREQ9,m_SilderFreq9);
	DDX_Control(pDX,IDC_SLIDER_FREQ8,m_SilderFreq8);
	DDX_Control(pDX,IDC_SLIDER_FREQ7,m_SilderFreq7);
	DDX_Control(pDX,IDC_SLIDER_FREQ6,m_SilderFreq6);
	DDX_Control(pDX,IDC_SLIDER_FREQ5,m_SilderFreq5);
	DDX_Control(pDX,IDC_SLIDER_FREQ4,m_SilderFreq4);
	DDX_Control(pDX,IDC_SLIDER_FREQ3,m_SilderFreq3);
	DDX_Control(pDX,IDC_SLIDER_FREQ2,m_SilderFreq2);
	DDX_Control(pDX,IDC_SLIDER_FREQ1,m_SilderFreq1);
	DDX_Control(pDX,IDC_WAVE,m_CtlWave);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDPAUDlg,CDialog)
	//{{AFX_MSG_MAP(CDPAUDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ1,OnCustomdrawSliderFreq1)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ2,OnCustomdrawSliderFreq2)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ10,OnCustomdrawSliderFreq10)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ3,OnCustomdrawSliderFreq3)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ4,OnCustomdrawSliderFreq4)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ5,OnCustomdrawSliderFreq5)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ6,OnCustomdrawSliderFreq6)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ7,OnCustomdrawSliderFreq7)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ8,OnCustomdrawSliderFreq8)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SLIDER_FREQ9,OnCustomdrawSliderFreq9)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ10,OnKillfocusEditFreq10)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ9,OnKillfocusEditFreq9)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ8,OnKillfocusEditFreq8)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ7,OnKillfocusEditFreq7)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ6,OnKillfocusEditFreq6)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ5,OnKillfocusEditFreq5)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ4,OnKillfocusEditFreq4)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ3,OnKillfocusEditFreq3)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ2,OnKillfocusEditFreq2)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQ1,OnKillfocusEditFreq1)
	ON_BN_CLICKED(IDC_BUTTON_SHOW,OnButtonShow)
	ON_BN_CLICKED(IDC_BUTTON_FLATEQ,OnButtonFlateq)
	ON_NOTIFY(UDN_DELTAPOS,IDC_SPIN_VALUE,OnDeltaposSpinValue)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE,OnSelchangeComboType)
	ON_CBN_SELCHANGE(IDC_COMBO_SLOPE, OnSelchangeComboSlope)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//CDPAUDlg message handlers

BOOL CDPAUDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon,TRUE);			//Set big icon
	SetIcon(m_hIcon,FALSE);		//Set small icon
	
	//TODO: Add extra initialization here
	int i;
	CWnd* pCtrlWnd;
	CRect m_ClientRect,tmprect;

	//变量初始化
	bShow=true;
	m_TopdB=20;
	m_BottomdB=-20;

	m_StartFreq=20;
	m_CurFreq=(float)m_StartFreq;
	m_EndFreq=20000;

	bLDown=FALSE;
	memset(&m_stYPos,0,sizeof(STPOSITION)*128);

	m_MousePoint.x=0;
	m_MousePoint.y=0;

	hRealSerial=INVALID_HANDLE_VALUE;
	mZeroPos=0;

	m_QValue=1;
	mXStep=0;
	pWaveDC=NULL;
	pPenGreenWeight=NULL;
	pPenRedWeight=NULL;
	pPenBlueLight=NULL;
	pPenGreenLight=NULL;

	SetWindowPos(&wndBottom,0,0,800,550,SWP_SHOWWINDOW);	

	hStatusWindow=CreateStatusWindow(WS_CHILD|WS_VISIBLE|WS_BORDER,
		TEXT(""),				//显示在状态栏上的信息
		this->GetSafeHwnd(),	//父窗口句柄
		1234);

	int pint[5]={200,350,450,600,-1};
	::SendMessage(hStatusWindow,SB_SETPARTS,5,(LPARAM)pint);

	::SendMessage(hStatusWindow,SB_SETTEXT,0,(LPARAM)TEXT("通信口状态"));
	::SendMessage(hStatusWindow,SB_SETTEXT,4,(LPARAM)TEXT("Copyright 2008,Ver1.0"));

	GetClientRect(&m_ClientRect);
	::GetWindowRect(hStatusWindow,&tmprect);

	//调整控件位置
	m_CtlWave.SetWindowPos(&wndBottom,3,m_ClientRect.top+3,m_ClientRect.right-6,
		m_ClientRect.top+300,SWP_SHOWWINDOW);

	pCtrlWnd=GetDlgItem(IDC_STATIC_FREQ);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,3,m_ClientRect.top+303,m_ClientRect.right-6,
		195,SWP_SHOWWINDOW);

	for(i=0;i<10;i++)
	{
		pCtrlWnd=GetDlgItem(m_EditDBCtrlID[i]);
		pCtrlWnd->GetWindowRect(&tmprect);
		pCtrlWnd->SetWindowPos(&wndBottom,15+i*(EDIT_DB_WIDTH+3),m_ClientRect.top+320,EDIT_DB_WIDTH,
			tmprect.Height(),SWP_SHOWWINDOW);
	}
	
	for(i=0;i<10;i++)
	{
		pCtrlWnd=GetDlgItem(m_EditFreqCtrlID[i]);
		pCtrlWnd->GetWindowRect(&tmprect);
		pCtrlWnd->SetWindowPos(&wndBottom,15+i*(EDIT_FREQ_WIDTH+3),m_ClientRect.top+320+30+100,EDIT_FREQ_WIDTH,
			tmprect.Height(),SWP_SHOWWINDOW);
		SetDlgItemInt(m_EditFreqCtrlID[i],m_MidFreq[i]);
	}

	for(i=0;i<10;i++)
	{
		pCtrlWnd=GetDlgItem(m_SliderCtrlID[i]);
		pCtrlWnd->GetWindowRect(&tmprect);
		pCtrlWnd->SetWindowPos(&wndBottom,15+i*(SLIDER_FREQ_WIDTH+3),m_ClientRect.top+320+25,SLIDER_FREQ_WIDTH,
			100,SWP_SHOWWINDOW);
	}
	m_SilderFreq1.SetRange(0,30);
	m_SilderFreq1.SetPos(15);
	m_SilderFreq2.SetRange(0,30);
	m_SilderFreq2.SetPos(15);
	m_SilderFreq3.SetRange(0,30);
	m_SilderFreq3.SetPos(15);
	m_SilderFreq4.SetRange(0,30);
	m_SilderFreq4.SetPos(15);
	m_SilderFreq5.SetRange(0,30);
	m_SilderFreq5.SetPos(15);
	m_SilderFreq6.SetRange(0,30);
	m_SilderFreq6.SetPos(15);
	m_SilderFreq7.SetRange(0,30);
	m_SilderFreq7.SetPos(15);
	m_SilderFreq8.SetRange(0,30);
	m_SilderFreq8.SetPos(15);
	m_SilderFreq9.SetRange(0,30);
	m_SilderFreq9.SetPos(15);
	m_SilderFreq10.SetRange(0,30);
	m_SilderFreq10.SetPos(15);

	m_dBValue[0]=15-m_SilderFreq1.GetPos();
	m_dBValue[1]=15-m_SilderFreq2.GetPos();
	m_dBValue[2]=15-m_SilderFreq3.GetPos();
	m_dBValue[3]=15-m_SilderFreq4.GetPos();
	m_dBValue[4]=15-m_SilderFreq5.GetPos();
	m_dBValue[5]=15-m_SilderFreq6.GetPos();
	m_dBValue[6]=15-m_SilderFreq7.GetPos();
	m_dBValue[7]=15-m_SilderFreq8.GetPos();
	m_dBValue[8]=15-m_SilderFreq9.GetPos();
	m_dBValue[9]=15-m_SilderFreq10.GetPos();

	m_SpinQValue.SetPos((int)(m_QValue*10));
	m_SpinQValue.SetRange32(1,100);
	sprintf(cQText,"%01f",m_QValue);
	SetDlgItemText(IDC_EDIT_QVALUE,cQText);

	pCtrlWnd=GetDlgItem(IDC_STATIC_DB);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,445,m_ClientRect.top+325,15,
		tmprect.Height(),SWP_SHOWWINDOW);

	pCtrlWnd=GetDlgItem(IDC_STATIC_HZ);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,445,m_ClientRect.top+455,15,
		tmprect.Height(),SWP_SHOWWINDOW);

	pCtrlWnd=GetDlgItem(IDC_STATIC_Q);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,500,m_ClientRect.top+385,tmprect.Width(),
		tmprect.Height(),SWP_SHOWWINDOW);

	pCtrlWnd=GetDlgItem(IDC_STATIC_TYPE);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,500,m_ClientRect.top+435,tmprect.Width(),
		tmprect.Height(),SWP_SHOWWINDOW);

	pCtrlWnd=GetDlgItem(IDC_BUTTON_SHOW);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,500,m_ClientRect.top+320,50,
		tmprect.Height(),SWP_SHOWWINDOW);

	pCtrlWnd=GetDlgItem(IDC_BUTTON_FLATEQ);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,500,m_ClientRect.top+350,50,
		tmprect.Height(),SWP_SHOWWINDOW);

	pCtrlWnd=GetDlgItem(IDC_EDIT_QVALUE);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,500,m_ClientRect.top+400,30,
		tmprect.Height(),SWP_SHOWWINDOW);

	pCtrlWnd=GetDlgItem(IDC_COMBO_TYPE);
	pCtrlWnd->SendMessage(CB_SETCURSEL,1,0); 
	m_Type=m_ComboType.GetCurSel();
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,500,m_ClientRect.top+450,tmprect.Width(),
		tmprect.Height(),SWP_SHOWWINDOW);

	m_ComboType.SetWindowPos(NULL,0,0,72,60,SWP_NOMOVE|SWP_NOZORDER);

	pCtrlWnd=GetDlgItem(IDC_COMBO_SLOPE);
	pCtrlWnd->SendMessage(CB_SETCURSEL,0,0); 
	m_Slope=m_ComboSlope.GetCurSel();
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,500,m_ClientRect.top+400,tmprect.Width(),
		tmprect.Height(),SWP_SHOWWINDOW);

	m_ComboSlope.SetWindowPos(NULL,0,0,72,60,SWP_NOMOVE|SWP_NOZORDER);
	::ShowWindow(pCtrlWnd->GetSafeHwnd(),SW_HIDE);

	pCtrlWnd=GetDlgItem(IDC_SPIN_VALUE);
	pCtrlWnd->GetWindowRect(&tmprect);
	pCtrlWnd->SetWindowPos(&wndBottom,530,m_ClientRect.top+399,20,
		tmprect.Height(),SWP_SHOWWINDOW);

	InitGraphics();
	CalcYGridPos();

	DrawXYGrid(&memDC);
	pWaveDC->BitBlt(WaveRect.left,WaveRect.top,WaveRect.right,WaveRect.bottom,
		&memDC,0,0,SRCCOPY);

	SetTimer(1,100,NULL);
	return TRUE;//return TRUE  unless you set the focus to a control
}

//If you add a minimize button to your dialog,you will need the code below
// to draw the icon.  For MFC applications using the document/view model,
// this is automatically done for you by the framework.

void CDPAUDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); //device context for painting

		SendMessage(WM_ICONERASEBKGND,(WPARAM) dc.GetSafeHdc(),0);

		//Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		//Draw the icon
		dc.DrawIcon(x,y,m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//The system calls this to obtain the cursor to display while the user drags
// the minimized window.
HCURSOR CDPAUDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDPAUDlg::InitGraphics()
{
	pWaveDC=m_CtlWave.GetDC();

	m_CtlWave.GetClientRect(&WaveRect);
	ValidRect.left=WaveRect.left+40;
	ValidRect.top=WaveRect.top+10;
	ValidRect.right=WaveRect.right;
	ValidRect.bottom=WaveRect.bottom-20;

	rgnWave.CreateRectRgn(WaveRect.left,WaveRect.top,WaveRect.right,WaveRect.bottom);
	rgnValid.CreateRectRgn(ValidRect.left,ValidRect.top,ValidRect.right,ValidRect.bottom);

	memDC.CreateCompatibleDC(pWaveDC);
	memBitmap.CreateCompatibleBitmap(pWaveDC,WaveRect.Width(),WaveRect.Height());
	memDC.SelectObject(&memBitmap);

	brushBack.CreateSolidBrush(RGB(0,0,0));
	brushRed.CreateSolidBrush(RGB(255,0,0));
	brushGreen.CreateSolidBrush(RGB(0,255,0));
	
	pPenGreenWeight=new CPen;
	pPenGreenLight=new CPen;
	pPenRedWeight=new CPen;
	pPenBlueLight=new CPen;

	//深绿色画笔
	pPenGreenWeight->CreatePen(PS_SOLID,1,RGB(0,255,0));
	//浅绿色画笔
	pPenGreenLight->CreatePen(PS_SOLID,1,RGB(0,128,0));
	//深红色画笔
	pPenRedWeight->CreatePen(PS_SOLID,1,RGB(255,0,0));
	//深蓝色画笔
	pPenBlueLight->CreatePen(PS_SOLID,1,RGB(0,0,128));

	//创建字体
    NONCLIENTMETRICS ncm;
    ncm.cbSize=sizeof(NONCLIENTMETRICS);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS),&ncm,0);
    mWaveFont.CreateFontIndirect(&(ncm.lfMessageFont));
}

void CDPAUDlg::CalcYGridPos()
{
	int i=(m_TopdB-m_BottomdB)/10;//10dB一行,应该只有4行有效
	int j=ValidRect.Height()/(i+2);//分成6份的比例,-30,30dB达不到,但要显示
	int val,top,bottom;
	int k=0;

	memset(&m_stYPos,0,sizeof(STPOSITION)*128);

	if(i<128)
	{
		for(k=0;k<i+1;k++)
		{
			m_stYPos[k].mPosition=ValidRect.top+j*(k+1);
			m_stYPos[k].mPosValue=m_TopdB-10*k;
		}
	}
	//计算0值位置
	i=0;
	while(1)
	{
		if(m_stYPos[i].mPosValue<=0)
		{
			val=m_stYPos[i].mPosValue;
			bottom=m_stYPos[i].mPosition;
			if(i>1)
				top=m_stYPos[i-1].mPosition;
			else
				top=ValidRect.top;
			break;
		}
		i++;
	}
	if(val!=0)
	{
		j=0;
		while(1)
		{
			val++;
			j++;
			if(val==0)
				break;
		}
		m_stYPos[k].mPosition=top+((bottom-top)/10)*(10-j);
		mZeroPos=m_stYPos[k].mPosition;
		m_stYPos[k].mPosValue=0;
	}
	else
	{
		mZeroPos=bottom;
	}

	//增加网格最顶和最底的值
	m_stYPos[k+1].mPosition=ValidRect.bottom;
	m_stYPos[k+1].mPosValue=m_stYPos[k-1].mPosValue-10;

	m_stYPos[k+2].mPosition=ValidRect.top;
	m_stYPos[k+2].mPosValue=m_stYPos[0].mPosValue+10;

	m_stYPos[k+3].mPosition=0;
	m_stYPos[k+3].mPosValue=0;
	
	InsertSort(m_stYPos);
}

void CDPAUDlg::DrawXYGrid(CDC *pDC)
{
	int i;
	CString str;
	
	pDC->SelectClipRgn(&rgnWave);
  	pDC->FillRect(&WaveRect,&brushBack);

	//绘制坐标轴
	pDC->SelectObject(pPenGreenWeight);
	//顶线
	pDC->MoveTo(ValidRect.left,ValidRect.top);
	pDC->LineTo(ValidRect.right,ValidRect.top);
	
	//垂直轴
	pDC->MoveTo(ValidRect.left,ValidRect.top);
	pDC->LineTo(ValidRect.left,ValidRect.bottom);
	//水平轴
	pDC->LineTo(ValidRect.right,ValidRect.bottom);

	//水平网格
	pDC->SetTextColor(RGB(255,255,0));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&mWaveFont);

	i=0;
	while(m_stYPos[i].mPosition!=0)
	{
		//绘制网格,选择浅绿色画笔
    	pDC->SelectObject(pPenGreenLight);
		pDC->MoveTo(ValidRect.left,m_stYPos[i].mPosition);
		pDC->LineTo(ValidRect.right,m_stYPos[i].mPosition);

		//绘制高亮短线段
    	pDC->SelectObject(pPenGreenWeight);
		pDC->MoveTo(ValidRect.left,m_stYPos[i].mPosition);
		pDC->LineTo(ValidRect.left+5,m_stYPos[i].mPosition);
		//刻度文字
		str.Format(_T("%ddB"),m_stYPos[i].mPosValue);
		pDC->TextOut(5,m_stYPos[i].mPosition,str);

		if((m_stYPos[i].mPosValue==0)||(m_stYPos[i].mPosValue==m_TopdB)
			||(m_stYPos[i].mPosValue==m_BottomdB))
		{
			if(m_stYPos[i].mPosValue==0)
			{
    			pDC->SelectObject(pPenGreenWeight);
				pDC->MoveTo(ValidRect.left,m_stYPos[i].mPosition);
				pDC->LineTo(ValidRect.right,m_stYPos[i].mPosition);
			}
			else if((m_stYPos[i].mPosValue==m_TopdB)||(m_stYPos[i].mPosValue==m_BottomdB))
			{
				pDC->SelectObject(pPenGreenLight);
				pDC->MoveTo(ValidRect.left,m_stYPos[i].mPosition);
				pDC->LineTo(ValidRect.right,m_stYPos[i].mPosition);
			}
			pDC->SelectObject(pPenGreenWeight);
			pDC->MoveTo(ValidRect.left+1,m_stYPos[i].mPosition-2);
			pDC->LineTo(ValidRect.left+1,m_stYPos[i].mPosition+3);

			pDC->MoveTo(ValidRect.left+2,m_stYPos[i].mPosition-2);
			pDC->LineTo(ValidRect.left+2,m_stYPos[i].mPosition+3);
		}

		i++;
	}
	//垂直网格
	DrawFreqGrid(pDC,m_StartFreq,m_EndFreq);

	return;
}

void CDPAUDlg::DrawFreqGrid(CDC *pDC,int m_sFreq,int m_eFreq)
{
	//垂直网格,频率横坐标以对数表示
	int i,j,val,carry;
	int step;
	float fLog;

	CString str;
	STDPG stDpg;
	int xLeft=0;
	int m_Interval;
	int xcount=0;

	memset(&stDpg,0,sizeof(STDPG));

	NodesOfFreqRange(m_sFreq,m_eFreq,&stDpg);
	val=m_sFreq;
	step=(int)((ValidRect.right-ValidRect.left)/(log10((float)m_eFreq)-log10((float)m_sFreq)))-4;

	for(i=0;i<stDpg.mCarrys;i++)
	{
		carry=BitsOfNumber(stDpg.mCarryVal[i]);
		for(j=0;j<stDpg.mElements[i];j++)
		{
			val+=(int)pow((double)10,carry-1);

			fLog=(float)(log10((float)val)-log10((float)m_sFreq));
			m_Interval=(int)(ValidRect.left+fLog*step);

	    	pDC->SelectObject(pPenGreenLight);
			pDC->MoveTo(m_Interval,ValidRect.bottom);
			pDC->LineTo(m_Interval,ValidRect.top);

			//绘制高亮短线段
	    	pDC->SelectObject(pPenGreenWeight);
   			pDC->MoveTo(m_Interval,ValidRect.bottom);
			pDC->LineTo(m_Interval,ValidRect.bottom-8);
		}
		//绘制高亮短线段
	    pDC->SelectObject(pPenGreenWeight);

		pDC->MoveTo(m_Interval-1,ValidRect.bottom);
		pDC->LineTo(m_Interval-1,ValidRect.bottom-8);

		pDC->MoveTo(m_Interval+1,ValidRect.bottom);
		pDC->LineTo(m_Interval+1,ValidRect.bottom-8);

		//刻度文字
		str=NumOfFreqStr(stDpg.mCarryVal[i]);
		pDC->TextOut(m_Interval-15,ValidRect.bottom+3,str);
	}

	carry=BitsOfNumber(val);
	for(j=0;j<stDpg.mElements[i];j++)
	{
		val+=(int)pow((double)10,carry);

		fLog=(float)(log10((float)val)-log10((float)m_sFreq));
		m_Interval=(int)(ValidRect.left+fLog*step);

    	pDC->SelectObject(pPenGreenLight);
		pDC->MoveTo(m_Interval,ValidRect.bottom);
		pDC->LineTo(m_Interval,ValidRect.top);
		//绘制高亮短线段
    	pDC->SelectObject(pPenGreenWeight);
		pDC->MoveTo(m_Interval,ValidRect.bottom);
		pDC->LineTo(m_Interval,ValidRect.bottom-8);
	}
 
	pDC->TextOut(ValidRect.top+200,ValidRect.top+20,"10倍频程半对数坐标");
}

void CDPAUDlg::OnTimer(UINT nIDEvent) 
{
	//TODO: Add your message handler code here and/or call default
	m_CtlWave.Invalidate();
	m_CtlWave.UpdateWindow();

    //内存绘图
    if(pWaveDC!=NULL)
    {
		DrawXYGrid(&memDC);
		if(m_Type==1)
		{
			DrawDempWave(&memDC);
		}
		else
		{
			DrawShelvingWave(&memDC);
		}
		pWaveDC->BitBlt(WaveRect.left,WaveRect.top,WaveRect.right,WaveRect.bottom,
			&memDC,0,0,SRCCOPY);
	}

	CDialog::OnTimer(nIDEvent);
}

void CDPAUDlg::DrawShelvingWave(CDC *pDC)
{
	//绘制低通波形
	int y[512],y3[512];
	double pi=3.1415926;
	int i,ny,j,F0,k =0;
	
	double C,L,R,XC,XL,XZ;

	memset(y3,0,sizeof(int)*512);
	j=0;
	C=0.0000047;

	pDC->SelectObject(pPenGreenWeight);
	pDC->SelectClipRgn(&rgnValid);

	F0=2000;	//中心频点暂定为1K
	R=1/(2*pi*F0*C);

	j=0;
	for(i=20;i<20000;i+=FREQ_STEP(i))
	{
		XC=1/(2*pi*i*C);

		if(m_Type==0)
			XZ=XC/(sqrt(R*R+XC*XC))*70;
		else
			XZ=R/(sqrt(R*R+XC*XC))*70;
		if(m_Slope==1)
			XZ=(XZ*XZ)/70;
		y[j]=mZeroPos-(int)XZ;

		y3[j]+=y[j];
		j++;
	}

	//画波形
	pDC->SelectObject(pPenGreenWeight);
	ny=(int)(y[0]);

	pDC->MoveTo(ValidRect.left,ny);
	j=0;
	for(i=20;i<20000;i+=FREQ_STEP(i))
	{
		ny=(int)(y[j++]);
		pDC->LineTo(CalcXPos(20,20000,i,&ValidRect),ny);
   		if(k==0 && ((i<=m_MidFreq[k]+FREQ_STEP(i))&&(i>=m_MidFreq[k]-FREQ_STEP(i))))
   		{
			MouseMoveRect.left=CalcXPos(20,20000,i,&ValidRect)-4;
			MouseMoveRect.right=MouseMoveRect.left+8;
			MouseMoveRect.top=ny-4;
			MouseMoveRect.bottom=MouseMoveRect.top+8;
   		}
	}

	pDC->SelectObject(pPenRedWeight);
	ny=mZeroPos-(int)(mZeroPos*10-(y3[0]));
	pDC->MoveTo(ValidRect.left,ny);
	j=0;
	for(i=20;i<20000;i+=FREQ_STEP(i))
	{
		//画波形
   		ny=mZeroPos-(int)(mZeroPos*10-(y3[j++]));
   		pDC->LineTo(CalcXPos(20,20000,i,&ValidRect),ny);
	}

	pDC->SelectObject(pPenGreenWeight);
	pDC->MoveTo(MouseMoveRect.left,MouseMoveRect.top);
	pDC->LineTo(MouseMoveRect.right,MouseMoveRect.top);
	pDC->LineTo(MouseMoveRect.right,MouseMoveRect.bottom);
	pDC->LineTo(MouseMoveRect.left,MouseMoveRect.bottom);
	pDC->LineTo(MouseMoveRect.left,MouseMoveRect.top);
}

void CDPAUDlg::DrawDempWave(CDC *pDC)
{
	//绘制带通波形
	int y[512],y3[512];
	double pi=3.1415926;
	int i,ny,j,F0,k;
	
	double C,L,R,XC,XL,XZ;

	memset(y3,0,sizeof(int)*512);
	j=0;
	C=0.0022;

	pDC->SelectObject(pPenGreenWeight);
	pDC->SelectClipRgn(&rgnValid);

	for(k=0;k<10;k++)
	{
		F0=m_MidFreq[k];
		L=dd2((pow(1/(2*pi*F0),2))/C); //取DOUBLE后八8位小数,四舍五入
		R=m_QValue*2*pi*F0*L; 

		j=0;
		for(i=20;i<20000;i+=FREQ_STEP(i))
		{
			XC=1/(2*pi*i*C);
			XL=2*pi*i*L;

			//XZ=(XL*XC)/((XL>XC)?(XL-XC):(XC-XL));
			XZ=(XL*XC)/fabs(XL-XC);
			XZ=(m_dBValue[k]*(R*XZ)/(sqrt(R*R+XZ*XZ)))*(4.5/R);
			y[j]=mZeroPos-(int)XZ;

			y3[j]+=y[j];
			j++;
		}

		//画波形
		pDC->SelectObject(pPenGreenWeight);
		ny=(int)(y[0]);
		if(bShow)
			pDC->MoveTo(ValidRect.left,ny);
		j=0;
		for(i=20;i<20000;i+=FREQ_STEP(i))
		{
   			ny=(int)(y[j++]);
			if(bShow)
    			pDC->LineTo(CalcXPos(20,20000,i,&ValidRect),ny);
    		if(k==0 && ((i<=m_MidFreq[k]+FREQ_STEP(i))&&(i>=m_MidFreq[k]-FREQ_STEP(i))))
    		{
				MouseMoveRect.left=CalcXPos(20,20000,i,&ValidRect)-4;
				MouseMoveRect.right=MouseMoveRect.left+8;
				MouseMoveRect.top=ny-4;
				MouseMoveRect.bottom=MouseMoveRect.top+8;
    		}
		}
	}

	pDC->SelectObject(pPenRedWeight);
	ny=mZeroPos-(int)(mZeroPos*10-(y3[0]));
	pDC->MoveTo(ValidRect.left,ny);
	j=0;
	for(i=20;i<20000;i+=FREQ_STEP(i))
	{
		//画波形
   		ny=mZeroPos-(int)(mZeroPos*10-(y3[j++]));
   		pDC->LineTo(CalcXPos(20,20000,i,&ValidRect),ny);
	}

	pDC->SelectObject(pPenGreenWeight);
	pDC->MoveTo(MouseMoveRect.left,MouseMoveRect.top);
	pDC->LineTo(MouseMoveRect.right,MouseMoveRect.top);
	pDC->LineTo(MouseMoveRect.right,MouseMoveRect.bottom);
	pDC->LineTo(MouseMoveRect.left,MouseMoveRect.bottom);
	pDC->LineTo(MouseMoveRect.left,MouseMoveRect.top);
}

void CDPAUDlg::OnCustomdrawSliderFreq1(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	*pResult = 0;
	m_dBValue[0]=15-m_SilderFreq1.GetPos();
	SetDlgItemInt(IDC_EDIT_DB1,m_dBValue[0]);
}

void CDPAUDlg::OnCustomdrawSliderFreq2(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[1]=15-m_SilderFreq2.GetPos();
	SetDlgItemInt(IDC_EDIT_DB2,m_dBValue[1]);
}

void CDPAUDlg::OnCustomdrawSliderFreq10(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[9]=15-m_SilderFreq10.GetPos();
	SetDlgItemInt(IDC_EDIT_DB10,m_dBValue[9]);
}

void CDPAUDlg::OnCustomdrawSliderFreq3(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[2]=15-m_SilderFreq3.GetPos();
	SetDlgItemInt(IDC_EDIT_DB3,m_dBValue[2]);
}

void CDPAUDlg::OnCustomdrawSliderFreq4(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[3]=15-m_SilderFreq4.GetPos();
	SetDlgItemInt(IDC_EDIT_DB4,m_dBValue[3]);
}

void CDPAUDlg::OnCustomdrawSliderFreq5(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[4]=15-m_SilderFreq5.GetPos();
	SetDlgItemInt(IDC_EDIT_DB5,m_dBValue[4]);
}

void CDPAUDlg::OnCustomdrawSliderFreq6(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[5]=15-m_SilderFreq6.GetPos();
	SetDlgItemInt(IDC_EDIT_DB6,m_dBValue[5]);
}

void CDPAUDlg::OnCustomdrawSliderFreq7(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[6]=15-m_SilderFreq7.GetPos();
	SetDlgItemInt(IDC_EDIT_DB7,m_dBValue[6]);
}

void CDPAUDlg::OnCustomdrawSliderFreq8(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[7]=15-m_SilderFreq8.GetPos();
	SetDlgItemInt(IDC_EDIT_DB8,m_dBValue[7]);
}

void CDPAUDlg::OnCustomdrawSliderFreq9(NMHDR* pNMHDR,LRESULT* pResult) 
{
	//TODO: Add your control notification handler code here
	
	*pResult = 0;
	m_dBValue[8]=15-m_SilderFreq9.GetPos();
	SetDlgItemInt(IDC_EDIT_DB9,m_dBValue[8]);
}

void CDPAUDlg::OnLButtonDown(UINT nFlags,CPoint point) 
{
	//TODO: Add your message handler code here and/or call default
	if(point.x>MouseMoveRect.left && point.x<MouseMoveRect.right
		&&point.y>MouseMoveRect.top && point.y<MouseMoveRect.bottom)
	{
		bLDown=TRUE;
	}
	else
	{
		bLDown=FALSE;
	}
	CDialog::OnLButtonDown(nFlags,point);
}

void CDPAUDlg::OnMouseMove(UINT nFlags,CPoint point) 
{
	//TODO: Add your message handler code here and/or call default
	if((point.x>=MouseMoveRect.left && point.x<=MouseMoveRect.right
		&&point.y>=MouseMoveRect.top && point.y<=MouseMoveRect.bottom)||bLDown)
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
	}

	if(m_MousePoint.x!=0 && m_MousePoint.y!=0 && bLDown)
	{
		if(m_MousePoint.y<=mZeroPos)
		{
			m_dBValue[0]=-(m_MousePoint.y-mZeroPos)/4.5;
		}
		else
		{
			m_dBValue[0]=(mZeroPos-m_MousePoint.y)/4.5;
		}
		SetDlgItemInt(IDC_EDIT_DB1,m_dBValue[0]);
		m_SilderFreq1.SetPos(15-m_dBValue[0]);
	}

	if(m_MousePoint.x!=0 && m_MousePoint.y!=0 && bLDown)
	{
		if(m_MousePoint.x<point.x)
		{
			if(m_MidFreq[0]<20000)
			{
				m_MidFreq[0]=CalcFreq(m_MousePoint.x,20,20000,&ValidRect);
				SetDlgItemInt(IDC_EDIT_FREQ1,m_MidFreq[0]);
			}
		}
		else if(m_MousePoint.x>point.x)
		{
			if(m_MidFreq[0]>20)
			{
				m_MidFreq[0]=CalcFreq(m_MousePoint.x,20,20000,&ValidRect);
				SetDlgItemInt(IDC_EDIT_FREQ1,m_MidFreq[0]);
			}
		}
	}

	m_MousePoint=point;
	CDialog::OnMouseMove(nFlags,point);
}

void CDPAUDlg::OnLButtonUp(UINT nFlags,CPoint point) 
{
	//TODO: Add your message handler code here and/or call default
	bLDown=FALSE;	
	CDialog::OnLButtonUp(nFlags,point);
}

BOOL CDPAUDlg::PreTranslateMessage(MSG* pMsg) 
{
	//TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)
    {
    	//把回车键转换成TAB键
		if(pMsg->wParam==VK_RETURN)
		{
			pMsg->wParam=VK_TAB;
			//return TRUE;
		}
		if(pMsg->wParam==VK_ESCAPE)
		{
			return TRUE;
		}
    }	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDPAUDlg::OnKillfocusEditFreq10() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[9]=GetDlgItemInt(IDC_EDIT_FREQ10);
}

void CDPAUDlg::OnKillfocusEditFreq9() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[8]=GetDlgItemInt(IDC_EDIT_FREQ9);
}

void CDPAUDlg::OnKillfocusEditFreq8() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[7]=GetDlgItemInt(IDC_EDIT_FREQ8);
}

void CDPAUDlg::OnKillfocusEditFreq7() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[6]=GetDlgItemInt(IDC_EDIT_FREQ7);
}

void CDPAUDlg::OnKillfocusEditFreq6() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[5]=GetDlgItemInt(IDC_EDIT_FREQ6);
}

void CDPAUDlg::OnKillfocusEditFreq5() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[4]=GetDlgItemInt(IDC_EDIT_FREQ5);
}

void CDPAUDlg::OnKillfocusEditFreq4() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[3]=GetDlgItemInt(IDC_EDIT_FREQ4);
}

void CDPAUDlg::OnKillfocusEditFreq3() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[2]=GetDlgItemInt(IDC_EDIT_FREQ3);
}

void CDPAUDlg::OnKillfocusEditFreq2() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[1]=GetDlgItemInt(IDC_EDIT_FREQ2);
}

void CDPAUDlg::OnKillfocusEditFreq1() 
{
	//TODO: Add your control notification handler code here
	m_MidFreq[0]=GetDlgItemInt(IDC_EDIT_FREQ1);
}

void CDPAUDlg::OnButtonShow() 
{
	//TODO: Add your control notification handler code here
	bShow=!bShow;
}

void CDPAUDlg::OnButtonFlateq() 
{
	//TODO: Add your control notification handler code here
	int i;
	for(i=0;i<10;i++)
		m_dBValue[i]=0;

	m_SilderFreq1.SetPos(15);
	m_SilderFreq2.SetPos(15);
	m_SilderFreq3.SetPos(15);
	m_SilderFreq4.SetPos(15);
	m_SilderFreq5.SetPos(15);
	m_SilderFreq6.SetPos(15);
	m_SilderFreq7.SetPos(15);
	m_SilderFreq8.SetPos(15);
	m_SilderFreq9.SetPos(15);
	m_SilderFreq10.SetPos(15);
}

void CDPAUDlg::OnDeltaposSpinValue(NMHDR* pNMHDR,LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	//TODO: Add your control notification handler code here
	*pResult = 0;
	m_QValue=pNMUpDown->iPos/10.0;
	sprintf(cQText,"%01f",m_QValue);
	SetDlgItemText(IDC_EDIT_QVALUE,cQText);
}

void CDPAUDlg::OnSelchangeComboType() 
{
	//TODO: Add your control notification handler code here
	m_Type=m_ComboType.GetCurSel();
	if(m_Type==1)
	{
		SetDlgItemText(IDC_STATIC_Q,"Q");
		::ShowWindow(GetDlgItem(IDC_COMBO_SLOPE)->GetSafeHwnd(),SW_HIDE);
		::ShowWindow(GetDlgItem(IDC_EDIT_QVALUE)->GetSafeHwnd(),SW_SHOW);
		::ShowWindow(GetDlgItem(IDC_SPIN_VALUE)->GetSafeHwnd(),SW_SHOW);
	}
	else
	{
		::ShowWindow(GetDlgItem(IDC_EDIT_QVALUE)->GetSafeHwnd(),SW_HIDE);
		::ShowWindow(GetDlgItem(IDC_SPIN_VALUE)->GetSafeHwnd(),SW_HIDE);
		::ShowWindow(GetDlgItem(IDC_COMBO_SLOPE)->GetSafeHwnd(),SW_SHOW);
		SetDlgItemText(IDC_STATIC_Q,"Slope");
	}
}

void CDPAUDlg::OnSelchangeComboSlope() 
{
	// TODO: Add your control notification handler code here
	m_Slope=m_ComboSlope.GetCurSel();
}
