/*
Auther: Noam Ben Shlomo(Bom2013)
*/
#include <Windows.h>
#include<iostream>

using namespace std;

#define BUFFER_SIZE 10

int main()
{
	char buffer[BUFFER_SIZE] = { 0 };
	DWORD dwBytesRead;

	// Create file handle
	HANDLE hFile = CreateFileA("test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "Error! error code: " << GetLastError() << endl;
		return 1;
	}

	// Read file using the handle
	BOOL readFileStatus = ReadFile(hFile, buffer, BUFFER_SIZE - 1, &dwBytesRead, NULL);
	if (readFileStatus == FALSE)
	{
		cout << "Error! error code: " << GetLastError() << endl;
		return 1;
	}

	if (dwBytesRead > 0 && dwBytesRead <= BUFFER_SIZE - 1) // Data readed
	{
		buffer[dwBytesRead] = '\0'; // Add NULL character to the end of the string
		cout << "Data readed from file:" << endl;
		cout << buffer << endl;
	}
	else if (dwBytesRead == 0) // No data readed
	{
		cout << "No data readed from file" << endl;
	}
	else // Unexpected value for dwBytesRead - Negative\Bigger than BUFFER_SIZE
	{
		cout << "Unexpected value for dwBytesRead" << endl;
	}

	// Close handle
	CloseHandle(hFile);
	return 0;
}