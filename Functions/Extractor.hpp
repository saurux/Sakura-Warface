#pragma once

#include <Windows.h>
#include <iostream>

class CExtractor {
public:
	static std::string GetTemporaryPath()
	{
		char buffer[MAX_PATH];
		GetTempPathA(MAX_PATH, buffer);

		return buffer;
	}

	static bool ExtractFile(std::string filename, BYTE* file, DWORD dwSize)
	{
		HANDLE hNewFile = CreateFileA(std::string(GetTemporaryPath() + filename).c_str(), GENERIC_ALL, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

		if (GetLastError() == ERROR_FILE_EXISTS)
		{
			CloseHandle(hNewFile);
			return true;
		}

		if (hNewFile == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD NumberOfBytesWritten = 0;
		if (!WriteFile(hNewFile, file, dwSize, &NumberOfBytesWritten, nullptr))
			return false;

		CloseHandle(hNewFile);
		return true;
	}
};