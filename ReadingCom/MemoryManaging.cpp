#include "header\MemoryManaging.h"
struct AlloMet
{
	uint32_t totalAllocated = 0;
	uint32_t totalfreed = 0;
	uint32_t CurrentUsage() { return totalAllocated - totalfreed; }
};
static AlloMet s_AlloMet;

void* MemoryManaging::operator new(size_t size)
{
	s_AlloMet.totalAllocated += size;

	return malloc(size);
}

void MemoryManaging::operator delete(void* memory, size_t size)
{
	s_AlloMet.totalfreed += size;

	free(memory);
}

void MemoryManaging::PrintMemoryUsage()
{
	cout << "Memory Usage: " << s_AlloMet.CurrentUsage() << " bytes.\n";
}
