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

    static void channelOutOfRange();

  public:
    DMX512USB(int deviceIndex);
    DMX512USB(const DMX512USB&) = delete;
    ~DMX512USB();

    void clear();
    inline void set(size_t channel, uint8_t value) {
        if (channel > 512) {
            channelOutOfRange();
        }
        m_data[channel + 1] = value;
    }
    void send();

    static int getDeviceCount();
    static std::string getDeviceNameForIndex(int index);
};
