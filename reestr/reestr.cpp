#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <time.h>

int main()
{
	HKEY hKey, MyParam;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	LPWSTR arr = calloc(512,sizeof(WCHAR));
	if (RegOpenKeyW(HKEY_CURRENT_USER, NULL, &hKey) == ERROR_SUCCESS)
	{
		RegCreateKeyW(hKey, L"MyParam", &MyParam);
		LPWSTR b = asctime(timeinfo);
		LPWSTR NewB= calloc(25, sizeof(WCHAR));
		MultiByteToWideChar(CP_OEMCP, 0, b, -1, NewB, wcslen(b)*2);
		wsprintf(arr, L"Текущее время: %s", NewB);
		if(RegSetValueExW(MyParam, L"Time", NULL, REG_SZ, arr, wcslen(arr)* sizeof(WCHAR))==ERROR_SUCCESS);
		{
			MessageBox(NULL, arr, L"Успешно", MB_OK);
		}
		RegCloseKey(hKey);
	}
	//else

	if (RegOpenKeyW(HKEY_CURRENT_USER, NULL, &hKey) == ERROR_SUCCESS)
	{
		LPWSTR StrKey = calloc(200, sizeof(WCHAR));
		DWORD dataType = 0, dataLen = 400;
		if (RegGetValueW(HKEY_CURRENT_USER, L"MyParam", L"Time", RRF_RT_ANY, &dataType, StrKey, &dataLen) == ERROR_SUCCESS)
		{
			MessageBox(NULL, StrKey, L"", MB_OK);
		}
		RegCloseKey(hKey);
	}

	return 0;
}