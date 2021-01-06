/*
Auther: Noam Ben Shlomo(bom2013)
Exercise 7.1: Count letter in file without using MapViewOfFile
*/
#include <Windows.h>
#include <stdio.h>

int main()
{
	CHAR fileName[] = "gibrish.bin";
	LPCSTR pFileName = fileName;
	
	// Create Handle for the file
	HANDLE hFile = CreateFileA(
		pFileName,	// File name
		GENERIC_READ,	// Read access
		0,	// No share
		NULL,	// No inheritance
		OPEN_EXISTING, // Open only if exist
		FILE_ATTRIBUTE_NORMAL,	// No other attributes set
		NULL	// No template file
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Error! Error code: %d", GetLastError());
		return 1;
	}

	// Read the data from the file
	DWORD fileSize = GetFileSize(hFile, NULL);
	LPVOID lpBuffer = malloc(fileSize + 1);
	BOOL bReadFileFlag = ReadFile(
		hFile, // Handle to file
		lpBuffer, // Pointer to buffer
		fileSize, // Maximum byte to read
		NULL, // Not interesting
		NULL // Very uninteresting
	);
	if (FALSE == bReadFileFlag)
	{
		printf("Error! Error code: %d", GetLastError());
		return 1;
	}

	// Count the number of 'A' in the data
	LPSTR data = (LPSTR)lpBuffer;
	size_t count = 0;
	for (size_t i = 0; i < fileSize; i++)
	{
		if (*(data + i) == 'A')
			count++;
	}
	printf("Number of \'A\' in the data: %zu", count);
	
	// Free the memory and cloase the handle
	free(lpBuffer);
	CloseHandle(hFile);

	return 0;
}