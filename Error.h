#ifndef _ERROR_H_
#define _ERROR_H_

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x400
#endif

#include "Types.h"
#include <Windows.h>
#include <Winbase.h>


void Error(const char* message);

#define ErrorMessage(message) Error(message);
#define AssertMessage(condition,message) if(!(condition)) Error(message);

#endif // _ERROR_H_
