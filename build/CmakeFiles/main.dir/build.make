# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/zizou/aman(v.3)"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/zizou/aman(v.3)/build"

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/waktu.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/waktu.c.o: ../waktu.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/waktu.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/waktu.c.o   -c "/home/zizou/aman(v.3)/waktu.c"

CMakeFiles/main.dir/waktu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/waktu.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/waktu.c" > CMakeFiles/main.dir/waktu.c.i

CMakeFiles/main.dir/waktu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/waktu.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/waktu.c" -o CMakeFiles/main.dir/waktu.c.s

CMakeFiles/main.dir/waktu.c.o.requires:
.PHONY : CMakeFiles/main.dir/waktu.c.o.requires

CMakeFiles/main.dir/waktu.c.o.provides: CMakeFiles/main.dir/waktu.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/waktu.c.o.provides.build
.PHONY : CMakeFiles/main.dir/waktu.c.o.provides

CMakeFiles/main.dir/waktu.c.o.provides.build: CMakeFiles/main.dir/waktu.c.o
.PHONY : CMakeFiles/main.dir/waktu.c.o.provides.build

CMakeFiles/main.dir/modif.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/modif.c.o: ../modif.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/modif.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/modif.c.o   -c "/home/zizou/aman(v.3)/modif.c"

CMakeFiles/main.dir/modif.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/modif.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/modif.c" > CMakeFiles/main.dir/modif.c.i

CMakeFiles/main.dir/modif.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/modif.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/modif.c" -o CMakeFiles/main.dir/modif.c.s

CMakeFiles/main.dir/modif.c.o.requires:
.PHONY : CMakeFiles/main.dir/modif.c.o.requires

CMakeFiles/main.dir/modif.c.o.provides: CMakeFiles/main.dir/modif.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/modif.c.o.provides.build
.PHONY : CMakeFiles/main.dir/modif.c.o.provides

CMakeFiles/main.dir/modif.c.o.provides.build: CMakeFiles/main.dir/modif.c.o
.PHONY : CMakeFiles/main.dir/modif.c.o.provides.build

CMakeFiles/main.dir/tool.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/tool.c.o: ../tool.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/tool.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/tool.c.o   -c "/home/zizou/aman(v.3)/tool.c"

CMakeFiles/main.dir/tool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/tool.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/tool.c" > CMakeFiles/main.dir/tool.c.i

CMakeFiles/main.dir/tool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/tool.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/tool.c" -o CMakeFiles/main.dir/tool.c.s

CMakeFiles/main.dir/tool.c.o.requires:
.PHONY : CMakeFiles/main.dir/tool.c.o.requires

CMakeFiles/main.dir/tool.c.o.provides: CMakeFiles/main.dir/tool.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/tool.c.o.provides.build
.PHONY : CMakeFiles/main.dir/tool.c.o.provides

CMakeFiles/main.dir/tool.c.o.provides.build: CMakeFiles/main.dir/tool.c.o
.PHONY : CMakeFiles/main.dir/tool.c.o.provides.build

CMakeFiles/main.dir/child.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/child.c.o: ../child.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/child.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/child.c.o   -c "/home/zizou/aman(v.3)/child.c"

CMakeFiles/main.dir/child.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/child.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/child.c" > CMakeFiles/main.dir/child.c.i

CMakeFiles/main.dir/child.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/child.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/child.c" -o CMakeFiles/main.dir/child.c.s

CMakeFiles/main.dir/child.c.o.requires:
.PHONY : CMakeFiles/main.dir/child.c.o.requires

CMakeFiles/main.dir/child.c.o.provides: CMakeFiles/main.dir/child.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/child.c.o.provides.build
.PHONY : CMakeFiles/main.dir/child.c.o.provides

CMakeFiles/main.dir/child.c.o.provides.build: CMakeFiles/main.dir/child.c.o
.PHONY : CMakeFiles/main.dir/child.c.o.provides.build

CMakeFiles/main.dir/setting.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/setting.c.o: ../setting.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/setting.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/setting.c.o   -c "/home/zizou/aman(v.3)/setting.c"

