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

add_subdirectory(Period)
add_subdirectory(HardwareCom)
add_subdirectory(Robotrunner)

#设置主函数
include_directories(./Robotrunner/include)
include_directories(./HardwareCom/include)
include_directories(./Period/include)
include_directories(./data_struct)

add_executable(code_struct main.cpp)
target_link_libraries(code_struct PRIVATE Robotrunner)
target_link_libraries(code_struct PRIVATE HardwareCom)
target_link_libraries(code_struct PRIVATE Period)

set_target_properties(code_struct PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)