LD = gcc
CC = gcc

# CFLAGS := \
	-Isrc/include \
	-Wall \
	-Wextra \
	-Werror \
	-std=gnu99 \
	-O3 \

CFLAGS := \
	-Isrc/include \
	-Wall \
	-Wextra \
	-Werror \
	-std=gnu99 \
	-g \

CFILES := $(shell find src/ -name '*.c')
OFILES := $(CFILES:.c=.o)

TARGET = fibonaphi

all: clean compile

compile: ld
	@ echo "Done!"
	
ld: $(OFILES)
	@ echo "[LD] $^"
	@ $(LD) $^ -o $(TARGET)

%.o: %.c
	@ echo "[CC] $<"
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ echo "[CLEAN]"
	@ rm -rf $(OFILES) $(TARGET)

