#pragma once

#include <iostream>
#include <string>
#include "Job.h"
using namespace std;

#define MAX 15000


class Queue : protected Job
{
private:
	Job queue[MAX];
	int front;
	int rear;
	int length;

public:
	Queue();

	void enqueue(Job item);
	Job dequeue();
	Job peek();
	bool isEmpty();
	bool isFull();
	void runJob();
};