#include <cctype>
#include <chrono>
#include <iostream>
#include <thread>

#include "dmx512usb.h"

int main(int argc, char** argv) {
    int n = DMX512USB::getDeviceCount();

    if (argc != 2 || !std::isdigit(argv[1][0])) {
        std::cout << std::endl
                  << "Usage: " << argv[0] << " <deviceindex>" << std::endl
                  << std::endl;
        std::cout << "Found " << n << " devices" << std::endl
                  << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << i << ": " << DMX512USB::getDeviceNameForIndex(i) << std::endl;
        }
        return 0;
    }

    if (argc > 1) {
        int deviceIndex = std::atoi(argv[1]);
        std::cout << "using device index " << deviceIndex << std::endl;
        DMX512USB dmx(deviceIndex);
        std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
        for (int i = 0; i < 1000; i++) {
            dmx.clear();
            dmx.set(0, 255);
            dmx.set(1, (i & 1) ? 255 : 0);
            dmx.set(2, (i & 1) ? 255 : 0);
            dmx.set(3, (i & 1) ? 255 : 0);
            dmx.send();
            t += std::chrono::milliseconds(25);
            std::this_thread::sleep_until(t);
        }
    }

    return 0;
}
