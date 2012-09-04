#ifndef _MEMAPI_H_
#define _MEMAPI_H_

#ifdef __cplusplus
/* #include <new> */
#include "stddef.h"
#include "sys_types.h"

void* operator new(size_t dwSize);
void* operator new [](size_t dwSize);
void operator delete(void * pBlock);
void operator delete [] (void * pBlock);


#endif /* #ifndef __cplusplus */

#endif /* #ifndef _MEMAPI_H_ */

