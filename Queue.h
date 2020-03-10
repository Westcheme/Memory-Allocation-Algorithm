#pragma once

#include <iostream>
#include <string>
#include "Job.h"
using namespace std;

#define MAX 2400


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
	int size();
	bool isEmpty();
	bool isFull();
	void print();
};