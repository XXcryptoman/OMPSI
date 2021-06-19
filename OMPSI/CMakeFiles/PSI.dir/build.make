# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nan/OPRF-OMPSI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nan/OPRF-OMPSI

# Include any dependencies generated for this target.
include OMPSI/CMakeFiles/PSI.dir/depend.make

# Include the progress variables for this target.
include OMPSI/CMakeFiles/PSI.dir/progress.make

# Include the compile flags for this target's objects.
include OMPSI/CMakeFiles/PSI.dir/flags.make

OMPSI/CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.o: OMPSI/CMakeFiles/PSI.dir/flags.make
OMPSI/CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.o: OMPSI/src/ChaChaPermutation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nan/OPRF-OMPSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object OMPSI/CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.o"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.o -c /home/nan/OPRF-OMPSI/OMPSI/src/ChaChaPermutation.cpp

OMPSI/CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.i"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nan/OPRF-OMPSI/OMPSI/src/ChaChaPermutation.cpp > CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.i

OMPSI/CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.s"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nan/OPRF-OMPSI/OMPSI/src/ChaChaPermutation.cpp -o CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.s

OMPSI/CMakeFiles/PSI.dir/src/CuckooHasher.cpp.o: OMPSI/CMakeFiles/PSI.dir/flags.make
OMPSI/CMakeFiles/PSI.dir/src/CuckooHasher.cpp.o: OMPSI/src/CuckooHasher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nan/OPRF-OMPSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object OMPSI/CMakeFiles/PSI.dir/src/CuckooHasher.cpp.o"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSI.dir/src/CuckooHasher.cpp.o -c /home/nan/OPRF-OMPSI/OMPSI/src/CuckooHasher.cpp

OMPSI/CMakeFiles/PSI.dir/src/CuckooHasher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSI.dir/src/CuckooHasher.cpp.i"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nan/OPRF-OMPSI/OMPSI/src/CuckooHasher.cpp > CMakeFiles/PSI.dir/src/CuckooHasher.cpp.i

OMPSI/CMakeFiles/PSI.dir/src/CuckooHasher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSI.dir/src/CuckooHasher.cpp.s"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nan/OPRF-OMPSI/OMPSI/src/CuckooHasher.cpp -o CMakeFiles/PSI.dir/src/CuckooHasher.cpp.s

OMPSI/CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.o: OMPSI/CMakeFiles/PSI.dir/flags.make
OMPSI/CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.o: OMPSI/src/OMPsiReceiver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nan/OPRF-OMPSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object OMPSI/CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.o"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.o -c /home/nan/OPRF-OMPSI/OMPSI/src/OMPsiReceiver.cpp

OMPSI/CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.i"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nan/OPRF-OMPSI/OMPSI/src/OMPsiReceiver.cpp > CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.i

OMPSI/CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.s"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nan/OPRF-OMPSI/OMPSI/src/OMPsiReceiver.cpp -o CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.s

OMPSI/CMakeFiles/PSI.dir/src/OMPsiSender.cpp.o: OMPSI/CMakeFiles/PSI.dir/flags.make
OMPSI/CMakeFiles/PSI.dir/src/OMPsiSender.cpp.o: OMPSI/src/OMPsiSender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nan/OPRF-OMPSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object OMPSI/CMakeFiles/PSI.dir/src/OMPsiSender.cpp.o"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSI.dir/src/OMPsiSender.cpp.o -c /home/nan/OPRF-OMPSI/OMPSI/src/OMPsiSender.cpp

OMPSI/CMakeFiles/PSI.dir/src/OMPsiSender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSI.dir/src/OMPsiSender.cpp.i"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nan/OPRF-OMPSI/OMPSI/src/OMPsiSender.cpp > CMakeFiles/PSI.dir/src/OMPsiSender.cpp.i

OMPSI/CMakeFiles/PSI.dir/src/OMPsiSender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSI.dir/src/OMPsiSender.cpp.s"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nan/OPRF-OMPSI/OMPSI/src/OMPsiSender.cpp -o CMakeFiles/PSI.dir/src/OMPsiSender.cpp.s

OMPSI/CMakeFiles/PSI.dir/src/utils.cpp.o: OMPSI/CMakeFiles/PSI.dir/flags.make
OMPSI/CMakeFiles/PSI.dir/src/utils.cpp.o: OMPSI/src/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nan/OPRF-OMPSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object OMPSI/CMakeFiles/PSI.dir/src/utils.cpp.o"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSI.dir/src/utils.cpp.o -c /home/nan/OPRF-OMPSI/OMPSI/src/utils.cpp

OMPSI/CMakeFiles/PSI.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSI.dir/src/utils.cpp.i"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nan/OPRF-OMPSI/OMPSI/src/utils.cpp > CMakeFiles/PSI.dir/src/utils.cpp.i

OMPSI/CMakeFiles/PSI.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSI.dir/src/utils.cpp.s"
	cd /home/nan/OPRF-OMPSI/OMPSI && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nan/OPRF-OMPSI/OMPSI/src/utils.cpp -o CMakeFiles/PSI.dir/src/utils.cpp.s

# Object files for target PSI
PSI_OBJECTS = \
"CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.o" \
"CMakeFiles/PSI.dir/src/CuckooHasher.cpp.o" \
"CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.o" \
"CMakeFiles/PSI.dir/src/OMPsiSender.cpp.o" \
"CMakeFiles/PSI.dir/src/utils.cpp.o"

# External object files for target PSI
PSI_EXTERNAL_OBJECTS =

lib/libPSI.a: OMPSI/CMakeFiles/PSI.dir/src/ChaChaPermutation.cpp.o
lib/libPSI.a: OMPSI/CMakeFiles/PSI.dir/src/CuckooHasher.cpp.o
lib/libPSI.a: OMPSI/CMakeFiles/PSI.dir/src/OMPsiReceiver.cpp.o
lib/libPSI.a: OMPSI/CMakeFiles/PSI.dir/src/OMPsiSender.cpp.o
lib/libPSI.a: OMPSI/CMakeFiles/PSI.dir/src/utils.cpp.o
lib/libPSI.a: OMPSI/CMakeFiles/PSI.dir/build.make
lib/libPSI.a: OMPSI/CMakeFiles/PSI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nan/OPRF-OMPSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library ../lib/libPSI.a"
	cd /home/nan/OPRF-OMPSI/OMPSI && $(CMAKE_COMMAND) -P CMakeFiles/PSI.dir/cmake_clean_target.cmake
	cd /home/nan/OPRF-OMPSI/OMPSI && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PSI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
OMPSI/CMakeFiles/PSI.dir/build: lib/libPSI.a

.PHONY : OMPSI/CMakeFiles/PSI.dir/build

OMPSI/CMakeFiles/PSI.dir/clean:
	cd /home/nan/OPRF-OMPSI/OMPSI && $(CMAKE_COMMAND) -P CMakeFiles/PSI.dir/cmake_clean.cmake
.PHONY : OMPSI/CMakeFiles/PSI.dir/clean

OMPSI/CMakeFiles/PSI.dir/depend:
	cd /home/nan/OPRF-OMPSI && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nan/OPRF-OMPSI /home/nan/OPRF-OMPSI/OMPSI /home/nan/OPRF-OMPSI /home/nan/OPRF-OMPSI/OMPSI /home/nan/OPRF-OMPSI/OMPSI/CMakeFiles/PSI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : OMPSI/CMakeFiles/PSI.dir/depend

