project(MyServer)
set(CMAKE_CXX_STANDARD 20)

## ========== include Qt5 ========== ##

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\")
set(Qt5Widgets_DIR "C:\\Qt\\5.15.2\\mingw81_64\\bin\\")
set(Qt5_DIR "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake\\Qt5\\")

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

add_subdirectory(server_lib)
include_directories(server_lib server_lib/include)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS} "C:/boost_1_81_0")

add_executable(${PROJECT_NAME} main.cpp server_lib/include/server.h)
target_link_directories(${PROJECT_NAME} PUBLIC server_lib/include)
target_link_libraries(${PROJECT_NAME} PUBLIC MyServerLib
        ${Boost_LIBRARIES}
        )