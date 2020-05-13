#pragma once

namespace Hooks
{
	class UpdateHook
	{
	public:
		static void CreateHook();

	private:
		static int disableUpdates_hook_v25(DWORD arg_0, DWORD arg_4);
	};
}