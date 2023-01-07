add_library(geometry
            point.cpp
            triangle.cpp
            tiling.cpp)
 
target_include_directories( geometry
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
