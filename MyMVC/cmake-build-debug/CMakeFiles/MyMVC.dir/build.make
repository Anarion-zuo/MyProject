# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/JetBrains/Toolbox/apps/CLion/ch-0/193.5662.56/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/local/JetBrains/Toolbox/apps/CLion/ch-0/193.5662.56/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anarion/Documents/MyProjects/MyMVC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MyMVC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MyMVC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyMVC.dir/flags.make

CMakeFiles/MyMVC.dir/main.cpp.o: CMakeFiles/MyMVC.dir/flags.make
CMakeFiles/MyMVC.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyMVC.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyMVC.dir/main.cpp.o -c /home/anarion/Documents/MyProjects/MyMVC/main.cpp

CMakeFiles/MyMVC.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyMVC.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anarion/Documents/MyProjects/MyMVC/main.cpp > CMakeFiles/MyMVC.dir/main.cpp.i

CMakeFiles/MyMVC.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyMVC.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anarion/Documents/MyProjects/MyMVC/main.cpp -o CMakeFiles/MyMVC.dir/main.cpp.s

CMakeFiles/MyMVC.dir/Request/Request.cpp.o: CMakeFiles/MyMVC.dir/flags.make
CMakeFiles/MyMVC.dir/Request/Request.cpp.o: ../Request/Request.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyMVC.dir/Request/Request.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyMVC.dir/Request/Request.cpp.o -c /home/anarion/Documents/MyProjects/MyMVC/Request/Request.cpp

CMakeFiles/MyMVC.dir/Request/Request.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyMVC.dir/Request/Request.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anarion/Documents/MyProjects/MyMVC/Request/Request.cpp > CMakeFiles/MyMVC.dir/Request/Request.cpp.i

CMakeFiles/MyMVC.dir/Request/Request.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyMVC.dir/Request/Request.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anarion/Documents/MyProjects/MyMVC/Request/Request.cpp -o CMakeFiles/MyMVC.dir/Request/Request.cpp.s

CMakeFiles/MyMVC.dir/Response/Response.cpp.o: CMakeFiles/MyMVC.dir/flags.make
CMakeFiles/MyMVC.dir/Response/Response.cpp.o: ../Response/Response.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MyMVC.dir/Response/Response.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyMVC.dir/Response/Response.cpp.o -c /home/anarion/Documents/MyProjects/MyMVC/Response/Response.cpp

CMakeFiles/MyMVC.dir/Response/Response.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyMVC.dir/Response/Response.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anarion/Documents/MyProjects/MyMVC/Response/Response.cpp > CMakeFiles/MyMVC.dir/Response/Response.cpp.i

CMakeFiles/MyMVC.dir/Response/Response.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyMVC.dir/Response/Response.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anarion/Documents/MyProjects/MyMVC/Response/Response.cpp -o CMakeFiles/MyMVC.dir/Response/Response.cpp.s

CMakeFiles/MyMVC.dir/Listener/Listener.cpp.o: CMakeFiles/MyMVC.dir/flags.make
CMakeFiles/MyMVC.dir/Listener/Listener.cpp.o: ../Listener/Listener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MyMVC.dir/Listener/Listener.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyMVC.dir/Listener/Listener.cpp.o -c /home/anarion/Documents/MyProjects/MyMVC/Listener/Listener.cpp

CMakeFiles/MyMVC.dir/Listener/Listener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyMVC.dir/Listener/Listener.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anarion/Documents/MyProjects/MyMVC/Listener/Listener.cpp > CMakeFiles/MyMVC.dir/Listener/Listener.cpp.i

CMakeFiles/MyMVC.dir/Listener/Listener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyMVC.dir/Listener/Listener.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anarion/Documents/MyProjects/MyMVC/Listener/Listener.cpp -o CMakeFiles/MyMVC.dir/Listener/Listener.cpp.s

# Object files for target MyMVC
MyMVC_OBJECTS = \
"CMakeFiles/MyMVC.dir/main.cpp.o" \
"CMakeFiles/MyMVC.dir/Request/Request.cpp.o" \
"CMakeFiles/MyMVC.dir/Response/Response.cpp.o" \
"CMakeFiles/MyMVC.dir/Listener/Listener.cpp.o"

# External object files for target MyMVC
MyMVC_EXTERNAL_OBJECTS =

MyMVC: CMakeFiles/MyMVC.dir/main.cpp.o
MyMVC: CMakeFiles/MyMVC.dir/Request/Request.cpp.o
MyMVC: CMakeFiles/MyMVC.dir/Response/Response.cpp.o
MyMVC: CMakeFiles/MyMVC.dir/Listener/Listener.cpp.o
MyMVC: CMakeFiles/MyMVC.dir/build.make
MyMVC: CMakeFiles/MyMVC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable MyMVC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyMVC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyMVC.dir/build: MyMVC

.PHONY : CMakeFiles/MyMVC.dir/build

CMakeFiles/MyMVC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyMVC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyMVC.dir/clean

CMakeFiles/MyMVC.dir/depend:
	cd /home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anarion/Documents/MyProjects/MyMVC /home/anarion/Documents/MyProjects/MyMVC /home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug /home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug /home/anarion/Documents/MyProjects/MyMVC/cmake-build-debug/CMakeFiles/MyMVC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyMVC.dir/depend

