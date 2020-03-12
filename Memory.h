#pragma once

#include <iostream>
#include <string>
#include "Job.h"

using namespace std;


struct Block
{
	int size;
	int internal_frag = 0;
	bool empty = true;
};

class Memory
{
private:
	int memorySize;
	Block *memoryBlocks;
	int lastLocation;
public:
	Memory(int memorySize, int blockSize);
	Block mallocFF(int size);
	Block mallocBF(int size);
	Block mallocNF(int size);
	Block mallocWF(int size);
	void free(int loc);
	void print();
	Block getLocationOf(int index);
};

