if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/third_party/pico-sdk/cmake/pico_sdk_init.cmake")
  message(FATAL_ERROR "Missing Pico SDK: run git submodule update --init --recursive")
endif()
include(${CMAKE_CURRENT_LIST_DIR}/third_party/pico-sdk/cmake/pico_sdk_init.cmake)
