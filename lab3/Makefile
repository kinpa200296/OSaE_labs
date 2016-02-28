.PHONY: all clean install uninstall test

CC = gcc
CFLAGS = -c -Wall -I $(INCLUDE_DIR)
TARGET = lab3
INSTALL_PREFIX = /usr/local/bin
SRC_DIR = src
INCLUDE_DIR = include
OBJECTS_DIR = obj
BIN_DIR = bin
TESTS_DIR = tests
INCLUDES = $(wildcard $(INCLUDE_DIR)/*.h)
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCES))
TESTS = $(patsubst $(TESTS_DIR)/test%.in, test%, $(wildcard $(TESTS_DIR)/*.in))

all: $(TARGET) test

clean:
	@rm -rf $(OBJECTS_DIR) $(BIN_DIR)

install: all
	@install $(BIN_DIR)/$(TARGET) $(INSTALL_PREFIX)

uninstall:
	@rm -rf $(INSTALL_PREFIX)/$(TARGET)

$(TARGET): dirs $(OBJECTS)
	@$(CC) -o $(BIN_DIR)/$(TARGET) $(OBJECTS)

dirs:
	@mkdir -p $(OBJECTS_DIR) $(BIN_DIR)

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@$(CC) $(CFLAGS) -o $@ $<

test:
	@for T in $(TESTS); do \
		$(BIN_DIR)/$(TARGET) $(TESTS_DIR)/$$T.in res.out; \
		res=$$(diff -q $(TESTS_DIR)/$$T.out res.out); \
		if [ "$$res" != "" ]; then \
			echo $$T......failed; \
			exit 1; \
		else \
			echo $$T......Ok; \
		fi; \
		rm res.out; \
	done
