// Auther: Noam Ben Shlomo(Bom2013)
// Exercise 5.3: Dining philosophers problem using multiple process
// SinglePhilosopher.cpp - Represents one philosopher

#include <Windows.h>
#include <string>
#include <iostream>

#define NUMBER_OF_PHILOSOPHER 5

using namespace std;

int main(int argc, char* argv[])
{
	// check number of argument
	if (argc != 2)
	{
		cout << "Wrong number of arguments" << endl;
		return 1;
	}

	// get the number of this philosopher
	const int philosopherNumber = atoi(argv[1]);

	// create mutex names
	const string mutexName1 = "Chopsticks" + philosopherNumber;
	const string mutexName2 = "Chopsticks" + (philosopherNumber + 1) % NUMBER_OF_PHILOSOPHER;

	// create mutex handles
	HANDLE hMutex1, hMutex2;

	// create\open first mutex
	hMutex1 = CreateMutexA(NULL, FALSE, mutexName1.c_str());
	if (hMutex1 == NULL)
	{
		cout << "Error while create mutex 1, error code: " << GetLastError() << endl;
		return 1;
	}

	// create\open second mutex
	hMutex2 = CreateMutexA(NULL, FALSE, mutexName2.c_str());
	if (hMutex2 == NULL)
	{

		cout << "Error while create mutex 2, error code: " << GetLastError() << endl;
		return 1;
	}

	// eat loop
	bool success = false;
	while (!success)
	{
		// wait for first mutex
		WaitForSingleObject(hMutex1, INFINITE);

		// check if second mutex is free
		DWORD waitResult = WaitForSingleObject(hMutex2, 0);
		if (waitResult == WAIT_OBJECT_0)
		{
			// if second mutex free eat and release the two mutexs
			printf("Philosopher number %d eat\n", philosopherNumber);
			ReleaseMutex(hMutex1);
			ReleaseMutex(hMutex2);
			success = true;
		}
		else
			// if second mutex isnt free, release first mutex to prevent deadlock
			ReleaseMutex(hMutex1);
	}

	// close both mutex handles
	CloseHandle(hMutex1);
	CloseHandle(hMutex2);

	return 0;
}