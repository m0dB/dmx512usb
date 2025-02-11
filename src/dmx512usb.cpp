#include "dmx512usb.h"

#include <stdexcept>
#include <string>

namespace {
void checkStatus(FT_STATUS ftStatus, const char* str) {
    if (ftStatus != FT_OK) {
        throw std::runtime_error(std::string("DMX512USB: ") + std::string(str) + std::string(" failed with status: ") + std::to_string(static_cast<int>(ftStatus)));
    }
}
} // namespace

DMX512USB::DMX512USB(int deviceIndex) {
    FT_STATUS ftStatus = FT_Open(deviceIndex, &m_ftHandle);
    checkStatus(ftStatus, "Open");
    ftStatus = FT_SetBitMode(m_ftHandle, 0x00, 0);
    checkStatus(ftStatus, "Set bit bang mode");
    ftStatus = FT_ResetDevice(m_ftHandle);
    checkStatus(ftStatus, "Reset device");
    ftStatus = FT_Purge(m_ftHandle, FT_PURGE_RX | FT_PURGE_TX);
    checkStatus(ftStatus, "Purge RX TX");
    ftStatus = FT_SetBaudRate(m_ftHandle, 250000);
    checkStatus(ftStatus, "Set baud-rate");
    ftStatus = FT_SetTimeouts(m_ftHandle, 50, 50);
    checkStatus(ftStatus, "Set time-outs");
    ftStatus = FT_SetDataCharacteristics(m_ftHandle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_NONE); // 8N1
    checkStatus(ftStatus, "Set data-characteristics");
    ftStatus = FT_SetFlowControl(m_ftHandle, FT_FLOW_NONE, 0, 0);
    checkStatus(ftStatus, "Set flow-control");
    ftStatus = FT_ClrRts(m_ftHandle);
    checkStatus(ftStatus, "ClrRts");
    ftStatus = FT_SetLatencyTimer(m_ftHandle, 2);
    checkStatus(ftStatus, "Set latency-timer");

    FT_W32_EscapeCommFunction(m_ftHandle, CLRRTS);

    FT_GetDeviceInfo(m_ftHandle, &m_ftDevice, m_ftDeviceID, m_ftSerialNumber, m_ftDeviceDescription, NULL);
}

DMX512USB::~DMX512USB() {
    if (m_ftHandle) {
        FT_Close(m_ftHandle);
    }
}

/* static */
void DMX512USB::channelOutOfRange() {
    throw std::runtime_error("DMX512USB: Channel out of range");
}

void DMX512USB::clear() {
    std::fill(m_data.begin(), m_data.end(), 0);
}

void DMX512USB::send() {
    if (m_ftHandle == NULL) {
        return;
    }
    FT_STATUS ftStatus;
    // start byte (0) following by 512 DMX bytes
    DWORD remaining = 513;
    DWORD offset = 0;

    ftStatus = FT_SetBreakOn(m_ftHandle);
    checkStatus(ftStatus, "Set break on");
    FT_SetBreakOff(m_ftHandle);
    checkStatus(ftStatus, "Set break off");
    while (remaining) {
        DWORD n;
        ftStatus = FT_Write(m_ftHandle, m_data.data() + offset, remaining, &n);
        checkStatus(ftStatus, "Write");
        remaining -= n;
        offset += n;
    }
    ftStatus = FT_Purge(m_ftHandle, FT_PURGE_RX | FT_PURGE_TX);
    checkStatus(ftStatus, "Purge");
}

int DMX512USB::getDeviceCount() {
    DWORD cnt = 0;
    FT_STATUS ftStatus = FT_ListDevices(&cnt, NULL, FT_LIST_NUMBER_ONLY);
    checkStatus(ftStatus, "List devices");
    return static_cast<int>(cnt);
}

std::string DMX512USB::getDeviceNameForIndex(int index) {
    PVOID pvoid{reinterpret_cast<PVOID>(index)};
    char buffer[256];
    FT_ListDevices(pvoid, buffer, FT_LIST_BY_INDEX);
    return std::string{buffer};
}
