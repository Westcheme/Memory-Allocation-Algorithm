#include "Memory.h"

Memory::Memory(int memorySiz, int blockSiz)
{
	memorySize = memorySiz;
	blockSize = blockSiz;
	memoryBlocks = new int*[memorySize];
	for (int i = 0; i < memorySize; ++i)
	{
		memoryBlocks[i] = new int[blockSize];
	}
}

void Memory::print()
{
	for (int i = 0; i < memorySize; i++)
	{
		for (int j = 0; j < blockSize; j++)
		{
			if (memoryBlocks[i][j] < 0) cout << "- ";
			else cout << memoryBlocks[i][j] << " ";
		}
		cout << endl;
	}
}

int Memory::mallocFF(Job job)
{
	for (int i = 0; i < memorySize; i++)
	{
		for (int j = 0; j < blockSize; j++)
		{
			if (memoryBlocks[i][j] < 0)
			{
				
			}
		}
	}
	return 0;
}

int Memory::mallocBF(int size)
{
	return 0;
}

int Memory::mallocNF(int size)
{
	return 0;
}

int Memory::mallocWF(int size)
{
	return 0;
}

void Memory::malloc(int loc)
{

}

void Memory::free(int loc)
{

}
