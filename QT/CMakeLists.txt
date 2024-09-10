cmake_minimum_required(VERSION 3.20)
project(RealtimeCurvePlot)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)#设置编译器版本为C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)# 设置指定的C++编译器版本是必须的
# 设置 C 编译器的优化等级
set(CMAKE_C_FLAGS_RELEASE "-O2") # 为 Release 类型设置 -O2 优化
set(CMAKE_C_FLAGS_DEBUG "-g")    # 为 Debug 类型设置 -g（生成调试信息），不设置优化

# 设置 C++ 编译器的优化等级
set(CMAKE_CXX_FLAGS_RELEASE "-O2") # 为 Release 类型设置 -O2 优化
set(CMAKE_CXX_FLAGS_DEBUG "-g")    # 为 Debug 类型设置 -g（生成调试信息），不设置优化

# 这些命令告诉 CMake 在构建过程中自动处理 UI 文件、MOC 文件和资源文件。
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH /home/roma/Qt/6.2.4/gcc_64)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED PrintSupport)

set(SOURCES
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        curveplotfifo.cpp
        curveplotfifo.h
        qcustomplot.cpp
        qcustomplot.h
        realtimecurveplot.h
        realtimecurveplot.cpp
)

add_library(RealtimeCurvePlot SHARED ${SOURCES})
set_target_properties(RealtimeCurvePlot PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
target_link_libraries(RealtimeCurvePlot PRIVATE Qt6::Widgets)
target_link_libraries(RealtimeCurvePlot PRIVATE Qt6::PrintSupport)
