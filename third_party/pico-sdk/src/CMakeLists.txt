add_library(hardware_spi STATIC spi.c)
target_include_directories(hardware_spi PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
add_subdirectory(common/pico_stdlib)
