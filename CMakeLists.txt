cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(pico_sdk_import.cmake)

project(mistable_phase1 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(third_party/pico-sdk/src)

add_library(freertos_kernel STATIC
  third_party/FreeRTOS-Kernel/tasks.c
  third_party/FreeRTOS-Kernel/portable/MemMang/heap_4.c
)
target_include_directories(freertos_kernel PUBLIC
  third_party/FreeRTOS-Kernel/include
  src
)

add_executable(mistable_phase1
  src/main.c
  src/log.c
  src/status.c
  src/video/video_engine.c
  src/video/tmds_pio.c
  src/video/patterns.c
  src/video/osd.c
  src/video/font8x8.c
  src/video/scale.c
  src/usb/usb_device_cdc.c
  src/usb/usb_host_piousb.c
  src/usb/hid_keyboard.c
  src/storage/sd_spi.c
  src/storage/ff_port.c
  src/storage/splash.c
)

target_include_directories(mistable_phase1 PRIVATE
  src
  src/video
  src/usb
  src/storage
  third_party/FreeRTOS-Kernel/include
  third_party/pico-sdk/include
)

target_link_libraries(mistable_phase1 PRIVATE
  pico_stdlib
  hardware_spi
  freertos_kernel
)

pico_generate_pio_header(mistable_phase1 ${CMAKE_CURRENT_LIST_DIR}/src/video/tmds.pio)
pico_generate_pio_header(mistable_phase1 ${CMAKE_CURRENT_LIST_DIR}/src/usb/piousb_host.pio)

pico_enable_stdio_usb(mistable_phase1 1)
pico_enable_stdio_uart(mistable_phase1 0)
pico_add_extra_outputs(mistable_phase1)
