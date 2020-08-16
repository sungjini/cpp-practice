cmake_minimum_required(VERSION 3.5)

SET ( CMAKE_BUILD_TYPE Debug )
SET ( CMAKE_VERBOSE_MAKEFILE true )

SET ( CMAKE_C_COMPILER "gcc" )
SET ( CMAKE_CXX_COMPILER "g++" )
SET ( CMAKE_CXX_STANDARD 14 )

add_compile_options(-Wall -Wextra -Wpedantic)

SET ( SOURCE_DIRECTORY ${PROJECT_SOURCE_DIR}/src )

add_subdirectory(src)

