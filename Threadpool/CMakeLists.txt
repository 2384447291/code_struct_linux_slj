cmake_minimum_required(VERSION 3.20)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 20)#设置编译器版本为C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)# 设置指定的C++编译器版本是必须的
# 设置 C 编译器的优化等级
set(CMAKE_C_FLAGS_RELEASE "-O2") # 为 Release 类型设置 -O2 优化
set(CMAKE_C_FLAGS_DEBUG "-g")    # 为 Debug 类型设置 -g（生成调试信息），不设置优化

# 设置 C++ 编译器的优化等级
set(CMAKE_CXX_FLAGS_RELEASE "-O2") # 为 Release 类型设置 -O2 优化
set(CMAKE_CXX_FLAGS_DEBUG "-g")    # 为 Debug 类型设置 -g（生成调试信息），不设置优化

#设置cmakelist的输出文件目录
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Set the include directories
include_directories(include)

# Add the source files
set(SOURCES src/thread_pool.cpp src/worker_thread.cpp)

#Generate the shared library把该生成的项目创建为共享库（创建的内容为上面定义的SOURCES内容）
add_library(ThreadPool SHARED ${SOURCES})

#指定了ThreadPool这个对象(上一步创建的shared库)，并将其地址设置为build/lib
set_target_properties(ThreadPool PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

#将pthread库连接到ThreadPool库
target_link_libraries(ThreadPool pthread)
