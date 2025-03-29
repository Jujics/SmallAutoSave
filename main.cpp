#include <cstdio>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string>
#include <locale>
#include <codecvt>

bool IsProcessRunning(const wchar_t* processName) {
    bool exists = false;
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(PROCESSENTRY32W);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32FirstW(snapshot, &entry)) {
        while (Process32NextW(snapshot, &entry)) {
            if (_wcsicmp(entry.szExeFile, processName) == 0) {
                exists = true;
                break;
            }
        }
    }

    CloseHandle(snapshot);
    return exists;
}

int main() {
    std::string process;
    std::cout << "Enter process name: ";
    std::cin >> process;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideProcess = converter.from_bytes(process);

    if (IsProcessRunning(wideProcess.c_str())) {
        printf("Is running!\n");
    } else {
        printf("Is not running.\n");
    }

    return 0;
}