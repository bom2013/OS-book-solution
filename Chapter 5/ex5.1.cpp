/*
Auther: Noam Ben Shlomo(bom2013)
Exercise 5.1: Dining philosophers problem
*/
#include <Windows.h>
#include<cstdio>

const int NUMBER_OF_PHILOSOPHERS = 5;
CRITICAL_SECTION csChopsticks[NUMBER_OF_PHILOSOPHERS];

DWORD WINAPI philosopherThread(LPVOID lpParam)
{
	int leftChopstick = *((int*)(lpParam));
	int rightChopstick = (leftChopstick + 1) % NUMBER_OF_PHILOSOPHERS;

	bool successfulCatch = false;
	while (!successfulCatch)
	{
		EnterCriticalSection(csChopsticks + leftChopstick);
		successfulCatch = TryEnterCriticalSection(csChopsticks + rightChopstick);
		if (successfulCatch) // If right chopstick available
		{
			printf("Philosopher number %d eat using %d and %d chopstick\n", leftChopstick, leftChopstick, rightChopstick);
			LeaveCriticalSection(csChopsticks + rightChopstick);
		}
		LeaveCriticalSection(csChopsticks + leftChopstick);
	}
	return 0;
}

int main()
{
	// Initialize the cs
	for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
	{
		InitializeCriticalSection(csChopsticks + i);
	}

	// Initialize chopstick number array
	int chopstickArray[NUMBER_OF_PHILOSOPHERS];
	for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
	{
		chopstickArray[i] = i;
	}

	// Create threads
	HANDLE hPhilosophers[NUMBER_OF_PHILOSOPHERS];
	for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
	{
		hPhilosophers[i] = CreateThread(
			NULL, // Default security descripter
			0, // Default stack size
			philosopherThread, // Thread function
			chopstickArray + i, // Parameter
			0, // Run immediately
			NULL // Thread identifier not returned
		);
	}

	// Wait for the threads to finish
	WaitForMultipleObjects(NUMBER_OF_PHILOSOPHERS, hPhilosophers, TRUE, INFINITE);

	// Free the cs
	for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
	{
		DeleteCriticalSection(csChopsticks + i);
	}

	return 0;
}