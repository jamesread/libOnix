cmake_minimum_required(VERSION 2.6)
project(libonix)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_library(onix SHARED src/surface.cpp src/main.cpp) 
set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")

#target_link_libraries(onix)

install(TARGETS onix DESTINATION lib)

include_directories(src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY examples)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY examples)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY examples)
set(CMAKE_EXECUTABLE_SUFFIX .bin)

add_executable(example_drawing examples/drawing.cpp)
target_link_libraries(example_drawing onix)
