#include "pch.h"
#include "HookAddresses.h"

namespace Hooks
{
	int spotifyVer = -1; // e.g. "25" == 1.1.25.559

	int HookAddresses::getSpotifyVersion()
	{
		if (spotifyVer != -1)
			return spotifyVer;

		LPCWSTR lpszFilePath = L"Spotify.exe";
		DWORD dwDummy;
		DWORD dwFVISize = GetFileVersionInfoSize(lpszFilePath, &dwDummy);
		LPBYTE lpVersionInfo = new BYTE[dwFVISize];
		GetFileVersionInfo(lpszFilePath, 0, dwFVISize, lpVersionInfo);
		UINT uLen;
		VS_FIXEDFILEINFO* lpFfi;
		VerQueryValue(lpVersionInfo, _T("\\"), (LPVOID*)&lpFfi, &uLen);
		DWORD dwFileVersionMS = lpFfi->dwFileVersionMS;
		DWORD dwFileVersionLS = lpFfi->dwFileVersionLS;
		delete[] lpVersionInfo;
		DWORD dwLeftMost = HIWORD(dwFileVersionMS);
		DWORD dwSecondLeft = LOWORD(dwFileVersionMS);
		DWORD dwSecondRight = HIWORD(dwFileVersionLS);
		DWORD dwRightMost = LOWORD(dwFileVersionLS);

		printf("Your Spotify version: %d.%d.%d.%d\n", dwLeftMost, dwSecondLeft, dwSecondRight, dwRightMost);

		return spotifyVer = (int)dwSecondRight;
	}
}