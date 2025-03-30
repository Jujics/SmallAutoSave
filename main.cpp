#include <cstdio>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string>
#include <locale>
#include <codecvt>
#include <ctime>
#include <conio.h>

using namespace std;

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

bool CheckTimeElapsed(time_t startTime, int minutes) {
    time_t currentTime;
    time(&currentTime);
    double seconds = difftime(currentTime, startTime);
    return (seconds >= minutes * 60);
}

void HideConsole()
{
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        ShowWindow(hwnd, SW_HIDE);
    }
}

void ShowConsole()
{
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        ShowWindow(hwnd, SW_SHOW);
    }
}

void SendCtrlS() {
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event('S', 0, 0, 0);
    keybd_event('S', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

    cout << "Sent Ctrl+S at " << __TIME__ << endl;
}

int main() {
    ShowConsole();
    std::string process;
    std::cout << "Enter process name: ";
    std::cin >> process;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideProcess = converter.from_bytes(process);

    if (IsProcessRunning(wideProcess.c_str())) {
        printf("Process is running!\n");
        int intervalMinutes;
        cout << "Every how many minutes do you want to save: ";
        cin >> intervalMinutes;
        HideConsole();
        const int intervalMillis = intervalMinutes * 60 * 1000;

        while (true) {
            SendCtrlS();

            DWORD startTime = GetTickCount();
            while (true) {
                Sleep(1000);

                if (!IsProcessRunning(wideProcess.c_str())) {
                    ShowConsole();
                    cout << "Process has been closed. Exiting..." << endl;
                    return 0;
                }

                if (GetTickCount() - startTime >= intervalMillis) {
                    break;
                }
            }
        }
    } else {
        printf("Process is not running.\n");
    }

    return 0;
}