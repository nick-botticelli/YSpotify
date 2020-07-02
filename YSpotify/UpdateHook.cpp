#include "pch.h"
#include "LoggingHook.h"
#include "HookUtil.h"
#include "SpotifyUtil.h"
#include "UpdateHook.h"

namespace Hooks
{
	typedef int(__thiscall* updateFunc_v25)(void* This, char* newVerStr, char** updateUrlStrPtr, int a4, int a5);
	updateFunc_v25 updateFunc_v25_hook = nullptr;

	typedef bool(__cdecl* isValidUrlFunc_v25)(int* urlThingArg, int arg_4);
	isValidUrlFunc_v25 isValidUrlFunc_v25_hook = nullptr;

	int __fastcall update_hook_v25(void* This, void* _EDX, char* newVerStr, char** updateUrlStrPtr, int a4, int a5)
	{
		*updateUrlStrPtr[0] = '\x00'; // Corrupt URL

		return updateFunc_v25_hook(This, newVerStr, updateUrlStrPtr, a4, a5);
	}

	bool __cdecl isValidUrl_hook_v25(int* urlThingArg, int arg_4)
	{
		unsigned char* source = (unsigned char*)*(void**)*(urlThingArg + 1);
		std::u16string u16_str(reinterpret_cast<const char16_t*>(source));
		std::string utf8Url = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16_str);

		//std::cout << "URL: " << utf8Url << std::endl;

		if (utf8Url.find("upgrade.scdn.co") != std::string::npos)
			return false;
		else
			return isValidUrlFunc_v25_hook(urlThingArg, arg_4);
	}

	void UpdateHook::CreateHook()
	{
		switch (utils::SpotifyUtil::getSpotifyVersion())
		{
		case utils::SpotifyUtil::SpotifyVersion::v1_1_25:
			updateFunc_v25_hook = (updateFunc_v25)utils::HookUtil::TrampHook32((char*)0x0056CA30, (char*)&update_hook_v25, 5); // 00FFF9F0
			//parseUrlFunc_v25_hook = (parseUrlFunc_v25)utils::HookUtil::TrampHook32((char*)0x00FFF9F0, (char*)&parseUrl_hook_v25, 6);
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_30:
			break;
		}
	}
}