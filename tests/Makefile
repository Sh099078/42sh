CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -fsanitize=address
DEBUG = -g #-fsanitize=address
# LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

MODULES   = exec utilities
SRC_DIR   = $(addprefix ../src/, $(MODULES)) cmains
SRC       = $(filter-out cmains/options.c ../src/exec/rule_case.c, \
							$(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.c)))
INCLUDES  = ../includes
OBJ = $(SRC:.c=.o)

BIN = bash

.DEFAULT_GOAL := all
.PHONY: all clean

all: $(SRC)
	$(CC) -I$(INCLUDES) $(CFLAGS) -g $(SRC) -o ${BIN}

clean:
	${RM} ${OBJ} ${BIN}
