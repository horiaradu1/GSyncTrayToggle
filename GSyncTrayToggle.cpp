#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <nvapi.h>
#include "resource.h"

#define WM_TRAYICON (WM_USER + 1)
#define ID_TRAYICON 1001
#define ID_TRAY_EXIT 2001
#define ID_GSYNC_OFF 2002
#define ID_GSYNC_FULLSCREEN 2003
#define ID_GSYNC_FULL_WINDOWED 2004
#define TIMER_ID_STATUS      2005
#define TIMER_INTERVAL_MS    5000

static NvU32 lastMode = 0xFFFFFFFF;
static UINT_PTR timerId = 0;

static HICON iconOff = nullptr, iconFull = nullptr, iconFullWin = nullptr;
static int   lastIconId = -1;

static bool nvapiInited = false;


HINSTANCE g_hInst;
NOTIFYICONDATA nid = {};

void LoadTrayIcons() {
    iconOff = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_ICON_OFF), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR | LR_SHARED);
    iconFull = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_ICON_FULL), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR | LR_SHARED);
    iconFullWin = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_ICON_FULLWINDOW), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR | LR_SHARED);
}

HICON PickIcon(NvU32 mode) {
    switch (mode) {
    case 1:  return iconFull;
    case 2:  return iconFullWin;
    default: return iconOff;
    }
}


