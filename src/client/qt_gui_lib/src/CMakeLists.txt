cmake_minimum_required(VERSION 3.10)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\")
set(Qt5Widgets_DIR "C:\\Qt\\5.15.2\\mingw81_64\\bin\\")
set(Qt5_DIR "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake\\Qt5\\")

project(gui)
set(CMAKE_CXX_STANDARD 17)

set(NAME MyClientGUI_Lib)

set(SOURCE_FILES
    Window.cpp
    )

set(HEADER_FILES
       ../include/qt_gui.h
       Window.h
       )

## ========== include Qt5 ========== ##

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories("C:\\Qt\\5.15.2\\mingw81_64\\include\\")
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

## ========== ========== =========== ##

include_directories(../include ../../client_lib/include)

add_library(${NAME} ${SOURCE_FILES} ${HEADER_FILES} ../include/qt_gui.h)
target_include_directories(${NAME} PUBLIC ../../client_lib ../../client_lib/include)
target_link_libraries(${NAME}
        Qt5::Widgets Qt5::Core Qt5::Gui
        MyClientLib
        )