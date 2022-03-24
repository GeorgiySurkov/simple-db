cmake_minimum_required(VERSION 3.10)

project(room_for_sale)

file(
        GLOB_RECURSE
        sources
        "src/*.cpp"
        "src/*.h"
)
add_executable(room_for_sale RoomForSale.cpp ${sources})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)