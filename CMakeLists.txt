cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(minx LANGUAGES CXX VERSION 0.1)

add_subdirectory("src")
add_subdirectory("include")

if (NOT MSVC)
  target_compile_options(minx PRIVATE -Wall -Wextra -Wshadow -Wunreachable-code -Wpedantic)
endif()

target_include_directories(minx PUBLIC ${PROJECT_BINARY_DIR})
