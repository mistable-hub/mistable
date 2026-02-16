cmake_minimum_required(VERSION 3.16)

include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake)

project(mistable_phase1 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/pico-sdk/src ${CMAKE_CURRENT_BINARY_DIR}/pico-sdk)

add_library(freertos_kernel STATIC
  third_party/FreeRTOS-Kernel/tasks.c
  third_party/FreeRTOS-Kernel/portable/MemMang/heap_4.c
)
target_include_directories(freertos_kernel PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/third_party/FreeRTOS-Kernel/include
  ${CMAKE_CURRENT_LIST_DIR}/src
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
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/video
  ${CMAKE_CURRENT_LIST_DIR}/src/usb
  ${CMAKE_CURRENT_LIST_DIR}/src/storage
  ${CMAKE_CURRENT_LIST_DIR}/third_party/pico-sdk/include
  ${CMAKE_CURRENT_LIST_DIR}/third_party/FreeRTOS-Kernel/include
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
