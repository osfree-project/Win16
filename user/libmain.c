#include <user.h>

extern  unsigned short          GetDS( void );
#pragma aux GetDS               = \
        "mov    ax,ds"          \
        value                   [ax];

BOOL WINAPI DllEntryPoint( DWORD reason, HINSTANCE inst, WORD ds,
                           WORD heap, DWORD reserved1, WORD reserved2 );

BOOL WINAPI LibMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	BOOL res;

	FUNCTION_START
	
	// Local Heap already initialized by OW Runtime, so we pass 0 here...
	res=DllEntryPoint( fdwReason, hinstDLL, GetDS(), 0, 0, 0 );
	FUNCTION_END
	return res;
}
