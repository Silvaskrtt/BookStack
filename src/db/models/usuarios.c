#include "usuarios.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// --------- Funções para tabela tbl_Usuarios ---------

// Cadastra novo usuário
char* cadUser(sqlite3 *db, const char *nome, const char *sobrenome, const char *cpf, const char *numtelefone) {
    if (!db || !nome || !sobrenome || !cpf || !numtelefone ||
        strlen(nome) == 0 || strlen(sobrenome) == 0 || strlen(cpf) == 0 || strlen(numtelefone) == 0) {
        fprintf(stderr, "Parâmetros inválidos para cadastrar usuário\n");
        return NULL;
    }

    // Gera ID do usuário
    char *novoID = genIdPers(db, "USR", "tbl_Usuarios", "ID_Usuario_PK", 3);
    if (!novoID) {
        fprintf(stderr, "Erro ao gerar novo ID para usuário\n");
        return NULL;
    }

    // Gera ID do telefone
    char *novoIDTel = genIdPers(db, "TLF", "tbl_TelefoneUsuario", "ID_Telefone_PK", 3);
    if (!novoIDTel) {
        fprintf(stderr, "Erro ao gerar novo ID para telefone\n");
        return NULL;
    }

    // SQL para inserção do usuário
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO tbl_Usuarios(ID_Usuario_PK, Nome, Sobrenome, CPF) VALUES(?, ?, ?, ?);";

    int resultado = SQLITE_ERROR;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        // Vincula parâmetros
        sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, nome, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, sobrenome, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, cpf, -1, SQLITE_TRANSIENT);

        resultado = sqlite3_step(stmt); // Executa
        sqlite3_finalize(stmt);

        if (resultado != SQLITE_DONE) {
            fprintf(stderr, "Erro ao inserir usuário: %s\n", sqlite3_errmsg(db));
            free(novoID);
            return NULL;
        }
    } else {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }

    // SQL para inserção do telefone
    sqlite3_stmt *stmt_tel;
    const char *sql_tel = "INSERT INTO tbl_TelefoneUsuario(ID_Telefone_PK, NumTelefone, ID_Usuario_FK) VALUES(?, ?, ?);";

    int resultado_tel = SQLITE_ERROR;
    if (sqlite3_prepare_v2(db, sql_tel, -1, &stmt_tel, NULL) == SQLITE_OK) {
        // Vincula parâmetros
        sqlite3_bind_text(stmt_tel, 1, novoIDTel, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt_tel, 2, numtelefone, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt_tel, 3, novoID, -1, SQLITE_TRANSIENT);

        resultado_tel = sqlite3_step(stmt_tel); // Executa
        sqlite3_finalize(stmt_tel);

        if (resultado_tel != SQLITE_DONE) {
            fprintf(stderr, "Erro ao inserir telefone: %s\n", sqlite3_errmsg(db));
            free(novoIDTel);
            return NULL;
        }
    } else {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        free(novoIDTel);
        return NULL;
    }

    printf("Usuário cadastrado com ID: %s\n", novoID);
    printf("Telefone cadastrado com ID: %s\n", novoIDTel);
    free(novoIDTel);
    return novoID;
}

// Lista todos os usuários
void listUser(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ID_Usuario_PK, Nome, Sobrenome, CPF FROM tbl_Usuarios;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n=== Lista de Usuários ===\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *id = (const char *)sqlite3_column_text(stmt, 0);
        const char *nome = (const char *)sqlite3_column_text(stmt, 1);
        const char *sobrenome = (const char *)sqlite3_column_text(stmt, 2);
        const char *cpf = (const char *)sqlite3_column_text(stmt, 3);
        printf("ID: %s | Nome: %s %s | CPF: %s\n", id, nome, sobrenome, cpf);
    }

    sqlite3_finalize(stmt);
}