CMakeFiles/main.dir/setting.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/setting.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/setting.c" > CMakeFiles/main.dir/setting.c.i

CMakeFiles/main.dir/setting.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/setting.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/setting.c" -o CMakeFiles/main.dir/setting.c.s

CMakeFiles/main.dir/setting.c.o.requires:
.PHONY : CMakeFiles/main.dir/setting.c.o.requires

CMakeFiles/main.dir/setting.c.o.provides: CMakeFiles/main.dir/setting.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/setting.c.o.provides.build
.PHONY : CMakeFiles/main.dir/setting.c.o.provides

CMakeFiles/main.dir/setting.c.o.provides.build: CMakeFiles/main.dir/setting.c.o
.PHONY : CMakeFiles/main.dir/setting.c.o.provides.build

CMakeFiles/main.dir/alarm.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/alarm.c.o: ../alarm.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/alarm.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/alarm.c.o   -c "/home/zizou/aman(v.3)/alarm.c"

CMakeFiles/main.dir/alarm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/alarm.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/alarm.c" > CMakeFiles/main.dir/alarm.c.i

CMakeFiles/main.dir/alarm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/alarm.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/alarm.c" -o CMakeFiles/main.dir/alarm.c.s

CMakeFiles/main.dir/alarm.c.o.requires:
.PHONY : CMakeFiles/main.dir/alarm.c.o.requires

CMakeFiles/main.dir/alarm.c.o.provides: CMakeFiles/main.dir/alarm.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/alarm.c.o.provides.build
.PHONY : CMakeFiles/main.dir/alarm.c.o.provides

CMakeFiles/main.dir/alarm.c.o.provides.build: CMakeFiles/main.dir/alarm.c.o
.PHONY : CMakeFiles/main.dir/alarm.c.o.provides.build

CMakeFiles/main.dir/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.c.o: ../main.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/main.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/main.c.o   -c "/home/zizou/aman(v.3)/main.c"

CMakeFiles/main.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/main.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/main.c" > CMakeFiles/main.dir/main.c.i

CMakeFiles/main.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/main.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/main.c" -o CMakeFiles/main.dir/main.c.s

CMakeFiles/main.dir/main.c.o.requires:
.PHONY : CMakeFiles/main.dir/main.c.o.requires

CMakeFiles/main.dir/main.c.o.provides: CMakeFiles/main.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.c.o.provides.build
.PHONY : CMakeFiles/main.dir/main.c.o.provides

CMakeFiles/main.dir/main.c.o.provides.build: CMakeFiles/main.dir/main.c.o
.PHONY : CMakeFiles/main.dir/main.c.o.provides.build

CMakeFiles/main.dir/global.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/global.c.o: ../global.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/global.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/global.c.o   -c "/home/zizou/aman(v.3)/global.c"

CMakeFiles/main.dir/global.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/global.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/global.c" > CMakeFiles/main.dir/global.c.i

CMakeFiles/main.dir/global.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/global.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/global.c" -o CMakeFiles/main.dir/global.c.s

CMakeFiles/main.dir/global.c.o.requires:
.PHONY : CMakeFiles/main.dir/global.c.o.requires

CMakeFiles/main.dir/global.c.o.provides: CMakeFiles/main.dir/global.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/global.c.o.provides.build
.PHONY : CMakeFiles/main.dir/global.c.o.provides

CMakeFiles/main.dir/global.c.o.provides.build: CMakeFiles/main.dir/global.c.o
.PHONY : CMakeFiles/main.dir/global.c.o.provides.build

CMakeFiles/main.dir/sound.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/sound.c.o: ../sound.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/sound.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/sound.c.o   -c "/home/zizou/aman(v.3)/sound.c"

CMakeFiles/main.dir/sound.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/sound.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/sound.c" > CMakeFiles/main.dir/sound.c.i

CMakeFiles/main.dir/sound.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/sound.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/sound.c" -o CMakeFiles/main.dir/sound.c.s

CMakeFiles/main.dir/sound.c.o.requires:
.PHONY : CMakeFiles/main.dir/sound.c.o.requires

CMakeFiles/main.dir/sound.c.o.provides: CMakeFiles/main.dir/sound.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/sound.c.o.provides.build
.PHONY : CMakeFiles/main.dir/sound.c.o.provides

