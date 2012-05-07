#define UNICODE

#include <windows.h>
#include "SDL_syswm.h"
#include <string>
#include "native.h"


/*
#include <atlbase.h>
CComModule _Module;
#include <atlwin.h>
#pragma comment(lib,"atl")
#pragma comment(lib,"User32.lib")
*/



//#include "WebBrowser.h"


// #ifdef UNICODE
typedef std::wstring InputBoxStringType;
typedef LPWSTR InputBoxCharPointerType;
typedef wchar_t InputBoxCharType;
#define InputBoxString(x) L##x
// #else
// typedef std::string InputBoxStringType;
// typedef LPSTR InputBoxCharPointerType;
// typedef char InputBoxCharType;
// #define InputBoxString(x) x
// #endif

HWND gDialogHandle = 0;
InputBoxStringType gResults ;


LRESULT CALLBACK InputBoxWndProc(HWND WndHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
    static InputBoxStringType *Results = 0;
    static HWND InputLabelHandle = 0;
    static HWND InputHandle = 0;

    switch(Message)
    {
        case WM_NCCREATE:
            {
                Results = (InputBoxStringType*)((CREATESTRUCT*)lParam)->lpCreateParams;
                break;
            }

        case WM_CLOSE:
        case WM_DESTROY:
            {

                PostQuitMessage(0);
                DestroyWindow( gDialogHandle);
                printf("destroywindow\n");
                break;
            }

        case WM_COMMAND:
            {
                int NotifyCode = HIWORD(wParam);
                int ControlId = LOWORD(wParam);
                HWND ControlHandle = (HWND)lParam;

                switch(ControlId)
                {
                    case 1001:
                        {
                            printf("input\n");
                            InputHandle = ControlHandle;
                            break;
                        }

                    case 1002:
                        {
                            printf("ok\n");
                            //if(InputHandle == 0 || !Results)
                            //{
                            //PostQuitMessage(0);
                            //DestroyWindow( gDialogHandle);
                            //break;
                            //}

                            InputBoxCharPointerType Buffer = new InputBoxCharType[256]; 
                            GetWindowText(InputHandle, Buffer, 256);
                            gResults = Buffer;
                            PostQuitMessage(0);
                            DestroyWindow( gDialogHandle);
                            break;
                        }

                    case 1003:
                        {
                            printf("cancel\n");
                            //if(InputHandle == 0 || !Results)
                            //{
                            //PostQuitMessage(0);
                            //DestroyWindow( gDialogHandle);
                            //break;
                            //}

                            gResults = InputBoxString("__CANCEL__");
                            PostQuitMessage(0);
                            DestroyWindow( gDialogHandle);
                            break;
                        }
                }
                break;
            }
    }
    return DefWindowProc(WndHandle, Message, wParam, lParam);
}

