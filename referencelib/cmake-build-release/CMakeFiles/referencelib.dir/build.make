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
CMAKE_COMMAND = "/Users/anarion/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.5662.56/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/anarion/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.5662.56/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/anarion/Documents/MyProjects/referencelib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/anarion/Documents/MyProjects/referencelib/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/referencelib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/referencelib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/referencelib.dir/flags.make

CMakeFiles/referencelib.dir/main.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/referencelib.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/main.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/main.cpp

CMakeFiles/referencelib.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/main.cpp > CMakeFiles/referencelib.dir/main.cpp.i

CMakeFiles/referencelib.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/main.cpp -o CMakeFiles/referencelib.dir/main.cpp.s

CMakeFiles/referencelib.dir/base/Object.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/base/Object.cpp.o: ../base/Object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/referencelib.dir/base/Object.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/base/Object.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/base/Object.cpp

CMakeFiles/referencelib.dir/base/Object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/base/Object.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/base/Object.cpp > CMakeFiles/referencelib.dir/base/Object.cpp.i

CMakeFiles/referencelib.dir/base/Object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/base/Object.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/base/Object.cpp -o CMakeFiles/referencelib.dir/base/Object.cpp.s

CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.o: ../gc/GarbageCollector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/gc/GarbageCollector.cpp

CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/gc/GarbageCollector.cpp > CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.i

CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/gc/GarbageCollector.cpp -o CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.s

CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.o: ../concurrent/base/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/Thread.cpp

CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/Thread.cpp > CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.i

CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/Thread.cpp -o CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.s

CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.o: ../concurrent/base/Mutex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/Mutex.cpp

CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/Mutex.cpp > CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.i

CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/Mutex.cpp -o CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.s

CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.o: ../concurrent/base/CondVar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/CondVar.cpp

CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/CondVar.cpp > CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.i

CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/concurrent/base/CondVar.cpp -o CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.s

CMakeFiles/referencelib.dir/base/HashFunctions.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/base/HashFunctions.cpp.o: ../base/HashFunctions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/referencelib.dir/base/HashFunctions.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/base/HashFunctions.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/base/HashFunctions.cpp

CMakeFiles/referencelib.dir/base/HashFunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/base/HashFunctions.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/base/HashFunctions.cpp > CMakeFiles/referencelib.dir/base/HashFunctions.cpp.i

CMakeFiles/referencelib.dir/base/HashFunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/base/HashFunctions.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/base/HashFunctions.cpp -o CMakeFiles/referencelib.dir/base/HashFunctions.cpp.s

CMakeFiles/referencelib.dir/container/SString.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/container/SString.cpp.o: ../container/SString.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/referencelib.dir/container/SString.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/container/SString.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/container/SString.cpp

CMakeFiles/referencelib.dir/container/SString.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/container/SString.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/container/SString.cpp > CMakeFiles/referencelib.dir/container/SString.cpp.i

CMakeFiles/referencelib.dir/container/SString.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/container/SString.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/container/SString.cpp -o CMakeFiles/referencelib.dir/container/SString.cpp.s

CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.o: ../io/Buffer/Buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/io/Buffer/Buffer.cpp

CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/io/Buffer/Buffer.cpp > CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.i

CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/io/Buffer/Buffer.cpp -o CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.s

CMakeFiles/referencelib.dir/allocator/Allocator.cpp.o: CMakeFiles/referencelib.dir/flags.make
CMakeFiles/referencelib.dir/allocator/Allocator.cpp.o: ../allocator/Allocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/referencelib.dir/allocator/Allocator.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/referencelib.dir/allocator/Allocator.cpp.o -c /Users/anarion/Documents/MyProjects/referencelib/allocator/Allocator.cpp

CMakeFiles/referencelib.dir/allocator/Allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/referencelib.dir/allocator/Allocator.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anarion/Documents/MyProjects/referencelib/allocator/Allocator.cpp > CMakeFiles/referencelib.dir/allocator/Allocator.cpp.i

CMakeFiles/referencelib.dir/allocator/Allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/referencelib.dir/allocator/Allocator.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anarion/Documents/MyProjects/referencelib/allocator/Allocator.cpp -o CMakeFiles/referencelib.dir/allocator/Allocator.cpp.s

# Object files for target referencelib
referencelib_OBJECTS = \
"CMakeFiles/referencelib.dir/main.cpp.o" \
"CMakeFiles/referencelib.dir/base/Object.cpp.o" \
"CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.o" \
"CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.o" \
"CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.o" \
"CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.o" \
"CMakeFiles/referencelib.dir/base/HashFunctions.cpp.o" \
"CMakeFiles/referencelib.dir/container/SString.cpp.o" \
"CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.o" \
"CMakeFiles/referencelib.dir/allocator/Allocator.cpp.o"

# External object files for target referencelib
referencelib_EXTERNAL_OBJECTS =

referencelib: CMakeFiles/referencelib.dir/main.cpp.o
referencelib: CMakeFiles/referencelib.dir/base/Object.cpp.o
referencelib: CMakeFiles/referencelib.dir/gc/GarbageCollector.cpp.o
referencelib: CMakeFiles/referencelib.dir/concurrent/base/Thread.cpp.o
referencelib: CMakeFiles/referencelib.dir/concurrent/base/Mutex.cpp.o
referencelib: CMakeFiles/referencelib.dir/concurrent/base/CondVar.cpp.o
referencelib: CMakeFiles/referencelib.dir/base/HashFunctions.cpp.o
referencelib: CMakeFiles/referencelib.dir/container/SString.cpp.o
referencelib: CMakeFiles/referencelib.dir/io/Buffer/Buffer.cpp.o
referencelib: CMakeFiles/referencelib.dir/allocator/Allocator.cpp.o
referencelib: CMakeFiles/referencelib.dir/build.make
referencelib: CMakeFiles/referencelib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable referencelib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/referencelib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/referencelib.dir/build: referencelib

.PHONY : CMakeFiles/referencelib.dir/build

CMakeFiles/referencelib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/referencelib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/referencelib.dir/clean

CMakeFiles/referencelib.dir/depend:
	cd /Users/anarion/Documents/MyProjects/referencelib/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anarion/Documents/MyProjects/referencelib /Users/anarion/Documents/MyProjects/referencelib /Users/anarion/Documents/MyProjects/referencelib/cmake-build-release /Users/anarion/Documents/MyProjects/referencelib/cmake-build-release /Users/anarion/Documents/MyProjects/referencelib/cmake-build-release/CMakeFiles/referencelib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/referencelib.dir/depend
