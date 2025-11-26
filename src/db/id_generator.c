#include "id_generator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// Gera IDs personalizados com prefixo (ex: USR001)
char* genIdPers(sqlite3 *db, const char *prefixo, const char *tabela, const char *colunaID, int totalDigitos) {
    if (!db || !prefixo || !tabela || !colunaID || totalDigitos <= 0) return NULL;

    // Consulta SQL para pegar o maior número já usado no ID
    char sql[256];
    snprintf(sql, sizeof(sql),
        "SELECT MAX(CAST(SUBSTR(%s, %d) AS INTEGER)) FROM %s WHERE %s LIKE '%s%%';",
        colunaID,
        (int)(strlen(prefixo) + 1),
        tabela,
        colunaID,
        prefixo);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    int proximoNumero = 1; // Valor padrão se não houver registros
    if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
        proximoNumero = sqlite3_column_int(stmt, 0) + 1; // Incrementa último número encontrado
    }
    sqlite3_finalize(stmt);

    // Aloca memória para o novo ID
    int tamanhoTotal = strlen(prefixo) + totalDigitos + 1;
    char *novoID = malloc(tamanhoTotal * sizeof(char));
    if (!novoID) return NULL;

    // Formata ID (ex: USR001)
    snprintf(novoID, tamanhoTotal, "%s%0*d", prefixo, totalDigitos, proximoNumero);
    return novoID;
}