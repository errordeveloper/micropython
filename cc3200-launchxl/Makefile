include ../py/mkenv.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include ../py/py.mk

CROSS_COMPILE = arm-none-eabi-

INC =  -I.
INC += -I$(PY_SRC)
INC += -I$(BUILD)
INC += -Ihal
INC += -I../stmhal

CFLAGS_CORTEX_M4 = -mthumb -mtune=cortex-m4 -mcpu=cortex-m4 -msoft-float -mfloat-abi=soft -fsingle-precision-constant -Wdouble-promotion
CFLAGS = $(INC) -Wall -Werror -ansi -std=gnu99 -nostdlib $(CFLAGS_CORTEX_M4) $(COPT)

#Debugging/Optimization
ifeq ($(DEBUG), 1)
CFLAGS += -O0 -ggdb
else
CFLAGS += -Os -DNDEBUG
endif

LDFLAGS = -nostdlib -T cc3200.ld -msoft-float -mfloat-abi=soft -Map=$@.map --cref

LIBGCC_FILE_NAME = $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)
LIBM_FILE_NAME   = $(shell $(CC) $(CFLAGS) -print-file-name=libm.a)
LIBC_FILE_NAME   = $(shell $(CC) $(CFLAGS) -print-file-name=libc.a)

LIBS  = -L $(dir $(LIBM_FILE_NAME)) -lm
LIBS += -L $(dir $(LIBC_FILE_NAME)) -lc
LIBS += -L $(dir $(LIBGCC_FILE_NAME)) -lgcc

CFLAGS += -fdata-sections -ffunction-sections
LDFLAGS += -Wl,--gc-sections

SRC_C = \
	main.c \
	pin_defs_cc3200.c \
	hal/gccollect.c \
	hal/cc3200_hal.c 

STM_SRC_C = $(addprefix stmhal/,\
	input.c \
	irq.c \
	pin.c \
	pin_named_pins.c \
	printf.c \
	pyexec.c \
	pybstdio.c \
	readline.c \
	string0.c \
	)

STM_SRC_S = $(addprefix stmhal/,\
	gchelper.s \
	)


OBJ = $(PY_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o) $(STM_SRC_C:.c=.o) $(STM_SRC_S:.s=.o))

all: $(BUILD)/firmware.elf

$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)
	$(Q)$(SIZE) $@

include ../py/mkrules.mk
