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
include HardwareCom/CMakeFiles/TestHardware.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include HardwareCom/CMakeFiles/TestHardware.dir/compiler_depend.make

# Include the progress variables for this target.
include HardwareCom/CMakeFiles/TestHardware.dir/progress.make

# Include the compile flags for this target's objects.
include HardwareCom/CMakeFiles/TestHardware.dir/flags.make

HardwareCom/CMakeFiles/TestHardware.dir/test/test.cpp.o: HardwareCom/CMakeFiles/TestHardware.dir/flags.make
HardwareCom/CMakeFiles/TestHardware.dir/test/test.cpp.o: /home/roma/Desktop/code_struct_linux_slj/HardwareCom/test/test.cpp
HardwareCom/CMakeFiles/TestHardware.dir/test/test.cpp.o: HardwareCom/CMakeFiles/TestHardware.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/roma/Desktop/code_struct_linux_slj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object HardwareCom/CMakeFiles/TestHardware.dir/test/test.cpp.o"
	cd /home/roma/Desktop/code_struct_linux_slj/build/HardwareCom && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT HardwareCom/CMakeFiles/TestHardware.dir/test/test.cpp.o -MF CMakeFiles/TestHardware.dir/test/test.cpp.o.d -o CMakeFiles/TestHardware.dir/test/test.cpp.o -c /home/roma/Desktop/code_struct_linux_slj/HardwareCom/test/test.cpp

HardwareCom/CMakeFiles/TestHardware.dir/test/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TestHardware.dir/test/test.cpp.i"
	cd /home/roma/Desktop/code_struct_linux_slj/build/HardwareCom && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roma/Desktop/code_struct_linux_slj/HardwareCom/test/test.cpp > CMakeFiles/TestHardware.dir/test/test.cpp.i

HardwareCom/CMakeFiles/TestHardware.dir/test/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TestHardware.dir/test/test.cpp.s"
	cd /home/roma/Desktop/code_struct_linux_slj/build/HardwareCom && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roma/Desktop/code_struct_linux_slj/HardwareCom/test/test.cpp -o CMakeFiles/TestHardware.dir/test/test.cpp.s

# Object files for target TestHardware
TestHardware_OBJECTS = \
"CMakeFiles/TestHardware.dir/test/test.cpp.o"

# External object files for target TestHardware
TestHardware_EXTERNAL_OBJECTS =

bin/TestHardware: HardwareCom/CMakeFiles/TestHardware.dir/test/test.cpp.o
bin/TestHardware: HardwareCom/CMakeFiles/TestHardware.dir/build.make
bin/TestHardware: /home/roma/Desktop/code_struct_linux_slj/lib/libHardwareCom.so
bin/TestHardware: /home/roma/Desktop/code_struct_linux_slj/lib/libPeriod.so
bin/TestHardware: HardwareCom/CMakeFiles/TestHardware.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/roma/Desktop/code_struct_linux_slj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/TestHardware"
	cd /home/roma/Desktop/code_struct_linux_slj/build/HardwareCom && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestHardware.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
HardwareCom/CMakeFiles/TestHardware.dir/build: bin/TestHardware
.PHONY : HardwareCom/CMakeFiles/TestHardware.dir/build

HardwareCom/CMakeFiles/TestHardware.dir/clean:
	cd /home/roma/Desktop/code_struct_linux_slj/build/HardwareCom && $(CMAKE_COMMAND) -P CMakeFiles/TestHardware.dir/cmake_clean.cmake
.PHONY : HardwareCom/CMakeFiles/TestHardware.dir/clean

HardwareCom/CMakeFiles/TestHardware.dir/depend:
	cd /home/roma/Desktop/code_struct_linux_slj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roma/Desktop/code_struct_linux_slj /home/roma/Desktop/code_struct_linux_slj/HardwareCom /home/roma/Desktop/code_struct_linux_slj/build /home/roma/Desktop/code_struct_linux_slj/build/HardwareCom /home/roma/Desktop/code_struct_linux_slj/build/HardwareCom/CMakeFiles/TestHardware.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : HardwareCom/CMakeFiles/TestHardware.dir/depend

