#ifndef id_GENERATOR_H
#define id_GENERATOR_H

#include <sqlite3.h>

// Função para gerar ID's personalizados

char* genIdPers(sqlite3 *db, const char *prefixo, const char *tabela, const char *colunaID, int totalDigitos);