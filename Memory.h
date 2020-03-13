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
	int totalInternalFrag = 0;
public:
	Memory(int memorySize, int blockSize);
	int mallocFF(int size);
	int mallocBF(int size);
	int mallocNF(int size);
	int mallocWF(int size);
	void free(int location, int size);
	void clear();
	int getTotalInternalFrag();
	int largestBlock();
	int smallestBlock();
	void print();
	Block& getLocation(int index);
};

