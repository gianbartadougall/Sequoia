# -*- MakeFile -*-

# Makefile settings
EXECUTABLE_NAME = GianSandBox
TARGET_SYSTEM = WINDOWS

# Create target name, build directory and executable path
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/$(EXECUTABLE_NAME).exe

CPP_SOURCE_DIRS = \
../Engine/Math/Src \
../Engine/Utils/Src \
Main/Src \
Utils/Src

GLFW_BUILD_DIRECTORY = ../Drivers/GLFW/build
GLEW_BUILD_DIRECTORY = ../Drivers/GLEW/build

GLFW_OBJECTS = $(foreach D, $(GLFW_BUILD_DIRECTORY), $(wildcard $(D)/*.o))
GLEW_OBJECTS = $(foreach D, $(GLEW_BUILD_DIRECTORY), $(wildcard $(D)/*.o))

GLFW_INCLUDES = -I../Drivers/GLFW/include -I../Drivers/GLFW/src
GLEW_INCLUDES = -I../Drivers/GLEW/include

# Generate list of includes for .cpp files based on the .cpp sources
CPP_INCLUDES = $(patsubst %/Src, -I%/Inc, $(CPP_SOURCE_DIRS))
CPP_INCLUDES += $(GLEW_INCLUDES)
CPP_INCLUDES += $(GLFW_INCLUDES)

CPP_EXCLUDES = \
../Engine/Math/Src/vector4f.cpp

# Compile all the required .cpp sources and associated directories
CPP_SOURCES_ALL = $(foreach D, $(CPP_SOURCE_DIRS), $(wildcard $(D)/*.cpp))
CPP_SOURCES = $(filter-out $(CPP_EXCLUDES),$(CPP_SOURCES_ALL))
CPP_OBJECTS = $(patsubst %.cpp, %.o, $(CPP_SOURCES))
CPP_OBJECTS_NO_DIR = $(foreach D, $(CPP_OBJECTS), $(BUILD_DIR)/$(notdir $(D)))

# Create list of dependcy files (.d files). These files are used by the
# compiler to ensure that any .cpp file that includes a .h file that has
# changed is recompiled
CPP_DEPENDENCIES = $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(CPP_SOURCES))
-include $(CPP_DEPENDENCIES)

# Optimisation flags
OPT = -Og
CPP_COMPILER=g++

# Ensures .cpp files are recompiled if header files are edited 
DEPENDENCY_FLAGS = -MP -MD

CPP_FLAGS = -Wall $(CPP_INCLUDES) $(DEPENDENCY_FLAGS) $(OPT) -I../Drivers/GLEW/include

# Build the dependency $(TARGET)
all: $(BUILD_DIR) $(EXECUTABLE)

# To build the executable, all the associated .o files are required. Because the .o files
# are saved in a different file so the linking is done seperatley
$(EXECUTABLE): $(CPP_OBJECTS) Linker

# Recipe to link all the .o files together and create the executable
Linker: $(CPP_OBJECTS_NO_DIR) $(GLFW_OBJECTS) $(GLEW_OBJECTS)
	$(CPP_COMPILER) -o $(EXECUTABLE) $^ -lgdi32 -lopengl32

# Delete build directory
clean:
	@rmdir /s /q $(BUILD_DIR)

# Run executable
run:
	.\$(EXECUTABLE)

# Generic recipe for making .o files from .cpp files
%.o:%.cpp
	$(CPP_COMPILER) $(CPP_FLAGS) -c -o $(BUILD_DIR)/$(notdir $@) $^

# Recipe to create build folder
$(BUILD_DIR):
	mkdir $@	

.PHONY: all run clean