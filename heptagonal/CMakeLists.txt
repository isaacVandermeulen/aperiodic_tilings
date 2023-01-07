add_library(heptagonal 
            middle_triangle.cpp
            tall_triangle.cpp
            tiling.cpp
            scalene_triangle.cpp
            wide_triangle.cpp)
 
target_include_directories(geometry
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
