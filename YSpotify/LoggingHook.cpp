#include "pch.h"
#include "LoggingHook.h"
#include "Utils.h"
#include "HookUtil.h"
#include "SpotifyUtil.h"

namespace Hooks
{
	// 1.1.25, 1.1.26-19, 1.1.26-21
	typedef int(__cdecl* loggerFunc_v25)(int intOne, int intTwo, DWORD multiByteStrOffset, char* originStr, int intThree, char* logMsgStr);
	loggerFunc_v25 loggerFunc_v25_hook = nullptr;

	// 1.1.27-7, 1.1.27-13, 1.1.30, 1.1.34
	// Not the same function as loggerFunc; sometimes gives a bad pointer for logMsgStr
	typedef char(__thiscall* loggerFunc2_v27)(void* This, int intOne, int intTwo, DWORD multiByteStrOffset, char* originStr, int intThree, char** logMsgStr);
	loggerFunc2_v27 loggerFunc_v27_hook = nullptr;

	// 1.1.34
	typedef int(__cdecl* newLoggerFunc_v27)(int* a1, char** logMsgStr);
	newLoggerFunc_v27 newLoggerFunc_v27_hook = nullptr;

	int __cdecl log_hook_v25(int intOne, int intTwo, DWORD multiByteStrOffset, char* originStr, int intThree, char* logMsgStr)
	{
		// std::cout << originStr << std::endl; // Origin class
		std::cout << logMsgStr << std::endl; // Log message

		return loggerFunc_v25_hook(intOne, intTwo, multiByteStrOffset, originStr, intThree, logMsgStr);
	}

	char __fastcall log_hook_v27(void* This, void* _EDX, int intOne, int intTwo, DWORD multiByteStrOffset, char* originStr, int intThree, char** logMsgStr)
	{
		if (!utils::Utils::IsBadReadPtr(*logMsgStr))
			std::cout << *logMsgStr << std::endl; // Log message
		else
			std::cout << originStr << std::endl; // Bad pointer... log origin class instead

		return loggerFunc_v27_hook(This, intOne, intTwo, multiByteStrOffset, originStr, intThree, logMsgStr);
	}

	int __cdecl new_log_hook_v27(int* a1, char** logMsgStr)
	{
		if (!utils::Utils::IsBadReadPtr(logMsgStr) && !utils::Utils::IsBadReadPtr(*logMsgStr))
			std::cout << *logMsgStr << std::endl; // Log message

		return newLoggerFunc_v27_hook(a1, logMsgStr);
	}

	void LoggingHook::CreateHook()
	{
		std::cout << "Creating LoggingHook..." << std::endl;

		switch (utils::SpotifyUtil::getSpotifyVersion())
		{
		case utils::SpotifyUtil::SpotifyVersion::v1_1_25:
			loggerFunc_v25_hook = (loggerFunc_v25)utils::HookUtil::TrampHook32((char*)0x0108BC70, (char*)&log_hook_v25, 5);
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_26_19:
			loggerFunc_v25_hook = (loggerFunc_v25)utils::HookUtil::TrampHook32((char*)0x010A0410, (char*)&log_hook_v25, 5);
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_26_21:
			loggerFunc_v25_hook = (loggerFunc_v25)utils::HookUtil::TrampHook32((char*)0x010A0210, (char*)&log_hook_v25, 5);
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_27_7:
			loggerFunc_v27_hook = (loggerFunc2_v27)utils::HookUtil::TrampHook32((char*)0x01088E90, (char*)&log_hook_v27, 5);
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_27_13:
			loggerFunc_v27_hook = (loggerFunc2_v27)utils::HookUtil::TrampHook32((char*) /*0x01088E20*/ 0x0108A7B0, (char*)&log_hook_v27, 5);
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_28:
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_29:
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_30:
			loggerFunc_v27_hook = (loggerFunc2_v27)utils::HookUtil::TrampHook32((char*)0x010B0CF0, (char*)&log_hook_v27, 5);
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_34:
			//loggerFunc_v27_hook = (loggerFunc2_v27)utils::HookUtil::TrampHook32((char*)0x010BAD90, (char*)&log_hook_v27, 5);
			newLoggerFunc_v27_hook = (newLoggerFunc_v27)utils::HookUtil::TrampHook32((char*)0x010B9110, (char*)&new_log_hook_v27, 5);
			break;
		}

		std::cout << "Created LoggingHook." << std::endl;
	}
}
