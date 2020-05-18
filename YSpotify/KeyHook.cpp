#include "pch.h"
#include "HookUtil.h"
#include "KeyHook.h"
#include "Utils.h"
#include "SpotifyUtil.h"

namespace Hooks
{
	void KeyHook::CreateHook()
	{
		std::cout << "Decryption IV: " << Utils::SpotifyUtil::getDecryptionIV() << std::endl;
	}
}