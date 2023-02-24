cmake_minimum_required(VERSION 3.10)
project(server)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\")
set(Qt5Widgets_DIR "C:\\Qt\\5.15.2\\mingw81_64\\bin\\")
set(Qt5_DIR "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake\\Qt5\\")

set(CMAKE_CXX_STANDARD 20)

set(NAME MyServerLib)

set(SOURCE_FILES
        Server.cpp
        DataBase.cpp)

set(HEADER_FILES
        Server.h
        DataBase.h)

## ========== include Qt5 ========== ##

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories("C:\\Qt\\5.15.2\\mingw81_64\\include\\")
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)

## ========== ========== ========== ##

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

## ========== ========== ========== ##

include_directories(../include/)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS} "C:/boost_1_81_0")

add_library(${NAME} ${SOURCE_FILES} ${HEADER_FILES} ../include/server.h)
target_link_libraries(${NAME}
        # PUBLIC
        ${Boost_LIBRARIES}
        )
target_link_directories(${NAME} PUBLIC ../include C:/boost_1_81_0/boost)
if(MINGW)
    target_link_libraries(${NAME} ws2_32)
endif()
