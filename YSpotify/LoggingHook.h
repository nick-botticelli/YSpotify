#pragma once

namespace Hooks
{
	class LoggingHook
	{
	public:
		static int enableSkips_hook_v25(DWORD arg_0);
		static int __cdecl log_hook_v25(int intOne, int intTwo, DWORD multiByteStrOffset, char* originStr, int intThree, char* logMsgStr);

		//static int log_hook_v27(int intOne, int intTwo, DWORD multiByteStrOffset, char* staticStr, int intThree, char* unfmtdLogMsgStr, DWORD arg_18);
		static char __fastcall log_hook_v27(void* thisArg, void* _EBX, int intOne, int intTwo, DWORD multiByteStrOffset, char* staticStr, int intThree, char** logMsgStr);

		static void CreateHook();
	};
}