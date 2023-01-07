cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(aperiodic_tilings)

add_subdirectory(geometry)
add_subdirectory(pentagonal)

add_executable(penrose penrose.cpp)
target_link_libraries(penrose geometry)
target_link_libraries(penrose pentagonal)
