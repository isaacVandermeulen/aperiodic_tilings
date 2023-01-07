add_library(pentagonal
    tall_triangle.cpp
    tiling.cpp
    wide_triangle.cpp)
 
target_include_directories(geometry
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
