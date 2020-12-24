cmake_minimum_required(VERSION 3.5)

project(basic_chess LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

file(GLOB files "*.h" "*.cpp" "*.ui")

add_executable(basic_chess ${files})

target_link_libraries(basic_chess PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
