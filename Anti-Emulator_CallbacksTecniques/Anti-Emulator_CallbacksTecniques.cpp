// Anti-Emulator_CallbacksTecniques.cpp : Defines the entry point for the console application.
//
#include"Common.h"


#include "TLS_Callback.h"
#include "FastPebLockRoutine_Callback.h"
#include "SecureMemoryCache_Callback.h"

// QEMU pure emulation (non-KVM);
// https://www.twosixlabs.com/running-windows-64-bit-in-qemu-emulation-mode/

int main(int argc, char* argv[])
{
	// ----------------------------------------------------
	 printf("*** TLS Callback ***\n");
	 if (callbackWasCalled == 0) 
	 {
		printf("Emulator was detected\n");
	 } 
	 else 
	 {
		 printf("Emulator was not detected\n");
	 }
	callbackWasCalled = 0;

	// ----------------------------------------------------
	printf ("\n\n*** FastPebLockRoutine Callback ***\n");
	DWORD dwVersion = GetVersion();
	DWORD dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	if (dwMajorVersion != 5) // If it's not Windows XP
		printf("Windows XP only\n");
	else
	{
		fastPebLockRoutine_doMyJob();
		if (callbackWasCalled == 1) 
		{
			printf("Emulator was not detected\n");
		}
		else
		{		 
			printf("Emulator was detected\n");
		}
	}
	callbackWasCalled = 0;

	// ----------------------------------------------------
	printf("\n\n*** SecureMemoryCache Callback ***\n");
	secureMemoryCache_doMyJob();
	if (callbackWasCalled == 1) 
	{
		printf("Emulator was not detected\n");
	}
	else
	{		 
		printf("Emulator was detected\n");
	}
	callbackWasCalled = 0;

	getchar();
	return 0;
}

