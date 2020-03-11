#pragma once

#include <iostream>
#include <string>
#include "Job.h"

using namespace std;


struct Block
{
	int size;
	int internal_frag;
	bool empty = true;
};

class Memory
{
private:
	int memorySize;
	Block *memoryBlocks;
public:
	Memory(int memorySize, int blockSize);
	Block mallocFF(int size);
	void mallocBF(int size);
	void mallocNF(int size);
	void mallocWF(int size);
	void malloc(int loc);
	void free(int loc);
	void print();
};

