#include "database.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// --------- Funções para tabela tbl_Livros ---------

// Adiciona novo livro
char* addLivro(sqlite3 *db, const char *titulo, const char *autor, const char *ano, int disponibilidade) {
    if (!db || !titulo || !autor || !ano || strlen(titulo) == 0 || strlen(autor) == 0 || strlen(ano) == 0) {
        fprintf(stderr, "Parâmetros inválidos para cadastrar livro\n");
        return NULL;
    }

    // Gera ID do livro
    char *novoID = genIdPers(db, "LIV", "tbl_Livros", "ID_Livro_PK", 3);
    if (!novoID) {
        fprintf(stderr, "Erro ao gerar novo ID para livro\n");
        return NULL;
    }

    // SQL de inserção
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO tbl_Livros(ID_Livro_PK, Titulo, Autor, Ano, Disponibilidade) VALUES(?, ?, ?, ?, ?);";

    int resultado = SQLITE_ERROR;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, titulo, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, autor, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, ano, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 5, disponibilidade);

        resultado = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (resultado != SQLITE_DONE) {
            fprintf(stderr, "Erro ao inserir o livro: %s\n", sqlite3_errmsg(db));
            free(novoID);
            return NULL;
        }
    } else {
        fprintf(stderr, "Erro ao preparar o statement: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }

    printf("Livro cadastrado com ID: %s\n", novoID);
    return novoID;
}