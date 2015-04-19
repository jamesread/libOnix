cmake_minimum_required(VERSION 2.6)
project(pyonix)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")

include_directories(SYSTEM ../src /usr/include/python2.7)
add_library(pyonix SHARED src/pysurface.cpp)
set_target_properties(pyonix PROPERTIES PREFIX "")
target_link_libraries(pyonix boost_python)
target_link_libraries(pyonix Onix)

install(TARGETS pyonix DESTINATION "/lib64/python2.7/site-packages/")
install(TARGETS pyonix DESTINATION "/lib64/python3.3/site-packages/")
