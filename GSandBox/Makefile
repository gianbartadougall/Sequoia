# -*- MakeFile -*-

# Makefile settings
EXECUTABLE_NAME = GianSandBox.exe

# Create target name, build directory and executable path
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)\$(EXECUTABLE_NAME)

# Relative path to GLFW and GLEW sources from this makefile
SEQUOIA_SUB_DIRS = $(wildcard ../Sequoia/*)
PROJECT_SUB_DIRS = $(wildcard *)
GLEW_DIRECTORY = ../Drivers/GLEW/src
GLFW_DIRECTORY = ../Drivers/GLFW/src

# Create list of .cpp sources for each folder
SEQUOIA_SOURCES = $(strip $(foreach D, $(SEQUOIA_SUB_DIRS), $(wildcard $(D)/Src/*.cpp)))
PROJECT_SOURCES = $(strip $(foreach D, $(PROJECT_SUB_DIRS), $(wildcard $(D)/Src/*.cpp)))
GLEW_SOURCES = $(GLEW_DIRECTORY)/glew.c
GLFW_SOURCES = $(patsubst %.c, $(GLFW_DIRECTORY)/%.c, monitor.c window.c win32_monitor.c win32_window.c init.c input.c context.c \
win32_init.c win32_thread.c win32_time.c win32_joystick.c wgl_context.c egl_context.c osmesa_context.c vulkan.c)

# Create list of .o files from .cpp and .c files
SEQUOIA_OBJECTS = $(patsubst %.cpp, %.o, $(SEQUOIA_SOURCES))
PROJECT_OBJECTS = $(patsubst %.cpp, %.o, $(PROJECT_SOURCES)) 
GLFW_OBJECTS = $(patsubst %.c, %.o, $(GLFW_SOURCES))
GLEW_OBJECTS = $(patsubst %.c, %.o, $(GLEW_SOURCES))

# Create list of .o files with a stripped directory
SEQUOIA_OBJECTS_BUILD_DIR = $(foreach D, $(SEQUOIA_OBJECTS), $(BUILD_DIR)/$(notdir $(D)))
PROJECT_OBJECTS_BUILD_DIR = $(foreach D, $(PROJECT_OBJECTS), $(BUILD_DIR)/$(notdir $(D)))
GLFW_OBJECTS_BUILD_DIR = $(foreach D, $(GLFW_OBJECTS), $(BUILD_DIR)/$(notdir $(D)))
GLEW_OBJECTS_BUILD_DIR = $(foreach D, $(GLEW_OBJECTS), $(BUILD_DIR)/$(notdir $(D)))

# Create list containing all the includes folders for the sequoia and project .cpp files.
# patsubst adds -I to start of each folder and strip removes leading and trailing white space
SEQUOIA_INCLUDE_FOLDERS = $(foreach D, $(SEQUOIA_SUB_DIRS), $(wildcard $(D)/Inc))
PROJECT_INCLUDE_FOLDERS = $(foreach D, $(PROJECT_SUB_DIRS), $(wildcard $(D)/Inc))
SEQUOIA_INCLUDES = $(strip $(patsubst %/Inc, -I%/Inc, $(SEQUOIA_INCLUDE_FOLDERS)))
PROJECT_INCLUDES = $(strip $(patsubst %/Inc, -I%/Inc, $(PROJECT_INCLUDE_FOLDERS)))

# Create list of .h includes for each folder in GLFW and GLEW folders
GLFW_INCLUDES = -I../Drivers/GLFW/include -I../Drivers/GLFW/src
GLEW_INCLUDES = -I../Drivers/GLEW/include 

# Compile list containing all .cpp object and include files
OBJECTS = $(SEQUOIA_OBJECTS) $(PROJECT_OBJECTS) $(GLFW_OBJECTS) $(GLEW_OBJECTS)
INCLUDES = $(SEQUOIA_INCLUDES) $(PROJECT_INCLUDES) $(GLFW_INCLUDES) $(GLEW_INCLUDES)

# Create list of dependcy files (.d files). These files are used by the
# compiler to ensure that any .cpp file that includes a .h file that has
# changed is recompiled
-include $($(patsubst %.cpp, $(BUILD_DIR)/%.d, $(SEQUOIA_SOURCES) $(PROJECT_SOURCES)))
-include $($(patsubst %.c, $(BUILD_DIR)/%.d, $(GLEW_SOURCES) $(GLFW_SOURCES)))

# Optimisation flags
OPT = -Og
CPP_COMPILER=g++
C_COMPILER=gcc

# Ensures .cpp files are recompiled if header files are edited 
DEPENDENCY_FLAGS = -MP -MD

SEQUOIA_FLAGS = -Wall $(INCLUDES) $(DEPENDENCY_FLAGS) $(OPT) -lm
PROJECT_FLAGS = -Wall $(INCLUDES) $(DEPENDENCY_FLAGS) $(OPT)
GLEW_FLAGS = -g -DGLEW_STATIC $(GLEW_INCLUDES) $(DEPENDENCY_FLAGS) $(OPT)
GLFW_FLAGS = -Wall $(GLFW_INCLUDES) $(DEPENDENCY_FLAGS) $(OPT)

# All must depend on the .cpp sources. This ensures that if a .cpp source changes, make
# will always recompile. The source dependencies will call recipes that will create the
# associated object files in the build directory. The last dependency 'Linker' will check
# those build files exist and link everything together. The linker must check the object
# files in the build folder exist incase make clean was just run but the sources haven't
# changed since the last make. This ensures the project will always compile correctly
all: $(BUILD_DIR) $(GLEW_SOURCES) $(GLFW_SOURCES) $(SEQUOIA_SOURCES) $(PROJECT_SOURCES) Linker

# Compilation is split from all because all contains dependency for build directory which means $^ cannot be used in action because
# it will include the build directory and thus cause an error
Linker: $(GLEW_OBJECTS_BUILD_DIR) $(GLFW_OBJECTS_BUILD_DIR) $(SEQUOIA_OBJECTS_BUILD_DIR) $(PROJECT_OBJECTS_BUILD_DIR)
	$(CPP_COMPILER) -o $(BUILD_DIR)/$(EXECUTABLE_NAME) $^ -lgdi32 -lopengl32

# Recipe to create build folder
$(BUILD_DIR):
	mkdir $@

# Generic recipes for creating the given object files from the required .cpp files
$(GLEW_SOURCES):
	$(C_COMPILER) $(GLEW_FLAGS) -c -o $(BUILD_DIR)/$(notdir $(basename $@)).o $@

$(GLFW_SOURCES):
	$(C_COMPILER) $(GLFW_FLAGS) -c -o $@ $(BUILD_DIR)/$(notdir $(basename $@)).o $@

$(SEQUOIA_SOURCES):
	$(CPP_COMPILER) $(SEQUOIA_FLAGS) -c -o $(BUILD_DIR)/$(notdir $(basename $@)).o $@

$(PROJECT_SOURCES):
	$(CPP_COMPILER) $(PROJECT_FLAGS) -c -o $(BUILD_DIR)/$(notdir $(basename $@)).o $@


# Generic recipes for creating the given object files from the required .cpp files
$(GLEW_OBJECTS_BUILD_DIR): $(GLEW_SOURCES)
	$(C_COMPILER) $(GLEW_FLAGS) -c -o $@ $(GLEW_DIRECTORY)/$(notdir $(basename $@)).c

$(GLFW_OBJECTS_BUILD_DIR): $(GLFW_SOURCES)
	$(C_COMPILER) $(GLFW_FLAGS) -c -o $@ $(GLFW_DIRECTORY)/$(notdir $(basename $@)).c

$(SEQUOIA_OBJECTS_BUILD_DIR): $(SEQUOIA_SOURCES)
	$(CPP_COMPILER) $(SEQUOIA_FLAGS) -c -o $@ $(strip $(filter %/$(notdir $(basename $@).cpp), $(SEQUOIA_SOURCES)))

$(PROJECT_OBJECTS_BUILD_DIR): $(PROJECT_SOURCES)
	$(CPP_COMPILER) $(PROJECT_FLAGS) -c -o $@ $(strip $(filter %/$(notdir $(basename $@).cpp), $(PROJECT_SOURCES)))

# Delete build directory
clean:
	@rmdir /s /q $(BUILD_DIR)

# Run executable
run:
	.\$(EXECUTABLE)

.PHONY: run clean