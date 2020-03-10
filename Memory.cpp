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
		if (memoryBlocks[i].empty == true)
		{
			for (int j = i; j < memorySize; j++)
			{
				if (freeBlockCount == blocksNeeded)
				{
					for (int k = i; k < i + blocksNeeded; k++)
					{
						memoryBlocks[k].empty = false;
						if (k == i + blocksNeeded - 1) memoryBlocks[k].internal_frag = memoryBlocks->size * blocksNeeded - size;
						return;
					}
				}
				if (memoryBlocks[j].empty == false)
				{
					int k = 0;
					while(memoryBlocks[k].empty == false)
					{
						k++;
					}
					i = k;
					break;
				}
				freeBlockCount++;
			}
		}
		if (i == memorySize-1)
		{
			cout << "NOT ENOUGH MEMORY SPACE TO ALLOCATE JOB";
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