cmake_minimum_required(VERSION 3.29)
project(DoubleJumper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/home/radamir/Qt/6.8.2/gcc_64/lib/cmake/")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        MultimediaWidgets
        REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(FORMS
        mainwindow.ui
)
add_executable(DoubleJumper main.cpp mainwindow.cpp MainMenuWidget.cpp PhysicsModel.cpp DoubleJumper.cpp platforms/AbstractPlatform.cpp
        platforms/GreenPlatform.cpp gameVisualisation/gameWidget.cpp game/Game.cpp game/Screen.cpp platforms/BrownPLatform.cpp
        platforms/BluePlatform.cpp gameVisualisation/ScoreBar.cpp items/AbstractItem.cpp items/Spring.cpp
        items/helicopterHat.cpp items/Jetpack.cpp)
target_link_libraries(DoubleJumper

        Qt::Core
        Qt::Gui
        Qt::Widgets stdc++
        Qt::Multimedia
        Qt::MultimediaWidgets
        m

)


