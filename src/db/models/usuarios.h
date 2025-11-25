#ifndef USUARIOS_H
#define USUARIOS_H

#include <sqlite3.h>

// --------- Funções da tbl_Usuarios ---------

char* cadUser(sqlite3 *db, const char *nome, const char *sobrenome, const char *cpf, const char *numtelefone);

void listUser(sqlite3 *db);

#endif