cmake_minimum_required(VERSION 3.27)

project(Visualizer)

add_library(Visualizer STATIC Visualizer.cpp Visualizer.h)
target_link_libraries(Visualizer raylib)

add_executable(VisualizerTest2D DP_2D_test.cpp)
target_link_libraries(VisualizerTest2D Visualizer)

add_executable(VisualizerTest1D DPtest.cpp)
target_link_libraries(VisualizerTest1D Visualizer)
