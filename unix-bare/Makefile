include ../py/mkenv.mk
-include mpconfigport.mk

# define main target
PROG = micropython

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include ../py/py.mk

# compiler settings
CFLAGS = -I. -I$(PY_SRC) -Wall -ansi -std=gnu99 -DUNIX $(CFLAGS_MOD) $(COPT)

UNAME_S := $(shell uname -s)
 ifeq ($(UNAME_S),Darwin)
    LDFLAGS = $(LDFLAGS_MOD) -lm -Wl,-map,$@.map
else
    LDFLAGS = $(LDFLAGS_MOD) -lm -Wl,-Map=$@.map,--cref
 endif

# Debugging/Optimization
ifdef DEBUG
CFLAGS += -g
COPT = -O0
else
COPT = -Os #-DNDEBUG
endif

# source files
SRC_C = \
	main.c \
	$(SRC_MOD)

OBJ = $(PY_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

include ../py/mkrules.mk

