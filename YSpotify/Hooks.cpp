#include "pch.h"
#include "Hooks.h"

namespace Hooks
{
	void HookHandler::InitHooks()
	{
		Hooks::UpdateHook::CreateHook();
		Hooks::KeyHook::CreateHook();

		// Do LoggingHook last
		Hooks::LoggingHook::CreateHook();
		std::cout << std::endl;
	}
}