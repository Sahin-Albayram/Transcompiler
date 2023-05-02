cmake_minimum_required(VERSION 3.24)
project(hw2 C)

set(CMAKE_C_STANDARD 11)

add_executable(hw2 main.c token.h token.c structs.h element.c shunk_yard.c llivm.c stack.c queue.c)
