cmake_minimum_required(VERSION 4.0)
project(kehindes_gameboy_emulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(kehindes_gameboy_emulator
        GameboyContext.cpp
        GameboyContext.h)
