#include "pch.h"
#include "HookUtil.h"
#include "Hooks.h"
#include "HookAddresses.h"

static const char* VERSION = "0.1";

DWORD WINAPI Init(LPVOID lpParam)
{
	// Create console and redirect all output (e.g. std::cout) there
	AllocConsole();
	FILE *fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);

	std::cout << "=== YSpotify v" << VERSION << " ===" << std::endl;

	int spotifyVer = Hooks::HookAddresses::getSpotifyVersion();
	if (spotifyVer < Hooks::HookAddresses::SUPPORT_OLDEST)
		std::cout << "Warning: Your spotify version appears to be too old! Please use 1.1." << Hooks::HookAddresses::SUPPORT_OLDEST << " or higher." << std::endl;
	else if (spotifyVer > Hooks::HookAddresses::SUPPORT_NEWEST)
		std::cout << "Warning: Your Spotify version appears to be too new! Please use 1.1." << Hooks::HookAddresses::SUPPORT_NEWEST << " or older" << std::endl;
	std::cout << std::endl;

	Hooks::HookHandler::InitHooks();

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwAttached, LPVOID lpvReserved)
{
	if (dwAttached == DLL_PROCESS_ATTACH)
		CreateThread(NULL, 0, &Init, NULL, 0, NULL);

	return 1;
}

