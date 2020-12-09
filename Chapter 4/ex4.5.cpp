/*
Auther: Noam Ben Shlomo(bom2013)
Exercise 4.5: 4 threads :)
*/
#include<Windows.h>
#include<cstdio>

DWORD WINAPI printThread(LPVOID lparam)
{
	for (int i = 0; i < 1000; i++)
	{
		printf("Thread %d, var = %d\n", *((LPINT)lparam), i);
	}
	return 0;
}

int main()
{
	int threadId[] = { 1, 2,3,4 };
	HANDLE hThreadArray[4];

	for (int i = 0; i < 4; i++)
	{
		hThreadArray[i] = CreateThread(NULL, 0, printThread, (threadId + i), 0, NULL);
	}

	WaitForMultipleObjects(4, hThreadArray, TRUE, INFINITE);

	return 0;
}