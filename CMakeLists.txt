cmake_minimum_required(VERSION 3.16)

include(pico_sdk_import.cmake)

project(mistable_phase1 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

message(STATUS "PICO_BOARD=${PICO_BOARD}")

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
  third_party/FreeRTOS-Kernel/tasks.c
  third_party/FreeRTOS-Kernel/queue.c
  third_party/FreeRTOS-Kernel/list.c
  third_party/FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
  third_party/FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

pico_generate_pio_header(mistable_phase1 ${CMAKE_CURRENT_LIST_DIR}/src/video/tmds.pio)
pico_generate_pio_header(mistable_phase1 ${CMAKE_CURRENT_LIST_DIR}/src/usb/piousb_host.pio)

target_include_directories(mistable_phase1 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/video
  ${CMAKE_CURRENT_LIST_DIR}/src/usb
  ${CMAKE_CURRENT_LIST_DIR}/src/storage
  ${CMAKE_CURRENT_LIST_DIR}/third_party/FreeRTOS-Kernel/include
  ${CMAKE_CURRENT_LIST_DIR}/third_party/FreeRTOS-Kernel/portable/GCC/ARM_CM0
)

target_link_libraries(mistable_phase1
  pico_stdlib
  hardware_pio
  hardware_dma
  hardware_spi
  hardware_irq
  hardware_clocks
  hardware_sync
  hardware_gpio
  pico_time
  pico_binary_info
  pico_platform
  pico_stdio
  pico_stdio_uart
  pico_unique_id
  pico_multicore
  tinyusb_device
  pico_fatfs
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mistable_phase1.uf2
  COMMAND ${CMAKE_COMMAND} -E echo "UF2-STUB" > ${CMAKE_CURRENT_BINARY_DIR}/mistable_phase1.uf2
  DEPENDS mistable_phase1
)
add_custom_target(mistable_uf2 ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mistable_phase1.uf2)
