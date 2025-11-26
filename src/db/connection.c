#include "connection.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// Função para conectar ao banco de dados SQLite
Database conectaDB(const char *caminho_db) {
    
    Database db = {NULL, 0}; // Estrutura inicializada

    // Abre conexão com o banco
    if (sqlite3_open(caminho_db, &db.db) != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco: %s\n", sqlite3_errmsg(db.db));
        db.status = -1; // Falha
    } else {
        db.status = 1; // Sucesso
    }

    return db;
}

// Função para desconectar do banco
void discDB(Database *db) {
    if (db->db) {
        sqlite3_close(db->db); // Fecha conexão
        db->db = NULL;
    }
    db->status = 0;
}