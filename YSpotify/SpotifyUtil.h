#pragma once

namespace Utils
{
	class SpotifyUtil
	{
	public:
		static const int SUPPORT_OLDEST = 25;
		static const int SUPPORT_NEWEST = 30;

		static int getSpotifyVersion();
		static std::string getDecryptionIV();
	};
}

