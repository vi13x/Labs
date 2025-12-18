cmake_minimum_required(VERSION 3.29)
project(LABA4_3sem)

set(CMAKE_CXX_STANDARD 20)

add_executable(LABA4_3sem main.cpp
        TransportVehicle.cpp
        Cart.cpp
        Car.cpp
        Bicycle.cpp
        Application.cpp)
