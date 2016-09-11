project(task1)
cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SRC_LIST source/*.cpp resources/*)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic -Wall -Wextra -Wpedantic -Wno-char-subscripts -Wno-unused-result -ggdb")

add_executable(${PROJECT_NAME} ${SRC_LIST})
