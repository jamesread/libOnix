cmake_minimum_required(VERSION 2.6)
project(onix-bindings-php)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_library(onixphp MODULE src/main.cpp)
target_link_libraries(onixphp onix)
set_target_properties(onixphp PROPERTIES PREFIX "")
set_target_properties(onixphp PROPERTIES OUTPUT_NAME "onix")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

include_directories(../src)
include_directories(/usr/include/php/)
include_directories(/usr/include/php/Zend/)
include_directories(/usr/include/php/TSRM/)
include_directories(/usr/include/php/main/)

install(FILES bin/onix.so DESTINATION /usr/lib64/php/modules/)
