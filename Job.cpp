#include "Job.h"

//Constructor for all Job types
Job::Job()
{
	arrivalTime = rand() % 5 + 1;
}

//Manually sets the arrival time of any Job type by adding the randomly generated number to the input parameter
void Job::setArrivalTime(int currentTime)
{
	arrivalTime += currentTime;
}

//Constructor for a Small Job
smallJob::smallJob()
{
	type = "Small";
	runTime = rand() % 3 + 4;
	codeSize = rand() % 41 + 40;
	stackSize = rand() % 21 + 20;
	numHeapElements = 50 * runTime;
	heapElements = new int[numHeapElements];
	for (int i = 0; i < numHeapElements; i++)
	{
		heapElements[i] = rand() % 31 + 20;
	}
}

//Constructor for Medium Job
mediumJob::mediumJob()
{
	type = "Medium";
	runTime = rand() % 3 + 9;
	codeSize = rand() % 61 + 60;
	stackSize = rand() % 41 + 40;
	numHeapElements = 100 * runTime;
	heapElements = new int[numHeapElements];
	for (int i = 0; i < numHeapElements; i++)
	{
		heapElements[i] = rand() % 31 + 20;
	}
}

//Constructor for a Large Job
largeJob::largeJob()
{
	type = "Large";
	runTime = rand() % 3 + 24;
	codeSize = rand() % 101 + 120;
	stackSize = rand() % 61 + 60;
	numHeapElements = 250 * runTime;
	heapElements = new int[numHeapElements];
	for (int i = 0; i < numHeapElements; i++)
	{
		heapElements[i] = rand() % 31 + 20;
	}
}

//Returns all of the contents, minus heap elements, of any Job type as a string
string Job::contents()
{
	string temp = "";

	temp += to_string(arrivalTime) + " ";
	temp += type + " ";
	temp += to_string(runTime) + " ";
	temp += to_string(codeSize) + " ";
	temp += to_string(stackSize) + " ";
	temp += to_string(numHeapElements) + '\n';

	return temp;
}

//Print all of the contents, minus heap elements, of any Job type to the terminal
void Job::print()
{
	cout << type << endl;
	cout << "Arrival Time: " << arrivalTime << endl;
	cout << "Run Time: " << runTime << endl;
	cout << "Code Size: " << codeSize << endl;
	cout << "Stack Size: " << stackSize << endl;
	cout << "# Heap Elements: " << numHeapElements << endl;
}
