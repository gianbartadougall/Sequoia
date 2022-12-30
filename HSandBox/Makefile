# -*- MakeFile -*-

# Create target name, build directory and executable path
EXECUTABLE_NAME = HaydenSandBox
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/$(EXECUTABLE_NAME).exe

CPP_SOURCE_DIRS = \
../Engine/Math/Src \
Main/Src 

C_SOURCE_DIRS = \
../Drivers/GLEW/src \
../Drivers/GLFW/src

C_INCLUDES = \
-IMain/Inc \
-I../Engine/Math/Inc \
-I../Drivers/GLEW/include \
-I../Drivers/GLFW/include

# List all directories containg .h files used by the project

CPP_EXCLUDES =
GLFW_SOURCES = $(patsubst %.c, ../Drivers/GLFW/src/%.c, monitor.c window.c win32_monitor.c win32_window.c init.c input.c context.c \
win32_init.c win32_thread.c win32_time.c win32_joystick.c wgl_context.c egl_context.c osmesa_context.c vulkan.c)
GLEW_SOURCES = $(patsubst %.c, ../Drivers/GLEW/src/%.c, glew.c)
C_SOURCES = $(GLFW_SOURCES) $(GLEW_SOURCES)



# List all the .cpp files to be compiled
CPP_SOURCES_ALL = $(foreach D, $(CPP_SOURCE_DIRS), $(wildcard $(D)/*.cpp))
CPP_SOURCES = $(filter-out $(CPP_EXCLUDES),$(CPP_SOURCES_ALL))

# Create list of all the object files (.o files)
OBJECTS_CPP = $(patsubst %.cpp, %.o, $(CPP_SOURCES))
OBJECTS_C = $(patsubst %.c, %.o, $(C_SOURCES))

# Create list of all the objects without the directo
OBJECTS_NO_DIR_CPP = $(foreach D, $(OBJECTS_CPP), $(BUILD_DIR)/$(notdir $(D)))
OBJECTS_NO_DIR_C = $(foreach D, $(OBJECTS_C), $(BUILD_DIR)/$(notdir $(D)))

# Create list of dependcy files (.d files). These files are used by the
# compiler to ensure that any .cpp file that includes a .h file that has
# changed is recompiled
DEPENDENCIES_CPP = $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(CPP_SOURCES))
-include $(DEPENDENCIES)
DEPENDENCIES_C = $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(C_SOURCES))
-include $(DEPENDENCIES)

# Optimisation flags
OPT = -Og

# Compile using g++ (compiler for c++)
CPP=g++
CC=gcc

# Ensures .cpp files are recompiled if header files are edited 
DEPENDENCY_FLAGS = -MP -MD

CFLAGS = -Wall $(C_INCLUDES) $(DEPENDENCY_FLAGS) $(OPT)

# Build the dependency $(TARGET)
all: $(BUILD_DIR) $(EXECUTABLE)

# To build the executable, all the associated .o files are required. Because the .o files
# are saved in a different file so the linking is done seperatley
$(EXECUTABLE): $(OBJECTS_CPP) $(OBJECTS_C) Linker

# Recipe to link all the .o files together and create the executable
Linker: $(OBJECTS_NO_DIR_CPP) $(OBJECTS_NO_DIR_C)
	$(CPP) -o $(EXECUTABLE) $^ -lgdi32 -lopengl32

# Delete build directory
clean:
	@rmdir /s /q $(BUILD_DIR)

# Run executable
run:
	.\$(EXECUTABLE)

%.o:%.cpp
	$(CPP) $(CFLAGS) -c -o $(BUILD_DIR)/$(notdir $@) $^

%.o:%.c
	$(CC) $(CFLAGS) -DGLEW_STATIC -c -o $(BUILD_DIR)/$(notdir $@) $^

# Recipe to create build folder
$(BUILD_DIR):
	mkdir $@	

.PHONY: all run clean