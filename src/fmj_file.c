
#include "fmj_types.h"

#if WINDOWS
FMJFileDirInfoResult fmj_file_win32_get_all_files_indir_(char* path, FMJMemoryArena* arena)
{
	FMJFileDirInfoResult result = {0};
	FMJString wild_card_path = fmj_string_append_char_to_char(path,"\\*", arena);
	result.files = fmj_fixed_buffer_init(1000, sizeof(FMJFileInfo),8);
	LPWIN32_FIND_DATAA ffd;
	HANDLE h_find = INVALID_HANDLE_VALUE;
	LARGE_INTEGER filesize;
	h_find = FindFirstFileA(wild_card_path.string, ffd);
	if (INVALID_HANDLE_VALUE == h_find)
	{
		return result;
	}

	do
	{
		if (ffd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		}
		else
		{
			filesize.LowPart = ffd->nFileSizeLow;
			filesize.HighPart = ffd->nFileSizeHigh;
			FMJFileInfo info = {0};
			info.name = fmj_string_create(ffd->cFileName, arena);
			fmj_fixed_buffer_push(&result.files, &info);
		}
	}
	while (FindNextFileA(h_find, ffd) != 0);
	return result;
}

FMJFileReadResult fmj_file_win32_read_entire_file(char* path)
{
	ASSERT(path);
	FMJFileReadResult result = {0};
	HANDLE file = CreateFileA(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		0,
		0
	);

	if (file != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER file_size;
		if (GetFileSizeEx(
			file,
			&file_size
		))
		{
			DWORD size_result;
			result.content = VirtualAlloc(
				0,
				file_size.QuadPart,
				MEM_COMMIT | MEM_RESERVE,
				PAGE_READWRITE
			);
			if (result.content)
			{
				if (ReadFile(
					file,
					result.content,
					file_size.QuadPart,
					&size_result,
					0
				))
				{
					result.content_size = file_size.QuadPart;
				}
				else
				{
					//TODO(ray):logging
				}
			}
			else
			{
				//TODO(ray):logging
				fmj_os_deallocate(result.content, result.content_size);
			}
		}
		else
		{
			//TODO(ray):logging
		}
	}
	else
	{
		//TODO(ray):logging
		s32 ErrorCode = GetLastError();
		OutputDebugStringA((char*)"INVALIDHANDLE");
	}
	CloseHandle(file);
	return result;
}

#elif OSX
#include <CoreFoundation/CoreFoundation.h>
FMJFileDirInfoResult fmj_file_osx_get_all_file_indir_(FMJStr path,MemoryArena *arena,bool recursively,bool get_full_path)
{
    FMJFileDirInfoResult result;
    result.files = fmj_fixed_buffer_init(1000,sizeof(FMJFileInfo),8);
    CFAllocatorRef alloc = CFAllocatorGetDefault();
    CFStringRef dir_ref = CFStringCreateWithCString(alloc, path.string, kCFStringEncodingASCII);
    CFURLRef url_ref = CFURLCreateWithString(alloc, dir_ref, NULL);
    CFURLEnumeratorOptions options = kCFURLEnumeratorDefaultBehavior;
    if(recursively)
    {
        options = kCFURLEnumeratorDescendRecursively;
    }
    
    CFURLEnumeratorRef enumerator = CFURLEnumeratorCreateForDirectoryURL(alloc, url_ref,options , 0);
    CFURLRef url = NULL;
    while (CFURLEnumeratorGetNextURL(enumerator, &url, NULL) == kCFURLEnumeratorSuccess)
    {
        if(recursively && CFURLHasDirectoryPath(url))
        {
            continue;
        }

        CFNumberRef value_num = NULL;
        CFMutableStringRef file_name =  CFStringCreateMutableCopy(kCFAllocatorDefault, 0, CFURLGetString(url));
        const char *cs = CFStringGetCStringPtr( file_name, kCFStringEncodingMacRoman ) ;
        FMJStr path_to_file = CreateStringFromLiteral((char*)cs, arena);
        FMJStr file_name = {0};
        if(get_full_path)
        {
            file_name = path_to_file;
            //remove file prefex
            while(*(file_name.string) != '/')//after we get past the file:/than we are ready
            {
                ++file_name.string;
                file_name.length--;
            }
        }
        else
        {
            file_name = GetFilenameFromPath(path_to_file,arena);
        }

        file_info info = {0};
        info.Name = file_name;
        YoyoPushBack(&result.files, info);
        if (CFURLCopyResourcePropertyForKey(url, kCFURLFileSizeKey, &value_num, 0) && (value_num != NULL))
        {
        }
        CFRelease(value_num);
        CFRelease(file_name);
    }
    //CFRelease(url);
    CFRelease(enumerator);
    CFRelease(dir_ref);
    CFRelease(url_ref);
    return result;
}

