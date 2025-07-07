cmake_minimum_required(VERSION 3.31)
project(Ubuntu1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Ubuntu1 main.c
        source/ringbuffer.h
        source/ringbuffer.c
        test/ringbuffer_test.cpp)
