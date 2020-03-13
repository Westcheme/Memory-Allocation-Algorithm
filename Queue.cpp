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
		Job temp;
		length--;
		temp = queue[front];
		front++;
		return temp;
	}
}

Job Queue::peek()
{
	return queue[front];
}

bool Queue::isEmpty()
{
	return (length == 0);
}

bool Queue::isFull()
{
	return (length == MAX);
}

void Queue::runJob()
{
	queue[front].run();
}