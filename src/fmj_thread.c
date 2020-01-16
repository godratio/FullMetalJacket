#include "fmj_types.h"

#if OSX
#include <x86intrin.h>
#elif WINDOWS
#include <intrin.h>
#elif IOS
#include <arm_neon.h>
#endif

#if IOS || OSX
#include <pthread.h>
#include <libkern/OSAtomic.h>
#include <sys/sysctl.h>
#elif WINDOWS
#endif

u64 fmj_thread_get_cpu_core_count()
{
    u64 result = 0;
#if WINDOWS
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    result = sysinfo.dwNumberOfProcessors;
#elif OSX
    int mib[4];
    int numCPU;
    std::size_t len = sizeof(numCPU); 
/* set the mib for hw.ncpu */
    mib[0] = CTL_HW;
    mib[1] = HW_AVAILCPU;  // alternatively, try HW_NCPU;
/* get the number of CPUs from the system */
    sysctl(mib, 2, &numCPU, &len, NULL, 0);

    if (numCPU < 1) 
    {
        mib[1] = HW_NCPU;
        sysctl(mib, 2, &numCPU, &len, NULL, 0);
        if (numCPU < 1)
            numCPU = 1;
    }
    result = numCPU;
#endif
return result;
}

u64 fmj_thread_get_thread_id()
{
#if IOS || OSX
    mach_port_t threadport = pthread_mach_thread_np(pthread_self());
    return (memory_index)threadport;
#elif WINDOWS
    u8 *ThreadLocalStorage = (u8 *)__readgsqword(0x30);
    u32 ThreadID = *(u32 *)(ThreadLocalStorage + 0x48);
    return ThreadID;
#endif
}

FMJThread fmj_thread_create(void*(*func)(void*),void* func_data)
{
    FMJThread result = {0};
#if IOS || OSX
    pthread_t tID;
    int tErr;
    tErr = pthread_create( &tID , NULL, func, func_data);
    result.id = (u64)tID;
#elif WINDOWS
    //CreateThread
    LPDWORD t_id;
    HANDLE handle =  
        CreateThread(
        0,
        0,
        (LPTHREAD_START_ROUTINE) func,
        func_data,
        0,
        t_id);
    result.id = (u64)handle;
    CloseHandle(handle);
#endif
    return result;
}
//TODO(Ray):WriteBarrier

//TODO(Ray):ReadBarrier

FMJ_ATOMICS_INLINE s64 fmj_thread_atomic_compare_exchange64(s64 volatile *value,s64 new_value,s64 comperand)
{
    s64 result = 0;
#if IOS || OSX
    result = __sync_val_compare_and_swap((s64* volatile)value,comperand,new_value);
#elif WINDOWS
    result = InterlockedCompareExchange64(value,new_value,comperand);
#endif
    return result;
}

FMJ_ATOMICS_INLINE s64 fmj_thread_atomic_increment64(s64 volatile *value)
{
    s64 result = 0;
#if IOS || OSX
    result = __sync_fetch_and_add((s64* volatile)value,(s64)1);
#elif WINDOWS
    result = InterlockedExchangeAdd64(value,1);
#endif
    return result;
}

FMJ_ATOMICS_INLINE s64 fmj_thread_atomic_decrement64(s64 volatile *value)
{
    s64 result = 0;
#if IOS || OSX
    result = __sync_fetch_and_sub((s64* volatile)value,(s64)1);    
#elif WINDOWS
    result = InterlockedExchangeAdd64(value,-1);
#endif
    return result;
}

FMJ_ATOMICS_INLINE s64 fmj_thread_atomic_add64(s64 volatile *value,s64 amount)
{
    s64 result = 0;
#if IOS || OSX
    result = __sync_fetch_and_add((s64* volatile)value,(s64)amount);
#elif WINDOWS
    result = InterlockedExchangeAdd64(value,amount);
#endif
    return result;
}

FMJ_ATOMICS_INLINE void fmj_thread_begin_ticket_mutex(FMJTicketMutex* mutex)
{
    s64 ticket = fmj_thread_atomic_add64(&mutex->ticket,1);
#if IOS
    while(ticket != mutex->serving){__asm__ __volatile__("yield");};
#else
    while(ticket != mutex->serving){_mm_pause();};
#endif
}

FMJ_ATOMICS_INLINE void fmj_thread_end_ticket_mutex(FMJTicketMutex* mutex)
{
    fmj_thread_atomic_add64(&mutex->serving,1);
}

FMJThreadSemaphore fmj_thread_create_semaphore(u64 value)
{
    FMJThreadSemaphore result = {0};
#if OSX || IOS
    dispatch_semaphore_t dis_sem = dispatch_semaphore_create(value);//long
    result.state = (void*)dis_sem;
#elif WINDOWS
    HANDLE hnd = CreateSemaphoreA(0,value,value,0);
    result.state = (void*)hnd;
#endif
    return result;
}


