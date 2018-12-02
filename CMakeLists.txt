cmake_minimum_required(VERSION 3.12)
project(Parte_II___Grafos_)

set(CMAKE_CXX_STANDARD 14)

include_directories(Grafos)

add_executable(Parte_II___Grafos_
        Grafos/main.cpp
        Grafos/Gulosos.cpp
        Grafos/Gulosos.h
        Grafos/Vertice.cpp
        Grafos/Vertice.h)
