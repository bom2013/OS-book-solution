/*
Auther: Noam Ben Shlomo(bom2013)
Exercise 4.3: Creating thread
*/
#include<Windows.h>
#include<iostream>

using namespace std;

struct Tuple
{
	INT a;
	INT b;
};

DWORD WINAPI testThread(LPVOID lparam)
{
	//struct Tuple* nums = (Tuple*)lparam;
	INT count = ((Tuple*)lparam)->a + ((Tuple*)lparam)->b;
	for (INT i = 0; i < count; i++)
	{
		cout << i << endl;
	}
	return 1;
}
int main()
{
	void *ptuple = new Tuple();
	((Tuple*)ptuple)->a = 1;
	((Tuple*)ptuple)->b = 2;
	HANDLE hThread = CreateThread(NULL, 0, testThread, ptuple, 0, NULL);
	if (hThread == NULL)
	{
		cout << "Error! error code: " << GetLastError() << endl;
		return 1;
	}

	// Wait for the thread
	WaitForSingleObject(hThread, INFINITE);

	// Free the memory
	delete ptuple;
	system("pause");
	return 0;
}