
#if WINDOWS
#include <windows.h>
void* fmj_os_win32_allocate(umm size)
{
    void* mem = VirtualAlloc(
        0,
        size,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
        );
    if(!mem)
    {
        // TODO(ray): Some error handling because we couldnt get the memory we need.
        ASSERT(false);
    }
    return mem;
}
#endif

void* fmj_os_allocate(umm size)
{
    void* result = 0;
#if OSX
    result = OSXAllocateMemory(size);
#elif WINDOWS
    result = fmj_os_win32_allocate(size);
#elif IOS
    result = IOSAllocateMemory(size);
#endif
    ASSERT(result);
    return result;    
}
