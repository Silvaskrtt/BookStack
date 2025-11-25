#ifndef CONNECTION_H
#define CONNECTION_H

#include <sqlite3.h>

// STRUCT para a conexao do DB
typedef struct {
    sqlite3 *db;
    int status;
} Database;

// --------- Funções para conexão do DB ---------

Database conectaDB(const char *caminho_db);
void discDB(Database *db);