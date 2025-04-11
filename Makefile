# Variabili
CC = gcc
CFLAGS = -std=c99 -pedantic -O2 -Wall -Iinclude
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TOOLS_DIR = tools
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(TOOLS_DIR)/main.c
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SOURCES)))
TARGET = $(BUILD_DIR)/program

# Regola di default
all: $(TARGET)

# Regola per creare l'eseguibile
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $@ $(SDL_LDFLAGS)

# Regola per creare i file oggetto da src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

# Regola per creare il file oggetto da tools/main.c
$(BUILD_DIR)/main.o: $(TOOLS_DIR)/main.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

# Pulizia
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
