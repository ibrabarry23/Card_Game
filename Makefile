# Variabili principali
CC = gcc
CFLAGS = -std=c99 -pedantic -O2 -Wall -Iinclude

# Directory
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# File di output
TARGET = $(BUILD_DIR)/program

# File sorgenti e oggetti
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Regole di compilazione
all: $(TARGET)

# Regola per creare l'eseguibile
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Regola per creare gli oggetti
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Pulizia
clean:
	rm -rf $(BUILD_DIR)

