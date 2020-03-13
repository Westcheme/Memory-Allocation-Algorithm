#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "Job.h"
#include "Memory.h"
#include "Queue.h"
using namespace std;


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
	bool simulateLostObjects = false;
	Job createdJob;
	Queue heapElementJobQueue;
	int codeLocation, stackLocation, heapLocation;
	ofstream randomJobs("randomJobs.txt");
	string testName, logFileName, metricsFileName;

	int memAllocated = 0;
	int numHeapAllocations = 0;
	int numLostObjects = 0;
	int totalMemorySizeLostObjects = 0;
	int numAllocations = 0;
	int numFreeRequests = 0, numHeapFreeRequests = 0;
	int smallestBlock, largestBlock;

	cout << "What would you like to name the Test? ";
	cin >> testName;

	cout << "Name of the Log File? ";
	cin >> logFileName;

	cout << "Name of the Metrics File? ";
	cin >> metricsFileName;

	ofstream logFile(logFileName + ".txt");
	ofstream metricsFile(metricsFileName + ".txt");

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

	while (true)
	{
		cout << "Generate Lost Objects? (y/n) ";
		cin >> lostObj;

		if (lostObj == 'Y' || lostObj == 'y')
		{
			simulateLostObjects = true;
			break;
		}
		else if (lostObj == 'N' || lostObj == 'n') break;
		else cout << "Must be y or n" << endl;
	}

	int test = 0;
	cout << endl << testName << endl;
	metricsFile << testName << endl;

	//Will run through each memory allocation type in order of FF, NF, BF, WF
	while (test < 4)
	{
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

			if (timeUnit == 6000)
			{
				largestBlock = myMemory.largestBlock();
				smallestBlock = myMemory.smallestBlock();
			}

			//Once the arrivalTime has been reached of the incoming job, allocate its code and stack, and begin allocating its heapElements
			if (createdJob.getArrivalTime() == timeUnit)
			{
				if (test == 0)
				{
					codeLocation = myMemory.mallocFF(createdJob.getCodeSize());
					stackLocation = myMemory.mallocFF(createdJob.getStackSize());
				}
				else if (test == 1)
				{
					codeLocation = myMemory.mallocNF(createdJob.getCodeSize());
					stackLocation = myMemory.mallocNF(createdJob.getStackSize());
				}
				else if (test == 2)
				{
					codeLocation = myMemory.mallocBF(createdJob.getCodeSize());
					stackLocation = myMemory.mallocBF(createdJob.getStackSize());
				}
				else if (test == 3)
				{
					codeLocation = myMemory.mallocWF(createdJob.getCodeSize());
					stackLocation = myMemory.mallocWF(createdJob.getStackSize());
				}
				numAllocations++;
				heapElementJobQueue.enqueue(createdJob);
				memAllocated += heapElementJobQueue.peek().totalJobSize();
			}

			//If heapElements must still be allocated then allocate them
			if (!heapElementJobQueue.isEmpty())
			{
				if (test == 0) heapLocation = myMemory.mallocFF(heapElementJobQueue.peek().getHeapElements());
				else if (test == 1) heapLocation = myMemory.mallocNF(heapElementJobQueue.peek().getHeapElements());
				else if (test == 2) heapLocation = myMemory.mallocBF(heapElementJobQueue.peek().getHeapElements());
				else if (test == 3) heapLocation = myMemory.mallocWF(heapElementJobQueue.peek().getHeapElements());
				myMemory.free(heapLocation, heapElementJobQueue.peek().getHeapElements());
				heapElementJobQueue.runJob();
				numHeapFreeRequests++;
				numHeapAllocations++;
			}

			//Once a jobs heapElements are finished allocating, free the job from memory
			if (heapElementJobQueue.peek().getRunTime() == 0 && !heapElementJobQueue.isEmpty())
			{
				if (simulateLostObjects == true && (currentNumSmlJobs % 100 == 0 || currentNumMedJobs % 100 == 0 || currentNumLrgJobs % 100 == 0))
				{
					numLostObjects++;
					totalMemorySizeLostObjects += heapElementJobQueue.dequeue().totalJobSize();
					goto skip;
				}
				myMemory.free(codeLocation, heapElementJobQueue.peek().getCodeSize());
				myMemory.free(stackLocation, heapElementJobQueue.peek().getStackSize());
				myMemory.free(heapLocation, heapElementJobQueue.peek().getHeapElements());
				numFreeRequests++;
				heapElementJobQueue.dequeue();
			}
			skip:

			//Outputting to Screen and Summary File
			if (timeUnit >= 200 && timeUnit % 20)
			{

			}

			timeUnit++;
		}

		//METRICS//
		if (test == 0) metricsFile << "\t\t\t\t\t" << "First Fit" << endl;
		else if (test == 1) metricsFile << "\t\t\t\t\t" << "Next Fit" << endl;
		else if (test == 2) metricsFile << "\t\t\t\t\t" << "Best Fit" << endl;
		else if (test == 3) metricsFile << "\t\t\t\t\t" << "Worst Fit" << endl;
		metricsFile << "number of small jobs" << "\t\t\t" << currentNumSmlJobs << endl;
		metricsFile << "number of medium jobs" << "\t\t\t" << currentNumMedJobs << endl;
		metricsFile << "number of large jobs" << "\t\t\t" << currentNumLrgJobs << endl;
		metricsFile << "total memory defined" << "\t\t\t" << numMemUnits * memUnitSize << endl;
		metricsFile << "memory allocated" << "\t\t\t" << memAllocated << endl;
		metricsFile << "% memory in use" << "\t\t\t\t" << (float)(numMemUnits * memUnitSize) / memAllocated * 100 << endl;
		metricsFile << "required amount of memory" << "\t\t" << memAllocated << endl;
		metricsFile << "internal fragmentation" << "\t\t\t" << myMemory.getTotalInternalFrag() << endl;
		metricsFile << "% internal fragmentation" << "\t\t" << setprecision(5) << (float)myMemory.getTotalInternalFrag() / (numMemUnits * memUnitSize) * 100 << endl;
		metricsFile << "% memory free" << "\t\t\t\t" << (float)100 - (numMemUnits * memUnitSize) / memAllocated * 100 << endl;
		metricsFile << "external fragmentation" << "\t\t\t" << memAllocated - (numMemUnits * memUnitSize) << endl;
		metricsFile << "largest free space" << "\t\t\t" << largestBlock * memUnitSize << endl;
		metricsFile << "smallest free space" << "\t\t\t" << smallestBlock * memUnitSize << endl;
		metricsFile << "number heap allocations" << "\t\t\t" << numHeapAllocations << endl;
		metricsFile << "number of lost ojects" << "\t\t\t" << numLostObjects << endl;
		if (simulateLostObjects == false) metricsFile << "total memory size of lost objects" << "\t" << totalMemorySizeLostObjects << endl;
		else if (simulateLostObjects == true) metricsFile << "total memory size of lost objects" << "\t" << totalMemorySizeLostObjects << endl;
		metricsFile << "% memory of lost objects" << "\t\t" << (float)totalMemorySizeLostObjects / memAllocated * 100 << endl;
		metricsFile << "number of allocations" << "\t\t\t" << numAllocations << endl;
		metricsFile << "number of allocation operations" << "\t\t" << numAllocations * 2 + (numHeapAllocations / 2) << endl;
		metricsFile << "number of free requests" << "\t\t\t" << numFreeRequests << endl;
		metricsFile << "number of free operations" << "\t\t" << numFreeRequests + numHeapFreeRequests <<endl << endl << endl;
		//METRICS//

		//Go to the next test
		test++;
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
