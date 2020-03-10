#include "Queue.h"


Queue::Queue()
{
	front = 0;
	rear = -1;
	length = 0;
}

void Queue::enqueue(Job item)
{
	if (isFull())
	{
		cout << "Queue is full";
	}
	else
	{
		rear++;
		queue[rear] = item;
		length++;
	}
}

Job Queue::dequeue()
{
	if (isEmpty())
	{
		cout << "Queue is empty";
	}
	else
	{
		length--;
		return queue[front++];
	}
}

Job Queue::peek()
{
	return queue[front];
}

int Queue::size()
{
	return length;
}

bool Queue::isEmpty()
{
	return (size() == 0);
}

bool Queue::isFull()
{
	return (size() == MAX);
}

/*
void Queue::print()
{
	for (int i = front; i < rear+1; i++)
	{
		cout << "ArrivalTime = " << queue[i].arrivalTime << endl;
		cout << "Type = " << queue[i].type << endl;
		cout << "RunTime = " << queue[i].runTime << endl;
		cout << "CodeSize = " << queue[i].codeSize << endl;
		cout << "StackSize =  " << queue[i].stackSize << endl;
		cout << "NumHeapElements =  " << queue[i].numHeapElements << endl;
	}
}
*/