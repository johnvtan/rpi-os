CC = aarch64-elf-gcc
CFLAGS = -Wall -Wextra -O2 -ffreestanding -nostdlib -nostdinc -B/usr/local/aarch64-elf/bin/aarch64-elf-
LFLAGS = -ffreestanding -O2 -nostdlib

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

IMG_NAME = kernel8.img

build: $(OBJECTS) $(HEADERS)
	echo $(OBJECTS)
	$(CC) -T linker.ld -o $(IMG_NAME) $(LFLAGS) $(OBJECTS)

$(OBJ_DIR)/%.o: $(KERN_SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KERN_SRC_DIR) -I$(KERN_HEAD_DIR) -c $< -o $@ 

$(OBJ_DIR)/%.o: $(COMMON_SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KERN_SRC_DIR) -I$(KERN_HEAD_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(KERN_SRC_DIR)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KERN_SRC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm $(IMG_NAME)

run: build
	qemu-system-aarch64 -M raspi3 -kernel $(IMG_NAME) -serial stdio
