cmake_minimum_required(VERSION 3.10)
project(Server_GTest)

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

## ========== include Boost ========== ##

set (BOOST_ROOT "C:/boost_1_81_0") # Путь к библиотеке Boost
set(Boost_DEBUG 1)
set(Boost_ARCHITECTURE -x64)
# set(Boost_COMPILER -)

if (WIN32)
    set(_WIN32_WINNT 0x0601)
endif()

set (Boost_NO_WARN_NEW_VERSIONS ON)
set (Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system program_options)
include_directories(C:/boost_1_81_0/boost)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS} "C:/boost_1_81_0")

## ========== ========== ========== ##

add_executable(${PROJECT_NAME} main_test.cpp server_test.h)
target_include_directories(${PROJECT_NAME} PUBLIC ../../src/server/server_lib ../../src/server/server_lib/include)
target_link_libraries(${PROJECT_NAME} gtest gtest_main MyServerLib
        ${Boost_LIBRARIES}
        )
target_link_directories(${PROJECT_NAME} PUBLIC C:/boost_1_81_0/boost)
if(MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
#target_link_libraries(${PROJECT_NAME} PUBLIC)