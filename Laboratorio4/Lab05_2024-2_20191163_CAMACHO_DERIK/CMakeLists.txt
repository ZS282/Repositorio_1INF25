cmake_minimum_required(VERSION 4.0)
project(Lab05_2024_2_20191163_CAMACHO_DERIK)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab05_2024_2_20191163_CAMACHO_DERIK main.cpp
        BibliotecaGenerica/BibliotecaGenerica.cpp
        BibliotecaGenerica/BibliotecaGenerica.h
        ListaconEnteros/ListaconEnteros.cpp
        ListaconEnteros/ListaconEnteros.h
        ListaconRegistros/ListaconRegistros.cpp
        ListaconRegistros/ListaconRegistros.h)
