# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jason/dev/chordical-plugin/Builds/CLion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jason/dev/chordical-plugin/Builds/CLion/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/VST3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VST3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VST3.dir/flags.make

chordical-plugin.vst3/Contents/./PkgInfo: ../PkgInfo
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content chordical-plugin.vst3/Contents/./PkgInfo"
	$(CMAKE_COMMAND) -E copy /Users/jason/dev/chordical-plugin/Builds/CLion/PkgInfo chordical-plugin.vst3/Contents/./PkgInfo

CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.o: CMakeFiles/VST3.dir/flags.make
CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.o: /Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jason/dev/chordical-plugin/Builds/CLion/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.o -c /Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp

CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp > CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.i

CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp -o CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.s

# Object files for target VST3
VST3_OBJECTS = \
"CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.o"

# External object files for target VST3
VST3_EXTERNAL_OBJECTS =

chordical-plugin.vst3/Contents/MacOS/chordical-plugin: CMakeFiles/VST3.dir/Users/jason/dev/chordical-plugin/JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp.o
chordical-plugin.vst3/Contents/MacOS/chordical-plugin: CMakeFiles/VST3.dir/build.make
chordical-plugin.vst3/Contents/MacOS/chordical-plugin: libchordical-plugin.a
chordical-plugin.vst3/Contents/MacOS/chordical-plugin: CMakeFiles/VST3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jason/dev/chordical-plugin/Builds/CLion/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX CFBundle shared module chordical-plugin.vst3/Contents/MacOS/chordical-plugin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VST3.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Copying \"chordical-plugin.vst3\" to \"/Users/jason/Library/Audio/Plug-Ins/VST3/\""
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove_directory /Users/jason/Library/Audio/Plug-Ins/VST3/chordical-plugin.vst3
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy_directory /Users/jason/dev/chordical-plugin/Builds/CLion/cmake-build-debug/chordical-plugin.vst3 /Users/jason/Library/Audio/Plug-Ins/VST3/chordical-plugin.vst3

# Rule to build all files generated by this target.
CMakeFiles/VST3.dir/build: chordical-plugin.vst3/Contents/MacOS/chordical-plugin
CMakeFiles/VST3.dir/build: chordical-plugin.vst3/Contents/./PkgInfo

.PHONY : CMakeFiles/VST3.dir/build

CMakeFiles/VST3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VST3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VST3.dir/clean

CMakeFiles/VST3.dir/depend:
	cd /Users/jason/dev/chordical-plugin/Builds/CLion/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jason/dev/chordical-plugin/Builds/CLion /Users/jason/dev/chordical-plugin/Builds/CLion /Users/jason/dev/chordical-plugin/Builds/CLion/cmake-build-debug /Users/jason/dev/chordical-plugin/Builds/CLion/cmake-build-debug /Users/jason/dev/chordical-plugin/Builds/CLion/cmake-build-debug/CMakeFiles/VST3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VST3.dir/depend

