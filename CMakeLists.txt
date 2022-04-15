cmake_minimum_required(VERSION 3.20)
project (TP C)

set(CMAKE_C_STANDARD 99)

add_executable(TP main.c matdin.c matdin.h utils.c utils.h jogo.c jogo.h menu.c menu.h)
