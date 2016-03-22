.PHONY: all clean install uninstall

CC = gcc
CFLAGS = -c -Wall -I $(INCLUDE_DIR)
TARGET = daemon_process
INSTALL_PREFIX = /usr/local/bin
SRC_DIR = src
INCLUDE_DIR = include
OBJECTS_DIR = obj
BIN_DIR = bin
INCLUDES = $(wildcard $(INCLUDE_DIR)/*.h)
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCES))
CONFIG = "config.txt"
CONFIG_DIR = ".."

all: $(TARGET)

clean:
	@rm -rf $(OBJECTS_DIR) $(BIN_DIR)

install: all
	@install $(BIN_DIR)/$(TARGET) $(INSTALL_PREFIX)
	@cp $(BIN_DIR)/$(CONFIG) $(INSTALL_PREFIX)/$(CONFIG)

uninstall:
	@rm -rf $(INSTALL_PREFIX)/$(TARGET)
	@rm $(INSTALL_PREFIX)/$(CONFIG)

$(TARGET): dirs $(OBJECTS) config
	@$(CC) -o $(BIN_DIR)/$(TARGET) $(OBJECTS)

dirs:
	@mkdir -p $(OBJECTS_DIR) $(BIN_DIR)

config:
	@cp $(CONFIG_DIR)/$(CONFIG) $(BIN_DIR)/$(CONFIG)

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@$(CC) $(CFLAGS) -o $@ $<
