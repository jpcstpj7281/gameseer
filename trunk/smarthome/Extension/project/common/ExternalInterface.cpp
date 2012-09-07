#ifndef IPHONE
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif


#include <hx/CFFI.h>
#include <stdio.h>

#ifdef _WIN32
#include "native.h"

int FW2UTF8Convert( const wchar_t* a_szSrc, int a_nSrcSize, char* a_szDest, int a_nDestSize )  
{  
 return WideCharToMultiByte( CP_UTF8, 0, a_szSrc, -1, a_szDest, a_nDestSize, NULL, NULL );  
}  
  

static value native_openInput () {
    return alloc_wstring ( native::openInput() );
}
DEFINE_PRIM (native_openInput, 0);

static char buf[1024];
static value native_openInput_neko () {
    //return alloc_string ( native::openInput() );

    const wchar_t* str = native::openInput();
    int sz = wcslen(str);
    memset( buf, 0, 1024);
    int len = FW2UTF8Convert (str, sz, buf, 1024);
    return alloc_string( "test");
}
DEFINE_PRIM (native_openInput_neko, 0);

static value native_openBrowser(value v){

    const wchar_t* url = val_wstring( v);
    return alloc_wstring (native::openBrowser( url ) );
}
DEFINE_PRIM (native_openBrowser, 1);
#endif

extern "C" void native_main () {

    // Here you could do some initialization, if needed

}
DEFINE_ENTRY_POINT (native_main);

extern "C" int test_register_prims () { return 0; }