FMJFileReadResult OSXReadEntireFile(char* Path)
{
    FMJFileReadResult result = {0};
    FILE *file = fopen (Path, "r");
    if (file == NULL)
    {
        //ASSERT(file);
        printf("Ray Engine Error No file found");
    }
    else
    {
        u64 file_size;
        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        kern_return_t kr;
        mach_vm_address_t address;
        result.content_size = (s32)file_size;
        mach_vm_size_t size = (mach_vm_size_t)file_size;
        kr = mach_vm_allocate(mach_task_self(), &address, size, VM_FLAGS_ANYWHERE);
        result.content = (void*)address;//allocl mem;
        fread(result.content, result.content_size, 1, file);
        fclose(file);
    }
    return result;
}

#elif IOS
#include <mach/mach_init.h>
FMJFileDirInfoResult fmj_file_ios_get_all_file_indir_(FMJStr path,MemoryArena *arena)
{
    dir_files_result result;
    result.files = YoyoInitVector(1000,sizeof(file_info),false);
    CFAllocatorRef alloc = CFAllocatorGetDefault();
    CFStringRef DirRef = CFStringCreateWithCString(alloc, path.string, kCFStringEncodingASCII);
    CFURLRef url_ref = CFURLCreateWithString(alloc, DirRef, NULL);
    CFURLEnumeratorRef enumerator = CFURLEnumeratorCreateForDirectoryURL(alloc, url_ref, kCFURLEnumeratorDefaultBehavior, 0);
    CFURLRef url = NULL;

    while (CFURLEnumeratorGetNextURL(enumerator, &url, NULL) == kCFURLEnumeratorSuccess)
    {
        CFNumberRef value_num = NULL;
        CFMutableStringRef file_name =  CFStringCreateMutableCopy(kCFAllocatorDefault, 0, CFURLGetString(url));
        const char *cs = CFStringGetCStringPtr( file_name, kCFStringEncodingMacRoman ) ;
        FMJStr path_to_file = CreateStringFromLiteral((char*)cs, arena);
        char* End = path_to_file.string + path_to_file.length - 1;
        u32 StepCount = 1;
        while(*(End - 1) != '/')
        {
            --End;
            ++StepCount;
        }
        FMJStr file_name = CreateStringFromLength(End, StepCount, arena);
        file_info info;
        info.Name = file_name;
        YoyoPushBack(&result.files, info);
        if (CFURLCopyResourcePropertyForKey(url, kCFURLFileSizeKey, &value_num, nullptr) && (value_num != NULL))
        {
        }
    }
    return result;
}

FMJFileReadResult IOSReadEntireFile(char* Path)
{
    FMJFileReadResult result;
    FILE *file = fopen (Path, "r");
    if (file == NULL)
    {
        ASSERT(file);
        printf("Ray Engine Error No file found");
    }
    else
    {
        u64 file_size;
        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        result.content_size = (s32)file_size;
        void* address = PlatformAllocateMemory(file_size);
        result.content = (void*)address;//allocl mem;
        fread(result.content, result.content_size, 1, file);
        fclose(file);
    }
    return result;
}
#endif

FMJFileDirInfoResult fmj_file_platform_get_all_files_in_dir(char* path, FMJMemoryArena* arena)
{
	FMJFileDirInfoResult result = {0};
#if WINDOWS
	result = fmj_file_win32_get_all_files_indir_(path, arena);
#elif OSX
    result = fmj_file_osx_get_all_file_indir_(path, arena,true,true);
#elif IOS
    result = fmj_file_ios_get_all_file_indir_(path, arena);
#endif
	return result;
}

FMJFileReadResult fmj_file_platform_read_entire_file(char* file_name)
{
	FMJFileReadResult result = {0};
#if WINDOWS
	result = fmj_file_win32_read_entire_file(file_name);
#elif OSX
	result = fmj_file_osx_read_entire_file(file_name);
#elif IOS
	result = fmj_file_ios_read_entire_file(file_name);
#endif
	return result;
}

bool fmj_write_to_file_(FILE* file, void* mem,u64 size, bool is_done)
{
    bool result = false;
    fwrite(mem, size, 1, file);
    if (ferror(file))
    {
        result = false;
    }
    else
    {
        result = true;
    }
    if(is_done)
    {
        fclose(file);
    }
    return result;
}

bool fmj_file_platform_write_memory(FMJFilePointer* file,char* file_name,void* mem,u64 size,bool is_done,char* options)
{
	if(file->file == NULL)
	{
		file->file = fopen(file_name, options);
	}
	return fmj_write_to_file_(file->file,mem, size,is_done);
}

