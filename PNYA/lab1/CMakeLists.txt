cmake_minimum_required(VERSION 3.16)
project(LOL)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.9.2/mingw_64/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(LOL
        main.cpp
        Array.cpp
        Array.h
)

target_link_libraries(LOL Qt6::Widgets)
