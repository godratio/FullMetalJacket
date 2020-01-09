
#if WINDOWS
#include <windows.h>
void* fmj_os_win32_allocate(umm size)
{
    void* mem = VirtualAlloc(0,size,MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
    if(!mem)
    {
        // TODO(ray): Some error handling because we couldnt get the memory we need.
        ASSERT(false);
    }
    ASSERT(mem);
    return mem;
}

void fmj_os_win32_deallocate(void* mem,umm size)
{
    ASSERT(mem);    
    VirtualFree(mem,size,MEM_RELEASE);
}

#elif OSX

void* fmj_os_osx_allocate(umm size)
{
    mach_vm_address_t address;
    kern_return_t kr;
    mach_vm_size_t size = (mach_vm_size_t)size;
    kr = mach_vm_allocate(mach_task_self(), &address, size, VM_FLAGS_ANYWHERE);
    ASSERT(address);
    return (void*)address;
}

void fmj_os_osx_deallocate(void* mem,s64 size)
{
    mach_vm_address_t address = (mach_vm_address_t)mem;
    mach_vm_deallocate(mach_task_self(), address, size);
}
#elif IOS

void* fmj_os_ios_allocate(umm size)
{
    mach_vm_address_t address;
    kern_return_t kr;
    mach_vm_size_t size = (mach_vm_size_t)size;
    kr = _kernelrpc_mach_vm_allocate_trap(mach_task_self(), &address, size, VM_FLAGS_ANYWHERE);
    ASSERT(address);
    return (void*)address;
}

void fmj_os_ios_deallocate(void* mem,s64 size)
{
    ASSERT(mem);
    mach_vm_address_t address = (mach_vm_address_t)mem;
    _kernelrpc_mach_vm_deallocate_trap(mach_task_self(), address, size);
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

inline void fmj_os_deallocate(void* mem,umm size)
{
#if OSX
    fmj_os_osx_deallocate(mem, size);
#elif WINDOWS
    fmj_os_win32_deallocate(mem,size);
#elif IOS
    fmj_os_ios_deallocate(mem,size);
#endif
}



