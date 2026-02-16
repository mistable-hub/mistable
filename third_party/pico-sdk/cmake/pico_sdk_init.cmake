include_guard(GLOBAL)

set(PICO_SDK_VERSION_STRING "offline-mock")

function(pico_sdk_init)
endfunction()

function(pico_enable_stdio_usb target enable)
endfunction()

function(pico_enable_stdio_uart target enable)
endfunction()

function(pico_add_extra_outputs target)
  add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:${target}> ${CMAKE_CURRENT_BINARY_DIR}/${target}.elf)
  add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "MOCK UF2 for ${target}" > ${CMAKE_CURRENT_BINARY_DIR}/${target}.uf2)
endfunction()

function(pico_generate_pio_header target pio_file)
  get_filename_component(pio_name ${pio_file} NAME_WE)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated/pio)
  set(out_h ${CMAKE_CURRENT_BINARY_DIR}/generated/pio/${pio_name}.pio.h)
  file(WRITE ${out_h} "#ifndef ${pio_name}_PIO_H\n#define ${pio_name}_PIO_H\nstatic inline void ${pio_name}_pio_init(void) {}\n#endif\n")
  target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated/pio)
endfunction()
