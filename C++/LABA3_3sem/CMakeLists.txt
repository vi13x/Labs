cmake_minimum_required(VERSION 3.29)
project(LABA3_3sem)

set(CMAKE_CXX_STANDARD 26)

add_executable(LABA3_3sem
        main.cpp
        TransportVehicle.cpp
        Car.cpp
        Bicycle.cpp
        Cart.cpp
        TransportVehicle.h
        Car.h
        Bicycle.h
        Cart.h)
