cmake_minimum_required(VERSION 3.18)

include(pico_sdk_import.cmake)
project(mistable_phase1 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if(PICO_BOARD STREQUAL "")
  set(PICO_BOARD waveshare_rp2350_pizero)
endif()

set(PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR}/cmake/boards)

pico_sdk_init()

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

pico_generate_pio_header(mistable_phase1 ${CMAKE_CURRENT_LIST_DIR}/src/video/tmds.pio)
pico_generate_pio_header(mistable_phase1 ${CMAKE_CURRENT_LIST_DIR}/src/usb/piousb_host.pio)

target_include_directories(mistable_phase1 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/video
  ${CMAKE_CURRENT_LIST_DIR}/src/usb
  ${CMAKE_CURRENT_LIST_DIR}/src/storage
)

target_compile_definitions(mistable_phase1 PRIVATE
  PIO_USB_DP_PIN=PIN_PIO_USB_DP
  PIO_USB_DM_PIN=PIN_PIO_USB_DM
)

target_link_libraries(mistable_phase1
  pico_stdlib
  pico_multicore
  hardware_pio
  hardware_dma
  hardware_irq
  hardware_spi
  tinyusb_device
  tinyusb_board
)

pico_enable_stdio_usb(mistable_phase1 1)
pico_enable_stdio_uart(mistable_phase1 0)

pico_add_extra_outputs(mistable_phase1)
