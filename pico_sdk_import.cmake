# This is a copy of the canonical Pico SDK import shim with a fixed local default path.
if (DEFINED ENV{PICO_SDK_PATH} AND (NOT PICO_SDK_PATH))
  set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
  message("Using PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
endif ()

if (DEFINED ENV{PICO_SDK_FETCH_FROM_GIT} AND (NOT PICO_SDK_FETCH_FROM_GIT))
  set(PICO_SDK_FETCH_FROM_GIT $ENV{PICO_SDK_FETCH_FROM_GIT})
  message("Using PICO_SDK_FETCH_FROM_GIT from environment ('${PICO_SDK_FETCH_FROM_GIT}')")
endif ()

if (DEFINED ENV{PICO_SDK_FETCH_FROM_GIT_PATH} AND (NOT PICO_SDK_FETCH_FROM_GIT_PATH))
  set(PICO_SDK_FETCH_FROM_GIT_PATH $ENV{PICO_SDK_FETCH_FROM_GIT_PATH})
  message("Using PICO_SDK_FETCH_FROM_GIT_PATH from environment ('${PICO_SDK_FETCH_FROM_GIT_PATH}')")
endif ()

if (NOT PICO_SDK_PATH)
  set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/third_party/pico-sdk)
endif ()

if (NOT EXISTS ${PICO_SDK_PATH}/pico_sdk_init.cmake)
  message(FATAL_ERROR "Pico SDK not found at ${PICO_SDK_PATH}; run git submodule update --init --recursive")
endif ()

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
