#include "Memory.h"

Memory::Memory(int memorySize, int blockSiz)
{
	memoryBlocks = new Job[memorySize];
	blockSize = blockSiz;
}