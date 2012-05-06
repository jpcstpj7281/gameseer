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
static value native_openInput () {
    return alloc_wstring ( native::openInput() );
}
DEFINE_PRIM (native_openInput, 0);

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
