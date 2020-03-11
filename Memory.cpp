#include "Memory.h"

Memory::Memory(int memorySiz, int blockSiz)
{
	memorySize = memorySiz;
	memoryBlocks = new Block[memorySiz];
	memoryBlocks->size = blockSiz;
}

void Memory::mallocFF(int size)
{
	int blocksNeeded = ceil(size / memoryBlocks->size);
	int freeBlockCount = 0;

	for (int i = 0; i < memorySize; i++)
	{
		if (memoryBlocks[i].empty == true) freeBlockCount++;
		else if (memoryBlocks[i].empty == false) freeBlockCount = 0;

		if (freeBlockCount == blocksNeeded)
		{
			for (int j = i - blocksNeeded + 1; j <= i; j++)
			{
				memoryBlocks[j].empty = false;
			}
			Block location = memoryBlocks[i - blocksNeeded + 1];
			memoryBlocks[i].internal_frag = blocksNeeded * memoryBlocks->size - size;
			return location;
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

//Prints the contents of the Memory
void Memory::print()
{
	for (int i = 0; i < memorySize; i++)
	{
		if (memoryBlocks[i].empty == true)
		{
			for (int j = 0; j < memoryBlocks->size; j++)
			{
				cout << "- ";
			}
		}
		else
		{
			for (int j = 0; j < memoryBlocks->size - memoryBlocks[i].internal_frag; j++)
			{
				cout << "1 ";
			}
			for (int j = 0; j < memoryBlocks[i].internal_frag; j++)
			{
				cout << "- ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
