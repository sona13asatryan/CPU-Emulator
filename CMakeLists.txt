cmake_minimum_required(VERSION 3.17)
 
project(ason)

set(CMAKE_CXX_STANDARD 11)

include_directories (include)

add_executable(ason src/main.cpp src/cpu.cpp src/ram.cpp)
