#include "WebBrowser.h"
/*
 * ==================
 * |   构造和析构   |
 * ==================
 * */
WebBrowser::WebBrowser(void):
    _refNum(0),
    _rcWebWnd(0),
    _bInPlaced(false),
    _bExternalPlace(false),
    _bCalledCanInPlace(false),
    _bWebWndInited(false),
    _pOleObj(NULL), 
    _pInPlaceObj(NULL), 
    _pStorage(NULL), 
    _pWB2(NULL), 
    _pHtmlDoc2(NULL), 
    _pHtmlDoc3(NULL), 
    _pHtmlWnd2(NULL), 
    _pHtmlEvent(NULL)
{
    ::memset( (PVOID)&_rcWebWnd,0,sizeof(_rcWebWnd));
    HRTEST_SE( OleInitialize(0),L"Ole初始化错误");
    HRTEST_SE( StgCreateDocfile(0,STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE,0,&_pStorage),L"StgCreateDocfile错误");
    HRTEST_SE( OleCreate(CLSID_WebBrowser,IID_IOleObject,OLERENDER_DRAW,0,this,_pStorage,(void**)&_pOleObj),L"Ole创建失败");
    HRTEST_SE( _pOleObj->QueryInterface(IID_IOleInPlaceObject,(LPVOID*)&_pInPlaceObj),L"OleInPlaceObject创建失败");
RETURN:
    return;
}
WebBrowser::~WebBrowser(void)
{
}
/*
   ==================
   |IUnknown methods|
   ==================
   */
