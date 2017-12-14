CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror
DEBUG = -g #-fsanitize=address
CPPFLAGS = _POSIX_C_SOURCE=200809L
# LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

MODULES   = exec utilities
SRC_DIR   = $(addprefix ../src/, $(MODULES)) cmains
SRC       = $(filter-out cmains/options.c ../src/exec/rule_case.c, \
							$(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.c)))
INCLUDES  = ../includes
OBJ = $(SRC:.c=.o)

BIN = 42sh

.DEFAULT_GOAL := all
.PHONY: all clean

all: $(SRC)
	$(CC) -I$(INCLUDES) $(CFLAGS) -g $(SRC) -o ${BIN}

clean:
	${RM} ${OBJ} ${BIN}
