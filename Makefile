# === Variabili ===
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2 -pedantic -Iinclude
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image

SRC_DIR = src
INCLUDE_DIR = include
TOOLS_DIR = tools
BUILD_DIR = build

# File sorgenti
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(TOOLS_DIR)/main.c
OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SOURCES)))

TARGET = $(BUILD_DIR)/program

# === Regola di default ===
all: $(TARGET)

# === Linking finale ===
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $@ $(SDL_LDFLAGS)

# === Regola per .o da src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

# === Regola per main
$(BUILD_DIR)/main.o: $(TOOLS_DIR)/main.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

# === Esegui
run: all
	./$(TARGET)

# === Pulizia
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean run