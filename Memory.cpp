#include "Memory.h"

Memory::Memory(int memorySiz, int blockSiz)
{
	memorySize = memorySiz;
	memoryBlocks = new Block[memorySiz];
	memoryBlocks->size = blockSiz;
}

//Returns the total internal fragmentation accumulated by the memory during runtime
int Memory::getTotalInternalFrag()
{
	return totalInternalFrag;
}

//Finds the first block of memory which fits and stores the data in that location
int Memory::mallocFF(int size)
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
			memoryBlocks[i].internal_frag = blocksNeeded * memoryBlocks->size - size;
			totalInternalFrag += memoryBlocks[i].internal_frag;
			lastLocation = i + 1;
			return i - blocksNeeded + 1;
		}
	}
	cout << endl << "COULD NOT FIT JOB INTO MEMORY";
	system("PAUSE");
	exit(EXIT_FAILURE);
}

//Finds the best block of memory which fits and stores the data in that location
int Memory::mallocBF(int size)
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
			memoryBlocks[i].internal_frag = blocksNeeded * memoryBlocks->size - size;
			totalInternalFrag += memoryBlocks[i].internal_frag;
			lastLocation = i + 1;
			return i - blocksNeeded + 1;
		}
	}
	cout << endl << "COULD NOT FIT JOB INTO MEMORY";
	system("PAUSE");
	exit(EXIT_FAILURE);
}

//Finds the next block of memory which fits and stores the data in that location
int Memory::mallocNF(int size)
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
			memoryBlocks[i].internal_frag = blocksNeeded * memoryBlocks->size - size;
			totalInternalFrag += memoryBlocks[i].internal_frag;
			lastLocation = i + 1;
			return i - blocksNeeded + 1;
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
			memoryBlocks[i].internal_frag = blocksNeeded * memoryBlocks->size - size;
			totalInternalFrag += memoryBlocks[i].internal_frag;
			lastLocation = i + 1;
			return i - blocksNeeded + 1;
		}
	}
	cout << endl << "COULD NOT FIT JOB INTO MEMORY";
	system("PAUSE");
	exit(EXIT_FAILURE);
}

//Finds the worst block of memory which fits and stores the data in that location
int Memory::mallocWF(int size)
{
	int blocksNeeded = ceil((float)size / memoryBlocks->size);
	int freeBlockCount = 0;
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

		if (i == memorySize - 1)
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
		for (int i = worstLocationIndex; i < worstLocationIndex + blocksNeeded; i++)
		{
			memoryBlocks[i].empty = false;
		}
		memoryBlocks[worstLocationIndex + blocksNeeded - 1].internal_frag = blocksNeeded * memoryBlocks->size - size;
		totalInternalFrag += memoryBlocks[worstLocationIndex + blocksNeeded - 1].internal_frag;
		lastLocation = worstLocationIndex + blocksNeeded - 1;
		return worstLocationIndex;
	}
	cout << endl << "COULD NOT FIT JOB INTO MEMORY";
	system("PAUSE");
	exit(EXIT_FAILURE);
}

//Given a jobs data location it will deallocate the data from memory and make it free for other data
void Memory::free(int location, int size)
{
	for (int i = location; i < location + size; i++)
	{
		memoryBlocks[i].empty = true;
		memoryBlocks[i].internal_frag = 0;
	}
}

//Clear the entire memory
void Memory::clear()
{
	for (int i = 0; i < memorySize; i++)
	{
		memoryBlocks[i].empty = true;
		memoryBlocks[i].internal_frag = 0;
	}
}

//Returns the size of the largest block of open memory
int Memory::largestBlock()
{
	int freeBlockCount = 0;
	int largestBlock = 0;
	for (int i = 0; i < memorySize; i++)
	{
		if (memoryBlocks[i].empty == true) freeBlockCount++;
		else if (memoryBlocks[i].empty == false)
		{
			if (freeBlockCount > largestBlock) largestBlock = freeBlockCount;
			freeBlockCount = 0;
		}

		if (i == memorySize - 1)
		{
			if (freeBlockCount > largestBlock) largestBlock = freeBlockCount;
		}
	}
	return largestBlock;
}

//Returns the size of the smallest block of open memory
int Memory::smallestBlock()
{
	int freeBlockCount = 0;
	int smallestBlock = 2400;
	for (int i = 0; i < memorySize; i++)
	{
		if (memoryBlocks[i].empty == true) freeBlockCount++;
		else if (memoryBlocks[i].empty == false)
		{
			if (freeBlockCount < smallestBlock && freeBlockCount != 0) smallestBlock = freeBlockCount;
			freeBlockCount = 0;
		}

		if (i == memorySize - 1)
		{
			if (freeBlockCount < smallestBlock && freeBlockCount != 0) smallestBlock = freeBlockCount;
		}
	}
	return smallestBlock;
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

Block& Memory::getLocation(int index)
{

	return memoryBlocks[index];
}
