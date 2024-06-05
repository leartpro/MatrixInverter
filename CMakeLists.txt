cmake_minimum_required(VERSION 3.28)
project(MatrixInverter)

set(CMAKE_CXX_STANDARD 26)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
set(SOURCE_FILES main.cpp)
add_executable(MatrixInverter ${SOURCE_FILES})
