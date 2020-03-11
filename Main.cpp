#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "Job.h"
#include "Memory.h"
#include "Queue.h"



Job createNewSmlJob(int currentTime);
Job createNewMedJob(int currentTime);
Job createNewLrgJob(int currentTime);



int main()
{
	srand(time(NULL));
	int smlJobPerc, medJobPerc, lrgJobPerc, memUnitSize, numMemUnits;
	int totalSmlJobs, totalMedJobs, totalLrgJobs;
	int actualTotalJobs = 0, currentNumSmlJobs = 0, currentNumMedJobs = 0, currentNumLrgJobs = 0;
	int randNum;
	int timeUnit = 0;
	char lostObj;
	Job createdJob;
	Queue heapElementJobQueue;
	ofstream randomJobs("randomJobs.txt");

	while (true)
	{
		cout << "Percentage of Small Jobs? ";
		cin >> smlJobPerc;

		cout << "Percentage of Medium Jobs? ";
		cin >> medJobPerc;
		
		cout << "Percentage of Large Jobs? ";
		cin >> lrgJobPerc;

		if (smlJobPerc + medJobPerc + lrgJobPerc == 100) break;
		else cout << "Must add to 100%" << endl;
	}

	totalSmlJobs = (float)2400 * smlJobPerc / 100;
	totalMedJobs = (float)2400 * medJobPerc / 100;
	totalLrgJobs = (float)2400 * lrgJobPerc / 100;

	cout << endl << "Total Small Jobs to be created: \t" << totalSmlJobs << endl;
	cout << "Total Medium Jobs to be created: \t" << totalMedJobs << endl;
	cout << "Total Large Jobs to be created: \t" << totalLrgJobs << endl << endl;

	while (true)
	{
		cout << "Memory Unit Size? ";
		cin >> memUnitSize;

		if (memUnitSize % 8 == 0 && memUnitSize != 0) break;
		else cout << "Must be a multiple of 8" << endl;
	}
	while (true)
	{
		cout << "Number of Memory Units? ";
		cin >> numMemUnits;

		if (numMemUnits > 0) break;
		else cout << "Must be greater than 0" << endl;
	}
	Memory myMemory(numMemUnits, memUnitSize);

	myMemory.print();
	cin.get();

	while (true)
	{
		cout << "Generate Lost Objects? (y/n) ";
		cin >> lostObj;

		if (lostObj == 'Y' || lostObj == 'y' || lostObj == 'N' || lostObj == 'n') break;
		else cout << "Must be y or n" << endl;
	}



	while (timeUnit < 12000)
	{
		//If timeUnit is a multiple of 5, a random job will be created based on the percentages input by the user
		if (timeUnit % 5 == 0)
		{
			randNum = rand() % (smlJobPerc + medJobPerc + lrgJobPerc);

			if (randNum < smlJobPerc && currentNumSmlJobs != totalSmlJobs)
			{
				createdJob = createNewSmlJob(timeUnit);
				randomJobs << createdJob.contents();
				currentNumSmlJobs++;
				actualTotalJobs++;
				if (currentNumSmlJobs == totalSmlJobs) smlJobPerc = 0;
			}
			else if (randNum >= smlJobPerc && randNum < (smlJobPerc + medJobPerc) && currentNumMedJobs != totalMedJobs)
			{
				createdJob = createNewMedJob(timeUnit);
				randomJobs << createdJob.contents();
				currentNumMedJobs++;
				actualTotalJobs++;
				if (currentNumMedJobs == totalMedJobs) medJobPerc = 0;
			}
			else if (randNum >= (smlJobPerc + medJobPerc) && randNum < (smlJobPerc + medJobPerc + lrgJobPerc) && currentNumLrgJobs != totalLrgJobs)
			{
				createdJob = createNewLrgJob(timeUnit);
				randomJobs << createdJob.contents();
				currentNumLrgJobs++;
				actualTotalJobs++;
				if (currentNumSmlJobs == totalLrgJobs) lrgJobPerc = 0;
			}
		}

		
		//Once the arrivalTime has been reached of the incoming job, allocate its code and stack, and begin allocating its heapElements
		if (createdJob.getArrivalTime() == timeUnit)
		{
			myMemory.mallocFF(createdJob.getCodeSize());
			myMemory.mallocFF(createdJob.getStackSize());
			myMemory.mallocFF(createdJob.getHeapElements());
			heapElementJobQueue.enqueue(createdJob);
		}

		//If heapElements must still be allocated then allocate them
		if (!heapElementJobQueue.isEmpty())
		{
			myMemory.mallocFF(heapElementJobQueue.peek().getHeapElements());
		}

		//Once a jobs heapElements are finished allocating, free the job from memory
		if (heapElementJobQueue.peek().getRunTime() == 0)
		{
			//myMemory.free(heapElementJobQueue.dequeue().getCodeLocation());
			//myMemory.free(heapElementJobQueue.dequeue().getStackLocation());
			//myMemory.free(heapElementJobQueue.dequeue().getHeapLocation());
		}
		

		timeUnit++;
	}
	randomJobs.close();

	cout << endl << endl << endl;
	cout << "Actual Total Jobs Created: \t" << actualTotalJobs << endl;
	cout << "Actual Small Jobs Created: \t" << currentNumSmlJobs << endl;
	cout << "Actual Medium Jobs Created: \t" << currentNumMedJobs << endl;
	cout << "Actual Large Jobs Created: \t" << currentNumLrgJobs << endl << endl;

	cout << "Actual Percentage of Small Jobs: \t" << (float)currentNumSmlJobs / actualTotalJobs * 100 << endl;
	cout << "Actual Percentage of Medium Jobs: \t" << (float)currentNumMedJobs / actualTotalJobs * 100 << endl;
	cout << "Actual Percentage of Large Jobs: \t" << (float)currentNumLrgJobs / actualTotalJobs * 100 << endl;

	return 0;
}


//Creates a new Small Job and returns it as a Job
//Takes in the current time unit as a parameter in order to set the arrival time of the Job
Job createNewSmlJob(int currentTime)
{
	smallJob newSmallJob = *new smallJob;
	newSmallJob.setArrivalTime(currentTime);
	return newSmallJob;
}

//Creates a new Medium Job and returns it as a Job
//Takes in the current time unit as a parameter in order to set the arrival time of the Job
Job createNewMedJob(int currentTime)
{
	mediumJob newMediumJob = *new mediumJob;
	newMediumJob.setArrivalTime(currentTime);
	return newMediumJob;
}

//Creates a new Large Job and returns it as a Job
//Takes in the current time unit as a parameter in order to set the arrival time of the Job
Job createNewLrgJob(int currentTime)
{
	largeJob newLargeJob = *new largeJob;
	newLargeJob.setArrivalTime(currentTime);
	return newLargeJob;
}
