cmake_minimum_required(VERSION 3.12) 
project(calc VERSION 1.0.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")
include (prevent_source_builds)
include (clang_tidy)

# If not using tests list all source files here
add_executable(${PROJECT_NAME} main.cpp "bignumber.h" "bignumbercalculator.h" "options.h" "options.cpp" "addition.h" "subtraction.h" "multiplication.h" "division.h" "exponentiation.h" "operation.h"     )

#target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#)

file(COPY input.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})