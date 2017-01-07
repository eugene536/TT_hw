project(task3)
cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SRC_LIST source/*.cpp)
file(GLOB_RECURSE HDR_LIST include/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -Wno-char-subscripts -Wno-unused-result -g -fsanitize=thread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -Wno-char-subscripts -Wno-unused-result -g -ggdb -fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -Wno-char-subscripts -Wno-unused-result -g ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -g -march=native -ffast-math -mtune=native")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")

#add_definitions(-D_LINUX)
#add_definitions(-DNDEBUG)
add_definitions(-D_GLIBCXX_DEBUG)
add_definitions(-DDEBUG)
include_directories(include)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HDR_LIST})
