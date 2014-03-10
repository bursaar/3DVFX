// NOTE FROM STUDENT
// This header file is taken from Example 27-03

/*
To track memory leaks include this header file in every CPP file in your project and use
the t2GNew and t2GDelete instead of new and delete.  Any memory leaks detected will be shown in the output window.
*/

#ifdef _DEBUG
  #define _CRTDBG_MAP_ALLOC
  #include <stdlib.h>
  #include <crtdbg.h>
#endif



#ifdef _DEBUG
  
  #define t2GNew new(_NORMAL_BLOCK, __FILE__, __LINE__)
  #define t2GDelete delete

  // Set to dump leaks at the program exit.
  #define t2GInitMemoryCheck() _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

#else  

  #define t2GNew new
  #define t2GDelete delete

  #define t2GInitMemoryCheck()

#endif 


/* if we wanted we could add code here to re-define new and delete to be replaced with our t2GNew and t2GDelete
like this :
#define new t2GNew
#define delete t2GDelete
this can cause problems however for instances when you try to use the alternate forms of new and delete such as placement new
or if you overide new in one of your classes.
*/