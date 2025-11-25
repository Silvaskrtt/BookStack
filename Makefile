# Compilador
CC = gcc

# Diretórios
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
EXEC = $(BUILD_DIR)/BookStack.exe

# Flags
CFLAGS = -Iinclude -Wall -std=c11 $(shell pkg-config --cflags gtk4)
LDFLAGS = -lsqlite3 $(shell pkg-config --libs gtk4) -mwindows

# Fontes
SRC = src/gui.c src/database.c
OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Alvo padrão
all: build

build: $(EXEC)

# Linkagem final
$(EXEC): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilação .c → .o
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(EXEC)

clean:
	rm -rf $(BUILD_DIR)
