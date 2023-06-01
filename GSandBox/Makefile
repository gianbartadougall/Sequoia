# -*- MakeFile -*-

# Makefile settings
EXECUTABLE_NAME = GianSandBox.exe

# Create target name, build directory and executable path
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)\$(EXECUTABLE_NAME)

# Create list of .cpp sources for each folder
SEQUOIA_SOURCES = $(shell dir /b /s "..\Sequoia\*.cpp")
PROJECT_SOURCES_FULL = $(shell dir /b /s "*.cpp")
PROJECT_SOURCES = $(filter-out $(foreach S, $(PROJECT_SOURCES_FULL), $(if $(findstring Discards\Src\, $S), $S)), $(PROJECT_SOURCES_FULL))
GLEW_SOURCES = ..\Drivers\GLEW\src\glew.c
GLFW_SOURCES = $(patsubst %.c, ..\Drivers\GLFW\src\\%.c, monitor.c window.c win32_monitor.c win32_window.c init.c input.c context.c \
win32_init.c win32_thread.c win32_time.c win32_joystick.c wgl_context.c egl_context.c osmesa_context.c vulkan.c)

# Create list of .o files from .cpp and .c files
SEQUOIA_OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)\\%.o, $(notdir $(SEQUOIA_SOURCES)))
PROJECT_OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)\\%.o, $(notdir $(PROJECT_SOURCES))) 
GLFW_OBJECTS = $(patsubst %.c, $(BUILD_DIR)\\%.o, $(notdir $(GLFW_SOURCES)))
GLEW_OBJECTS = $(patsubst %.c, $(BUILD_DIR)\\%.o, $(notdir $(GLEW_SOURCES)))

# Generate list of include directories for each section
GLFW_INCLUDES = -I../Drivers/GLFW/include -I../Drivers/GLFW/src
GLEW_INCLUDES = -I../Drivers/GLEW/include 

# The shell command finds all the paths to the .h files. The dir command removes the .h filename from the
# the paths. The patsubst command removes the trailing \ so it ends in \Inc instead of \Inc\. The sort command
# removes all the duplicate paths. The addprefix adds -I to the start of each path
SEQUOIA_HEADERS = $(shell dir /b /s "..\Sequoia\*.h")
SEQUOIA_INCLUDES = $(addprefix -I, $(sort $(patsubst %\Inc\, %\Inc, $(dir $(SEQUOIA_HEADERS)))))

PROJECT_HEADERS = $(shell dir /b /s "*.h")
PROJECT_INCLUDES = $(addprefix -I, $(sort $(patsubst %\Inc\, %\Inc, $(dir $(PROJECT_HEADERS)))))

# Compile list containing all .cpp object and include files
INCLUDES = $(SEQUOIA_INCLUDES) $(PROJECT_INCLUDES) $(GLFW_INCLUDES) $(GLEW_INCLUDES)

# Optimisation flags
OPT=-Og
CPP_COMPILER=g++
C_COMPILER=gcc
DEBUG_MODE=-g
FLAGS=-Wall -Wextra

SEQUOIA_FLAGS = $(FLAGS) $(DEBUG_MODE) $(INCLUDES) $(OPT) -lm
PROJECT_FLAGS = $(FLAGS) $(DEBUG_MODE) $(INCLUDES) $(OPT) -lm
GLEW_FLAGS = $(DEBUG_MODE) -DGLEW_STATIC $(GLEW_INCLUDES) $(OPT)
GLFW_FLAGS = $(DEBUG_MODE) $(GLFW_INCLUDES) $(OPT)

# The first prerequisite checks if the build directory exists. The next prerequistes will
# try recompile the .o files if they do not exist or if the sources files have been updated
# since the last builld. The line $(wordlist 2,$(words $^),$^) just ensures that only the 
# prerequistes after $(BUILD_DIR) are used
all: $(BUILD_DIR) $(GLEW_OBJECTS) $(GLFW_OBJECTS) $(SEQUOIA_OBJECTS) $(PROJECT_OBJECTS)
	$(CPP_COMPILER) -o $(EXECUTABLE) $(wordlist 2, $(words $^), $^) -lgdi32 -lopengl32

# Recipe to create build folder
$(BUILD_DIR):
	mkdir $@

# Generic recipes for creating the given object files from the required .cpp files
$(GLEW_OBJECTS): $(GLEW_SOURCES)
	$(C_COMPILER) $(GLEW_FLAGS) -c -o $@ $(filter %\$(notdir $(basename $@)).c, $^)

$(GLFW_OBJECTS): $(GLFW_SOURCES)
	$(C_COMPILER) $(GLFW_FLAGS) -c -o $@ $(filter %\$(notdir $(basename $@)).c, $^)

# The filtering is there to reconstruct the path to the .cpp file so the .o file
# can be compiled properly
$(SEQUOIA_OBJECTS): $(SEQUOIA_SOURCES) $(SEQUOIA_HEADERS)
	$(CPP_COMPILER) $(SEQUOIA_FLAGS) -c -o $@ $(filter %\$(notdir $*).cpp, $(SEQUOIA_SOURCES))

# The filtering is there to reconstruct the path to the .cpp file so the .o file
# can be compiled properly
$(PROJECT_OBJECTS): $(PROJECT_SOURCES) $(PROJECT_HEADERS)
	$(CPP_COMPILER) $(PROJECT_FLAGS) -c -o $@ $(filter %\$(notdir $*).cpp, $(PROJECT_SOURCES))

# Speed up next build process by only removing non 3rd party .o files as the 3rd party .o files
# will never change
clean:
	@del /f $(SEQUOIA_OBJECTS) $(PROJECT_OBJECTS)
	
# Remove the entire build directory
fullclean:
	@rmdir /s /q $(BUILD_DIR)

# Run executable
run:
	.\$(EXECUTABLE)

.PHONY: run clean fullclean