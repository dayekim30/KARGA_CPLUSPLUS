#pragma once
#include <iostream>
#include <memory>
using namespace std;
class MemoryManaging {
 
	MemoryManaging() {}
	~MemoryManaging() {}
	
	void* operator new(size_t size);
	void operator delete(void* memory, size_t size);
	void PrintMemoryUsage();
};


