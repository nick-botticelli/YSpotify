#pragma once

namespace utils
{
	class SpotifyUtil
	{
	public:
		static const int SUPPORT_OLDEST = 25;
		static const int SUPPORT_NEWEST = 30;

		static int getSpotifyVersion();
		static std::string getDecryptionIV();
		static std::string getDecryptionIV_Legacy();
	};
}

