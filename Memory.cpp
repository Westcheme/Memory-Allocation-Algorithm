#include "Memory.h"

Memory::Memory(int memorySiz, int blockSiz)
{
	memorySize = memorySiz;
	memoryBlocks = new Block[memorySiz];
	memoryBlocks->size = blockSiz;
}

//Finds the first block of memory which fits and stores the data in that location
Block Memory::mallocFF(int size)
{
	int blocksNeeded = ceil((float)size / memoryBlocks->size);
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
			lastLocation = i + 1;
			return location;
		}
	}
	cout << endl << "COULD NOT FIT JOB INTO MEMORY";
	exit(EXIT_FAILURE);
}

//Finds the best block of memory which fits and stores the data in that location
Block Memory::mallocBF(int size)
{
	int blocksNeeded = ceil((float)size / memoryBlocks->size);
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
			lastLocation = i + 1;
			return location;
		}
	}
	cout << endl << "COULD NOT FIT JOB INTO MEMORY";
	exit(EXIT_FAILURE);
}

//Finds the next block of memory which fits and stores the data in that location
Block Memory::mallocNF(int size)
{
	int blocksNeeded = ceil((float)size / memoryBlocks->size);
	int freeBlockCount = 0;

	for (int i = lastLocation; i < memorySize; i++)
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
			lastLocation = i + 1;
			return location;
		}
	}
	for (int i = 0; i < lastLocation; i++)
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
			lastLocation = i + 1;
			return location;
		}
	}
	cout << endl << "COULD NOT FIT JOB INTO MEMORY";
	exit(EXIT_FAILURE);
}

//Finds the worst block of memory which fits and stores the data in that location
Block Memory::mallocWF(int size)
{
	int blocksNeeded = ceil((float)size / memoryBlocks->size);
	int freeBlockCount = 0;
	Block worstLocation = *memoryBlocks;
	int worstLocationIndex = 0;
	int worstSize = 0;

	for (int i = 0; i < memorySize; i++)
	{
		if (memoryBlocks[i].empty == true) freeBlockCount++;
		else if (memoryBlocks[i].empty == false)
		{
			if (freeBlockCount > worstSize)
			{
				worstLocationIndex = i - freeBlockCount;
				worstSize = freeBlockCount;
			}
			freeBlockCount = 0;
		}
		else if (i == memorySize - 1)
		{
			if (freeBlockCount > worstSize)
			{
				worstLocationIndex = i - freeBlockCount + 1;
				worstSize = freeBlockCount;
			}
		}
	}
	if (blocksNeeded <= worstSize)
	{
		for (int i = worstLocationIndex; i < i + blocksNeeded; i++)
		{
			memoryBlocks[i].empty = false;
		}
		Block location = memoryBlocks[worstLocationIndex + blocksNeeded - 1];
		memoryBlocks[worstLocationIndex + blocksNeeded - 1].internal_frag = blocksNeeded * memoryBlocks->size - size;
		lastLocation = worstLocationIndex + blocksNeeded - 1;
		return location;
	}
}

//Given a jobs data location it will deallocate the data from memory and make it free for other data
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

Block Memory::getLocationOf(int index)
{
	return memoryBlocks[index];
}