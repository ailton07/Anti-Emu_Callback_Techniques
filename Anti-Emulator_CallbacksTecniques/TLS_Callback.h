#include"Common.h"

// Reference: http://lallouslab.net/2017/05/30/using-cc-tls-callbacks-in-visual-studio-with-your-32-or-64bits-programs/
void WINAPI tls_callback1(
    PVOID DllHandle,
    DWORD Reason,
    PVOID Reserved)
{
	printf ("\n*** TLS Callback executed - reason: %d ***\n", Reason);
	if (Reason == DLL_PROCESS_ATTACH )
		callbackWasCalled = Reason;
}

//-------------------------------------------------------------------------
// TLS 32/64 bits example by Elias Bachaalany <lallousz-x86@yahoo.com>
#ifdef _M_AMD64
    #pragma comment (linker, "/INCLUDE:_tls_used")
    #pragma comment (linker, "/INCLUDE:p_tls_callback1")
    #pragma const_seg(push)
    #pragma const_seg(".CRT$XLAAA")
        EXTERN_C const PIMAGE_TLS_CALLBACK p_tls_callback1 = tls_callback1;
    #pragma const_seg(pop)
#endif
#ifdef _M_IX86
    #pragma comment (linker, "/INCLUDE:__tls_used")
    #pragma comment (linker, "/INCLUDE:_p_tls_callback1")
    #pragma data_seg(push)
    #pragma data_seg(".CRT$XLAAA")
        EXTERN_C PIMAGE_TLS_CALLBACK p_tls_callback1 = tls_callback1;
    #pragma data_seg(pop)
#endif
//-------------------------------------------------------------------------

		DWORD WINAPI ThreadProc(CONST LPVOID lpParam) 
		{
			ExitThread(0);
		}
