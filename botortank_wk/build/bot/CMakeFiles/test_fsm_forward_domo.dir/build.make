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
CMAKE_SOURCE_DIR = /home/botortank/botortank_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/botortank/botortank_ws/build

# Include any dependencies generated for this target.
include bot/CMakeFiles/test_fsm_forward_domo.dir/depend.make

# Include the progress variables for this target.
include bot/CMakeFiles/test_fsm_forward_domo.dir/progress.make

# Include the compile flags for this target's objects.
include bot/CMakeFiles/test_fsm_forward_domo.dir/flags.make

bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o: bot/CMakeFiles/test_fsm_forward_domo.dir/flags.make
bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o: /home/botortank/botortank_ws/src/bot/src/test_fsm_forward_domo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/botortank/botortank_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o"
	cd /home/botortank/botortank_ws/build/bot && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o -c /home/botortank/botortank_ws/src/bot/src/test_fsm_forward_domo.cpp

bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.i"
	cd /home/botortank/botortank_ws/build/bot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/botortank/botortank_ws/src/bot/src/test_fsm_forward_domo.cpp > CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.i

bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.s"
	cd /home/botortank/botortank_ws/build/bot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/botortank/botortank_ws/src/bot/src/test_fsm_forward_domo.cpp -o CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.s

bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o.requires:

.PHONY : bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o.requires

bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o.provides: bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o.requires
	$(MAKE) -f bot/CMakeFiles/test_fsm_forward_domo.dir/build.make bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o.provides.build
.PHONY : bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o.provides

bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o.provides.build: bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o


# Object files for target test_fsm_forward_domo
test_fsm_forward_domo_OBJECTS = \
"CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o"

# External object files for target test_fsm_forward_domo
test_fsm_forward_domo_EXTERNAL_OBJECTS =

/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: bot/CMakeFiles/test_fsm_forward_domo.dir/build.make
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /opt/ros/kinetic/lib/libroscpp.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /opt/ros/kinetic/lib/librosconsole.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /opt/ros/kinetic/lib/librostime.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /opt/ros/kinetic/lib/libcpp_common.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libboost_atomic.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo: bot/CMakeFiles/test_fsm_forward_domo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/botortank/botortank_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo"
	cd /home/botortank/botortank_ws/build/bot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_fsm_forward_domo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bot/CMakeFiles/test_fsm_forward_domo.dir/build: /home/botortank/botortank_ws/devel/lib/bot/test_fsm_forward_domo

.PHONY : bot/CMakeFiles/test_fsm_forward_domo.dir/build

bot/CMakeFiles/test_fsm_forward_domo.dir/requires: bot/CMakeFiles/test_fsm_forward_domo.dir/src/test_fsm_forward_domo.cpp.o.requires

.PHONY : bot/CMakeFiles/test_fsm_forward_domo.dir/requires

bot/CMakeFiles/test_fsm_forward_domo.dir/clean:
	cd /home/botortank/botortank_ws/build/bot && $(CMAKE_COMMAND) -P CMakeFiles/test_fsm_forward_domo.dir/cmake_clean.cmake
.PHONY : bot/CMakeFiles/test_fsm_forward_domo.dir/clean

bot/CMakeFiles/test_fsm_forward_domo.dir/depend:
	cd /home/botortank/botortank_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/botortank/botortank_ws/src /home/botortank/botortank_ws/src/bot /home/botortank/botortank_ws/build /home/botortank/botortank_ws/build/bot /home/botortank/botortank_ws/build/bot/CMakeFiles/test_fsm_forward_domo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bot/CMakeFiles/test_fsm_forward_domo.dir/depend

