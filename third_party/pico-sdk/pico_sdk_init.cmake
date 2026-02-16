# Minimal pico-sdk stub for build scaffolding
if (NOT DEFINED PICO_SDK_PATH)
  set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}")
endif()

set(PICO_SDK_VERSION_STRING "stub-0.1")

function(pico_sdk_init)
  if (TARGET pico_stdlib)
    return()
  endif()

  add_library(pico_stub STATIC
    "${PICO_SDK_PATH}/src/common/pico_stdlib/pico_stub.c"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_spi/spi_stub.c"
    "${PICO_SDK_PATH}/src/rp2_common/pico_fatfs/ff.c"
  )
  target_include_directories(pico_stub PRIVATE
    "${PICO_SDK_PATH}/src/common/pico_stdlib/include"
    "${PICO_SDK_PATH}/src/common/pico_base/include"
    "${PICO_SDK_PATH}/src/common/pico_time/include"
    "${PICO_SDK_PATH}/src/common/pico_binary_info/include"
    "${PICO_SDK_PATH}/src/common/hardware_timer/include"
    "${PICO_SDK_PATH}/src/common/hardware_uart/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_pio/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_dma/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_spi/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_irq/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_clocks/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_sync/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_platform/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_stdio/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_stdio_uart/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_unique_id/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_multicore/include"
    "${PICO_SDK_PATH}/src/rp2_common/tinyusb_device/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_fatfs/include"
  )

  add_library(pico_stdlib INTERFACE)
  target_link_libraries(pico_stdlib INTERFACE pico_stub)
  target_include_directories(pico_stdlib INTERFACE
    "${PICO_SDK_PATH}/src/common/pico_stdlib/include"
    "${PICO_SDK_PATH}/src/common/pico_base/include"
    "${PICO_SDK_PATH}/src/common/pico_time/include"
    "${PICO_SDK_PATH}/src/common/pico_binary_info/include"
    "${PICO_SDK_PATH}/src/common/hardware_timer/include"
    "${PICO_SDK_PATH}/src/common/hardware_uart/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_pio/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_dma/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_spi/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_irq/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_clocks/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_sync/include"
    "${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_platform/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_stdio/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_stdio_uart/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_unique_id/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_multicore/include"
    "${PICO_SDK_PATH}/src/rp2_common/tinyusb_device/include"
    "${PICO_SDK_PATH}/src/rp2_common/pico_fatfs/include"
  )

  add_library(hardware_pio INTERFACE)
  target_include_directories(hardware_pio INTERFACE "${PICO_SDK_PATH}/src/rp2_common/hardware_pio/include")
  add_library(hardware_dma INTERFACE)
  target_include_directories(hardware_dma INTERFACE "${PICO_SDK_PATH}/src/rp2_common/hardware_dma/include")
  add_library(hardware_spi INTERFACE)
  target_include_directories(hardware_spi INTERFACE "${PICO_SDK_PATH}/src/rp2_common/hardware_spi/include")
  add_library(hardware_irq INTERFACE)
  target_include_directories(hardware_irq INTERFACE "${PICO_SDK_PATH}/src/rp2_common/hardware_irq/include")
  add_library(hardware_clocks INTERFACE)
  target_include_directories(hardware_clocks INTERFACE "${PICO_SDK_PATH}/src/rp2_common/hardware_clocks/include")
  add_library(hardware_sync INTERFACE)
  target_include_directories(hardware_sync INTERFACE "${PICO_SDK_PATH}/src/rp2_common/hardware_sync/include")
  add_library(hardware_gpio INTERFACE)
  target_include_directories(hardware_gpio INTERFACE "${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include")

  add_library(pico_time INTERFACE)
  target_include_directories(pico_time INTERFACE "${PICO_SDK_PATH}/src/common/pico_time/include")
  add_library(pico_binary_info INTERFACE)
  target_include_directories(pico_binary_info INTERFACE "${PICO_SDK_PATH}/src/common/pico_binary_info/include")
  add_library(pico_platform INTERFACE)
  target_include_directories(pico_platform INTERFACE "${PICO_SDK_PATH}/src/rp2_common/pico_platform/include")
  add_library(pico_stdio INTERFACE)
  target_include_directories(pico_stdio INTERFACE "${PICO_SDK_PATH}/src/rp2_common/pico_stdio/include")
  add_library(pico_stdio_uart INTERFACE)
  target_include_directories(pico_stdio_uart INTERFACE "${PICO_SDK_PATH}/src/rp2_common/pico_stdio_uart/include")
  add_library(pico_unique_id INTERFACE)
  target_include_directories(pico_unique_id INTERFACE "${PICO_SDK_PATH}/src/rp2_common/pico_unique_id/include")
  add_library(pico_multicore INTERFACE)
  target_include_directories(pico_multicore INTERFACE "${PICO_SDK_PATH}/src/rp2_common/pico_multicore/include")
  add_library(tinyusb_device INTERFACE)
  target_include_directories(tinyusb_device INTERFACE "${PICO_SDK_PATH}/src/rp2_common/tinyusb_device/include")
  add_library(pico_fatfs INTERFACE)
  target_include_directories(pico_fatfs INTERFACE "${PICO_SDK_PATH}/src/rp2_common/pico_fatfs/include")
endfunction()

function(pico_generate_pio_header target pio_file)
  get_filename_component(pio_name "${pio_file}" NAME)
  set(out "${CMAKE_CURRENT_BINARY_DIR}/${pio_name}.h")
  add_custom_command(
    OUTPUT "${out}"
    COMMAND "${CMAKE_COMMAND}" -DOUT="${out}" -DNAME="${pio_name}" -P "${PICO_SDK_PATH}/tools/pio_gen.cmake"
    DEPENDS "${pio_file}"
    VERBATIM
  )
  set_source_files_properties("${out}" PROPERTIES GENERATED TRUE)
  add_custom_target(${target}_${pio_name}_pio_header DEPENDS "${out}")
  add_dependencies(${target} ${target}_${pio_name}_pio_header)
  target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
endfunction()
