CC = gcc

# Diretórios
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
EXEC = $(BUILD_DIR)/BookStack.exe

# Flags
CFLAGS = -Iinclude -Wall -std=c11 $(shell pkg-config --cflags gtk4)
LDFLAGS = -lsqlite3 $(shell pkg-config --libs gtk4) -mwindows

# Fontes (automatizado para incluir novos arquivos em subpastas)
SRC = $(wildcard src/*.c) $(wildcard src/db/*.c) $(wildcard src/db/models/*.c) $(wildcard src/view/*.c) $(wildcard src/view/controllers/*.c)

# Objetos correspondentes (espelha subdiretório dentro de $(OBJ_DIR))
OBJ = $(patsubst src/%.c,$(OBJ_DIR)/src/%.o,$(SRC))

# Alvo padrão
all: build

build: $(EXEC)

# Linkagem final
$(EXEC): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilação .c → .o (cria diretório de destino se necessário)
$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(EXEC)

clean:
	rm -rf $(BUILD_DIR)
