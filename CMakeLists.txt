cmake_minimum_required(VERSION 3.15)
project(TravellingSalesman)
set(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 14)

add_executable(TravellingSalesman src/main.cpp src/Matrix.cpp src/Matrix.h src/BranchAndBound.cpp src/BranchAndBound.h src/Tour.cpp src/Tour.h src/Explorer.cpp src/Explorer.h)