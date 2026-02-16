if (NOT TARGET pico_stdlib)
  include(${CMAKE_CURRENT_LIST_DIR}/../cmake/pico_stub_sdk.cmake)
endif()
