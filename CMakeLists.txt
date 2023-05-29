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
#link_directories(bin)
#link_directories("C:\\msys64\\mingw64\\lib")
#link_directories("C:\\msys64\\mingw64\\bin")
#include_directories("C:\\msys64\\mingw64\\include")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(assimp REQUIRED)

#find_package(GLEW REQUIRED)
#include_directories(${GLEW_INCLUDE_DIRS})
#link_libraries(${GLEW_LIBRARIES})

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
  Viewer.cpp
  Viewer.h
  Mesh.cpp
  Mesh.h
  Model.cpp
  Model.h
  Vertex.h
  Texture.h
  MyLineEditWidget.cpp
  MyLineEditWidget.h
  Floor.cpp
  Floor.h
  MyPushButton.cpp
  MyPushButton.h
  CameraOpenGLWidget.cpp
  CameraOpenGLWidget.h
  BtnMeshMode.cpp
  BtnMeshMode.h
  BtnInfo.cpp
  BtnInfo.h
  GameObject.cpp
  GameObject.h
  GlewInit.cpp
  GlewInit.h
)

#if(assimp_FOUND)
##    target_include_directories(clib PRIVATE ${assimp_FOUND})
#    target_link_libraries(OpenGLDemo ${assimp_FOUND})
#    message(${assimp_LIBRARY})
#else(assimp_FOUND)
#    message(FATAL_ERROR ”CURL library not found”)
#endif(assimp_FOUND)

target_link_libraries(OpenGLDemo Qt5::Widgets)
target_link_libraries(OpenGLDemo glew32)
target_link_libraries(OpenGLDemo opengl32)
#target_link_libraries(OpenGLDemo zlibstatic)
#target_link_libraries(OpenGLDemo ${assimp_LIBRARY})
target_link_libraries(OpenGLDemo libassimp.dll.a)


