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
