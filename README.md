# MinGW + vscode 环境

使用glew32、libassimp.dll.a。

## 环境配置
1. path中配置mingw路径， 参考：D:\mingw64\bin
2. 配置QTDIR，供cmakelists使用，参考：C:\Qt\Qt5.12.6\5.12.6\mingw73_64
3. path中配置qt动态链接库路径，参考：%QTDIR%\bin

## 运行
1. 将bin目录下的动态库复制到build文件夹
2. 将shader文件夹复制到build文件夹

# Visual Studio 2019 环境

使用glew32s、assimp-vc142-mtd。

其他与mingw+vscode环境类似。

# 打包

1. 将exe拷到单独的文件夹
2. 运行windeployqt OpenGLDemo.exe，自动将运行时需要的dll拷贝