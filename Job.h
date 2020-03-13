#pragma once

#include <iostream>
#include <string>
#include "Memory.h"
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
	int codeLocation;
	int stackLocation;
	int heapLocation;

public:
	Job();
	void print();
	void setArrivalTime(int currentTime);
	string contents();
	string getType();
	int getArrivalTime();
	int getRunTime();
	int getCodeSize();
	int getStackSize();
	int getNumHeapElements();
	int getHeapElements();
	int getTotalHeapSize();
	int totalJobSize();
	int getCodeLocation();
	int getStackLocation();
	int getHeapLocation();
	void setCodeLocation(int codeLocationIndex);
	void setStackLocation(int stackLocationIndex);
	void setHeapLocation(int heapLocationIndex);
	void run();
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
