cmake_minimum_required(VERSION 3.17)
project(mandatory_1 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion")

find_package(OpenMP REQUIRED)

add_library(mandelbrot mandelbrot.h mandelbrot.cpp)

add_executable(SeqMandel mandelbrot_seq.cpp)

target_link_libraries(SeqMandel PRIVATE OpenMP::OpenMP_CXX mandelbrot)