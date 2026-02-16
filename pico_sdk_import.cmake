if(NOT DEFINED PICO_SDK_PATH)
  set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/third_party/pico-sdk")
endif()

if(NOT EXISTS "${PICO_SDK_PATH}/cmake/pico_sdk_init.cmake")
  message(FATAL_ERROR "Pico SDK not found. Set PICO_SDK_PATH or run git submodule update --init --recursive")
endif()

include(${PICO_SDK_PATH}/cmake/pico_sdk_init.cmake)
