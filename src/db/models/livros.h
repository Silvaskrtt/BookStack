#ifndef LIVROS_H
#define LIVROS_H

#include <sqlite3.h>

// --------- Funções da tbl_Livros ---------

char* addLivro(sqlite3 *db, const char *titulo, const char *autor, const char *ano, int disponibilidade);

void listLivro(sqlite3 *db);

#endif