cmake_minimum_required(VERSION 3.5)
project(week03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(week03 COMMAND make -C $(CMAKE_CURRENT_SOURCE_DIR)
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})