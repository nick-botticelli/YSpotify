#pragma once
#include "pch.h"

namespace Utils
{
	class Utils
	{
	public:
		static void removeForbiddenChar(std::string* s);
		static std::string hex2string(std::string str);
		static std::wstring ConvertUtf8ToUtf16(const std::string& str);
	};
}