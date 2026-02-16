if (NOT PICO_SDK_PATH)
  get_filename_component(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
endif ()

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
