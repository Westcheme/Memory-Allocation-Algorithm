#pragma once

#include <iostream>
#include <string>
#include "Job.h"

using namespace std;


class Memory
{
private:
	Job *memoryBlocks;
	int blockSize;
public:
	Memory(int memorySize, int blockSize);
};

