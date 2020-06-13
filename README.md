# YSpotify
A WIP Spotify hooking application inspired by XSpotify

# Installing
This project uses [vcpkg](https://github.com/microsoft/vcpkg) to manage dependencies.

1. Clone repository
2. Install vcpkg if not already installed
3. Use vcpkg to install required dependencies (e.g. `vcpkg install openssl-windows:x86-windows-static`)
4. Configure build output directory (this project is customized for my setup, you may need to change it)
5. Build in Visual Studio

# Using
1. Make sure YSpotifyInjector.exe (or your DLL injector of choice) and YSpotify.dll are located in the same folder as Spotify.exe
2. Start Spotify and then YSpotifyInjector (or vice versa; YSpotifyInjector will wait for Spotify.exe to launch).

# Dependencies (VCPKG)
* openssl-windows:x86-windows-static

# Notes
* As of now, 1.1.31 (newest) is not supported; ~~1.1.30 can be installed through the official installer located [here](https://download.spotify.com/SpotifyFullSetup.exe).~~
* I have almost no C++ coding experience. Feel free to create a PR, but I want to keep this project simple for me.
* Research is my own (+ some of meik97's research)
* Tools used for research: IDA Pro, Ghidra, Cheat Engine, and Windbg
* Currently for Spotify 1.1.25, with some functionality on 1.1.26, 1.1.27, and 1.1.30
* **This program does not circumvent any of Spotify's access controls, DRM, or copyright protection**

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