cmake_minimum_required(VERSION 3.5)

project(client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "--coverage -Wall")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task1 task1/main.cpp task1/Graph.h task1/ArcGraph.h task1/ListGraph.h task1/MatrixGraph.h task1/SetGraph.h)
add_executable(task2 task2/main.cpp task2/Graph.h task2/ListGraph.h task2/CountShortPaths.h)
add_executable(task3 task3/main.cpp task3/Graph.h task3/Dijkstra.h)
