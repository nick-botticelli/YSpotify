#pragma once

namespace utils
{
	class SpotifyUtil
	{
	public:
		enum class SpotifyVersion
		{
			v1_1_25,
			v1_1_26_19,
			v1_1_26_21,
			v1_1_27_7,
			v1_1_27_13,
			v1_1_28,
			v1_1_29,
			v1_1_30,
			v1_1_31,
			v1_1_32_39,
			v1_1_32_41
		};

		static const int SUPPORT_OLDEST = 25;
		static const int SUPPORT_NEWEST = 30;

		static SpotifyVersion getSpotifyVersion();
		static std::string getDecryptionIV();
	};
}

