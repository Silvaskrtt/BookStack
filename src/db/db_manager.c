#include "db_manager.h"
#include "models/usuarios.h"
#include "models/livros.h"
#include "models/emprestimos.h"
#include <stdio.h>

/*
 * DB Manager - Implementação
 * Centraliza todas as operações de banco de dados
 */

// ========== GERENCIAMENTO DE CONEXÃO ==========

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
