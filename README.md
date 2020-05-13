# YSpotify
Spotify hooking application inspired by XSpotify

# Installing
This project uses [vcpkg](https://github.com/microsoft/vcpkg) to manage dependencies.

1. Clone repository
2. ~~Install vcpkg if not already installed~~
3. ~~Use vcpkg to install required dependencies~~
4. Configure build output directory (this project is customized for my setup, with it pointed to %appdata%\Spotify_old)
5. Build in Visual Studio

# Using
1. Make sure YSpotifyInjector.exe (or your Dll injector of choice) and YSpotify.dll are located in the same folder as Spotify.exe
2. Start Spotify and then YSpotifyInjector (or vice versa; YSpotifyInjector will wait for Spotify.exe to launch).

# Dependencies
* None yet

# Notes
* As of now, 1.1.31 (newest) is not supported; 1.1.30 can be installed through the official installer located [here](https://download.spotify.com/SpotifyFullSetup.exe).
* I have almost no C++ coding experience, a lot of this is StackOverflow'd and copy-pasted. Feel free to create a PR.
* Research is my own (+ some of meik97's research)
* Tools used for research: IDA Pro, Cheat Engine, and Windbg
* Currently for Spotify 1.1.25 - 1.1.30 only

# Spotify Updates
Prevent Spotify from updating by performing the following commands:
>rm %localappdata%\Spotify\Update
>
>mkdir %localappdata%\Spotify\Update
>
>icacls %localappdata%\Spotify\Update /deny "%username%":D
>
>icacls %localappdata%\Spotify\Update /deny "%username%":R

# Acknowledgements
[meik97](https://github.com/meik97) - Prior work and inspiration for this project.

# License
The MIT License (MIT)