cmake_minimum_required(VERSION 3.5)

add_compile_options(-Wall -Wextra -Wpedantic)

#add_executable(main main.cpp)
#target_compile_features(main PRIVATE cxx_lambda_init_captures)

add_executable(unique_ptr unique_ptr.cpp)


