cmake_minimum_required(VERSION 3.5)

project(OpenGLDemo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
link_directories(lib)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(OpenGLDemo
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  MyOpenGLWidget.cpp
  MyOpenGLWidget.h
  Shader.cpp
  Shader.h
  Cube.cpp
  Cube.h
  glad.c
  Viewer.cpp
  Viewer.h
)

target_link_libraries(OpenGLDemo PRIVATE Qt5::Widgets glew32.lib glew32.dll glfw3.dll libglfw3.a libglfw3dll.a opengl32.dll)
#target_link_libraries(OpenGLDemo PRIVATE Qt5::Widgets)
