if (NOT DEFINED PICO_SDK_PATH)
  set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/third_party/pico-sdk")
endif()

if (NOT EXISTS "${PICO_SDK_PATH}/external/pico_sdk_import.cmake")
  message(FATAL_ERROR "Pico SDK not found at ${PICO_SDK_PATH}. Set PICO_SDK_PATH or vendor third_party/pico-sdk")
endif()

include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")
