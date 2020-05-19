#include "pch.h"
#include "Hooks.h"
#include "Utils.h"

namespace Utils
{
	void Utils::removeForbiddenChar(std::string* s)
	{
		std::string::iterator it;

		for (it = s -> begin(); it < s -> end(); ++it)
		{
			switch (*it)
			{
			    case '/':case '\\':case ':':case '?':case '"':case '<':case '>':case '|': case ';':case '+':case '@':case '=':case ',':case '#': case '*':case '~':
				    *it = '_';
			}
		}
	}

	std::string Utils::hex2string(std::string str)
	{
		std::string res;
		res.reserve(str.size() / 2);

		for (int i = 0; i < str.size(); i += 2)
		{
			std::istringstream iss(str.substr(i, 2));
			int temp;

			iss >> std::hex >> temp;
			res += static_cast<char>(temp);
		}

		return res;
	}

	std::wstring Utils::ConvertUtf8ToUtf16(const std::string& str)
	{
		std::wstring convertedString;
		int requiredSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, 0, 0);

		if (requiredSize > 0)
		{
			std::vector<wchar_t> buffer(requiredSize);

			MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &buffer[0], requiredSize);
			convertedString.assign(buffer.begin(), buffer.end() - 1);
		}

		return convertedString;
	}

	const char* Utils::ScanIn(const char* pattern, const char* mask, const char* begin, unsigned int size)
	{
		unsigned int patternLength = strlen(mask);

		for (unsigned int i = 0; i < size - patternLength; i++)
		{
			bool found = true;
			for (unsigned int j = 0; j < patternLength; j++)
			{
				if (mask[j] != '?' && pattern[j] != *(begin + i + j))
				{
					found = false;
					break;
				}
			}

			if (found)
				return (begin + i);
		}

		return nullptr;
	}
}