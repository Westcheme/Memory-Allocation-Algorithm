#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "Job.h"
using namespace std;


Job *createNewSmlJob(int currentTime);
Job *createNewMedJob(int currentTime);
Job *createNewLrgJob(int currentTime);


int main()
{
	srand(time(NULL));
	int smlJobPerc, medJobPerc, lrgJobPerc, memUnitSize;
	int totalSmlJobs, totalMedJobs, totalLrgJobs;
	int actualTotalJobs = 0, currentNumSmlJobs = 0, currentNumMedJobs = 0, currentNumLrgJobs = 0;
	bool smlJobsDone = false, medJobsDone = false, lrgJobsDone = false;
	int randNum;
	int timeUnit = 0, runTime = 12000, timeBlock = 5, totalJobs = runTime / timeBlock;
	Job *createdJob;
	ofstream algorithmInput("algorithmInput.txt");

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

	totalSmlJobs = (float)totalJobs * smlJobPerc / 100;
	totalMedJobs = (float)totalJobs * medJobPerc / 100;
	totalLrgJobs = (float)totalJobs * lrgJobPerc / 100;

	cout << endl << "Total Small Jobs to be created: \t" << totalSmlJobs << endl;
	cout << "Total Medium Jobs to be created: \t" << totalMedJobs << endl;
	cout << "Total Large Jobs to be created: \t" << totalLrgJobs << endl << endl;


	while (true)
	{
		cout << "Memory Unity Size? ";
		cin >> memUnitSize;

		if (memUnitSize % 8 == 0) break;
		else cout << "Must be a multiple of 8" << endl;
	}


	while (timeUnit < runTime)
	{
		cout << timeUnit << "------------" << endl;

		if (timeUnit % 5 == 0)
		{
			randNum = (rand() % (smlJobPerc + medJobPerc + lrgJobPerc)) + 1;

			if (randNum <= smlJobPerc && currentNumSmlJobs != totalSmlJobs)
			{
				createdJob = createNewSmlJob(timeUnit);
				algorithmInput << createdJob->contents();
				createdJob->print();
				currentNumSmlJobs++;
				actualTotalJobs++;
				if (currentNumSmlJobs == totalSmlJobs) smlJobPerc = 0;
			}
			else if (randNum > smlJobPerc && randNum <= smlJobPerc + medJobPerc && currentNumMedJobs != totalMedJobs)
			{
				createdJob = createNewMedJob(timeUnit);
				algorithmInput << createdJob->contents();
				createdJob->print();
				currentNumMedJobs++;
				actualTotalJobs++;
				if (currentNumMedJobs == totalMedJobs) medJobPerc = 0;
			}
			else if (randNum > smlJobPerc + medJobPerc && randNum <= smlJobPerc + medJobPerc + lrgJobPerc && currentNumLrgJobs != totalLrgJobs)
			{
				createdJob = createNewLrgJob(timeUnit);
				algorithmInput << createdJob->contents();
				createdJob->print();
				currentNumLrgJobs++;
				actualTotalJobs++;
				if (currentNumSmlJobs == totalLrgJobs) lrgJobPerc = 0;
			}
		}

		cout << endl << endl << endl;
		timeUnit++;
	}

	cout << "Actual Total Jobs Created: \t" << actualTotalJobs << endl;
	cout << "Actual Small Jobs Created: \t" << currentNumSmlJobs << endl;
	cout << "Actual Medium Jobs Created: \t" << currentNumMedJobs << endl;
	cout << "Actual Large Jobs Created: \t" << currentNumLrgJobs << endl << endl;

	cout << "Actual Percentage of Small Jobs: \t" << (float)currentNumSmlJobs / totalJobs * 100 << endl;
	cout << "Actual Percentage of Medium Jobs: \t" << (float)currentNumMedJobs / totalJobs * 100 << endl;
	cout << "Actual Percentage of Large Jobs: \t" << (float)currentNumLrgJobs / totalJobs * 100 << endl;

	algorithmInput.close();
	system("PAUSE");
	return 0;
}

Job *createNewSmlJob(int currentTime)
{
	smallJob *newSmallJob = new smallJob;
	newSmallJob->setArrivalTime(currentTime);
	return newSmallJob;
}

Job *createNewMedJob(int currentTime)
{
	mediumJob *newMediumJob = new mediumJob;
	newMediumJob->setArrivalTime(currentTime);
	return newMediumJob;
}

Job *createNewLrgJob(int currentTime)
{
	largeJob *newLargeJob = new largeJob;
	newLargeJob->setArrivalTime(currentTime);
	return newLargeJob;
}