cmake_minimum_required(VERSION 3.25)
project(sunfish_c C)

set(CMAKE_C_STANDARD 23)

add_executable(sunfish_c main.c map.c map.h pieceSquareTables.h pieceSquareTables.c debug.c debug.h)
