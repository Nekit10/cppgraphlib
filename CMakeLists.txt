cmake_minimum_required(VERSION 3.16)
project(cppgraphlib)

set(CMAKE_CXX_STANDARD 17)

add_library(cppgraphlib graph.cpp graph.h)

include_directories(.)
add_executable(graphtests unittests/graph_tests.cpp include/catch.hpp graph.cpp graph.h)