void UpdateTrayIcon(NvU32 mode) {
    /*int iconId = IDI_ICON_OFF;
    if (mode == 1) iconId = IDI_ICON_FULL;
    else if (mode == 2) iconId = IDI_ICON_FULLWINDOW;

    HICON hIcon = (HICON)LoadImage(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(iconId),
        IMAGE_ICON,
        16, 16,
        LR_DEFAULTCOLOR
    );

    if (!hIcon) {
        MessageBox(NULL, L"Failed to load tray icon", L"Error", MB_OK);
        return;
    }

    nid.hIcon = hIcon;*/

    int iconId = (mode == 1) ? 1 : (mode == 2) ? 2 : 0;
    if (iconId != lastIconId) {
        nid.hIcon = PickIcon(mode);
        lastIconId = iconId;
        nid.uFlags = NIF_ICON | NIF_TIP;
    }
    else {
        nid.uFlags = NIF_TIP;
    }


    switch (mode) {
    case 0:
        wcscpy_s(nid.szTip, L"G-SYNC: Off");
        break;
    case 1:
        wcscpy_s(nid.szTip, L"G-SYNC: Fullscreen Only");
        break;
    case 2:
        wcscpy_s(nid.szTip, L"G-SYNC: Fullscreen + Windowed");
        break;
    default:
        wcscpy_s(nid.szTip, L"G-SYNC: Unknown");
        break;
    }

    Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void SetGSyncMode(NvU32 mode) {
    // mode: 0 = Off, 1 = Fullscreen only, 2 = Fullscreen + Windowed

    if (!nvapiInited) return;
    NvDRSSessionHandle hSession = nullptr;

    if (NvAPI_DRS_CreateSession(&hSession) == NVAPI_OK) {
        NvAPI_DRS_LoadSettings(hSession);
        NvDRSProfileHandle hProfile;

        if (NvAPI_DRS_GetCurrentGlobalProfile(hSession, &hProfile) == NVAPI_OK) {
            struct {
                NvU32 settingId, value;
            } settings[3];

            if (mode == 0) {
                // Off
                settings[0] = { 294973784, 0 };
                settings[1] = { 278196727, 0 };
                settings[2] = { 279476687, 4 };
            }
            else if (mode == 1) {
                // Fullscreen only
                settings[0] = { 294973784, 1 };
                settings[1] = { 278196727, 1 };
                settings[2] = { 279476687, 0 };
            }
            else if (mode == 2) {
                // Fullscreen + windowed
                settings[0] = { 294973784, 2 };
                settings[1] = { 278196727, 2 };
                settings[2] = { 279476687, 0 };
            }

            for (auto& s : settings) {
                NVDRS_SETTING set = {};
                set.version = NVDRS_SETTING_VER;
                set.settingId = s.settingId;
                set.settingType = NVDRS_DWORD_TYPE;
                set.u32CurrentValue = s.value;
                NvAPI_DRS_SetSetting(hSession, hProfile, &set);
            }

            NvAPI_DRS_SaveSettings(hSession);
        }

        NvAPI_DRS_DestroySession(hSession);
    }

    UpdateTrayIcon(mode);
}

NvU32 GetCurrentGsyncMode(NvDRSSessionHandle hSession, NvDRSProfileHandle hProfile) {
    NVDRS_SETTING current = {};
    current.version = NVDRS_SETTING_VER;

    if (NvAPI_DRS_GetSetting(hSession, hProfile, 294973784, &current) == NVAPI_OK) {
        return current.u32CurrentValue; // 0 = Off, 1 = FS only, 2 = FS+Win
    }

    return 0;
}

NvU32 GetCurrentMode() {
    if (!nvapiInited) return 0;
    NvU32 mode = 0;
    NvDRSSessionHandle hSession = nullptr;

    if (NvAPI_DRS_CreateSession(&hSession) == NVAPI_OK) {
        NvAPI_DRS_LoadSettings(hSession);
        NvDRSProfileHandle hProfile;
        if (NvAPI_DRS_GetCurrentGlobalProfile(hSession, &hProfile) == NVAPI_OK) {
            mode = GetCurrentGsyncMode(hSession, hProfile);
        }
        NvAPI_DRS_DestroySession(hSession);
    }

    return mode;
}

void ShowContextMenu(HWND hwnd, NvU32 currentState) {
    POINT pt;
    GetCursorPos(&pt);

    HMENU hMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING | (currentState == 0 ? MF_CHECKED : 0), (UINT_PTR)ID_GSYNC_OFF, L"G-SYNC Off");
    AppendMenuW(hMenu, MF_STRING | (currentState == 1 ? MF_CHECKED : 0), (UINT_PTR)ID_GSYNC_FULLSCREEN, L"G-SYNC Fullscreen Only");
    AppendMenuW(hMenu, MF_STRING | (currentState == 2 ? MF_CHECKED : 0), (UINT_PTR)ID_GSYNC_FULL_WINDOWED, L"G-SYNC Fullscreen + Windowed");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(hMenu, MF_STRING, (UINT_PTR)ID_TRAY_EXIT, L"Exit");


    SetForegroundWindow(hwnd);
    TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
    DestroyMenu(hMenu);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_TIMER:
        if (wParam == timerId) {
            NvU32 mode = GetCurrentMode();
            if (mode != lastMode) {
                lastMode = mode;
                UpdateTrayIcon(mode);
            }
            return 0;
        }
        break;

    case WM_TRAYICON:
        switch (LOWORD(lParam)) {
        case WM_LBUTTONUP:
        case WM_RBUTTONUP: {
            NvU32 mode = GetCurrentMode();
            if (mode != lastMode) {
                lastMode = mode;
                UpdateTrayIcon(mode);
            }
            NvDRSSessionHandle hSession = nullptr;
            if (NvAPI_DRS_CreateSession(&hSession) == NVAPI_OK) {
                NvAPI_DRS_LoadSettings(hSession);
                NvDRSProfileHandle hProfile;
                if (NvAPI_DRS_GetCurrentGlobalProfile(hSession, &hProfile) == NVAPI_OK) {
                    NvU32 mode = GetCurrentGsyncMode(hSession, hProfile);
                    ShowContextMenu(hwnd, mode);
                }
                NvAPI_DRS_DestroySession(hSession);
            }
            break;
        }
        }
        return 0;

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
            case ID_GSYNC_OFF:
                SetGSyncMode(0);
                break;
            case ID_GSYNC_FULLSCREEN:
                SetGSyncMode(1);
                break;
            case ID_GSYNC_FULL_WINDOWED:
                SetGSyncMode(2);
                break;
            case ID_TRAY_EXIT:
                DestroyWindow(hwnd);
                break;
        }
        return 0;
        }

    case WM_DESTROY:
        if (timerId) {
            KillTimer(hwnd, timerId);
            timerId = 0;
        }
        if (nvapiInited) {
            NvAPI_Unload();
            nvapiInited = false;
        }
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    HANDLE hMutex = CreateMutexW(NULL, TRUE, L"GSyncTrayToggleMutex");

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBoxW(NULL, L"G-SYNC Toggle is already running.", L"Already Running", MB_OK | MB_ICONINFORMATION);
        return 0;
    }

    g_hInst = hInstance;

    const wchar_t CLASS_NAME[] = L"GSyncTrayClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"GSyncTray", 0,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) return 0;

    // Setup tray icon
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = ID_TRAYICON;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    //nid.hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_ICON_OFF), IMAGE_ICON, 16, 16, 0);
    wcscpy_s(nid.szTip, L"G-SYNC Toggle");

    // Wait for taskbar to be ready
    HWND hShellTrayWnd = NULL;
    for (int i = 0; i < 10 && hShellTrayWnd == NULL; ++i) {
        hShellTrayWnd = FindWindow(L"Shell_TrayWnd", NULL);
        if (hShellTrayWnd == NULL) Sleep(500); // wait 500ms
    }

    LoadTrayIcons();
    if (!iconOff || !iconFull || !iconFullWin) {
        MessageBoxW(hwnd, L"Failed to load tray icons", L"GSyncTrayToggle", MB_OK | MB_ICONERROR);
    }
    nid.hIcon = PickIcon(lastMode);
    Shell_NotifyIcon(NIM_ADD, &nid);

    nid.uVersion = NOTIFYICON_VERSION_4;
    Shell_NotifyIcon(NIM_SETVERSION, &nid);

    if (NvAPI_Initialize() == NVAPI_OK) {
        nvapiInited = true;
    }
    else {
        MessageBoxW(hwnd, L"NvAPI_Initialize failed", L"GSyncTrayToggle", MB_OK | MB_ICONERROR);
    }

    lastMode = GetCurrentMode();
    UpdateTrayIcon(lastMode);
    SetGSyncMode(lastMode);

	// Set time to get G-SYNC status every 5 seconds, in case of update from elseware
    timerId = SetTimer(hwnd, TIMER_ID_STATUS, TIMER_INTERVAL_MS, NULL);
    if (timerId == 0) {
        DWORD err = GetLastError();
        wchar_t buf[128];
        swprintf_s(buf, L"Timer failed: %lu", err);
        MessageBoxW(hwnd, buf, L"GSyncTrayToggle", MB_OK | MB_ICONERROR);
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
