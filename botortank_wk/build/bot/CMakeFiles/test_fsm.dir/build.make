# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/sayri/botortank/botortank_wk/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sayri/botortank/botortank_wk/build

# Include any dependencies generated for this target.
include bot/CMakeFiles/test_fsm.dir/depend.make

# Include the progress variables for this target.
include bot/CMakeFiles/test_fsm.dir/progress.make

# Include the compile flags for this target's objects.
include bot/CMakeFiles/test_fsm.dir/flags.make

bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o: bot/CMakeFiles/test_fsm.dir/flags.make
bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o: /home/sayri/botortank/botortank_wk/src/bot/src/test_fsm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sayri/botortank/botortank_wk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o"
	cd /home/sayri/botortank/botortank_wk/build/bot && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o -c /home/sayri/botortank/botortank_wk/src/bot/src/test_fsm.cpp

bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_fsm.dir/src/test_fsm.cpp.i"
	cd /home/sayri/botortank/botortank_wk/build/bot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sayri/botortank/botortank_wk/src/bot/src/test_fsm.cpp > CMakeFiles/test_fsm.dir/src/test_fsm.cpp.i

bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_fsm.dir/src/test_fsm.cpp.s"
	cd /home/sayri/botortank/botortank_wk/build/bot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sayri/botortank/botortank_wk/src/bot/src/test_fsm.cpp -o CMakeFiles/test_fsm.dir/src/test_fsm.cpp.s

bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o.requires:

.PHONY : bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o.requires

bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o.provides: bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o.requires
	$(MAKE) -f bot/CMakeFiles/test_fsm.dir/build.make bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o.provides.build
.PHONY : bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o.provides

bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o.provides.build: bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o


# Object files for target test_fsm
test_fsm_OBJECTS = \
"CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o"

# External object files for target test_fsm
test_fsm_EXTERNAL_OBJECTS =

/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: bot/CMakeFiles/test_fsm.dir/build.make
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /opt/ros/lunar/lib/libroscpp.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /opt/ros/lunar/lib/librosconsole.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /opt/ros/lunar/lib/librosconsole_log4cxx.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /opt/ros/lunar/lib/librosconsole_backend_interface.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /opt/ros/lunar/lib/libxmlrpcpp.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /opt/ros/lunar/lib/libroscpp_serialization.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /opt/ros/lunar/lib/librostime.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /opt/ros/lunar/lib/libcpp_common.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm: bot/CMakeFiles/test_fsm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sayri/botortank/botortank_wk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm"
	cd /home/sayri/botortank/botortank_wk/build/bot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_fsm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bot/CMakeFiles/test_fsm.dir/build: /home/sayri/botortank/botortank_wk/devel/lib/bot/test_fsm

.PHONY : bot/CMakeFiles/test_fsm.dir/build

bot/CMakeFiles/test_fsm.dir/requires: bot/CMakeFiles/test_fsm.dir/src/test_fsm.cpp.o.requires

.PHONY : bot/CMakeFiles/test_fsm.dir/requires

bot/CMakeFiles/test_fsm.dir/clean:
	cd /home/sayri/botortank/botortank_wk/build/bot && $(CMAKE_COMMAND) -P CMakeFiles/test_fsm.dir/cmake_clean.cmake
.PHONY : bot/CMakeFiles/test_fsm.dir/clean

bot/CMakeFiles/test_fsm.dir/depend:
	cd /home/sayri/botortank/botortank_wk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sayri/botortank/botortank_wk/src /home/sayri/botortank/botortank_wk/src/bot /home/sayri/botortank/botortank_wk/build /home/sayri/botortank/botortank_wk/build/bot /home/sayri/botortank/botortank_wk/build/bot/CMakeFiles/test_fsm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bot/CMakeFiles/test_fsm.dir/depend
