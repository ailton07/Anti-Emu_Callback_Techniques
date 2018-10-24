#include "Common.h"

// https://www.dreamincode.net/forums/topic/240599-peb-access/

struct PEB
{
    UCHAR InheritedAddressSpace;                     
    UCHAR ReadImageFileExecOptions;                  
    UCHAR BeingDebugged;                             
    UCHAR Spare;                                     
    PVOID Mutant;                                    
    PVOID ImageBaseAddress;                          
    struct PEB_LDR_DATA *Ldr;                    
    void * ProcessParameters;                        
    PVOID SubSystemData;                             
    PVOID ProcessHeap;                               
    PVOID FastPebLock;                               
    void * FastPebLockRoutine;              
    void * FastPebUnlockRoutine;            
    ULONG EnvironmentUpdateCount;                    
    PVOID* KernelCallbackTable;                      
    PVOID EventLogSection;                           
    PVOID EventLog;                                  
    void * FreeList;                        
    ULONG TlsExpansionCounter;                       
    PVOID TlsBitmap;                                 
    ULONG TlsBitmapBits[0x2];                            
    PVOID ReadOnlySharedMemoryBase;                  
    PVOID ReadOnlySharedMemoryHeap;                  
    PVOID* ReadOnlyStaticServerData;                 
    PVOID AnsiCodePageData;                          
    PVOID OemCodePageData;                           
    PVOID UnicodeCaseTableData;                      
    ULONG NumberOfProcessors;                        
    ULONG NtGlobalFlag;                              
    UCHAR Spare2[0x4];                               
    ULARGE_INTEGER CriticalSectionTimeout;           
    ULONG HeapSegmentReserve;                        
    ULONG HeapSegmentCommit;                         
    ULONG HeapDeCommitTotalFreeThreshold;            
    ULONG HeapDeCommitFreeBlockThreshold;            
    ULONG NumberOfHeaps;                             
    ULONG MaximumNumberOfHeaps;                      
    PVOID** ProcessHeaps;                            
    PVOID GdiSharedHandleTable;                      
    PVOID ProcessStarterHelper;                      
    PVOID GdiDCAttributeList;                        
    PVOID LoaderLock;                                
    ULONG OSMajorVersion;                            
    ULONG OSMinorVersion;                            
    ULONG OSBuildNumber;                             
    ULONG OSPlatformId;                              
    ULONG ImageSubSystem;                            
    ULONG ImageSubSystemMajorVersion;                
    ULONG ImageSubSystemMinorVersion;                
    ULONG GdiHandleBuffer[0x22];                     
    PVOID ProcessWindowStation;                      
} ;


struct PEB *GetPEB()
{
__asm
	{
		mov  eax ,fs:30h
	}	
}


void fastPebLockRoutineCallback() 
{
	printf ("*** FastPebLockRoutine Callback executed ***\n");
	callbackWasCalled = 1;
}

void fastPebLockRoutine_doMyJob()
{
	// https://www.dreamincode.net/forums/topic/240599-peb-access/
	PEB *peb = GetPEB();
	(peb)->FastPebLockRoutine = &fastPebLockRoutineCallback;
	// RtlAcquirePebLock();
	// The Book Attack and Defend Computer Security Set: 
	// Windows API functions, such as GetEnvironmentVariable, make calls into RtlAcquirePebLock
	LPCTSTR lpName = 0;
	LPTSTR  lpBuffer = 0;
	DWORD   nSize = 0;
	GetEnvironmentVariable(lpName, lpBuffer, nSize);

	//if (callbackWasCalled)
		//printf ("Emulator was detected");
}