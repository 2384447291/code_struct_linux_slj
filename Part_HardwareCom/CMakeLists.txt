cmake_minimum_required(VERSION 3.20)
project(HardwareCom)

#############################################本地库生成#############################################
# Set the include directoriesW
include_directories(./include)
include_directories(../Part_Period/include)
include_directories(../data_struct)

# Add the source files
set(SOURCES src/UartCommunication.cpp src/DM_USB2CAN.cpp src/Camera.cpp)

#Generate the shared library把该生成的项目创建为共享库（创建的内容为上面定义的SOURCES内容）
add_library(HardwareCom SHARED ${SOURCES})

# target_link_libraries(HardwareCom "../lib/libPeriod.so")
target_link_libraries(HardwareCom PRIVATE Period)

#指定了ThreadPool这个对象(上一步创建的shared库)，并将其地址设置为build/lib
set_target_properties(HardwareCom PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
#############################################可执行文件输出#############################################
include_directories(../motor)
add_executable(TestHardware test/test.cpp)
target_link_libraries(TestHardware PRIVATE HardwareCom)
target_link_libraries(TestHardware PRIVATE Period)
set_target_properties(TestHardware PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build/bin)

