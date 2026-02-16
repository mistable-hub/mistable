# Minimal Pico SDK import shim for this repository
if (NOT DEFINED PICO_SDK_PATH)
  set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/third_party/pico-sdk")
endif()

if (EXISTS "${PICO_SDK_PATH}/pico_sdk_init.cmake")
  include("${PICO_SDK_PATH}/pico_sdk_init.cmake")
else()
  message(FATAL_ERROR "Pico SDK not found at ${PICO_SDK_PATH}. Set PICO_SDK_PATH to a valid pico-sdk.")
endif()
