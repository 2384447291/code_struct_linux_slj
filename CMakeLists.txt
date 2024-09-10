cmake_minimum_required(VERSION 3.20)
project(code_struct)

set(CMAKE_CXX_STANDARD 20)#设置编译器版本为C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)# 设置指定的C++编译器版本是必须的
# 设置 C 编译器的优化等级
set(CMAKE_C_FLAGS_RELEASE "-O2") # 为 Release 类型设置 -O2 优化
set(CMAKE_C_FLAGS_DEBUG "-g")    # 为 Debug 类型设置 -g（生成调试信息），不设置优化

# 设置 C++ 编译器的优化等级
set(CMAKE_CXX_FLAGS_RELEASE "-O2") # 为 Release 类型设置 -O2 优化
set(CMAKE_CXX_FLAGS_DEBUG "-g")    # 为 Debug 类型设置 -g（生成调试信息），不设置优化

#分批编译子文件
add_subdirectory(Part_Period)
add_subdirectory(Part_HardwareCom)
add_subdirectory(Part_Robotrunner)

############################################设置主函数############################################
#查找外来库
set(CMAKE_PREFIX_PATH /home/roma/Qt/6.2.4/gcc_64)
# 查找并加载 PkgConfig 模块
# PkgConfig 是一个用于管理编译过程中库的路径和编译器标志的工具
# REQUIRED 关键字表示如果 PkgConfig 没有找到，CMake 将停止并报错。
find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED PrintSupport)
# pkg_check_modules 函数通过 pkg-config 工具查找名为 libevdev 的模块
# 查找到的结果将被存储在几个变量中，例如：
#     libevdev_INCLUDE_DIRS: 包含库的头文件的目录。
#     libevdev_LIBRARY_DIRS: 包含库的目录。
#     libevdev_LIBRARIES: 库文件的名称。
pkg_check_modules(libevdev REQUIRED libevdev)

# 生成可执行文件
add_executable(code_struct main.cpp)

#导入头文件索引
include_directories(./Part_Robotrunner/include)
include_directories(./Part_HardwareCom/include)
include_directories(./Part_Period/include)
include_directories(./QT)
include_directories(./data_struct)
include_directories(${libevdev_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

# 指定 PUBLIC 会使链接信息和包含路径在目标和依赖目标中都可见。
# 指定 PRIVATE 只会使链接信息在目标中可见，而不会传播给依赖目标。
target_link_libraries(code_struct PRIVATE Period)
target_link_libraries(code_struct PRIVATE HardwareCom)
target_link_libraries(code_struct PRIVATE Robotrunner)
target_link_libraries(code_struct PRIVATE ${libevdev_LIBRARIES})
target_link_libraries(code_struct PRIVATE ${OpenCV_LIBRARIES})
target_link_libraries(code_struct PRIVATE Qt6::Widgets)
target_link_libraries(code_struct PRIVATE Qt6::PrintSupport)
target_link_libraries(code_struct PRIVATE pthread)

# 导入先前编译生成的
target_link_libraries(code_struct PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/libRealtimeCurvePlot.so)

set_target_properties(code_struct PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)