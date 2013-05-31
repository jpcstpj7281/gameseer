// ButtonST.cpp : implementation file

#include "stdafx.h"
#include "ButtonST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonST

static unsigned short bCheckMask[]=
{
	0x0000,0x0000,0x000c,0x000c,0x003c,0x003c,0xc0fc,0xc0fc,
	0xf3f0,0xf3f0,0xffc0,0xffc0,0x3f00,0x3f00,0x0c00,0x0c00
};

CButtonST::CButtonST()
{
	bInitialCDC=FALSE;
	m_bIsFlat=FALSE;
	mBitmapID=0;
	pBKDC=NULL;
	lBStyle=0;
	m_bImage=FALSE;

    //创建字体
    NONCLIENTMETRICS ncm;
    ncm.cbSize=sizeof(NONCLIENTMETRICS);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS),&ncm,0);
    m_Font.CreateFontIndirect(&(ncm.lfMessageFont));
}

CButtonST::~CButtonST()
{
}

BEGIN_MESSAGE_MAP(CButtonST,CButton)
	//{{AFX_MSG_MAP(CButtonST)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonST message handlers
void CButtonST::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC=CDC::FromHandle(lpDIS->hDC);
	CWnd *pParentWnd;
	CPen penBtnHiLight;
	CPen penBtnShadow;

	CRect rect;
	CString sTitle;
	CRect BtnRect,ParentRect;
	BOOL bIsFocused;
	BOOL bIsPressed;
	
	bIsPressed=(lpDIS->itemState&ODS_SELECTED);
  	bIsFocused=(lpDIS->itemState&ODS_FOCUS);

	GetWindowRect(&BtnRect);
	pParentWnd=GetParentOwner();
	pParentWnd->GetWindowRect(&ParentRect);

	InitMemCDC(pDC,BtnRect);

	GetWindowText(sTitle);

	rect.left=lpDIS->rcItem.left;
	rect.top=lpDIS->rcItem.top;
	rect.right=lpDIS->rcItem.right;
	rect.bottom=lpDIS->rcItem.bottom;

	m_BuffDC.SetBkMode(TRANSPARENT);

	if(pBKDC!=NULL)
	{
		m_BuffDC.BitBlt(0,0,RWIDTH(rect),RHIGHT(rect),pBKDC,
			BtnRect.left-ParentRect.left,BtnRect.top-ParentRect.top,SRCCOPY);
	}
	else
	{
		CBrush brushBackground(RGB(236,233,216));
		m_BuffDC.FillRect(rect,&brushBackground);
	}

	if(m_bImage)
	{
		ImageOpen(&m_BuffDC,szImageFileName);
	}
	else
	{
		DrawTransparentBitmap(&m_BuffDC,mBitmapID,rect,RGB(0,0,0));
	}

	if(bIsPressed||m_bIsFlat)
	{
		penBtnHiLight.CreatePen(PS_SOLID,2,GetSysColor(COLOR_BTNSHADOW));
		penBtnShadow.CreatePen(PS_SOLID,2,GetSysColor(COLOR_BTNHILIGHT));

		CBrush brushBackground(RGB(0,255,0));
		m_BuffDC.FillRect(rect,&brushBackground);
	}
	else
	{
		penBtnShadow.CreatePen(PS_SOLID,2,GetSysColor(COLOR_BTNSHADOW));
		penBtnHiLight.CreatePen(PS_SOLID,2,GetSysColor(COLOR_BTNHILIGHT));

		CBrush brushBackground(RGB(210,210,210));
		m_BuffDC.FillRect(rect,&brushBackground);
	}

	if(bIsFocused&& !m_bIsFlat)
	{
		CBrush brushBackground(RGB(128,128,128));
		m_BuffDC.FillRect(rect,&brushBackground);
	}
	if(bIsFocused||m_bIsFlat)
	{
		m_BuffDC.SelectObject(penBtnHiLight);
        m_BuffDC.MoveTo(lpDIS->rcItem.left,lpDIS->rcItem.bottom-1);
        m_BuffDC.LineTo(lpDIS->rcItem.left,lpDIS->rcItem.top);
        m_BuffDC.LineTo(lpDIS->rcItem.right,lpDIS->rcItem.top);

        //Disegno i bordi a destra e in basso
        //Dark gray line
        m_BuffDC.SelectObject(penBtnShadow);
        m_BuffDC.MoveTo(lpDIS->rcItem.left,lpDIS->rcItem.bottom-1);
        m_BuffDC.LineTo(lpDIS->rcItem.right-1,lpDIS->rcItem.bottom-1);
        m_BuffDC.LineTo(lpDIS->rcItem.right-1,lpDIS->rcItem.top-1);
	}

	if(lBStyle&BS_CHECKBOX)
	{
		unsigned short Mask;
		unsigned char i,j;
		unsigned long lx,ty;
		lx=rect.right-16*2;
		ty=rect.top+(rect.Height()-16)/2;
		for(i=0;i<16;i++)
		{
			Mask=0x8000;
			for(j=0;j<16;j++)
			{
				if(Mask&bCheckMask[i])
					m_BuffDC.SetPixel(lx+j,ty+i,RGB(0,0,0));
				Mask>>=1;
			}
		}
	}
	if(lBStyle&WS_BORDER)
	{
        m_BuffDC.SelectObject(&penBtnHiLight);
        m_BuffDC.MoveTo(rect.left,rect.bottom-1);
        m_BuffDC.LineTo(rect.left,rect.top);
        m_BuffDC.LineTo(rect.right,rect.top);

        m_BuffDC.SelectObject(penBtnShadow);
        m_BuffDC.MoveTo(rect.left,rect.bottom-1);
        m_BuffDC.LineTo(rect.right-1,rect.bottom-1);
        m_BuffDC.LineTo(rect.right-1,rect.top-1);
	}

	m_BuffDC.SelectObject(&m_Font);
	if(lBStyle&BS_LEFTTEXT)
	{
		m_BuffDC.DrawText(sTitle,-1,rect,DT_SINGLELINE|DT_BOTTOM|DT_VCENTER|DT_LEFT);
	}
	else
	{
		m_BuffDC.DrawText(sTitle,-1,rect,DT_SINGLELINE|DT_BOTTOM|DT_VCENTER|DT_CENTER);
	}

	pDC->BitBlt(0,0,RWIDTH(rect),RHIGHT(rect),&m_BuffDC,0,0,SRCCOPY);
}

