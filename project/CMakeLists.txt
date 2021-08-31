cmake_minimum_required(VERSION 3.10)
project("mvcodecleaner")

set (CMAKE_CXX_STANDARD 11)

add_executable(${CMAKE_PROJECT_NAME}
               main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME})
