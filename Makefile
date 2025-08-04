# Compilador e flags
CC = gcc
CFLAGS = -Iinclude -Wall -std=c11 $(shell pkg-config --cflags gtk4)
LDFLAGS = -lsqlite3 $(shell pkg-config --libs gtk4) -mwindows

# Arquivos fonte (somente os necessários para o comando)
SRC = src/gui.c src/database.c

# Diretórios
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
EXEC = $(BUILD_DIR)/BookStack.exe

# Arquivos objeto
OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Regra padrão (compilar e executar)
all: build run

# Compilar
build: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilar arquivos .c para .o
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Executar
run:
	@./$(EXEC)

# Limpar arquivos
clean:
	rm -rf $(BUILD_DIR)
