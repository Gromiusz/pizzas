cmake_minimum_required(VERSION 3.11.0)

# TODO: Write proper build system :)
project(Pizzas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)

enable_testing()

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)