static InputBoxStringType ShowInputBox(HWND OwnerWindowHandle, const InputBoxStringType &InputLabel, const InputBoxStringType &InputText, const InputBoxStringType &Title)
{
    WNDCLASS WndClass;
    HWND InputLabelHandle = 0;
    HWND InputHandle = 0;
    HWND OkButtonHandle = 0, CancelButtonHandle = 0;
    InputBoxStringType Result = InputBoxString("");

    ZeroMemory(&WndClass, sizeof(WNDCLASS));
    WndClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(0, IDC_ARROW);
    WndClass.hInstance = GetModuleHandle(0);
    WndClass.lpszClassName = InputBoxString("InputBox");
    WndClass.lpfnWndProc = InputBoxWndProc;
    RegisterClass(&WndClass);

    int X = 0, Y = 0;
    int Width = 0, Height = 0;
    RECT TempRect;
    GetWindowRect(GetDesktopWindow(), &TempRect);
    Width = (int)((float)(TempRect.right - TempRect.left) * 0.25f);
    Height = 150;
    X = ((TempRect.right - TempRect.left) / 2) - (Width / 2);
    Y = ((TempRect.bottom - TempRect.top) / 2) - (Height / 2);
    gDialogHandle = CreateWindowEx(0, InputBoxString("InputBox"), Title.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE, X, Y, Width, Height, OwnerWindowHandle, 0, GetModuleHandle(0), (LPVOID)&Result);

    int LabelX = 5, LabelY = 5;
    int LabelWidth = Width - 10, LabelHeight = 24;
    InputLabelHandle = CreateWindowEx(0, InputBoxString("STATIC"), InputLabel.c_str(), WS_CHILD | WS_VISIBLE, LabelX, LabelY, LabelWidth, LabelHeight, gDialogHandle, 0, GetModuleHandle(0), 0);

    int TBoxX = 5, TBoxY = 29;
    int TBoxWidth = Width - 20, TBoxHeight = 24;
    InputHandle = CreateWindowEx(0, InputBoxString("EDIT"), InputText.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE, TBoxX, TBoxY, TBoxWidth, TBoxHeight, gDialogHandle, (HMENU)1001, GetModuleHandle(0), 0);

    int OkBtnX = (Width / 2) - 75, OkBtnY = Height - 60;
    int OkBtnWidth = 75, OkBtnHeight = 24;
    OkButtonHandle = CreateWindowEx(0, InputBoxString("BUTTON"), InputBoxString("Ok"), WS_CHILD | WS_VISIBLE, OkBtnX, OkBtnY, OkBtnWidth, OkBtnHeight, gDialogHandle, (HMENU)1002, GetModuleHandle(0), 0);

    int CancelBtnX = (Width / 2) + 25, CancelBtnY = Height - 60;
    int CancelBtnWidth = 75, CancelBtnHeight = 24;
    CancelButtonHandle = CreateWindowEx(0, InputBoxString("BUTTON"), InputBoxString("Cancel"), WS_CHILD | WS_VISIBLE, CancelBtnX, CancelBtnY, CancelBtnWidth, CancelBtnHeight, gDialogHandle, (HMENU)1003, GetModuleHandle(0), 0);

    MSG Message;
    ZeroMemory(&Message, sizeof(MSG));
    while(Message.message != WM_QUIT)
    {
        if(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
    }
    return Result;
}

#undef InputBoxString

/*
const wchar_t* gURL;

LRESULT CALLBACK BrowserWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    RECT rc;
    IWebBrowser2* iWebBrowser;
    VARIANT varMyURL;
    static CAxWindow WinContainer;
    LPOLESTR pszName=OLESTR("shell.Explorer.2");
    GetClientRect(hWnd, &rc);

    //VARIANT_BOOL pBool;
    //if ( iWebBrowser != NULL){
    //iWebBrowser->get_Busy( &pBool);
    //if ( pBool == false){ wprintf(L"not busy now\n"); }
    //}
    switch(message)
    {
        case WM_CREATE:
            wprintf( L"*** WM_CREATE open url: %s\n", gURL);
            WinContainer.Create(hWnd, rc, 0,WS_CHILD |WS_VISIBLE);
            WinContainer.CreateControl(pszName);
            WinContainer.QueryControl(__uuidof(IWebBrowser2),(void**)&iWebBrowser); 
            VariantInit(&varMyURL);
            varMyURL.vt = VT_BSTR; 
            varMyURL.bstrVal = SysAllocString(gURL);
            iWebBrowser-> Navigate2(&varMyURL,0,0,0,0);



            VariantClear(&varMyURL); 
            iWebBrowser-> Release(); 
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (int)DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}

const wchar_t* launchEmbedBrowser(const wchar_t* url)
{
    static TCHAR szAppName[]=TEXT("WebBrowser");
    static TCHAR szClassName[]=TEXT("WebBrowser");
    HWND hWnd;
    MSG msg;
    WNDCLASS wndclass;
    wndclass.style=CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc=BrowserWndProc;
    wndclass.cbClsExtra=0;
    wndclass.cbWndExtra=0;
    wndclass.hInstance=GetModuleHandle(0);
    wndclass.hIcon=LoadIcon(GetModuleHandle(0), IDI_APPLICATION);
    wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName=NULL;
    wndclass.lpszClassName=szClassName;

    if(!RegisterClass(&wndclass))
    {
        MessageBox(NULL,TEXT("Error!"),szAppName,MB_ICONERROR);
        return 0;
    }

    hWnd=CreateWindow(szClassName,szAppName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, 0,CW_USEDEFAULT,0,NULL,NULL,GetModuleHandle(0),NULL);
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return L"";
}
*/

namespace native {

    const wchar_t* openInput()
    {
        ShowInputBox(0, L"Please enter your name:", L"", L"Name Entry");
        //printf( "Result: %ls\n" , Result.c_str());
        return gResults.c_str();
    }

    const wchar_t * openBrowser( const wchar_t* url ){
        ShellExecute(NULL,L"open",url,NULL,NULL,SW_SHOW); 
        return L"ok";
    }
    //const wchar_t * openEmbedBrowser( const wchar_t* url ){
    //wprintf( L"*** open url: %s\n", url);
    //gURL = url;
    //return launchEmbedBrowser(url);
    //}

}

