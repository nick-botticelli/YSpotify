#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

static const char* VERSION = "1.0";

static const char* DLL_FILE_PATH = "YSpotify.dll";
static const wchar_t* PROC_NAME = L"Spotify.exe";

DWORD GetProcId(const wchar_t* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!wcscmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            }
            while (Process32Next(hSnap, &procEntry));
        }
    }

    CloseHandle(hSnap);
    return procId;
}

void StartDllInjection()
{
    const char* dllPath = DLL_FILE_PATH;
    const wchar_t* procName = PROC_NAME;
    DWORD procId = 0;

    while (!procId)
    {
        procId = GetProcId(procName);
        Sleep(50);
    }

    // Possibly injecting too fast into Spotify.exe resulting in an error, so delay?
    Sleep(50);

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    if (hProc && hProc != INVALID_HANDLE_VALUE)
    {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);

        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
        if (hThread)
            CloseHandle(hThread);
    }

    if (hProc)
        CloseHandle(hProc);
}

int main()
{
    std::cout << "=== YSpotifyInjector v" << VERSION << " ===" << std::endl << std::endl;

    std::wcout << "Attempting to inject \"" << DLL_FILE_PATH << "\" into \"" << std::wstring(PROC_NAME) << "\"..." << std::endl;
    StartDllInjection();
    std::cout << "Injected." << std::endl;

    return 0;
}