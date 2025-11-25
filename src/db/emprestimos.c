#include "database.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// --------- Funções para tabela tbl_Emprestimos ---------

// Registra empréstimo de um livro
char* regEmpLivro(sqlite3 *db, const char *data_emprestimo, const char *data_devolucao, const char *id_livro_fk, const char *id_usuario_fk) {
    if (!db || !data_emprestimo || !data_devolucao || !id_livro_fk || !id_usuario_fk ||
        strlen(data_emprestimo) == 0 || strlen(data_devolucao) == 0 ||
        strlen(id_livro_fk) == 0 || strlen(id_usuario_fk) == 0) {
        fprintf(stderr, "Parâmetros inválidos para registrar o empréstimo do livro com ID: %s\n", id_livro_fk);
        return NULL;
    }

    // Gera ID do empréstimo
    char *novoID = genIdPers(db, "EMP", "tbl_Emprestimos", "ID_Emprestimo_PK", 3);
    if (!novoID) {
        fprintf(stderr, "Erro ao gerar novo ID para o empréstimo\n");
        return NULL;
    }

    // SQL de inserção
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO tbl_Emprestimos(ID_Emprestimo_PK, Data_Emprestimo, Data_Devolucao, ID_Livro_FK, ID_Usuario_FK) VALUES(?, ?, ?, ?, ?);";

    int resultado = SQLITE_ERROR;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, data_emprestimo, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, data_devolucao, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, id_livro_fk, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, id_usuario_fk, -1, SQLITE_TRANSIENT);

        resultado = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (resultado != SQLITE_DONE) {
            fprintf(stderr, "Erro ao registrar empréstimo: %s\n", sqlite3_errmsg(db));
            free(novoID);
            return NULL;
        }
    } else {
        fprintf(stderr, "Erro ao preparar o statement: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }

    printf("Empréstimo registrado com ID: %s\n", novoID);
    return novoID;
}

// Consulta todos os empréstimos e exibe formatado
void consultEmp(sqlite3 *db) {
    const char *sql =
        "SELECT "
        "    tbl_Emprestimos.ID_Emprestimo_PK, "
        "    tbl_Emprestimos.ID_Livro_FK, "
        "    tbl_Emprestimos.ID_Usuario_FK, "
        "    tbl_Livros.Titulo, "
        "    tbl_Usuarios.Nome, "
        "    tbl_Usuarios.Sobrenome "
        "FROM tbl_Emprestimos "
        "INNER JOIN tbl_Livros "
        "    ON tbl_Emprestimos.ID_Livro_FK = tbl_Livros.ID_Livro_PK "
        "INNER JOIN tbl_Usuarios "
        "    ON tbl_Emprestimos.ID_Usuario_FK = tbl_Usuarios.ID_Usuario_PK;";

    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Cabeçalho formatado
    printf("---------------------------------------------------------------------------------------------\n");
    printf("| %-12s | %-8s | %-10s | %-30s | %-12s | %-12s |\n",
           "ID Emprestimo", "ID Livro", "ID Usuário", "Título", "Nome", "Sobrenome");
    printf("---------------------------------------------------------------------------------------------\n");

    // Percorre resultados
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char *id_emprestimo_pk = sqlite3_column_text(stmt, 0);
        const unsigned char *id_livro_fk      = sqlite3_column_text(stmt, 1);
        const unsigned char *id_usuario_fk    = sqlite3_column_text(stmt, 2);
        const unsigned char *titulo           = sqlite3_column_text(stmt, 3);
        const unsigned char *nome             = sqlite3_column_text(stmt, 4);
        const unsigned char *sobrenome        = sqlite3_column_text(stmt, 5);

        printf("| %-12s | %-8s | %-10s | %-30s | %-12s | %-12s |\n",
               id_emprestimo_pk ? (const char*)id_emprestimo_pk : "",
               id_livro_fk ? (const char*)id_livro_fk : "",
               id_usuario_fk ? (const char*)id_usuario_fk : "",
               titulo ? (const char*)titulo : "",
               nome ? (const char*)nome : "",
               sobrenome ? (const char*)sobrenome : "");
    }

    printf("---------------------------------------------------------------------------------------------\n");

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao percorrer resultados: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}