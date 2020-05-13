#pragma once

namespace Hooks
{
	class LoggingHook
	{
	public:
		static int log_hook_v25(void* arg0, int num1, int strOffset, unsigned __int8 char1);
		static int log_hook_v30(DWORD arg_0, DWORD arg_4, DWORD arg_8);

		static int enableSkips_hook_v25(DWORD arg_0);
		static int log2_hook_v25(int intOne, int intTwo, DWORD multiByteStrOffset, char* staticStr, int intThree, char* string);

		static void CreateHook();
	};
}