CMakeFiles/main.dir/sound.c.o.provides.build: CMakeFiles/main.dir/sound.c.o
.PHONY : CMakeFiles/main.dir/sound.c.o.provides.build

CMakeFiles/main.dir/database_.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/database_.c.o: ../database_.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/database_.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/database_.c.o   -c "/home/zizou/aman(v.3)/database_.c"

CMakeFiles/main.dir/database_.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/database_.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/database_.c" > CMakeFiles/main.dir/database_.c.i

CMakeFiles/main.dir/database_.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/database_.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/database_.c" -o CMakeFiles/main.dir/database_.c.s

CMakeFiles/main.dir/database_.c.o.requires:
.PHONY : CMakeFiles/main.dir/database_.c.o.requires

CMakeFiles/main.dir/database_.c.o.provides: CMakeFiles/main.dir/database_.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/database_.c.o.provides.build
.PHONY : CMakeFiles/main.dir/database_.c.o.provides

CMakeFiles/main.dir/database_.c.o.provides.build: CMakeFiles/main.dir/database_.c.o
.PHONY : CMakeFiles/main.dir/database_.c.o.provides.build

CMakeFiles/main.dir/tray.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/tray.c.o: ../tray.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/tray.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/tray.c.o   -c "/home/zizou/aman(v.3)/tray.c"

CMakeFiles/main.dir/tray.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/tray.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/tray.c" > CMakeFiles/main.dir/tray.c.i

CMakeFiles/main.dir/tray.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/tray.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/tray.c" -o CMakeFiles/main.dir/tray.c.s

CMakeFiles/main.dir/tray.c.o.requires:
.PHONY : CMakeFiles/main.dir/tray.c.o.requires

CMakeFiles/main.dir/tray.c.o.provides: CMakeFiles/main.dir/tray.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/tray.c.o.provides.build
.PHONY : CMakeFiles/main.dir/tray.c.o.provides

CMakeFiles/main.dir/tray.c.o.provides.build: CMakeFiles/main.dir/tray.c.o
.PHONY : CMakeFiles/main.dir/tray.c.o.provides.build

CMakeFiles/main.dir/table.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/table.c.o: ../table.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/table.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/table.c.o   -c "/home/zizou/aman(v.3)/table.c"

CMakeFiles/main.dir/table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/table.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/table.c" > CMakeFiles/main.dir/table.c.i

CMakeFiles/main.dir/table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/table.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/table.c" -o CMakeFiles/main.dir/table.c.s

CMakeFiles/main.dir/table.c.o.requires:
.PHONY : CMakeFiles/main.dir/table.c.o.requires

CMakeFiles/main.dir/table.c.o.provides: CMakeFiles/main.dir/table.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/table.c.o.provides.build
.PHONY : CMakeFiles/main.dir/table.c.o.provides

CMakeFiles/main.dir/table.c.o.provides.build: CMakeFiles/main.dir/table.c.o
.PHONY : CMakeFiles/main.dir/table.c.o.provides.build

CMakeFiles/main.dir/local.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/local.c.o: ../local.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/local.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/local.c.o   -c "/home/zizou/aman(v.3)/local.c"

CMakeFiles/main.dir/local.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/local.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/local.c" > CMakeFiles/main.dir/local.c.i

CMakeFiles/main.dir/local.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/local.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/local.c" -o CMakeFiles/main.dir/local.c.s

CMakeFiles/main.dir/local.c.o.requires:
.PHONY : CMakeFiles/main.dir/local.c.o.requires

CMakeFiles/main.dir/local.c.o.provides: CMakeFiles/main.dir/local.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/local.c.o.provides.build
.PHONY : CMakeFiles/main.dir/local.c.o.provides

CMakeFiles/main.dir/local.c.o.provides.build: CMakeFiles/main.dir/local.c.o
.PHONY : CMakeFiles/main.dir/local.c.o.provides.build

CMakeFiles/main.dir/dbCreate.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/dbCreate.c.o: ../dbCreate.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/dbCreate.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/dbCreate.c.o   -c "/home/zizou/aman(v.3)/dbCreate.c"

