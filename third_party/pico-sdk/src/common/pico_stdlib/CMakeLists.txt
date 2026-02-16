add_library(pico_stdlib STATIC stdlib.c)
target_include_directories(pico_stdlib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../../include)
