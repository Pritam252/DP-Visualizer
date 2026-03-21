cmake_minimum_required(VERSION 3.27)

project(Visualizer)

find_package(raylib REQUIRED)

add_library(Visualizer STATIC Visualizer.cpp Visualizer.h)
target_include_directories(Visualizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Visualizer PUBLIC raylib)

add_executable(VisualizerTest2D DP_2D_test.cpp)
target_link_libraries(VisualizerTest2D Visualizer)

add_executable(VisualizerTest1D DP_1D_test.cpp)
target_link_libraries(VisualizerTest1D Visualizer)

install(TARGETS Visualizer
    EXPORT Visualizer
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES Visualizer.h
    DESTINATION include)