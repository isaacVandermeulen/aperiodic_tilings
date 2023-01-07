cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(aperiodic_tilings)

add_subdirectory(geometry)
add_subdirectory(pentagonal)
add_subdirectory(heptagonal)

add_executable(aperiodic_tiling aperiodic_tiling.cpp)
target_link_libraries(aperiodic_tiling geometry)
target_link_libraries(aperiodic_tiling pentagonal)
target_link_libraries(aperiodic_tiling heptagonal)
