# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joseph/CLionProjects/OpenGLProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joseph/CLionProjects/OpenGLProject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OpenGLProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGLProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGLProject.dir/flags.make

CMakeFiles/OpenGLProject.dir/main.cpp.o: CMakeFiles/OpenGLProject.dir/flags.make
CMakeFiles/OpenGLProject.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joseph/CLionProjects/OpenGLProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGLProject.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OpenGLProject.dir/main.cpp.o -c /home/joseph/CLionProjects/OpenGLProject/main.cpp

CMakeFiles/OpenGLProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLProject.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joseph/CLionProjects/OpenGLProject/main.cpp > CMakeFiles/OpenGLProject.dir/main.cpp.i

CMakeFiles/OpenGLProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLProject.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joseph/CLionProjects/OpenGLProject/main.cpp -o CMakeFiles/OpenGLProject.dir/main.cpp.s

CMakeFiles/OpenGLProject.dir/src/glad.c.o: CMakeFiles/OpenGLProject.dir/flags.make
CMakeFiles/OpenGLProject.dir/src/glad.c.o: ../src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joseph/CLionProjects/OpenGLProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OpenGLProject.dir/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OpenGLProject.dir/src/glad.c.o   -c /home/joseph/CLionProjects/OpenGLProject/src/glad.c

CMakeFiles/OpenGLProject.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OpenGLProject.dir/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/joseph/CLionProjects/OpenGLProject/src/glad.c > CMakeFiles/OpenGLProject.dir/src/glad.c.i

CMakeFiles/OpenGLProject.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OpenGLProject.dir/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/joseph/CLionProjects/OpenGLProject/src/glad.c -o CMakeFiles/OpenGLProject.dir/src/glad.c.s

# Object files for target OpenGLProject
OpenGLProject_OBJECTS = \
"CMakeFiles/OpenGLProject.dir/main.cpp.o" \
"CMakeFiles/OpenGLProject.dir/src/glad.c.o"

# External object files for target OpenGLProject
OpenGLProject_EXTERNAL_OBJECTS =

OpenGLProject: CMakeFiles/OpenGLProject.dir/main.cpp.o
OpenGLProject: CMakeFiles/OpenGLProject.dir/src/glad.c.o
OpenGLProject: CMakeFiles/OpenGLProject.dir/build.make
OpenGLProject: include/glfw-3.2.1/src/libglfw3.a
OpenGLProject: /usr/lib/librt.so
OpenGLProject: /usr/lib/libm.so
OpenGLProject: /usr/lib/libX11.so
OpenGLProject: /usr/lib/libXrandr.so
OpenGLProject: /usr/lib/libXinerama.so
OpenGLProject: /usr/lib/libXxf86vm.so
OpenGLProject: /usr/lib/libXcursor.so
OpenGLProject: CMakeFiles/OpenGLProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joseph/CLionProjects/OpenGLProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable OpenGLProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGLProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGLProject.dir/build: OpenGLProject

.PHONY : CMakeFiles/OpenGLProject.dir/build

CMakeFiles/OpenGLProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGLProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGLProject.dir/clean

CMakeFiles/OpenGLProject.dir/depend:
	cd /home/joseph/CLionProjects/OpenGLProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joseph/CLionProjects/OpenGLProject /home/joseph/CLionProjects/OpenGLProject /home/joseph/CLionProjects/OpenGLProject/cmake-build-debug /home/joseph/CLionProjects/OpenGLProject/cmake-build-debug /home/joseph/CLionProjects/OpenGLProject/cmake-build-debug/CMakeFiles/OpenGLProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGLProject.dir/depend

