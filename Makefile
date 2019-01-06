# Compiler flags
CC = g++
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS = -g -Wall -Wextra -Werror
else
	CFLAGS = -Wall -Wextra -Werror
endif

# Project files
SRCS = Main.cpp Texture.cpp UserInput.cpp Snake.cpp Game.cpp Board.cpp
OBJS = $(SRCS:.c=.o)
EXEC = snake

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LINKER_FLAGS) -o $(EXEC)

