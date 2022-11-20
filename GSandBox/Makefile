# -*- MakeFile -*-

# Create target name, build directory and executable path
EXECUTABLE_NAME = GianSandBox
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/$(EXECUTABLE_NAME).exe

CPP_SOURCE_DIRS = \
../Engine/Math/Src \
Main/Src

C_INCLUDES = \
-I../Drivers/OpenGL/src \
-I../Drivers/OpenGL/include \
-I../Drivers/OpenGL/include/GLFW

CPP_INCLUDES = \
-IMain/Inc \
-I../Drivers/OpenGL/include \
-I../Engine/Math/Inc \
-I../Drivers/OpenGL/src

# List all directories containg .h files used by the project

CPP_EXCLUDES = \
../Engine/Math/Src/vector4f.cpp

# window.c contains functions required for windowCreate etc
C_SOURCES = \
../Drivers/OpenGL/src/monitor.c \
../Drivers/OpenGL/src/window.c \
../Drivers/OpenGL/src/win32_monitor.c \
../Drivers/OpenGL/src/win32_window.c \
../Drivers/OpenGL/src/init.c \
../Drivers/OpenGL/src/input.c \
../Drivers/OpenGL/src/context.c \
../Drivers/OpenGL/src/win32_init.c \
../Drivers/OpenGL/src/win32_thread.c \
../Drivers/OpenGL/src/vulkan.c \
../Drivers/OpenGL/src/win32_time.c \
../Drivers/OpenGL/src/win32_joystick.c \
../Drivers/OpenGL/src/wgl_context.c \
../Drivers/OpenGL/src/egl_context.c \
../Drivers/OpenGL/src/osmesa_context.c \

C_OBJECTS_NO_DIR = \
$(BUILD_DIR)/monitor.o \
$(BUILD_DIR)/window.o \
$(BUILD_DIR)/win32_monitor.o \
$(BUILD_DIR)/win32_window.o \
$(BUILD_DIR)/init.o \
$(BUILD_DIR)/input.o \
$(BUILD_DIR)/context.o \
$(BUILD_DIR)/win32_init.o \
$(BUILD_DIR)/win32_thread.o \
$(BUILD_DIR)/vulkan.o \
$(BUILD_DIR)/win32_time.o \
$(BUILD_DIR)/win32_joystick.o \
$(BUILD_DIR)/wgl_context.o \
$(BUILD_DIR)/egl_context.o \
$(BUILD_DIR)/osmesa_context.o

# List all the .cpp files to be compiled
CPP_SOURCES_ALL = $(foreach D, $(CPP_SOURCE_DIRS), $(wildcard $(D)/*.cpp))
#C_SOURCES_ALL = $(foreach D, $(C_SOURCE_DIRS), $(wildcard $(D)/*.c))

CPP_SOURCES = $(filter-out $(CPP_EXCLUDES),$(CPP_SOURCES_ALL))
#C_SOURCES = $(filter-out $(C_EXCLUDES),$(C_SOURCES_ALL))

# Create list of all the object files (.o files)
CPP_OBJECTS = $(patsubst %.cpp, %.o, $(CPP_SOURCES))
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

# Create list of all the objects without the directo
CPP_OBJECTS_NO_DIR = $(foreach D, $(CPP_OBJECTS), $(BUILD_DIR)/$(notdir $(D)))
#C_OBJECTS_NO_DIR = $(foreach D, $(C_OBJECTS), $(BUILD_DIR)/$(notdir $(D)))


$(info C OBJECTS: $(C_OBJECTS))
$(info C OBJECTS NO DIR: $(C_OBJECTS_NO_DIR))
$(info CPP OBJECTS: $(CPP_OBJECTS))
$(info CPP OBJECTS NO DIR: $(CPP_OBJECTS_NO_DIR))

# Create list of dependcy files (.d files). These files are used by the
# compiler to ensure that any .cpp file that includes a .h file that has
# changed is recompiled
CPP_DEPENDENCIES = $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(CPP_SOURCES))
#C_DEPENDENCIES = $(patsubst %.c, $(BUILD_DIR)/%.d, $(CPP_SOURCES))
-include $(CPP_DEPENDENCIES)
#-include $(C_DEPENDENCIES)

# Optimisation flags
OPT = -Og

# Compile using g++ (compiler for c++)
C_COMPILER=gcc
CPP_COMPILER=g++

# Ensures .cpp files are recompiled if header files are edited 
DEPENDENCY_FLAGS = -MP -MD

CPP_FLAGS = -Wall $(CPP_INCLUDES) $(DEPENDENCY_FLAGS) $(OPT)
C_FLAGS = -Wall $(C_INCLUDES) $(DEPENDENCY_FLAGS) $(OPT)

# Build the dependency $(TARGET)
all: $(BUILD_DIR) $(EXECUTABLE)

# To build the executable, all the associated .o files are required. Because the .o files
# are saved in a different file so the linking is done seperatley
$(EXECUTABLE): $(CPP_OBJECTS) $(C_OBJECTS) Linker

# Recipe to link all the .o files together and create the executable
Linker: $(CPP_OBJECTS_NO_DIR) $(C_OBJECTS_NO_DIR)
	$(CPP_COMPILER) -o $(EXECUTABLE) $(OPENGL_DLL_SOURCES) $^ -lgdi32 -lopengl32

# Delete build directory
clean:
	@rmdir /s /q $(BUILD_DIR)

# Run executable
run:
	.\$(EXECUTABLE)

# Generic recipe for making .o files from .cpp files
%.o:%.cpp
	$(CPP_COMPILER) $(CPP_FLAGS) -c -o $(BUILD_DIR)/$(notdir $@) $^

# Generic recipe for making .o files from .c files
%.o:%.c
	$(C_COMPILER) $(C_FLAGS) -c -o $(BUILD_DIR)/$(notdir $@) $^

# Recipe to create build folder
$(BUILD_DIR):
	mkdir $@	

.PHONY: all run clean