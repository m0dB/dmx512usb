cmake_minimum_required(VERSION 3.5)
project(dmx512usb)

if (NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/d2xx/release/ftd2xx.h)
  message(FATAL_ERROR "FTDI d2xx library not found. See README.md for instructions")
endif()

add_library(d2xx STATIC IMPORTED)
set_target_properties(d2xx PROPERTIES
  IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/d2xx/release/build/libftd2xx.a"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/d2xx/release"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(example src/example.cpp src/dmx512usb.cpp src/dmx512usb.h)

target_compile_options(example PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_link_libraries(example PUBLIC d2xx "-framework CoreFoundation" "-framework IOKit")
