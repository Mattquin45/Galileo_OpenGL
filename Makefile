CC = gcc
CFLAGS = -Wall -std=c99 -O2

# Homebrew prefixes
GLFW_PREFIX := $(shell brew --prefix glfw)
GLEW_PREFIX := $(shell brew --prefix glew)

# Include and library paths
INCLUDES = -I$(GLFW_PREFIX)/include -I$(GLEW_PREFIX)/include
LIBS = -L$(GLFW_PREFIX)/lib -L$(GLEW_PREFIX)/lib \
       -lglfw -lGLEW -lpthread \
       -framework Cocoa -framework OpenGL -framework IOKit

# Output executable
OUTPUT = galileo_air

# Source and object files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Default target
all: $(OUTPUT)

# Linking
$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<


# Clean
clean:
	rm -f $(OBJ) $(OUTPUT)