STDMETHODIMP WebBrowser::QueryInterface(REFIID iid,void**ppvObject)
{
    *ppvObject = 0;
    if ( iid == IID_IOleClientSite )
        *ppvObject = (IOleClientSite*)this;
    if ( iid == IID_IUnknown )
        *ppvObject = this;
    if ( iid == IID_IDispatch )
        *ppvObject = (IDispatch*)this;
    if ( _bExternalPlace == false)
    {
        if ( iid == IID_IOleInPlaceSite )
            *ppvObject = (IOleInPlaceSite*)this;
        if ( iid == IID_IOleInPlaceFrame )
            *ppvObject = (IOleInPlaceFrame*)this;
        if ( iid == IID_IOleInPlaceUIWindow )
            *ppvObject = (IOleInPlaceUIWindow*)this;
    }
    /*
       这里是一点走私货, 留在以后讲,如果有机会,你可以发现,原来如此简单.
       if ( iid == DIID_DWebBrowserEvents2 )
     *ppvObject = (DWebBrowserEvents2 *)this;
     if ( iid == IID_IDocHostUIHandler)
     *ppvObject = (IDocHostUIHandler*)this;
     */
    if ( *ppvObject )
    {
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}
STDMETHODIMP_(ULONG)  WebBrowser::AddRef()
{
    return ::InterlockedIncrement( &_refNum );
}
STDMETHODIMP_(ULONG)  WebBrowser::Release()
{
    return ::InterlockedDecrement( &_refNum );
}
/*
   =====================
   | IDispatch Methods |
   =====================
   */
HRESULT _stdcall WebBrowser::GetTypeInfoCount(
        unsigned int * pctinfo) 
{
    return E_NOTIMPL;
}
HRESULT _stdcall WebBrowser::GetTypeInfo(
        unsigned int iTInfo,
        LCID lcid,
        ITypeInfo FAR* FAR* ppTInfo) 
{
    return E_NOTIMPL;
}
HRESULT _stdcall WebBrowser::GetIDsOfNames(REFIID riid, 
        OLECHAR FAR* FAR* rgszNames, 
        unsigned int cNames, 
        LCID lcid, 
        DISPID FAR* rgDispId )
{
    return E_NOTIMPL;
}
HRESULT _stdcall WebBrowser::Invoke(
        DISPID dispIdMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS* pDispParams,
        VARIANT* pVarResult,
        EXCEPINFO* pExcepInfo,
        unsigned int* puArgErr)
{
    /* 走私货,留在以后讲,是关于DWebBrowserEvents2让人激动的实现,而且简单.
    // DWebBrowserEvents2
    if( dispIdMember == DISPID_DOCUMENTCOMPLETE)
    {
    DocumentComplete(pDispParams->rgvarg[1].pdispVal,pDispParams->rgvarg[0].pvarVal);
    return S_OK;
    }
    if( dispIdMember == DISPID_BEFORENAVIGATE2)
    {
    BeforeNavigate2( pDispParams->rgvarg[6].pdispVal,
    pDispParams->rgvarg[5].pvarVal,
    pDispParams->rgvarg[4].pvarVal,
    pDispParams->rgvarg[3].pvarVal,
    pDispParams->rgvarg[2].pvarVal,
    pDispParams->rgvarg[1].pvarVal,
    pDispParams->rgvarg[0].pboolVal);
    return S_OK;
    }
    */
    return E_NOTIMPL;
}
/*
   ========================
   |IOleClientSite methods|
   ========================
   */
STDMETHODIMP WebBrowser::SaveObject()
{
    return S_OK;
}
STDMETHODIMP WebBrowser::GetMoniker(DWORD dwA,DWORD dwW,IMoniker**pm)
{
    *pm = 0;
    return E_NOTIMPL;
}
STDMETHODIMP WebBrowser::GetContainer(IOleContainer**pc)
{
    *pc = 0;
    return E_FAIL;
}
STDMETHODIMP WebBrowser::ShowObject()
{
    return S_OK;
}
STDMETHODIMP WebBrowser::OnShowWindow(BOOL f)
{
    return S_OK;
}
STDMETHODIMP WebBrowser::RequestNewObjectLayout()
{
    return S_OK;
}
/*
   =========================
   |IOleInPlaceSite methods|
   =========================
   */
STDMETHODIMP WebBrowser::GetWindow(HWND *p)
{
    *p = GetHWND();
    return S_OK;
}
STDMETHODIMP WebBrowser::ContextSensitiveHelp(BOOL)
{
    return E_NOTIMPL;
}
STDMETHODIMP WebBrowser::CanInPlaceActivate()//If this function return S_FALSE, AX cannot activate in place!
{
    if ( _bInPlaced )//Does WebBrowser Control already in placed?
    {
        _bCalledCanInPlace = true;
        return S_OK;
    }
    return S_FALSE;
}
STDMETHODIMP WebBrowser::OnInPlaceActivate()
{
    return S_OK;
}
STDMETHODIMP WebBrowser::OnUIActivate()
{
    return S_OK;
}
STDMETHODIMP WebBrowser::GetWindowContext(IOleInPlaceFrame** ppFrame,IOleInPlaceUIWindow **ppDoc,LPRECT r1,LPRECT r2,LPOLEINPLACEFRAMEINFO o)
{

    *ppFrame = (IOleInPlaceFrame*)this;
    AddRef();
    *ppDoc = NULL;
    ::GetClientRect(  GetHWND() ,&_rcWebWnd );
    *r1 = _rcWebWnd;
    *r2 = _rcWebWnd;
    o->cb = sizeof(OLEINPLACEFRAMEINFO);
    o->fMDIApp = false;
    o->hwndFrame = GetParent( GetHWND() );
    o->haccel = 0;
    o->cAccelEntries = 0;

    return S_OK;
}
STDMETHODIMP WebBrowser::Scroll(SIZE s)
{
    return E_NOTIMPL;
}
STDMETHODIMP WebBrowser::OnUIDeactivate(int)
{
    return S_OK;
}
STDMETHODIMP WebBrowser::OnInPlaceDeactivate()
{
    return S_OK;
}
STDMETHODIMP WebBrowser::DiscardUndoState()
{
    return S_OK;
}
STDMETHODIMP WebBrowser::DeactivateAndUndo()
{
    return S_OK;
}
STDMETHODIMP WebBrowser::OnPosRectChange(LPCRECT)
{
    return S_OK;
}
/*
   ==========================
   |IOleInPlaceFrame methods|
   ==========================
   */
STDMETHODIMP WebBrowser::GetBorder(LPRECT l)
{
    ::GetClientRect(  GetHWND() ,&_rcWebWnd );
    *l = _rcWebWnd;
    return S_OK;
}
STDMETHODIMP WebBrowser::RequestBorderSpace(LPCBORDERWIDTHS b)
{
    return S_OK;
}
STDMETHODIMP WebBrowser::SetBorderSpace(LPCBORDERWIDTHS b)
{
    return S_OK;
}
STDMETHODIMP WebBrowser::SetActiveObject(IOleInPlaceActiveObject*pV,LPCOLESTR s)
{
    return S_OK;
}
STDMETHODIMP WebBrowser::SetStatusText(LPCOLESTR t)
{
    return E_NOTIMPL;
}
STDMETHODIMP WebBrowser::EnableModeless(BOOL f)
{
    return E_NOTIMPL;
}
STDMETHODIMP WebBrowser::TranslateAccelerator(LPMSG,WORD)
{
    return E_NOTIMPL;
}
HRESULT _stdcall WebBrowser::RemoveMenus(HMENU h)
{
    return E_NOTIMPL;
}
HRESULT _stdcall WebBrowser::InsertMenus(HMENU h,LPOLEMENUGROUPWIDTHS x)
{
    return E_NOTIMPL;
}
HRESULT _stdcall WebBrowser::SetMenu(HMENU h,HOLEMENU hO,HWND hw)
{
    return E_NOTIMPL;
}
/*
   ====================
   |DWebBrowserEvents2|
   ====================
   */
/*  走私货,以后再讲
    void 
    WebBrowser::DocumentComplete( IDispatch *pDisp,VARIANT *URL)
    {
//老天保佑,多好的函数啊.
return ;
}
void 
WebBrowser::BeforeNavigate2( IDispatch *pDisp,VARIANT *&url,VARIANT *&Flags,VARIANT *&TargetFrameName,VARIANT *&PostData,VARIANT *&Headers,VARIANT_BOOL *&Cancel)
{
PCWSTR pcwApp = L"app:";
if( url->vt != VT_BSTR )
return;
if( 0 == _wcsnicmp( pcwApp, url->bstrVal,wcslen(pcwApp)) )
{
 *Cancel = VARIANT_TRUE;
 _OnHtmlCmd( url->bstrVal+wcslen(pcwApp) );
 return;
 }
 *Cancel = VARIANT_FALSE;
 }
 */
/*
   ===============
   |Other Methods|
   ===============
   */
    IWebBrowser2* 
WebBrowser::GetWebBrowser2()
{
    if( _pWB2 != NULL )
        return _pWB2;
    NULLTEST_SE( _pOleObj,L"Ole对象为空");
    HRTEST_SE( _pOleObj->QueryInterface(IID_IWebBrowser2,(void**)&_pWB2),L"QueryInterface IID_IWebBrowser2 失败");
    return _pWB2;
RETURN:
    return NULL;
}
    IHTMLDocument2*    
WebBrowser::GetHTMLDocument2()
{
    if( _pHtmlDoc2 != NULL )
        return _pHtmlDoc2;
    IWebBrowser2* pWB2 = NULL;
    NULLTEST(pWB2 = GetWebBrowser2());//GetWebBrowser2已经将错误原因交给LastError.
    IDispatch* pDp =  NULL;
    HRTEST_SE(pWB2->get_Document(&pDp),L"DWebBrowser2::get_Document 错误");
    HRTEST_SE(pDp->QueryInterface(IID_IHTMLDocument2,(void**)&_pHtmlDoc2),L"QueryInterface IID_IHTMLDocument2 失败");
    return _pHtmlDoc2;
RETURN:
    return NULL;
}
    IHTMLDocument3*    
WebBrowser::GetHTMLDocument3()
{
    if( _pHtmlDoc3 != NULL )
        return _pHtmlDoc3;
    IWebBrowser2* pWB2 = NULL;
    NULLTEST(pWB2 = GetWebBrowser2());//GetWebBrowser2已经将错误原因交给LastError.
    IDispatch* pDp =  NULL;
    HRTEST_SE(pWB2->get_Document(&pDp),L"DWebBrowser2::get_Document 错误");
    HRTEST_SE(pDp->QueryInterface(IID_IHTMLDocument3,(void**)&_pHtmlDoc3),L"QueryInterface IID_IHTMLDocument3 失败");
    return _pHtmlDoc3;
RETURN:
    return NULL;
}
    IHTMLWindow2*
WebBrowser::GetHTMLWindow2()
{
    if( _pHtmlWnd2 != NULL)
        return _pHtmlWnd2;
    IHTMLDocument2*  pHD2 = GetHTMLDocument2();
    NULLTEST( pHD2 );
    HRTEST_SE( pHD2->get_parentWindow(&_pHtmlWnd2),L"IHTMLWindow2::get_parentWindow 错误" );
    return _pHtmlWnd2;
RETURN:
    return NULL;
}
    IHTMLEventObj*   
WebBrowser::GetHTMLEventObject()
{
    if( _pHtmlEvent != NULL )
        return _pHtmlEvent;
    IHTMLWindow2* pHW2;
    NULLTEST( pHW2 = GetHTMLWindow2() );
    HRTEST_SE( pHW2->get_event(&_pHtmlEvent),L"IHTMLWindow2::get_event 错误");
    return _pHtmlEvent;
RETURN:
    return NULL;
}
    BOOL       
WebBrowser::SetWebRect(LPRECT lprc)
{
    BOOL bRet = FALSE;
    if( false == _bInPlaced )//尚未OpenWebBrowser操作,直接写入_rcWebWnd
    {
        _rcWebWnd = *lprc;
    }
    else//已经打开WebBrowser,通过 IOleInPlaceObject::SetObjectRects 调整大小
    {
        SIZEL size;
        size.cx = RECTWIDTH(*lprc);
        size.cy = RECTHEIGHT(*lprc);
        IOleObject* pOleObj;
        NULLTEST( pOleObj= _GetOleObject());
        HRTEST_E( pOleObj->SetExtent(  1,&size ),L"SetExtent 错误");
        IOleInPlaceObject* pInPlace;
        NULLTEST( pInPlace = _GetInPlaceObject());
        HRTEST_E( pInPlace->SetObjectRects(lprc,lprc),L"SetObjectRects 错误");
        _rcWebWnd = *lprc;
    }
    bRet = TRUE;
RETURN:
    return bRet;
}
    BOOL    
WebBrowser::OpenWebBrowser()
{
    BOOL bRet = FALSE;
    NULLTEST_E( _GetOleObject(),L"ActiveX对象为空" );//对于本身的实现函数,其自身承担错误录入工作

    if( (RECTWIDTH(_rcWebWnd) && RECTHEIGHT(_rcWebWnd)) == 0 )
        ::GetClientRect( GetHWND() ,&_rcWebWnd);//设置WebBrowser的大小为窗口的客户区大小.

    if( _bInPlaced == false )// Activate In Place
    {
        _bInPlaced = true;//_bInPlaced must be set as true, before INPLACEACTIVATE, otherwise, once DoVerb, it would return error;
        _bExternalPlace = 0;//lParam;

        HRTEST_E( _GetOleObject()->DoVerb(OLEIVERB_INPLACEACTIVATE,0,this,0, GetHWND()  ,&_rcWebWnd),L"关于INPLACE的DoVerb错误");
        _bInPlaced = true;


        //*  挂接DWebBrwoser2Event
        IConnectionPointContainer* pCPC = NULL;
        IConnectionPoint*          pCP  = NULL;
        HRTEST_E(
                GetWebBrowser2()->QueryInterface(IID_IConnectionPointContainer,(void**)&pCPC),L"枚举IConnectionPointContainer接口失败");
        HRTEST_E( pCPC->FindConnectionPoint(
                    DIID_DWebBrowserEvents2,&pCP),L"FindConnectionPoint失败");
        DWORD dwCookie = 0;
        HRTEST_E( pCP->Advise(
                    (IUnknown*)(void*)this,&dwCookie),L"IConnectionPoint::Advise失败");
    }
    bRet = TRUE;
RETURN:
    return bRet;
}
    BOOL    
WebBrowser::OpenURL(VARIANT* pVarUrl)
{
    BOOL bRet = FALSE;
    HRTEST_E(
            GetWebBrowser2()->Navigate2(
                pVarUrl,0,0,0,0),L"GetWebBrowser2
            失败");
    bRet = TRUE;
RETURN:
    return bRet;
}
