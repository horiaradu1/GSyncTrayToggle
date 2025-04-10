//#include <iostream>
//#include <nvapi.h>
//
//#ifndef NVAPI_MAX_DISPLAYIDS_T
//#define NVAPI_MAX_DISPLAYIDS_T 16
//#endif
//
//void GetVrrInfo(NvU32 displayId) {
//    NV_GET_VRR_INFO vrrInfo = {};
//    vrrInfo.version = NV_GET_VRR_INFO_VER;
//
//    NvAPI_Status status = NvAPI_Disp_GetVRRInfo(displayId, &vrrInfo);
//    if (status == NVAPI_OK) {
//        std::cout << "VRR Info for Display ID: " << displayId << "\n";
//        std::cout << "Is VRR Enabled: " << (vrrInfo.bIsVRREnabled ? "Yes" : "No") << "\n";
//        std::cout << "Is VRR Possible: " << (vrrInfo.bIsVRRPossible ? "Yes" : "No") << "\n";
//        std::cout << "Is VRR Requested: " << (vrrInfo.bIsVRRRequested ? "Yes" : "No") << "\n";
//        std::cout << "Is VRR Indicator Enabled: " << (vrrInfo.bIsVRRIndicatorEnabled ? "Yes" : "No") << "\n";
//        std::cout << "Is Display in VRR Mode: " << (vrrInfo.bIsDisplayInVRRMode ? "Yes" : "No") << "\n";
//    }
//    else {
//        std::cerr << "Failed to get VRR info for display ID " << displayId << ", error: " << status << std::endl;
//    }
//}
//
//void GetVirtualRefreshRateData(NvU32 displayId) {
//    NV_GET_VIRTUAL_REFRESH_RATE_DATA virtualRefreshRateData = {};
//    virtualRefreshRateData.version = NV_GET_VIRTUAL_REFRESH_RATE_DATA_VER;
//
//    NvAPI_Status status = NvAPI_DISP_GetVirtualRefreshRateData(displayId, &virtualRefreshRateData);
//    if (status == NVAPI_OK) {
//        std::cout << "Virtual Refresh Rate Info for Display ID: " << displayId << "\n";
//        std::cout << "Version: " << virtualRefreshRateData.version << "\n";
//        std::cout << "Frame Interval (in microseconds): " << virtualRefreshRateData.frameIntervalUs << "\n";
//        std::cout << "rrx1k: " << virtualRefreshRateData.rrx1k << "\n";
//        std::cout << "isGamingVrr: " << virtualRefreshRateData.bIsGamingVrr << "\n";
//        std::cout << "reservedEx: " << virtualRefreshRateData.reservedEx << "\n";
//    }
//    else {
//        std::cerr << "Failed to get virtual refresh rate data for display ID " << displayId << ", error: " << status << std::endl;
//    }
//}
//
//
//void GetAdaptiveSyncData(NvU32 displayId) {
//    NV_GET_ADAPTIVE_SYNC_DATA_V1 adaptiveSyncData = {};
//    adaptiveSyncData.version = NV_GET_ADAPTIVE_SYNC_DATA_VER;
//
//    NvAPI_Status status = NvAPI_DISP_GetAdaptiveSyncData(displayId, &adaptiveSyncData);
//    if (status != NVAPI_OK) {
//        std::cerr << "Failed to get adaptive sync data for display ID " << displayId << ", error: " << status << std::endl;
//        return;
//    }
//
//    std::cout << "Adaptive Sync Data for Display ID " << displayId << ":\n";
//    std::cout << "Max Frame Interval: " << adaptiveSyncData.maxFrameInterval << " microseconds\n";
//    std::cout << "Adaptive Sync Disabled: " << (adaptiveSyncData.bDisableAdaptiveSync ? "Yes" : "No") << "\n";
//    std::cout << "Frame Splitting Disabled: " << (adaptiveSyncData.bDisableFrameSplitting ? "Yes" : "No") << "\n";
//    std::cout << "Last Flip Refresh Count: " << adaptiveSyncData.lastFlipRefreshCount << "\n";
//    std::cout << "Last Flip Timestamp: " << adaptiveSyncData.lastFlipTimeStamp << "\n";
//}
//
//void PrintDisplayIdInfo(const NV_GPU_DISPLAYIDS& displayId) {
//    std::cout << "Display ID: " << displayId.displayId << std::endl;
//    std::cout << "Version: " << displayId.version << std::endl;
//    std::cout << "Connector Type: " << displayId.connectorType << std::endl;
//
//    std::cout << "Is Dynamic: " << displayId.isDynamic << std::endl;
//    std::cout << "Is MultiStream Root Node: " << displayId.isMultiStreamRootNode << std::endl;
//    std::cout << "Is Active: " << displayId.isActive << std::endl;
//    std::cout << "Is Cluster: " << displayId.isCluster << std::endl;
//    std::cout << "Is OS Visible: " << displayId.isOSVisible << std::endl;
//    std::cout << "Is WFD (Deprecated): " << displayId.isWFD << std::endl;
//    std::cout << "Is Connected: " << displayId.isConnected << std::endl;
//    std::cout << "Is Physically Connected: " << displayId.isPhysicallyConnected << std::endl;
//}
//
//void PrintMonitorCapabilities(NvU32 displayId) {
//    NV_MONITOR_CAPABILITIES monitorCaps = {};
//    monitorCaps.version = NV_MONITOR_CAPABILITIES_VER;
//    NvAPI_Status status = NvAPI_DISP_GetMonitorCapabilities(displayId, &monitorCaps);
//
//    if (status == NVAPI_OK) {
//        std::cout << "Monitor Capabilities for Display ID: " << displayId << std::endl;
//        std::cout << "Supports VRR: " << (monitorCaps.data.caps.supportVRR ? "Yes" : "No") << std::endl;
//        std::cout << "Supports ULMB: " << (monitorCaps.data.caps.supportULMB ? "Yes" : "No") << std::endl;
//        std::cout << "True G-SYNC: " << (monitorCaps.data.caps.isTrueGsync ? "Yes" : "No") << std::endl;
//        std::cout << "Supports RLA: " << (monitorCaps.data.caps.isRLACapable ? "Yes" : "No") << std::endl;
//        std::cout << "Currently Capable of VRR: " << (monitorCaps.data.caps.currentlyCapableOfVRR ? "Yes" : "No") << std::endl;
//    }
//    else {
//        std::cerr << "Failed to get monitor capabilities for display ID: " << displayId << std::endl;
//    }
//}
//
//void GetGSyncStatus(NvGSyncDeviceHandle hNvGSyncDevice, NvPhysicalGpuHandle hPhysicalGpu) {
//    NV_GSYNC_STATUS gsyncStatus = {};
//    gsyncStatus.version = NV_GSYNC_STATUS_VER;
//
//    NvAPI_Status status = NvAPI_GSync_GetSyncStatus(hNvGSyncDevice, hPhysicalGpu, &gsyncStatus);
//    if (status == NVAPI_OK) {
//        std::cout << "G-SYNC Status: " << (gsyncStatus.bIsSyncSignalAvailable ? "Enabled" : "Disabled") << std::endl;
//    }
//    else {
//        char errorMsg[64];
//        NvAPI_GetErrorMessage(status, errorMsg);
//        std::cerr << "Failed to get G-SYNC status: " << errorMsg << std::endl;
//    }
//}
//
//void PrintDisplayConfig() {
//    NvU32 pathInfoCount = 0;
//
//    NvAPI_Status status = NvAPI_DISP_GetDisplayConfig(&pathInfoCount, nullptr);
//    if (status != NVAPI_OK) {
//        std::cerr << "Failed to get display config path info count: " << status << std::endl;
//        return;
//    }
//
//    if (pathInfoCount == 0) {
//        std::cerr << "No display configurations found!" << std::endl;
//        return;
//    }
//
//    NV_DISPLAYCONFIG_PATH_INFO_V2* pathInfo = new NV_DISPLAYCONFIG_PATH_INFO_V2[pathInfoCount];
//    for (NvU32 i = 0; i < pathInfoCount; ++i) {
//        pathInfo[i].version = NV_DISPLAYCONFIG_PATH_INFO_VER2;
//    }
//
//    // Second pass: get path information
//    status = NvAPI_DISP_GetDisplayConfig(&pathInfoCount, pathInfo);
//    if (status != NVAPI_OK) {
//        std::cerr << "Failed to get display config path info: " << status << std::endl;
//        delete[] pathInfo;
//        return;
//    }
//
//    std::cout << "Display Configuration Info:\n";
//    for (NvU32 i = 0; i < pathInfoCount; ++i) {
//        std::cout << "Path " << i << " Info:\n";
//        std::cout << "   Source ID: " << pathInfo[i].sourceId << std::endl;
//        std::cout << "   Target Info Count: " << pathInfo[i].targetInfoCount << std::endl;
//
//        if (pathInfo[i].targetInfo != nullptr) {
//            for (NvU32 j = 0; j < pathInfo[i].targetInfoCount; ++j) {
//                std::cout << "   Target " << j << " Info:\n";
//                std::cout << "      Target Display ID: " << pathInfo[i].targetInfo[j].displayId << std::endl;
//                std::cout << "      Target Display Type: " << pathInfo[i].targetInfo[j].details << std::endl;
//            }
//        }
//
//        if (pathInfo[i].sourceModeInfo != nullptr) {
//            std::cout << "   Source Mode Info:\n";
//            std::cout << "      Resolution Width: " << pathInfo[i].sourceModeInfo->resolution.width << std::endl;
//            std::cout << "      Resolution Height: " << pathInfo[i].sourceModeInfo->resolution.height << std::endl;
//        }
//
//        std::cout << "   Is Non-NVIDIA Adapter: " << (pathInfo[i].IsNonNVIDIAAdapter ? "Yes" : "No") << std::endl;
//        std::cout << "   OS Adapter ID: " << pathInfo[i].pOSAdapterID << std::endl;
//    }
//
//    delete[] pathInfo;
//}
//
//void EnumerateNvidiaDisplayHandles() {
//    NvU32 displayIndex = 0;
//    NvDisplayHandle nvDisplayHandle;
//    NvAPI_Status status;
//
//    while (true) {
//        status = NvAPI_EnumNvidiaDisplayHandle(displayIndex, &nvDisplayHandle);
//        if (status == NVAPI_OK) {
//            std::cout << "Found NVIDIA display handle for display index " << displayIndex << ": " << nvDisplayHandle << std::endl;
//        }
//        else if (status == NVAPI_END_ENUMERATION) {
//            std::cout << "No more displays to enumerate.\n";
//            break;
//        }
//        else {
//            std::cerr << "Error occurred while enumerating display handle at index " << displayIndex << ": " << status << std::endl;
//            break;
//        }
//        ++displayIndex;
//    }
//}
//
//int main() {
//    NvAPI_Status status = NvAPI_Initialize();
//    if (status != NVAPI_OK) {
//        char errorMsg[64];
//        NvAPI_GetErrorMessage(status, errorMsg);
//        std::cerr << "NVAPI initialization failed: " << errorMsg << std::endl;
//        return -1;
//    }
//    std::cout << "NVAPI initialized successfully\n";
//
//    NvPhysicalGpuHandle gpuHandles[NVAPI_MAX_PHYSICAL_GPUS] = { nullptr };
//    NvU32 gpuCount = 0;
//    status = NvAPI_EnumPhysicalGPUs(gpuHandles, &gpuCount);
//    if (status != NVAPI_OK || gpuCount == 0) {
//        std::cerr << "Failed to enumerate GPUs.\n";
//        return -1;
//    }
//
//    std::cout << "Detected " << gpuCount << " NVIDIA GPU(s):\n";
//
//    for (NvU32 i = 0; i < gpuCount; ++i) {
//        NvAPI_ShortString gpuName;
//        NvAPI_GPU_GetFullName(gpuHandles[i], gpuName);
//        std::cout << " - GPU " << i << ": " << gpuName << "\n";
//    }
//
//    NV_GPU_DISPLAYIDS displayIds[NVAPI_MAX_DISPLAYIDS_T] = {};
//    NvU32 displayCount = NVAPI_MAX_DISPLAYIDS_T;
//
//    for (int i = 0; i < NVAPI_MAX_DISPLAYIDS_T; ++i) {
//        displayIds[i].version = NV_GPU_DISPLAYIDS_VER;
//    }
//
//    status = NvAPI_GPU_GetConnectedDisplayIds(gpuHandles[0], displayIds, &displayCount, 0);
//    if (status != NVAPI_OK) {
//        char errorMsg[64];
//        NvAPI_GetErrorMessage(status, errorMsg);
//        std::cerr << "Failed to get connected display IDs. Status code: 0x"
//            << std::hex << status << " - " << errorMsg << std::endl;
//        return -1;
//    }
//
//    std::cout << "Connected display IDs:\n";
//    for (NvU32 i = 0; i < displayCount; ++i) {
//        std::cout << "###################DispalyIdInfo###########################" << std::endl;
//        PrintDisplayIdInfo(displayIds[i]);
//        std::cout << "###################MonitorCapabilities#####################" << std::endl;
//        PrintMonitorCapabilities(displayIds[i].displayId);
//        std::cout << "###################AdaptiveSyncData########################" << std::endl;
//        GetAdaptiveSyncData(displayIds[i].displayId);
//        std::cout << "###################VRR Info###########################" << std::endl;
//        GetVrrInfo(displayIds[i].displayId);
//        std::cout << "###################Virtual Refresh Rate Data#####################" << std::endl;
//        GetVirtualRefreshRateData(displayIds[i].displayId);
//        std::cout << "###########################################################" << std::endl;
//    }
//
//    PrintDisplayConfig();
//
//    EnumerateNvidiaDisplayHandles();
//
//    NvGSyncDeviceHandle gsyncHandles[NVAPI_MAX_GSYNC_DEVICES] = { nullptr };
//    NvU32 gsyncCount = 0;
//    status = NvAPI_GSync_EnumSyncDevices(gsyncHandles, &gsyncCount);
//    std::cout << "G-SYNC devices handles: " << gsyncHandles << std::endl;
//    std::cout << "G-SYNC devices count: " << gsyncCount << std::endl;
//    std::cout << "G-SYNC devices status: " << status << std::endl;
//    if (status != NVAPI_OK || gsyncCount == 0) {
//        std::cerr << "No G-SYNC devices found.\n";
//        return -1;
//    }
//
//    std::cout << "Detected " << gsyncCount << " G-SYNC devices:\n";
//    for (NvU32 i = 0; i < gsyncCount; ++i) {
//        std::cout << " - G-SYNC Device " << i << "\n";
//
//        GetGSyncStatus(gsyncHandles[i], gpuHandles[0]);
//    }
//
//
//    NvAPI_Unload();
//
//    return 0;
//}
