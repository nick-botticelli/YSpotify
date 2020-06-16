#include "pch.h"
#include "Hooks.h"
#include "Utils.h"

#define BUFFSIZE 1024

namespace utils
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

		for (size_t i = 0; i < str.size(); i += 2)
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

	// Internal scanner to match bytes in the program's memory. ? = wildcard
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

	// Returns true if the pointer points to an invalid address (e.g. unaccessible)
	bool Utils::IsBadReadPtr(void* p)
	{
		MEMORY_BASIC_INFORMATION mbi = { 0 };
		if (::VirtualQuery(p, &mbi, sizeof(mbi)))
		{
			DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
			bool b = !(mbi.Protect & mask);
			// check the page is not a guard page
			if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

			return b;
		}

		return true;
	}

	MODULEINFO Utils::GetModuleInfo(char* szModule)
	{
		MODULEINFO modInfo = { 0 };
		HMODULE hModule = GetModuleHandleA(szModule);
		if (hModule != 0)
			GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
		return modInfo;
	}

	std::string Utils::getFileMD5(const std::string& fname)
	{
		char buffer[BUFFSIZE];
		unsigned char digest[MD5_DIGEST_LENGTH];

		std::stringstream ss;
		std::string md5string;

		std::ifstream ifs(fname, std::ifstream::binary);

		MD5_CTX md5Context;

		MD5_Init(&md5Context);

		while (ifs.good())
		{
			ifs.read(buffer, BUFFSIZE);
			MD5_Update(&md5Context, buffer, ifs.gcount());
		}

		ifs.close();

		int res = MD5_Final(digest, &md5Context);

		if (res == 0) // hash failed
			return {};   // or raise an exception

		// set up stringstream format
		ss << std::hex << std::uppercase << std::setfill('0');

		for (unsigned char uc : digest)
			ss << std::setw(2) << (int)uc;

		md5string = ss.str();

		return md5string;
	}
}