# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ahmadghanayem/CLionProjects/SquidGame-Final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SquidGame_Final.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/SquidGame_Final.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SquidGame_Final.dir/flags.make

CMakeFiles/SquidGame_Final.dir/main.cpp.o: CMakeFiles/SquidGame_Final.dir/flags.make
CMakeFiles/SquidGame_Final.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SquidGame_Final.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquidGame_Final.dir/main.cpp.o -c /Users/ahmadghanayem/CLionProjects/SquidGame-Final/main.cpp

CMakeFiles/SquidGame_Final.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquidGame_Final.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ahmadghanayem/CLionProjects/SquidGame-Final/main.cpp > CMakeFiles/SquidGame_Final.dir/main.cpp.i

CMakeFiles/SquidGame_Final.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquidGame_Final.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ahmadghanayem/CLionProjects/SquidGame-Final/main.cpp -o CMakeFiles/SquidGame_Final.dir/main.cpp.s

CMakeFiles/SquidGame_Final.dir/library2.cpp.o: CMakeFiles/SquidGame_Final.dir/flags.make
CMakeFiles/SquidGame_Final.dir/library2.cpp.o: ../library2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SquidGame_Final.dir/library2.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquidGame_Final.dir/library2.cpp.o -c /Users/ahmadghanayem/CLionProjects/SquidGame-Final/library2.cpp

CMakeFiles/SquidGame_Final.dir/library2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquidGame_Final.dir/library2.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ahmadghanayem/CLionProjects/SquidGame-Final/library2.cpp > CMakeFiles/SquidGame_Final.dir/library2.cpp.i

CMakeFiles/SquidGame_Final.dir/library2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquidGame_Final.dir/library2.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ahmadghanayem/CLionProjects/SquidGame-Final/library2.cpp -o CMakeFiles/SquidGame_Final.dir/library2.cpp.s

CMakeFiles/SquidGame_Final.dir/Player.cpp.o: CMakeFiles/SquidGame_Final.dir/flags.make
CMakeFiles/SquidGame_Final.dir/Player.cpp.o: ../Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SquidGame_Final.dir/Player.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquidGame_Final.dir/Player.cpp.o -c /Users/ahmadghanayem/CLionProjects/SquidGame-Final/Player.cpp

CMakeFiles/SquidGame_Final.dir/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquidGame_Final.dir/Player.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ahmadghanayem/CLionProjects/SquidGame-Final/Player.cpp > CMakeFiles/SquidGame_Final.dir/Player.cpp.i

CMakeFiles/SquidGame_Final.dir/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquidGame_Final.dir/Player.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ahmadghanayem/CLionProjects/SquidGame-Final/Player.cpp -o CMakeFiles/SquidGame_Final.dir/Player.cpp.s

CMakeFiles/SquidGame_Final.dir/Group.cpp.o: CMakeFiles/SquidGame_Final.dir/flags.make
CMakeFiles/SquidGame_Final.dir/Group.cpp.o: ../Group.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SquidGame_Final.dir/Group.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquidGame_Final.dir/Group.cpp.o -c /Users/ahmadghanayem/CLionProjects/SquidGame-Final/Group.cpp

CMakeFiles/SquidGame_Final.dir/Group.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquidGame_Final.dir/Group.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ahmadghanayem/CLionProjects/SquidGame-Final/Group.cpp > CMakeFiles/SquidGame_Final.dir/Group.cpp.i

CMakeFiles/SquidGame_Final.dir/Group.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquidGame_Final.dir/Group.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ahmadghanayem/CLionProjects/SquidGame-Final/Group.cpp -o CMakeFiles/SquidGame_Final.dir/Group.cpp.s

CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.o: CMakeFiles/SquidGame_Final.dir/flags.make
CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.o: ../SquidGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.o -c /Users/ahmadghanayem/CLionProjects/SquidGame-Final/SquidGame.cpp

CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ahmadghanayem/CLionProjects/SquidGame-Final/SquidGame.cpp > CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.i

CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ahmadghanayem/CLionProjects/SquidGame-Final/SquidGame.cpp -o CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.s

# Object files for target SquidGame_Final
SquidGame_Final_OBJECTS = \
"CMakeFiles/SquidGame_Final.dir/main.cpp.o" \
"CMakeFiles/SquidGame_Final.dir/library2.cpp.o" \
"CMakeFiles/SquidGame_Final.dir/Player.cpp.o" \
"CMakeFiles/SquidGame_Final.dir/Group.cpp.o" \
"CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.o"

# External object files for target SquidGame_Final
SquidGame_Final_EXTERNAL_OBJECTS =

SquidGame_Final: CMakeFiles/SquidGame_Final.dir/main.cpp.o
SquidGame_Final: CMakeFiles/SquidGame_Final.dir/library2.cpp.o
SquidGame_Final: CMakeFiles/SquidGame_Final.dir/Player.cpp.o
SquidGame_Final: CMakeFiles/SquidGame_Final.dir/Group.cpp.o
SquidGame_Final: CMakeFiles/SquidGame_Final.dir/SquidGame.cpp.o
SquidGame_Final: CMakeFiles/SquidGame_Final.dir/build.make
SquidGame_Final: CMakeFiles/SquidGame_Final.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable SquidGame_Final"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SquidGame_Final.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SquidGame_Final.dir/build: SquidGame_Final
.PHONY : CMakeFiles/SquidGame_Final.dir/build

CMakeFiles/SquidGame_Final.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SquidGame_Final.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SquidGame_Final.dir/clean

CMakeFiles/SquidGame_Final.dir/depend:
	cd /Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ahmadghanayem/CLionProjects/SquidGame-Final /Users/ahmadghanayem/CLionProjects/SquidGame-Final /Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug /Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug /Users/ahmadghanayem/CLionProjects/SquidGame-Final/cmake-build-debug/CMakeFiles/SquidGame_Final.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SquidGame_Final.dir/depend

