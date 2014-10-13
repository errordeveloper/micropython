include ../py/mkenv.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include ../py/py.mk

CROSS_COMPILE = arm-none-eabi-

INC =  -I.
INC += -Ihal
INC += -I$(PY_SRC)
INC += -I$(BUILD)
INC += -I../stmhal

CFLAGS_CORTEX_M4 = -mthumb -mtune=cortex-m4 -march=armv7e-m -mcpu=cortex-m4 -msoft-float -mfloat-abi=soft -Dgcc -DCCWARE -DSL_FULL -DSL_PLATFORM_MULTI_THREADED -fsingle-precision-constant -Wdouble-promotion
CFLAGS = $(INC) -Wall -Werror -ansi -std=gnu99 -nostdlib $(CFLAGS_CORTEX_M4) $(COPT)

CFLAGS += -Os -DNDEBUG -ffunction-sections -fdata-sections

LDFLAGS = -Wl,-nostdlib  -Wl,--gc-sections -T cc3200.lds -Wl,-Map=$@.map --specs=nano.specs

SRC_C = \
	main.c \
	hal/cc3200_hal.c \
	modpyb.c \
	pybstdio.c \
	hal/systick.c \
	pyexec.c \
	uart.c \
	help.c \
	hal/cpu.c \
	hal/interrupt.c \
	pybsystick.c \
	bufhelper.c \
	hal/startup_gcc.c

STM_SRC_C = $(addprefix stmhal/,\
	gccollect.c \
	input.c \
	irq.c \
	printf.c \
	readline.c \
	string0.c \
	)

STM_SRC_S = $(addprefix stmhal/,\
	gchelper.s \
	)


OBJ = $(PY_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o) $(SRC_S:.s=.o) $(STM_SRC_C:.c=.o) $(STM_SRC_S:.s=.o))

all: $(BUILD)/firmware.elf

$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(CC) -o $@ $(LDFLAGS) $(OBJ) $(LIBS)
	$(Q)$(SIZE) $@

include ../py/mkrules.mk
