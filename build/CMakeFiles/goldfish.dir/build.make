# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/workspace/goldfish/final-project-Lightningtow

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/goldfish/final-project-Lightningtow/build

# Include any dependencies generated for this target.
include CMakeFiles/goldfish.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/goldfish.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/goldfish.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/goldfish.dir/flags.make

CMakeFiles/goldfish.dir/src/main.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/goldfish.dir/src/main.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/goldfish.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/main.cpp.o -MF CMakeFiles/goldfish.dir/src/main.cpp.o.d -o CMakeFiles/goldfish.dir/src/main.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/main.cpp

CMakeFiles/goldfish.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/main.cpp > CMakeFiles/goldfish.dir/src/main.cpp.i

CMakeFiles/goldfish.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/main.cpp -o CMakeFiles/goldfish.dir/src/main.cpp.s

CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o: ../src/Goldfish/Goldfish.cpp
CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o -MF CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o.d -o CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/Goldfish.cpp

CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/Goldfish.cpp > CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.i

CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/Goldfish.cpp -o CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.s

CMakeFiles/goldfish.dir/src/Card.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/Card.cpp.o: ../src/Card.cpp
CMakeFiles/goldfish.dir/src/Card.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/goldfish.dir/src/Card.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/Card.cpp.o -MF CMakeFiles/goldfish.dir/src/Card.cpp.o.d -o CMakeFiles/goldfish.dir/src/Card.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/Card.cpp

CMakeFiles/goldfish.dir/src/Card.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/Card.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/Card.cpp > CMakeFiles/goldfish.dir/src/Card.cpp.i

CMakeFiles/goldfish.dir/src/Card.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/Card.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/Card.cpp -o CMakeFiles/goldfish.dir/src/Card.cpp.s

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o: ../src/Goldfish/goldfish_cardData.cpp
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o -MF CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o.d -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_cardData.cpp

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_cardData.cpp > CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.i

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_cardData.cpp -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.s

CMakeFiles/goldfish.dir/src/GameResult.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/GameResult.cpp.o: ../src/GameResult.cpp
CMakeFiles/goldfish.dir/src/GameResult.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/goldfish.dir/src/GameResult.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/GameResult.cpp.o -MF CMakeFiles/goldfish.dir/src/GameResult.cpp.o.d -o CMakeFiles/goldfish.dir/src/GameResult.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/GameResult.cpp

CMakeFiles/goldfish.dir/src/GameResult.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/GameResult.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/GameResult.cpp > CMakeFiles/goldfish.dir/src/GameResult.cpp.i

CMakeFiles/goldfish.dir/src/GameResult.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/GameResult.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/GameResult.cpp -o CMakeFiles/goldfish.dir/src/GameResult.cpp.s

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o: ../src/Goldfish/goldfish_gameFuncs.cpp
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o -MF CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o.d -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_gameFuncs.cpp

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_gameFuncs.cpp > CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.i

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_gameFuncs.cpp -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.s

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o: ../src/Goldfish/goldfish_interface.cpp
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o -MF CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o.d -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_interface.cpp

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_interface.cpp > CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.i

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_interface.cpp -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.s

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o: ../src/Goldfish/goldfish_landFuncs.cpp
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o -MF CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o.d -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_landFuncs.cpp

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_landFuncs.cpp > CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.i

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_landFuncs.cpp -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.s

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o: CMakeFiles/goldfish.dir/flags.make
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o: ../src/Goldfish/goldfish_fileFuncs.cpp
CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o: CMakeFiles/goldfish.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o -MF CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o.d -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o -c /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_fileFuncs.cpp

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_fileFuncs.cpp > CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.i

CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/goldfish/final-project-Lightningtow/src/Goldfish/goldfish_fileFuncs.cpp -o CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.s

# Object files for target goldfish
goldfish_OBJECTS = \
"CMakeFiles/goldfish.dir/src/main.cpp.o" \
"CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o" \
"CMakeFiles/goldfish.dir/src/Card.cpp.o" \
"CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o" \
"CMakeFiles/goldfish.dir/src/GameResult.cpp.o" \
"CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o" \
"CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o" \
"CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o" \
"CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o"

# External object files for target goldfish
goldfish_EXTERNAL_OBJECTS =

goldfish: CMakeFiles/goldfish.dir/src/main.cpp.o
goldfish: CMakeFiles/goldfish.dir/src/Goldfish/Goldfish.cpp.o
goldfish: CMakeFiles/goldfish.dir/src/Card.cpp.o
goldfish: CMakeFiles/goldfish.dir/src/Goldfish/goldfish_cardData.cpp.o
goldfish: CMakeFiles/goldfish.dir/src/GameResult.cpp.o
goldfish: CMakeFiles/goldfish.dir/src/Goldfish/goldfish_gameFuncs.cpp.o
goldfish: CMakeFiles/goldfish.dir/src/Goldfish/goldfish_interface.cpp.o
goldfish: CMakeFiles/goldfish.dir/src/Goldfish/goldfish_landFuncs.cpp.o
goldfish: CMakeFiles/goldfish.dir/src/Goldfish/goldfish_fileFuncs.cpp.o
goldfish: CMakeFiles/goldfish.dir/build.make
goldfish: CMakeFiles/goldfish.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable goldfish"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/goldfish.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/goldfish.dir/build: goldfish
.PHONY : CMakeFiles/goldfish.dir/build

CMakeFiles/goldfish.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/goldfish.dir/cmake_clean.cmake
.PHONY : CMakeFiles/goldfish.dir/clean

CMakeFiles/goldfish.dir/depend:
	cd /root/workspace/goldfish/final-project-Lightningtow/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/goldfish/final-project-Lightningtow /root/workspace/goldfish/final-project-Lightningtow /root/workspace/goldfish/final-project-Lightningtow/build /root/workspace/goldfish/final-project-Lightningtow/build /root/workspace/goldfish/final-project-Lightningtow/build/CMakeFiles/goldfish.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/goldfish.dir/depend
