cmake_minimum_required(VERSION 3.20)
project(Robotrunner)

#############################################本地库生成#############################################
# Set the include directories
include_directories(../HardwareCom/include)
include_directories(../Period/include)
include_directories(../data_struct)
include_directories(./include)
# Add the source files
set(SOURCES src/RobotRunner.cpp)

#Generate the shared library把该生成的项目创建为共享库（创建的内容为上面定义的SOURCES内容）
add_library(Robotrunner SHARED ${SOURCES})

#指定了ThreadPool这个对象(上一步创建的shared库)，并将其地址设置为build/lib
set_target_properties(Robotrunner PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

#将pthread库连接到ThreadPool库
target_link_libraries(Robotrunner pthread)
#############################################可执行文件输出#############################################
include_directories(../HardwareCom/include)
include_directories(../Period/include)
add_executable(TestRobotrunner test/test.cpp)
target_link_libraries(TestRobotrunner PRIVATE Robotrunner)
target_link_libraries(TestRobotrunner PRIVATE HardwareCom)
target_link_libraries(TestRobotrunner PRIVATE Period)
set_target_properties(TestRobotrunner PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build/bin)
