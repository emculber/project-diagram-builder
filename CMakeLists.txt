cmake_minimum_required (VERSION 2.6)

project (cagewin)
set (CMAKE_C_FLAGS "-Wall -Wextra -Werror")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable (cagewin src/main.c)
