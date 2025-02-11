extern "C" {
#include "ftd2xx.h"
}

#include <array>
#include <cstdint>

class DMX512USB {
    FT_HANDLE m_ftHandle{};

    std::array<uint8_t, 513> m_data{};

    FT_DEVICE m_ftDevice{};
    LPDWORD m_ftDeviceID{};
    PCHAR m_ftSerialNumber{};
    PCHAR m_ftDeviceDescription{};

    // throws exception
    static void channelOutOfRange();

  public:
    // Opens and initializes device at index deviceIndex.
    // The index has to be >= 0 and < DMX512USB::getDeviceCount()
    DMX512USB(int deviceIndex);
    // Closes the device
    ~DMX512USB();

    DMX512USB(const DMX512USB&) = delete;

    // Clear DMX512 data buffer
    void clear();

    // Set value for channel in DMX512 data buffer
    inline void set(size_t channel, uint8_t value) {
        if (channel >= 512) {
            channelOutOfRange();
        }
        m_data[channel + 1] = value;
    }

    // Send the DMX512 data buffer (write to device)
    void send();

    // Get the number of connected devices
    static int getDeviceCount();
    // Get the name of the device at given index
    static std::string getDeviceNameForIndex(int deviceIndex);
};
