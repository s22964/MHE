cmake_minimum_required(VERSION 3.21)
project(Zadanie4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(Zadanie4 main.cpp funkcje.h funkcjeImpl.cpp)
