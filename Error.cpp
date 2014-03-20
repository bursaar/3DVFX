#include "Error.h"

/*****************************************************************************************/

void 
Error(const char* message)
{
	MessageBox(0, message, "Error", MB_OK);
	
	if(IsDebuggerPresent())
	{
		_asm int 3;
	}
	else
	{
		/// Stop execution since an error has occured and we arent debugging
		_exit(1);
	}
}

/*****************************************************************************************/