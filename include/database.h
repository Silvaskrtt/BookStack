#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

// --------- Funções da tbl_Usuarios ---------

char* cadUser(sqlite3 *db, const char *nome, const char *sobrenome, const char *cpf, const char *numtelefone);

void listUser(sqlite3 *db);

// --------- Funções da tbl_Livros ---------

char* addLivro(sqlite3 *db, const char *titulo, const char *autor, const char *ano, int disponibilidade);

void listLivro(sqlite3 *db);

// --------- Funções da tbl_Emprestimos ---------

char* regEmpLivro(sqlite3 *db, const char *data_emprestimo, const char *data_devolucao, const char *id_livro_fk, const char *id_usuario_fk);

void consultEmp(sqlite3 *db);

#endif