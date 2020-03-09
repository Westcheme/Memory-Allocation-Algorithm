#pragma once

#include <iostream>
#include <string>
#include "Job.h"

using namespace std;


class Memory
{
private:
	int **memoryBlocks;
	int memorySize;
	int blockSize;
public:
	Memory(int memorySize, int blockSize);
	void print();
	int mallocFF(Job job);
	int mallocBF(int size);
	int mallocNF(int size);
	int mallocWF(int size);
	void malloc(int loc);
	void free(int loc);
};

