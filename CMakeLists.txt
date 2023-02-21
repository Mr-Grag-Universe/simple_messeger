cmake_minimum_required(VERSION 3.10)
project(simple_messeger)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(test)

# target_link_libraries(Client_GTest MyClientLib)

add_executable(simple_messeger main.cpp)
