# DMX512USB

C++ class DMX512USB for sending DMX512 data using an FTDI USB device.

## Pre-requisites (macOS)

Download the DMG of the latest version (1.4.30 at time of writing) from https://ftdichip.com/drivers/d2xx-drivers/

Mount the dmg and copy the release folder:
cp -r /Volumes/dmg/release d2xx/

(Adapting to Windows or Linux should be straightforward)

## Build instructions (macOS)

mkdir build
cd build
cmake ..
make

to build a simple example application