CMakeFiles/main.dir/dbCreate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/dbCreate.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/dbCreate.c" > CMakeFiles/main.dir/dbCreate.c.i

CMakeFiles/main.dir/dbCreate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/dbCreate.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/dbCreate.c" -o CMakeFiles/main.dir/dbCreate.c.s

CMakeFiles/main.dir/dbCreate.c.o.requires:
.PHONY : CMakeFiles/main.dir/dbCreate.c.o.requires

CMakeFiles/main.dir/dbCreate.c.o.provides: CMakeFiles/main.dir/dbCreate.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/dbCreate.c.o.provides.build
.PHONY : CMakeFiles/main.dir/dbCreate.c.o.provides

CMakeFiles/main.dir/dbCreate.c.o.provides.build: CMakeFiles/main.dir/dbCreate.c.o
.PHONY : CMakeFiles/main.dir/dbCreate.c.o.provides.build

CMakeFiles/main.dir/menu.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/menu.c.o: ../menu.c
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/zizou/aman(v.3)/build/CMakeFiles" $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/menu.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/menu.c.o   -c "/home/zizou/aman(v.3)/menu.c"

CMakeFiles/main.dir/menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/menu.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E "/home/zizou/aman(v.3)/menu.c" > CMakeFiles/main.dir/menu.c.i

CMakeFiles/main.dir/menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/menu.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S "/home/zizou/aman(v.3)/menu.c" -o CMakeFiles/main.dir/menu.c.s

CMakeFiles/main.dir/menu.c.o.requires:
.PHONY : CMakeFiles/main.dir/menu.c.o.requires

CMakeFiles/main.dir/menu.c.o.provides: CMakeFiles/main.dir/menu.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/menu.c.o.provides.build
.PHONY : CMakeFiles/main.dir/menu.c.o.provides

CMakeFiles/main.dir/menu.c.o.provides.build: CMakeFiles/main.dir/menu.c.o
.PHONY : CMakeFiles/main.dir/menu.c.o.provides.build

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/waktu.c.o" \
"CMakeFiles/main.dir/modif.c.o" \
"CMakeFiles/main.dir/tool.c.o" \
"CMakeFiles/main.dir/child.c.o" \
"CMakeFiles/main.dir/setting.c.o" \
"CMakeFiles/main.dir/alarm.c.o" \
"CMakeFiles/main.dir/main.c.o" \
"CMakeFiles/main.dir/global.c.o" \
"CMakeFiles/main.dir/sound.c.o" \
"CMakeFiles/main.dir/database_.c.o" \
"CMakeFiles/main.dir/tray.c.o" \
"CMakeFiles/main.dir/table.c.o" \
"CMakeFiles/main.dir/local.c.o" \
"CMakeFiles/main.dir/dbCreate.c.o" \
"CMakeFiles/main.dir/menu.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/waktu.c.o
main: CMakeFiles/main.dir/modif.c.o
main: CMakeFiles/main.dir/tool.c.o
main: CMakeFiles/main.dir/child.c.o
main: CMakeFiles/main.dir/setting.c.o
main: CMakeFiles/main.dir/alarm.c.o
main: CMakeFiles/main.dir/main.c.o
main: CMakeFiles/main.dir/global.c.o
main: CMakeFiles/main.dir/sound.c.o
main: CMakeFiles/main.dir/database_.c.o
main: CMakeFiles/main.dir/tray.c.o
main: CMakeFiles/main.dir/table.c.o
main: CMakeFiles/main.dir/local.c.o
main: CMakeFiles/main.dir/dbCreate.c.o
main: CMakeFiles/main.dir/menu.c.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/waktu.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/modif.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/tool.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/child.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/setting.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/alarm.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/global.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/sound.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/database_.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/tray.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/table.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/local.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/dbCreate.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/menu.c.o.requires
.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd "/home/zizou/aman(v.3)/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/zizou/aman(v.3)" "/home/zizou/aman(v.3)" "/home/zizou/aman(v.3)/build" "/home/zizou/aman(v.3)/build" "/home/zizou/aman(v.3)/build/CMakeFiles/main.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

