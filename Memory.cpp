#include "Memory.h"

Memory::Memory(int memorySiz, int blockSiz)
{
	memorySize = memorySiz;
	memoryBlocks = new Block[memorySiz];
	memoryBlocks->size = blockSiz;
}

void Memory::mallocFF(int size)
{
	for (int i = 0; i < memorySize; i++)
	{
		if (memoryBlocks[i].empty == true)
		{
			for (int j = 0; j < memorySize; j++)
			{

			}
		}
	}
}

void Memory::mallocBF(int size)
{
	
}

void Memory::mallocNF(int size)
{
	
}

void Memory::mallocWF(int size)
{
	
}

void Memory::malloc(int loc)
{

}

void Memory::free(int loc)
{

}
