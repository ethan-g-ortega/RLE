cmake_minimum_required(VERSION 3.16)
project(rle_ci CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(rle src/rle.cpp)
target_include_directories(rle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(rle_app src/main.cpp)
target_link_libraries(rle_app PRIVATE rle)

enable_testing()
add_subdirectory(tests)
