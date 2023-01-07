add_library(geometry triangle.cpp point.cpp)
message("${CMAKE_CURRENT_SOURCE_DIR} is the current source")
 
target_include_directories( geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
