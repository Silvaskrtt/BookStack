#include "db_manager.h"
#include "models/usuarios.h"
#include "models/livros.h"
#include "models/emprestimos.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * DB Manager - Implementação
 * Centraliza todas as operações de banco de dados
 */

// ========== GERENCIAMENTO DE CONEXÃO ==========

// Retorna o caminho do banco de dados
const char* get_db_path(void) {
    static char db_path[512] = {0};
    
    // Se a variável de ambiente estiver definida, usa ela
    const char *env_path = getenv("BOOKSTACK_DB_PATH");
    if (env_path) {
        return env_path;
    }
    
    // Se o caminho relativo existe, usa ele
    FILE *test = fopen("database/BOOKSTACK.db", "r");
    if (test) {
        fclose(test);
        return "database/BOOKSTACK.db";
    }
    
    // Tenta caminho relativo a partir do diretório build (quando executado como make run)
    test = fopen("../database/BOOKSTACK.db", "r");
    if (test) {
        fclose(test);
        return "../database/BOOKSTACK.db";
    }
    
    // Fallback: retorna o caminho padrão e deixa SQLite reportar o erro
    return "database/BOOKSTACK.db";
}

Database db_init(const char *db_path) {
    if (!db_path) {
        fprintf(stderr, "Erro: caminho do banco de dados inválido\n");
        return (Database){NULL, -1};
    }
    return conectaDB(db_path);
}

void db_close(Database *db) {
    if (db) {
        discDB(db);
    }
}

// ========== OPERAÇÕES COM USUÁRIOS ==========

char* db_user_create(Database db, const char *nome, const char *sobrenome, 
                     const char *cpf, const char *telefone) {
    if (!db.db || db.status != 1) {
        fprintf(stderr, "Erro: conexão com banco inválida\n");
        return NULL;
    }
    
    return cadUser(db.db, nome, sobrenome, cpf, telefone);
}

void db_user_list(Database db) {
    if (!db.db || db.status != 1) {
        fprintf(stderr, "Erro: conexão com banco inválida\n");
        return;
    }
    
    listUser(db.db);
}

// ========== OPERAÇÕES COM LIVROS ==========

char* db_book_create(Database db, const char *titulo, const char *autor, 
                     const char *ano, int disponibilidade) {
    if (!db.db || db.status != 1) {
        fprintf(stderr, "Erro: conexão com banco inválida\n");
        return NULL;
    }
    
    return addLivro(db.db, titulo, autor, ano, disponibilidade);
}

void db_book_list(Database db) {
    if (!db.db || db.status != 1) {
        fprintf(stderr, "Erro: conexão com banco inválida\n");
        return;
    }
    
    listLivro(db.db);
}

// ========== OPERAÇÕES COM EMPRÉSTIMOS ==========

char* db_loan_create(Database db, const char *data_emprestimo, 
                     const char *data_devolucao, const char *id_livro, 
                     const char *id_usuario) {
    if (!db.db || db.status != 1) {
        fprintf(stderr, "Erro: conexão com banco inválida\n");
        return NULL;
    }
    
    return regEmpLivro(db.db, data_emprestimo, data_devolucao, id_livro, id_usuario);
}

void db_loan_list(Database db) {
    if (!db.db || db.status != 1) {
        fprintf(stderr, "Erro: conexão com banco inválida\n");
        return;
    }
    
    consultEmp(db.db);
}
