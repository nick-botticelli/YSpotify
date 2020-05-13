#include "pch.h"
#include "LoggingHook.h"
#include "HookUtil.h"
#include "HookAddresses.h"

namespace Hooks
{
	// 1.1.25
	typedef int (__cdecl* tSub_108BB10)(void* arg0, int num1, int strOffset, unsigned __int8 char1);
	tSub_108BB10 oSub_108BB10 = nullptr;

	// 1.1.30
	typedef int(__cdecl* tSub_10B3C60)(DWORD arg_0, DWORD arg_4, DWORD arg_8);
	tSub_10B3C60 oSub_10B3C60 = nullptr;

	// 1.1.25
	typedef int(__cdecl* tSub_108BC70)(int intOne, int intTwo, DWORD multiByteStrOffset, char* staticStr, int intThree, char* string);
	tSub_108BC70 oSub_108BC70 = nullptr;

	// Return eax register, which contains a pointer to a pointer to the string for the log
	int getFormattedStrPtr_v25()
	{
		__asm mov eax, eax
	}

	// Return eax register, which contains a pointer to a pointer to the string for the log from [ebx+8]
	int getFormattedStrPtr_v30()
	{
		//__asm mov eax, [ebp+18h] // Originally +08h, but with detour, +18h

		__asm mov eax, eax
	}

	int LoggingHook::log_hook_v25(void* arg0, int num1, int strOffset, unsigned __int8 char1) // 1.1.25
	{
		int out = getFormattedStrPtr_v25();
		int checkVal = *(int*)out;

		// TODO: Automatically parse ptr addrs to check if they are readable memory
		// Inaccessible regions: 0x20202020, 0x63617274, 0x68636163
		if (checkVal != 538976288 && checkVal != 1667330676 && checkVal != 1751343459)
			std::cout << ((char*)*(int*)out) << std::endl;

		return oSub_108BB10(arg0, num1, strOffset, char1);
	}

	int LoggingHook::log_hook_v30(DWORD arg_0, DWORD arg_4, DWORD arg_8) // 1.1.30
	{
		int out = getFormattedStrPtr_v30();
		//int checkVal = *(int*)out;

		//std::cout << out << std::endl;
		
		// Inaccessible regions: 0x20202020, 0x63617274, 0x68636163
		// Anti debug? When it receives this value, it corrupts eax, leading to std::cout crashing everything
		/*if (checkVal != 538976288 && checkVal != 1667330676 && checkVal != 1751343459)
			std::cout << ((char*)*(int*)out) << std::endl;*/

		return oSub_10B3C60(arg_0, arg_4, arg_8);
	}

	int LoggingHook::enableSkips_hook_v25(DWORD arg_0)
	{
		return 1;
	}

	int LoggingHook::log2_hook_v25(int intOne, int intTwo, DWORD multiByteStrOffset, char* staticStr, int intThree, char* string)
	{
		// std::cout << staticStr << std::endl; // Origin classes
		std::cout << string << std::endl; // Log messages

		return oSub_108BC70(intOne, intTwo, multiByteStrOffset, staticStr, intThree, string);
	}

	void LoggingHook::CreateHook()
	{
		std::cout << "Creating LoggingHook..." << std::endl;

		switch (Hooks::HookAddresses::getSpotifyVersion())
		{
		case 25:
			//oSub_108BB10 = (tSub_108BB10)Utils::HookUtil::TrampHook32((char*)0x0108BB24, (char*)&log_hook_v25, 6);
			//Utils::HookUtil::Detour32((char*)0x745db0, (char*)&enableSkips_hook_v25, 5);
			oSub_108BC70 = (tSub_108BC70)Utils::HookUtil::TrampHook32((char*)0x0108BC70, (char*)&log2_hook_v25, 5);
		case 30:
			oSub_10B3C60 = (tSub_10B3C60)Utils::HookUtil::TrampHook32((char*)/*0x010B3C71*/ 0x010B3D77, (char*)&log_hook_v30, /*6*/ 7);
		}

		std::cout << "Created LoggingHook." << std::endl;
	}
}
