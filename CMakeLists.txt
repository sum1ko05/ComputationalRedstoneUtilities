cmake_minimum_required(VERSION 3.24)
project(ComputationalRedstoneUtilities VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/validators)

add_subdirectory(apps/rem1_assembler)