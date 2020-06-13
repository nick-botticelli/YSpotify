#include "pch.h"
#include "LoggingHook.h"
#include "HookUtil.h"
#include "SpotifyUtil.h"
#include "UpdateHook.h"

namespace Hooks
{
	int UpdateHook::disableUpdates_hook_v25(DWORD arg_0, DWORD arg_4)
	{
		return 0;
	}

	void UpdateHook::CreateHook()
	{
		switch (utils::SpotifyUtil::getSpotifyVersion())
		{
		case utils::SpotifyUtil::SpotifyVersion::v1_1_25:
			utils::HookUtil::Detour32((char*)0x56CE1A, (char*)&disableUpdates_hook_v25, 5); // 0x00FFF9F0 = black screen on startup
			break;
		case utils::SpotifyUtil::SpotifyVersion::v1_1_30:
			break;
		}
	}
}