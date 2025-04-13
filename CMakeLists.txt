cmake_minimum_required(VERSION 3.29)
project(DoubleJumper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/home/radamir/Qt/6.8.2/gcc_64/lib/cmake/")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(FORMS
        mainwindow.ui
)
add_executable(DoubleJumper main.cpp mainwindow.cpp)
target_link_libraries(DoubleJumper

        Qt::Core
        Qt::Gui
        Qt::Widgets stdc++

)


