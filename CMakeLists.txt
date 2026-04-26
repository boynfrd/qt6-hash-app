cmake_minimum_required(VERSION 3.21)
project(QtHashApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(QtHashApp
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/sha1hasher.h
    src/sha1hasher.cpp
    src/sha256hasher.h
    src/sha256hasher.cpp
)

target_include_directories(QtHashApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(QtHashApp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
