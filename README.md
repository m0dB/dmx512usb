# DMX512USB

C++ class DMX512USB for sending DMX512 data using a USB RS485 DMX 512 stage lighting equipment control cable (USB to DIN 3-pin XLR)

Instructions below are for macOS, but adapting to Windows or Linux should be straightforward.

Tested with two 36-LED PAR RGB LED spots and a cheap ($10) USB-DMX cable.

## Pre-requisites

Download the DMG of the latest version (1.4.30 at time of writing) from https://ftdichip.com/drivers/d2xx-drivers/

Mount the dmg and copy the release folder:

```shell
cp -r /Volumes/dmg/release d2xx/
```

## Build instructions

To build a simple example application:

```shell
mkdir build
cd build
cmake ..
make
```

The example application toggles the first 4 DMX channels between 0 and 255 at 40 Hz, effectively causing a strobe effect.

## References

- https://en.wikipedia.org/wiki/DMX512
- https://github.com/njazz/DMX485/
- https://forum.lazarus.freepascal.org/index.php?topic=5773.0
