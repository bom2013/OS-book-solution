// Auther: Noam Ben Shlomo(Bom2013)
// Exercise 5.3: Dining philosophers problem using multiple process
// ex5_3.cpp - main program that create and handle the 5 process

#include <Windows.h>
#include <string>
#include <iostream>

#define CHILD_PROCESS_EXE_PATH "SinglePhilosopher.exe"
#define NUMBER_OF_PHILOSOPHER 5

constexpr const int pathSize = 26; // exe path + space + digit + NULL

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hMutexList[NUMBER_OF_PHILOSOPHER];

	// create mutexs
	for (size_t i = 0; i < NUMBER_OF_PHILOSOPHER; i++)
	{
		string mutexName = "Chopsticks" + i;
		hMutexList[i] = CreateMutexA(NULL, FALSE, mutexName.c_str());
	}

	// create the process
	STARTUPINFOA si;
	PROCESS_INFORMATION piList[NUMBER_OF_PHILOSOPHER];
	for (size_t i = 0; i < NUMBER_OF_PHILOSOPHER; i++)
	{
		char commandLine[pathSize];
		sprintf_s(commandLine, pathSize, "%s %d", CHILD_PROCESS_EXE_PATH, i);
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&piList[i], sizeof(piList[i]));
		BOOL createResult = CreateProcessA(
			NULL,
			commandLine,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&piList[i]);
		if (!createResult)
		{
			cout << "Error while create process number " << i + 1 << ", error code: " << GetLastError() << endl;
		}
	}

	// wait for each process to terminate
	for (size_t i = 0; i < NUMBER_OF_PHILOSOPHER; i++)
	{
		WaitForSingleObject(piList[i].hProcess, INFINITE);
	}

	// close all mutex handles
	for (size_t i = 0; i < NUMBER_OF_PHILOSOPHER; i++)
	{
		CloseHandle(hMutexList[i]);
	}

	// close all process and threads handles
	for (size_t i = 0; i < NUMBER_OF_PHILOSOPHER; i++)
	{
		CloseHandle(piList[i].hProcess);
		CloseHandle(piList[i].hThread);
	}

	return 0;
}