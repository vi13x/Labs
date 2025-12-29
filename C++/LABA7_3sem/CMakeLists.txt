cmake_minimum_required(VERSION 3.26)
project(LABA7_3sem)

set(CMAKE_CXX_STANDARD 20)

add_executable(LABA7_3sem main.cpp
        TransportVehicle.cpp
        Cart.cpp
        Car.cpp
        Bicycle.cpp
        Application.cpp
        ExceptionHandler.cpp
        Application.h
        Application.h)

