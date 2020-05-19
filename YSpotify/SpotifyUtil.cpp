#include "pch.h"
#include "SpotifyUtil.h"

namespace Utils
{
	int spotifyVer = -1; // e.g. "25" == 1.1.25.559
	std::string decryptionIV = "null";

	int SpotifyUtil::getSpotifyVersion()
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

	std::string SpotifyUtil::getDecryptionIV()
	{
		if (decryptionIV.compare("null") != 0)
			return decryptionIV;

		unsigned int ivKeyAddr = 0xC8F325;
		switch (Utils::SpotifyUtil::getSpotifyVersion())
		{
		case 25:
			ivKeyAddr = 0xC8F325;
			break;
		case 30:
			ivKeyAddr = 0xCA9170;
			break;
		}

		unsigned char ivBuffer[16] = { 0 };
		char ivStr[33] = { 0 };

		// Copy the IV from the text segment of Spotify (4x 4 byte segments split by 3x 3 bytes of opcodes)
		int correctedIndex = 0;
		for (int i = 0; i < 25; i++)
		{
			if ((i < 4 || i > 6) && (i < 11 || i > 13) && (i < 18 || i > 20)) // Skip opcodes
				ivBuffer[correctedIndex] = *(char*)((DWORD)ivKeyAddr + i);
			else
				correctedIndex--;

			correctedIndex++;
		}

		for (int i = 0; i < 16; i++)
			sprintf(ivStr + i * 2, "%02X", ivBuffer[i]);

		return decryptionIV = std::string(ivStr);
	}
}