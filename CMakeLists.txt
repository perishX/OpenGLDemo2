cmake_minimum_required(VERSION 3.5)

project(OpenGLDemo LANGUAGES CXX)

# 修改QT环境
set (CMAKE_PREFIX_PATH "D:\\Qt\\Qt5.12.6\\5.12.6\\mingw73_64")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
link_directories(lib)

include_directories(src/animation)
include_directories(src/model)
include_directories(src/util)
include_directories(src/widgets)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB ANIMATION_HEAD "./src/animation/*.h")
file(GLOB ANIMATION_SOURCE "./src/animation/*.cpp")
file(GLOB MODEL_HEAD "./src/model/*.h")
file(GLOB MODEL_SOURCE "./src/model/*.cpp")
file(GLOB UTIL_HEAD "./src/util/*.h")
file(GLOB UTIL_SOURCE "./src/util/*.cpp")
file(GLOB WIDGETS_HEAD "./src/widgets/*.h")
file(GLOB WIDGETS_SOURCE "./src/widgets/*.cpp")

add_executable(OpenGLDemo
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  ${ANIMATION_HEAD}
  ${ANIMATION_SOURCE}
  ${MODEL_HEAD}
  ${MODEL_SOURCE}
  ${UTIL_HEAD}
  ${UTIL_SOURCE}
  ${WIDGETS_HEAD}
  ${WIDGETS_SOURCE}
)

target_link_libraries(OpenGLDemo Qt5::Widgets)
target_link_libraries(OpenGLDemo glew32)
target_link_libraries(OpenGLDemo opengl32)
target_link_libraries(OpenGLDemo libassimp.dll.a)
