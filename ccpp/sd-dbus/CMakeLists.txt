cmake_minimum_required(VERSION 2.0)
set(component_name main)
project(${component_name})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -fdiagnostics-all-candidates")

add_executable(${component_name} 
main.cpp
)
target_link_libraries(${component_name} -lsystemd)