/*
Auther: Noam Ben Shlomo(bom2013)
Exercise 7.2: Count letter in file using MapViewOfFile
*/
#include <Windows.h>
#include <stdio.h>

int countChar(LPSTR pBuffer, int bufferSize, char letter)
{
	int count = 0;
	for (size_t i = 0; i < bufferSize; i++)
	{
		if (pBuffer[i] == letter)
		{
			count++;
		}
	}
	return count;
}

int main()
{
	// Create Handle to the file
	CHAR fileName[] = "gibrish.bin";
	LPCSTR pFileName = fileName;
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
	
	// Create File Mapping Handle to the file
	HANDLE hMapFile = CreateFileMappingA(
		hFile, // Handle to the file
		NULL, // No inheritance
		PAGE_READONLY, // Read only access
		0, // Current hFile size
		0, // Current hFile size
		NULL // No sharing needed
	);
	if (NULL == hMapFile)
	{
		printf("Error! Error code: %d", GetLastError());
		return 1;
	}

	// Get the system allocation granularity.
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	DWORD dwSysAllocGran = SysInfo.dwAllocationGranularity;
	printf("System allocation granularity is %lu\n", dwSysAllocGran);

	// Read from file, one page at time
	DWORD fileSize = GetFileSize(hFile, NULL);
	int bufferNumber = 0;
	int count = 0;
	int fileLocation = bufferNumber * dwSysAllocGran;
	while (fileLocation <= (fileSize - dwSysAllocGran))
	{
		LPSTR pBuffer = (LPSTR)MapViewOfFile(
			hMapFile, // Handle to the file mapping object
			FILE_MAP_READ, // Read only
			0, // High order file offset
			fileLocation, // Low order file offset
			dwSysAllocGran // System allocation granularity
		);
		if (NULL == pBuffer)
		{
			printf("Error! Error code: %d", GetLastError());
			return 1;
		}
		// Count the char in the data readed from the file
		int tempCount = countChar(pBuffer, dwSysAllocGran, 'A');
		count += tempCount;
		printf("Buffer number %d: count = %d\n", bufferNumber, tempCount);
		
		// Promote the variables to the next part of the file
		bufferNumber++;
		fileLocation = bufferNumber * dwSysAllocGran;
		
		// Release the view we finished to work with
		UnmapViewOfFile(pBuffer);
	}

	// Work with the reminder of the file
	int reminder = fileSize - fileLocation;
	LPSTR pBuffer = (LPSTR)MapViewOfFile(
		hMapFile, // Handle to the file mapping object
		FILE_MAP_READ, // Read only
		0, // High order file offset
		fileLocation, // Low order file offset
		reminder // System allocation granularity
	);
	if (NULL == pBuffer)
	{
		printf("Error! Error code: %d", GetLastError());
		return 1;
	}
	// Count the char in the remind data
	int tempCount = countChar(pBuffer, reminder, 'A');
	count += tempCount;
	printf("Reminder: count = %d\n", tempCount);
	// Release the view we finished to work with
	UnmapViewOfFile(pBuffer);

	printf("Total \'A\' count is %d\n", count);

	// Close the Handles
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return 0;
}