void CButtonST::SetBitmapID(int nID,CDC *pParentDC)
{
	mBitmapID=nID;
	pBKDC=pParentDC;
}

void CButtonST::InitMemCDC(CDC *pDC,CRect bRect)
{
	if(bInitialCDC==TRUE)
		return;

	CBitmap m_temp;

	m_BuffDC.CreateCompatibleDC(pDC);

	m_temp.CreateCompatibleBitmap(pDC,RWIDTH(bRect),RHIGHT(bRect));
	m_BuffDC.SelectObject(&m_temp);

	bInitialCDC=TRUE;
}

void CButtonST::OnMouseMove(UINT nFlags,CPoint point)
{
}

void CButtonST::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
}

void CButtonST::SetFlat(BOOL bState)
{
  	m_bIsFlat=bState;
  	Invalidate();
}

void CButtonST::SetOwnerStyle(LONG lStyle)
{
  	lBStyle=lStyle;
  	Invalidate();
}

void CButtonST::SetImageFile(char *szFilename)
{
	m_bImage=TRUE;
	_tcscpy(szImageFileName,szFilename);

	Invalidate();
}

void CButtonST::ImageOpen(CDC *pDC,char *szFilename)
{
	TCHAR *m_szFileExt;
	HDC hDC=pDC->GetSafeHdc();

	m_szFileExt=szFilename+_tcslen(szFilename)-3;

	pDC->TextOut(5,5,szFilename,strlen(szFilename));

	if((strcmp(m_szFileExt,"bmp")==0)||(strcmp(m_szFileExt,"BMP")==0))
	{
		BITMAP bmpInfo;
		HDC hTempDC;	//临时图层
		HBITMAP hbitmap;
		hbitmap=(HBITMAP)::LoadImage(NULL,szFilename,
			IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		GetObject(hbitmap,sizeof(BITMAP),(LPSTR)&bmpInfo);

		hTempDC=CreateCompatibleDC(hDC);
		SelectObject(hTempDC,hbitmap);

		BitBlt(hDC,5,30,bmpInfo.bmWidth,bmpInfo.bmHeight,hTempDC,0,0,SRCCOPY);

		DeleteObject(hbitmap);
		DeleteObject(hbitmap);

		return;
	}
	else
	{
		//显示其他类型的图形文件
		IStream *pStm;
		IPicture *pPic;
		HANDLE hFile=INVALID_HANDLE_VALUE;
		HGLOBAL hGlobal;
		DWORD lsize;
		DWORD hsize;
		DWORD dwBytesRead;
		LPVOID pvData=NULL;
		double fX,fY;
		OLE_XSIZE_HIMETRIC hmWidth; 
		OLE_YSIZE_HIMETRIC hmHeight; 
		//获取文件长度
		hFile=CreateFile(szFilename,GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);	//读写共享
		if(hFile==INVALID_HANDLE_VALUE)
			return;
		lsize=GetFileSize(hFile,&hsize);
		hGlobal=GlobalAlloc(GMEM_MOVEABLE,lsize);
		if(hGlobal!=NULL)
		{
			if((pvData=GlobalLock(hGlobal))!=NULL)
			{
				ReadFile(hFile,pvData,lsize,&dwBytesRead,NULL);
				GlobalUnlock(hGlobal);
				CreateStreamOnHGlobal(hGlobal,TRUE,&pStm);
				if(SUCCEEDED(OleLoadPicture(pStm,lsize,FALSE,IID_IPicture,(LPVOID*)&pPic)))
				{
					pStm->Release();
					pStm=NULL;
					pPic->get_Width(&hmWidth); 
					pPic->get_Height(&hmHeight); 

					fX=(double)GetDeviceCaps(hDC,HORZRES)*(double)hmWidth/((double)GetDeviceCaps(hDC,HORZSIZE)*100.0); 
					fY=(double)GetDeviceCaps(hDC,VERTRES)*(double)hmHeight/((double)GetDeviceCaps(hDC,VERTSIZE)*100.0); 

					pPic->Render(hDC,5,30,(DWORD)620,(DWORD)470,0,hmHeight,hmWidth,-hmHeight,NULL);
					pPic->Release();
					pPic=NULL;
				}
			}
		}
		CloseHandle(hFile);
	}
}
void CButtonST::DrawTransparentBitmap(CDC *pDC,UINT IDImage,CRect &rect,COLORREF rgbMask)
{
	//将特定背景色作为透明来显示图象
	BITMAP bm;
	CBitmap bmAndObject,bmAndMem,mBitmap;
	CDC cdcMem,cdcObject,cdcTemp;   
	POINT ptSize;   

	if(IDImage==NULL)
		return;
	mBitmap.LoadBitmap(IDImage);
	cdcTemp.CreateCompatibleDC(pDC);
	cdcTemp.SelectObject(&mBitmap);

	mBitmap.GetBitmap(&bm);
	ptSize.x=bm.bmWidth;			//Get width of bitmap   
	ptSize.y=bm.bmHeight;			//Get height of bitmap   
	cdcTemp.DPtoLP(&ptSize,1);		//Convert from device to logical points   
    
	//Create some DCs to hold temporary data.   
	cdcObject.CreateCompatibleDC(pDC);
	cdcMem.CreateCompatibleDC(pDC);
    
	//Monochrome DC   
	bmAndObject.CreateBitmap(ptSize.x,ptSize.y,1,1,NULL);
	bmAndMem.CreateCompatibleBitmap(pDC,ptSize.x,ptSize.y); 
    
	//Each DC must select a bitmap object to store pixel data.   
	cdcObject.SelectObject(bmAndObject);
	cdcMem.SelectObject(bmAndMem);
    
	//Set proper mapping mode.   
	cdcTemp.SetMapMode(pDC->GetMapMode());   
    
	//Set the background color of the source DC to the color. 
	//contained in the parts of the bitmap that should be transparent 
	cdcTemp.SetBkColor(rgbMask); 
  
	//Create the object mask for the bitmap by performing a BitBlt 
	//from the source bitmap to a monochrome bitmap. 
	cdcObject.BitBlt(0,0,ptSize.x,ptSize.y,&cdcTemp,0,0,SRCCOPY); 
	//Copy the background of the main DC to the destination. 
	cdcMem.BitBlt(0,0,ptSize.x,ptSize.y,pDC,rect.left,rect.top,SRCCOPY);
	//Mask out the places where the bitmap will be placed. 
	cdcMem.BitBlt(0,0,ptSize.x,ptSize.y,&cdcObject,0,0,SRCAND);
	//XOR the bitmap with the background on the destination DC. 
	cdcMem.BitBlt(0,0,ptSize.x,ptSize.y,&cdcTemp,0,0,SRCPAINT); 
	//Copy the destination to the screen. 
  	pDC->BitBlt(rect.left,rect.top,ptSize.x,ptSize.y,&cdcMem,0,0,SRCCOPY); 

	//Delete the memory bitmaps. 
	DeleteObject(bmAndObject); 
  	DeleteObject(bmAndMem); 
  	DeleteObject(mBitmap);
  
  	//Delete the memory DCs. 
  	DeleteDC(cdcMem); 
  	DeleteDC(cdcObject); 
	DeleteDC(cdcTemp); 
}
