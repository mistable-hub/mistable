add_library(pico_stdlib INTERFACE)

function(pico_sdk_init)
endfunction()

function(pico_enable_stdio_usb target enabled)
  set(_unused "${target}${enabled}")
endfunction()

function(pico_enable_stdio_uart target enabled)
  set(_unused "${target}${enabled}")
endfunction()

function(pico_generate_pio_header target pio_file)
  get_filename_component(pio_name "${pio_file}" NAME_WE)
  set(out_dir "${CMAKE_CURRENT_BINARY_DIR}/generated/pio")
  set(out_file "${out_dir}/${pio_name}.pio.h")

  file(MAKE_DIRECTORY "${out_dir}")
  file(WRITE "${out_file}" "#pragma once\n/* Generated from ${pio_file} */\n")
  target_include_directories(${target} PRIVATE "${out_dir}")
endfunction()

function(pico_add_extra_outputs target)
  add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${target}>" "${CMAKE_CURRENT_BINARY_DIR}/${target}.elf"
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${target}>" "${CMAKE_CURRENT_BINARY_DIR}/${target}.uf2"
    VERBATIM
  )
endfunction()
