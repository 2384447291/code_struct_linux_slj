# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake-3.30.0-rc3-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.30.0-rc3-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/roma/Desktop/code_struct_linux_slj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/roma/Desktop/code_struct_linux_slj/build

# Include any dependencies generated for this target.
include Robotrunner/CMakeFiles/Robotrunner.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Robotrunner/CMakeFiles/Robotrunner.dir/compiler_depend.make

# Include the progress variables for this target.
include Robotrunner/CMakeFiles/Robotrunner.dir/progress.make

# Include the compile flags for this target's objects.
include Robotrunner/CMakeFiles/Robotrunner.dir/flags.make

Robotrunner/CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o: Robotrunner/CMakeFiles/Robotrunner.dir/flags.make
Robotrunner/CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o: /home/roma/Desktop/code_struct_linux_slj/Robotrunner/src/RobotRunner.cpp
Robotrunner/CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o: Robotrunner/CMakeFiles/Robotrunner.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/roma/Desktop/code_struct_linux_slj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Robotrunner/CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o"
	cd /home/roma/Desktop/code_struct_linux_slj/build/Robotrunner && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Robotrunner/CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o -MF CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o.d -o CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o -c /home/roma/Desktop/code_struct_linux_slj/Robotrunner/src/RobotRunner.cpp

Robotrunner/CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.i"
	cd /home/roma/Desktop/code_struct_linux_slj/build/Robotrunner && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roma/Desktop/code_struct_linux_slj/Robotrunner/src/RobotRunner.cpp > CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.i

Robotrunner/CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.s"
	cd /home/roma/Desktop/code_struct_linux_slj/build/Robotrunner && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roma/Desktop/code_struct_linux_slj/Robotrunner/src/RobotRunner.cpp -o CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.s

# Object files for target Robotrunner
Robotrunner_OBJECTS = \
"CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o"

# External object files for target Robotrunner
Robotrunner_EXTERNAL_OBJECTS =

/home/roma/Desktop/code_struct_linux_slj/lib/libRobotrunner.so: Robotrunner/CMakeFiles/Robotrunner.dir/src/RobotRunner.cpp.o
/home/roma/Desktop/code_struct_linux_slj/lib/libRobotrunner.so: Robotrunner/CMakeFiles/Robotrunner.dir/build.make
/home/roma/Desktop/code_struct_linux_slj/lib/libRobotrunner.so: Robotrunner/CMakeFiles/Robotrunner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/roma/Desktop/code_struct_linux_slj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/roma/Desktop/code_struct_linux_slj/lib/libRobotrunner.so"
	cd /home/roma/Desktop/code_struct_linux_slj/build/Robotrunner && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Robotrunner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Robotrunner/CMakeFiles/Robotrunner.dir/build: /home/roma/Desktop/code_struct_linux_slj/lib/libRobotrunner.so
.PHONY : Robotrunner/CMakeFiles/Robotrunner.dir/build

Robotrunner/CMakeFiles/Robotrunner.dir/clean:
	cd /home/roma/Desktop/code_struct_linux_slj/build/Robotrunner && $(CMAKE_COMMAND) -P CMakeFiles/Robotrunner.dir/cmake_clean.cmake
.PHONY : Robotrunner/CMakeFiles/Robotrunner.dir/clean

Robotrunner/CMakeFiles/Robotrunner.dir/depend:
	cd /home/roma/Desktop/code_struct_linux_slj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roma/Desktop/code_struct_linux_slj /home/roma/Desktop/code_struct_linux_slj/Robotrunner /home/roma/Desktop/code_struct_linux_slj/build /home/roma/Desktop/code_struct_linux_slj/build/Robotrunner /home/roma/Desktop/code_struct_linux_slj/build/Robotrunner/CMakeFiles/Robotrunner.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Robotrunner/CMakeFiles/Robotrunner.dir/depend

