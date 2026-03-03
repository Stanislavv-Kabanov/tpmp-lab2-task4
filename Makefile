CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
DEBUG_FLAGS = -g -O0

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data
DOCS_DIR = docs

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/program

.PHONY: all clean debug run test help

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJ_DIR) $(BIN_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

run: all
	./$(TARGET)

test: all
	@echo "Запуск тестов..."
	@./$(TARGET)
	@echo "Проверьте $(DATA_DIR)/output.txt для результатов"
	@echo "Отчет о тестировании находится в $(DOCS_DIR)/tests.md"

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DATA_DIR)/output.txt

cleanall: clean
	rm -f *.txt
	rm -rf $(DATA_DIR)/*.txt

help:
	@echo "Доступные команды:"
	@echo "  make all     - сборка проекта"
	@echo "  make debug   - сборка с отладочной информацией"
	@echo "  make run     - запуск программы"
	@echo "  make test    - запуск программы и напоминание о тестах"
	@echo "  make clean   - очистка"
	@echo "  make cleanall- полная очистка"
