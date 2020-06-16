#pragma once
#include "pch.h"

namespace utils
{
	class Utils
	{
	public:
		static void removeForbiddenChar(std::string* s);
		static std::string hex2string(std::string str);
		static std::wstring ConvertUtf8ToUtf16(const std::string& str);
		static const char* ScanIn(const char* pattern, const char* mask, const char* begin, unsigned int size);
		static bool IsBadReadPtr(void* p);
		static MODULEINFO GetModuleInfo(char* szModule);
		static std::string getFileMD5(const std::string& fname);
	};
}