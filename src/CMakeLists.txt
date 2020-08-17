cmake_minimum_required(VERSION 3.5)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(main main.cpp)
#target_compile_features(main PRIVATE cxx_lambda_init_captures)

add_executable(02_unique_ptr 02_unique_ptr.cpp)

add_executable(03_reference 03_reference.cpp)

add_executable(05_rvalue_ref 05_rvalue_ref.cpp)
