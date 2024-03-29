# -*- MakeFile -*-

# Create target name, build directory and executable path
EXECUTABLE_NAME = Sequoia
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/$(EXECUTABLE_NAME).exe

CPP_SOURCE_DIRS = \
../Engine/Math/Src \
Main/Src

C_INCLUDES = \
-IMain/Inc \
-I../Engine/Math/Inc 

# List all directories containg .h files used by the project

C_EXCLUDES = \
../Engine/Math/Src/vector4f.cpp

OPENGL_INCLUDES = \
-I../Drivers/OpenGL/include/GLFW

$(info TEST $(CPP_SOURCE_DIRS))
# List all the .cpp files to be compiled
CPP_SOURCES_ALL = $(foreach D, $(CPP_SOURCE_DIRS), $(wildcard $(D)/*.cpp) )
CPP_SOURCES = $(filter-out $(C_EXCLUDES),$(CPP_SOURCES_ALL))

# Create list of all the object files (.o files)
OBJECTS = $(patsubst %.cpp, %.o, $(CPP_SOURCES))

# Create list of all the objects without the directo
OBJECTS_NO_DIR = $(foreach D, $(OBJECTS), $(BUILD_DIR)/$(notdir $(D)))

# Create list of dependcy files (.d files). These files are used by the
# compiler to ensure that any .cpp file that includes a .h file that has
# changed is recompiled
DEPENDENCIES = $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(CPP_SOURCES))
-include $(DEPENDENCIES)
# Optimisation flags
OPT = -Og

# Compile using g++ (compiler for c++)
CC=g++

# Ensures .cpp files are recompiled if header files are edited 
DEPENDENCY_FLAGS = -MP -MD

CFLAGS = -Wall $(C_INCLUDES) $(DEPENDENCY_FLAGS) $(OPT) $(OPENGL_INCLUDES)

# Build the dependency $(TARGET)
all: $(BUILD_DIR) $(EXECUTABLE)

# To build the executable, all the associated .o files are required. Because the .o files
# are saved in a different file so the linking is done seperatley
$(EXECUTABLE): $(OBJECTS) Linker

#	$(CC) -o $(EXECUTABLE) $^

# Recipe to link all the .o files together and create the executable
Linker: $(OBJECTS_NO_DIR)
	$(CC) -o $(EXECUTABLE) $^

# Delete build directory
clean:
	@rmdir /s /q $(BUILD_DIR)

# Run executable
run:
	.\$(EXECUTABLE)

%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(notdir $@) $^

# Recipe to create build folder
$(BUILD_DIR):
	mkdir $@	

.PHONY: all run clean