#include "pch.h"
#include "Hooks.h"

namespace Hooks
{
	void HookHandler::InitHooks()
	{
		Hooks::LoggingHook::CreateHook();
		Hooks::UpdateHook::CreateHook();
	}
}