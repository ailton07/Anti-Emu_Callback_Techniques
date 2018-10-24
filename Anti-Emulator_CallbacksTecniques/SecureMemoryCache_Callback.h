#include "Common.h"

// https://docs.microsoft.com/pt-br/windows/desktop/api/winbase/nf-winbase-addsecurememorycachecallback
#define _WIN32_WINNT 0x0600

BOOLEAN pSecureMemoryCache_Callback(PVOID Addr, SIZE_T Range) {
	printf ("*** pSecureMemoryCache Callback executed***\n");
	callbackWasCalled = 1;
	return true;
}


//typedef NTSTATUS  (__stdcall *RTL_REGISTER_SECURE_MEMORY_CACHE_CALLBACK)(IN PRTL_SECURE_MEMORY_CACHE_CALLBACK  	Callback);
// http://redplait.blogspot.com/2010/09/ntdll-official-hooks.html
typedef NTSTATUS (NTAPI *PRTL_SECURE_MEMORY_CACHE_CALLBACK)(IN PVOID Address, IN SIZE_T Length);
// typedef NTSTATUS RtlRegisterSecureMemoryCacheCallback(IN PRTL_SECURE_MEMORY_CACHE_CALLBACK CallBack);
//http://gate.upm.ro/os/LABs/Windows_OS_Internals_Curriculum_Resource_Kit-ACADEMIC/WindowsResearchKernel-WRK/WRK-v1.2/public/sdk/inc/ntrtl.h
typedef NTSTATUS  (__stdcall *RTL_REGISTER_SECURE_MEMORY_CACHE_CALLBACK)(IN PRTL_SECURE_MEMORY_CACHE_CALLBACK CallBack);

//https://doxygen.reactos.org/da/d08/sdk_2lib_2rtl_2security_8c.html#a040153c76c7b9f216601d890c3104b0a
typedef NTSTATUS  (__stdcall *RTL_FLUSH_SECURE_MEMORY_CACHE)(IN PVOID 	MemoryCache,IN OPTIONAL SIZE_T 	MemoryLength );
void secureMemoryCache_doMyJob()
{

	HMODULE lib=GetModuleHandle(TEXT("ntdll.dll"));
	if(lib != 0) 
	{
		RTL_REGISTER_SECURE_MEMORY_CACHE_CALLBACK rtlRegisterSecureMemoryCacheCallback =
			(RTL_REGISTER_SECURE_MEMORY_CACHE_CALLBACK) GetProcAddress(lib, "RtlRegisterSecureMemoryCacheCallback");

		if(rtlRegisterSecureMemoryCacheCallback != 0)
		{
			//printf("rtlRegisterSecureMemoryCacheCallback encontrado com sucesso 0x%x\n", rtlRegisterSecureMemoryCacheCallback );
			rtlRegisterSecureMemoryCacheCallback((PRTL_SECURE_MEMORY_CACHE_CALLBACK) pSecureMemoryCache_Callback);
			//
			RTL_FLUSH_SECURE_MEMORY_CACHE rtlFlushSecureMemory = 
				(RTL_FLUSH_SECURE_MEMORY_CACHE) GetProcAddress(lib, "RtlFlushSecureMemoryCache");
			if(rtlFlushSecureMemory != 0)
			{
				//printf("rtlFlushSecureMemory encontrado com sucesso 0x%x\n", rtlFlushSecureMemory );
				int * espaco = (int*)malloc (sizeof(int));
				rtlFlushSecureMemory(espaco,sizeof(int));
			}
			else
			{
				printf("Erro ao encontrar rtlFlushSecureMemoryCache\n");
			}			
		}
		else
		{
			printf("Erro ao encontrar rtlRegisterSecureMemoryCacheCallback\n");
		}

	} 

	/*int * espaco = (int*)malloc (sizeof(int));
	PSECURE_MEMORY_CACHE_CALLBACK PsecureMemoryCacheCallback; 
	__try 
	{
		if (AddSecureMemoryCacheCallback((PSECURE_MEMORY_CACHE_CALLBACK) pSecureMemoryCache_Callback))
		{
			printf("Callback added\n");
			VirtualFree(espaco,sizeof(int), 0);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		printf("Erro %d\n", GetLastError());
		callbackWasCalled = 1;
	}*/

}
	