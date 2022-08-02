#include <bua/core.h>

#include <cstdlib>
#include <cstdio>

////////////////////////////////////////////////////////////////////////////////

// Usage of static EASTL libraries requires own definitions of "new"
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line) 
{
	printf("Allocation of %zu bytes made.\n", size);
	return malloc(size);
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) 
{
	printf("Allocation of %zu bytes made.\n", size);
	return malloc(size);
}

////////////////////////////////////////////////////////////////////////////////
