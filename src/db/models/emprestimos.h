#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

#include <sqlite3.h>

// --------- Funções da tbl_Emprestimos ---------

char* regEmpLivro(sqlite3 *db, const char *data_emprestimo, const char *data_devolucao, const char *id_livro_fk, const char *id_usuario_fk);

void consultEmp(sqlite3 *db);

#endif