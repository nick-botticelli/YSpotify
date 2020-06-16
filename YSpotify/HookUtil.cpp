#include "pch.h"
#include "HookUtil.h"

namespace utils
{
	// Source: https://guidedhacking.com/threads/simple-x86-c-trampoline-hook.14188/
	bool HookUtil::Detour32(char* src, char* dst, const intptr_t len)
	{
		if (len < 5) return false;

		DWORD  curProtection;
		VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

		intptr_t  relativeAddress = (intptr_t)(dst - (intptr_t)src) - 5;

		*src = (char)'\xE9';
		*(intptr_t*)((intptr_t)src + 1) = relativeAddress;

		VirtualProtect(src, len, curProtection, &curProtection);
		return true;
	}

	// Source: https://guidedhacking.com/threads/simple-x86-c-trampoline-hook.14188/
	char* HookUtil::TrampHook32(char* src, char* dst, const intptr_t len)
	{
		// Make sure the length is greater than 5
		if (len < 5) return 0;

		// Create the gateway (len + 5 for the overwritten bytes + the jmp)
		void* gateway = VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

		//Write the stolen bytes into the gateway
		memcpy(gateway, src, len);

		// Get the gateway to destination addy
		intptr_t  gatewayRelativeAddr = ((intptr_t)src - (intptr_t)gateway) - 5;

		// Add the jmp opcode to the end of the gateway
		*(char*)((intptr_t)gateway + len) = 0xE9;

		// Add the address to the jmp
		*(intptr_t*)((intptr_t)gateway + len + 1) = gatewayRelativeAddr;

		// Perform the detour
		Detour32(src, dst, len);

		return (char*)gateway;
	}
}