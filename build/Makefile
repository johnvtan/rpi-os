ARCH = arm-none-eabi-
CC = $(ARCH)gcc

CPUFLAG = cortex-a7
CFLAGS = -mcpu=$(CPUFLAG) -Wall -Wextra -O2 -ffreestanding -fpic -std=gnu99
LFLAGS = -ffreestanding -nostdlib -O2

KERN_SRC_DIR = ../src/kernel
KERN_HEAD_DIR = ../inc
COMMON_SRC_DIR = ../src/common
OBJ_DIR = objects

KERN_SRCS = $(wildcard $(KERN_SRC_DIR)/*.c)
COMMON_SRCS = $(wildcard $(COMMON_SRC_DIR)/*.c)
ASM_SRCS = $(wildcard $(KERN_SRC_DIR)/*.S)

OBJECTS = $(patsubst $(KERN_SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(KERN_SRCS))
OBJECTS += $(patsubst $(COMMON_SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(COMMON_SRCS))
OBJECTS += $(patsubst $(KERN_SRC_DIR)/%.S, $(OBJ_DIR)/%.o, $(ASM_SRCS))
HEADERS = $(wildcard $(KERN_HEAD_DIR)/*.h)

IMG_NAME = kernel.elf

build: clean directories program

directories:
	mkdir -p $(OBJ_DIR)

program: $(OBJECTS) $(HEADERS)
	echo $(OBJECTS)
	$(CC) -T linker.ld -o $(IMG_NAME) $(LFLAGS) $(OBJECTS)

$(OBJ_DIR)/%.o: $(KERN_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(KERN_SRC_DIR) -I$(KERN_HEAD_DIR) -c $< -o $@ 

$(OBJ_DIR)/%.o: $(COMMON_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(KERN_SRC_DIR) -I$(KERN_HEAD_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(KERN_SRC_DIR)/%.S
	$(CC) $(CFLAGS) -I$(KERN_SRC_DIR) -c $< -o $@

run: build
	qemu-system-arm -M raspi2 -kernel $(IMG_NAME) -serial stdio -m 256

all: build

debug: CFLAGS += -g -DDEBUG
debug: build

clean:
	rm -rf $(OBJ_DIR)
	rm $(IMG_NAME)

