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
CMAKE_SOURCE_DIR = /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control

# Utility rule file for control_autogen.

# Include any custom commands dependencies for this target.
include src/CMakeFiles/control_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/control_autogen.dir/progress.make

src/CMakeFiles/control_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/alumno/robocomp/components/Proyecto_Robotica/practica2/control/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target control"
	cd /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control/src && /usr/bin/cmake -E cmake_autogen /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control/src/CMakeFiles/control_autogen.dir/AutogenInfo.json Debug

control_autogen: src/CMakeFiles/control_autogen
control_autogen: src/CMakeFiles/control_autogen.dir/build.make
.PHONY : control_autogen

# Rule to build all files generated by this target.
src/CMakeFiles/control_autogen.dir/build: control_autogen
.PHONY : src/CMakeFiles/control_autogen.dir/build

src/CMakeFiles/control_autogen.dir/clean:
	cd /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control/src && $(CMAKE_COMMAND) -P CMakeFiles/control_autogen.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/control_autogen.dir/clean

src/CMakeFiles/control_autogen.dir/depend:
	cd /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control/src /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control/src /home/alumno/robocomp/components/Proyecto_Robotica/practica2/control/src/CMakeFiles/control_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/control_autogen.dir/depend

