#pragma once

#include <iostream>
#include <string>
using namespace std;



class Job
{
protected:
	string type;
	int arrivalTime;
	int runTime;
	int codeSize;
	int stackSize;
	int numHeapElements;
	int *heapElements;

public:
	Job();
	void print();
	void setArrivalTime(int currentTime);
	string contents();
	void set(string type, int arrivalTime, int runTime, int codeSize, int stackSize, int numHeapElements);
	int getArrivalTime();
	int getCodeSize();
	int getStackSize();
};


class smallJob : public Job
{
public:
	smallJob();
};

class mediumJob : public Job
{
public:
	mediumJob();
};

class largeJob : public Job
{
public:
	largeJob();
};
