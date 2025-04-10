#include <windows.h>
#include <iostream>
#include <nvapi.h>

bool toggleGSync(NvDRSSessionHandle hSession, NvDRSProfileHandle hProfile) {
    NvAPI_Status status;
    NVDRS_SETTING current = {};
    current.version = NVDRS_SETTING_VER;

    // Value of Enable G-SYNC globally
    status = NvAPI_DRS_GetSetting(hSession, hProfile, 294973784, &current);
    if (status != NVAPI_OK) {
        std::wcerr << L"Failed to read G-SYNC global state.\n";
        return false;
    }

    bool enable = (current.u32CurrentValue == 0);

    struct {
        NvU32 settingId;
        NvU32 valueOn;
        NvU32 valueOff;
    } settingsToToggle[] = {
        {294973784, 2, 0}, // Enable G-SYNC globally
        {279476687, 0, 4}, // G-SYNC mode
        {278196727, 2, 0}, // VRR requested state
        {6600001,    1, 0}  // Preferred refresh rate
    };

    for (auto& entry : settingsToToggle) {
        NVDRS_SETTING s = {};
        s.version = NVDRS_SETTING_VER;
        s.settingId = entry.settingId;
        s.settingType = NVDRS_DWORD_TYPE;
        s.u32CurrentValue = enable ? entry.valueOn : entry.valueOff;

        status = NvAPI_DRS_SetSetting(hSession, hProfile, &s);
        if (status != NVAPI_OK) {
            std::wcerr << L"Failed to set setting ID " << entry.settingId << L"\n";
        }
    }

    NvAPI_DRS_SaveSettings(hSession);
    std::wcout << L"G-SYNC has been turned " << (enable ? L"ON" : L"OFF") << L".\n";
    return true;
}

bool checkGlobalSettings(NvDRSSessionHandle hSession, NvDRSProfileHandle hProfile) {

    const int maxSettings = 256;
    NVDRS_SETTING* settings = new NVDRS_SETTING[maxSettings];
    for (int i = 0; i < maxSettings; ++i) {
        settings[i].version = NVDRS_SETTING_VER;
    }

    NvU32 settingsCount = maxSettings;
    if (NvAPI_DRS_EnumSettings(hSession, hProfile, 0, &settingsCount, settings) == NVAPI_OK) {
        std::wcout << L"Found " << settingsCount << L" settings in Global Profile:\n";

        for (NvU32 i = 0; i < settingsCount; ++i) {
            NvAPI_UnicodeString settingName;
            if (NvAPI_DRS_GetSettingNameFromId(settings[i].settingId, &settingName) != NVAPI_OK) {
                wcscpy_s(reinterpret_cast<wchar_t*>(settingName), NVAPI_UNICODE_STRING_MAX, L"<Unknown>");
            }

            std::wcout << L"Setting ID: " << settings[i].settingId
                << L" | Type: " << settings[i].settingType
                << L" | Name: " << reinterpret_cast<wchar_t*>(&settingName[0]);

            switch (settings[i].settingType) {
            case NVDRS_DWORD_TYPE:
                std::wcout << L" | DWORD Value: " << settings[i].u32CurrentValue << L"\n";
                break;
            case NVDRS_WSTRING_TYPE:
                std::wcout << L" | WSTRING Value: " << settings[i].wszCurrentValue << L"\n";
                break;
            case NVDRS_STRING_TYPE:
                std::wcout << L" | STRING Value: [not shown]" << L"\n";
                break;
            case NVDRS_BINARY_TYPE:
                std::wcout << L" | BINARY Value\n";
                break;
            default:
                std::wcout << L" | Unknown Type\n";
                break;
            }
        }
    }
    else {
        std::wcout << L"No settings found or enumeration failed.\n";
    }

    delete[] settings;
    return true;
}

int main() {
    if (NvAPI_Initialize() != NVAPI_OK) {
        std::cerr << "NvAPI_Initialize failed.\n";
        return -1;
    }

    NvDRSSessionHandle hSession = nullptr;
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        std::cerr << "NvAPI_DRS_CreateSession failed.\n";
        NvAPI_Unload();
        return -1;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        std::cerr << "NvAPI_DRS_LoadSettings failed.\n";
        NvAPI_DRS_DestroySession(hSession);
        NvAPI_Unload();
        return -1;
    }

    NvDRSProfileHandle hProfile;

    //if (NvAPI_DRS_GetCurrentGlobalProfile(hSession, &hProfile) == NVAPI_OK) {
    //    toggleGSync(hSession, hProfile);
    //}

    if (NvAPI_DRS_GetCurrentGlobalProfile(hSession, &hProfile) == NVAPI_OK) {
        checkGlobalSettings(hSession, hProfile);
    }

    NvAPI_DRS_DestroySession(hSession);
    NvAPI_Unload();

    return 0;
}
