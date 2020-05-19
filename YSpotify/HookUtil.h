#pragma once
#include "pch.h"

namespace utils
{
	class HookUtil
	{
	public:
		static char* TrampHook32(char* src, char* dst, const intptr_t len);
		static bool Detour32(char* src, char* dst, const intptr_t len);
	};
}