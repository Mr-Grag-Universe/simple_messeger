cmake_minimum_required(VERSION 3.10)
project(Client_GTest)

if (MSVC)
    # warning level 4
    # add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wno-dev)
endif()
cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} main_test.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../src/client/client_lib ../../src/client/client_lib/include)
target_link_libraries(${PROJECT_NAME} gtest gtest_main MyClientLib)
#target_link_libraries(${PROJECT_NAME} PUBLIC)