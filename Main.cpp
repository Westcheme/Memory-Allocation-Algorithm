#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "Job.h"
#include "Memory.h"
using namespace std;


Job *createNewSmlJob(int currentTime);
Job *createNewMedJob(int currentTime);
Job *createNewLrgJob(int currentTime);


int main()
{
	srand(time(NULL));
	int smlJobPerc, medJobPerc, lrgJobPerc, memUnitSize, numMemUnits;
	int totalSmlJobs, totalMedJobs, totalLrgJobs;
	int actualTotalJobs = 0, currentNumSmlJobs = 0, currentNumMedJobs = 0, currentNumLrgJobs = 0;
	int randNum;
	int timeUnit = 0;
	char lostObj;
	Job *createdJob;
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

	cout << "Generate lost objs? (y/n)";
	cin >> lostObj;
	
	Memory myMemory(numMemUnits, memUnitSize);

	//Random Job Generation Algorithm
	while (timeUnit < 12000)
	{
		//cout << timeUnit << "------------" << endl;

		//If timeUnit is a multiple of 5, a random job will be created based on the percentages input by the user
		if (timeUnit % 5 == 0)
		{
			randNum = (rand() % (smlJobPerc + medJobPerc + lrgJobPerc)) + 1;

			if (randNum <= smlJobPerc && currentNumSmlJobs != totalSmlJobs)
			{
				createdJob = createNewSmlJob(timeUnit);
				randomJobs << createdJob->contents();
				//createdJob->print();
				currentNumSmlJobs++;
				actualTotalJobs++;
				if (currentNumSmlJobs == totalSmlJobs) smlJobPerc = 0;
			}
			else if (randNum > smlJobPerc && randNum <= smlJobPerc + medJobPerc && currentNumMedJobs != totalMedJobs)
			{
				createdJob = createNewMedJob(timeUnit);
				randomJobs << createdJob->contents();
				//createdJob->print();
				currentNumMedJobs++;
				actualTotalJobs++;
				if (currentNumMedJobs == totalMedJobs) medJobPerc = 0;
			}
			else if (randNum > smlJobPerc + medJobPerc && randNum <= smlJobPerc + medJobPerc + lrgJobPerc && currentNumLrgJobs != totalLrgJobs)
			{
				createdJob = createNewLrgJob(timeUnit);
				randomJobs << createdJob->contents();
				//createdJob->print();
				currentNumLrgJobs++;
				actualTotalJobs++;
				if (currentNumSmlJobs == totalLrgJobs) lrgJobPerc = 0;
			}
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
	

	int at, rt, cs, ss, nhe, *he;
	string t;
	Job incomingJob;
	ifstream algorithmInput("randomJobs.txt");
	timeUnit = 0;

	//Memory Allocation Algorithm
	while (timeUnit < 12000)
	{
		algorithmInput >> at >> t >> rt >> cs >> ss >> nhe;

		incomingJob.set(t, at, rt, cs, ss, nhe);

		incomingJob.print();
		cout << endl;

		//if (timeUnit == incomingJob.arrivalTime)
		//{
		//	myMemory.mallocFF(incomingJob);
		//}

		timeUnit++;
	}


	system("PAUSE");
	return 0;
}


//Creates a new Small Job and returns it as a Job
//Takes in the current time unit as a parameter in order to set the arrival time of the Job
Job *createNewSmlJob(int currentTime)
{
	smallJob *newSmallJob = new smallJob;
	newSmallJob->setArrivalTime(currentTime);
	return newSmallJob;
}

//Creates a new Medium Job and returns it as a Job
//Takes in the current time unit as a parameter in order to set the arrival time of the Job
Job *createNewMedJob(int currentTime)
{
	mediumJob *newMediumJob = new mediumJob;
	newMediumJob->setArrivalTime(currentTime);
	return newMediumJob;
}

//Creates a new Large Job and returns it as a Job
//Takes in the current time unit as a parameter in order to set the arrival time of the Job
Job *createNewLrgJob(int currentTime)
{
	largeJob *newLargeJob = new largeJob;
	newLargeJob->setArrivalTime(currentTime);
	return newLargeJob;
}
