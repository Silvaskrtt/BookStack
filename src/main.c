#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <windows.h>

#define TAM_MAX 100     // Tamanho máximo para as strings usadas no programa

// Remove o caractere de nova linha do final da string, caso exista
void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

int main() {

    // Configura o console para aceitar caracteres UTF-8 no Windows
    SetConsoleOutputCP(CP_UTF8);

    // Variáveis para dados do usuário
    char nome[TAM_MAX];
    char sobrenome[TAM_MAX];
    char cpf[TAM_MAX];
    char numtelefone[TAM_MAX];

    // Variáveis para dados do livro
    char titulo[TAM_MAX];
    char autor[TAM_MAX];
    char ano[TAM_MAX];
    char disponibilidade[TAM_MAX];

    // Variáveis para dados do empréstimo
    char data_emprestimo[TAM_MAX];
    char data_devolucao[TAM_MAX];
    char id_livro_fk[TAM_MAX];
    char id_usuario_fk[TAM_MAX];

    // ===== Cadastro de Usuário =====
    printf("=== Cadastro de Usuário ===\n");

    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    removerNovaLinha(nome);

    printf("Sobrenome: ");
    fgets(sobrenome, sizeof(sobrenome), stdin);
    removerNovaLinha(sobrenome);

    printf("CPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    removerNovaLinha(cpf);

    printf("Telefone: ");
    fgets(numtelefone, sizeof(numtelefone), stdin);
    removerNovaLinha(numtelefone);

    // ===== Cadastro de Livro =====
    printf("=== Cadastro de Livro ===\n");

    printf("Título: ");
    fgets(titulo, sizeof(titulo), stdin);
    removerNovaLinha(titulo);

    printf("Autor: ");
    fgets(autor, sizeof(autor), stdin);
    removerNovaLinha(autor);

    printf("Ano: ");
    fgets(ano, sizeof(ano), stdin);
    removerNovaLinha(ano);

    printf("Disponibilidade (0 ou 1): ");
    fgets(disponibilidade, sizeof(disponibilidade), stdin);
    removerNovaLinha(disponibilidade);
    int dispInt = atoi(disponibilidade);  // Converte para inteiro

    // ===== Cadastro de Empréstimo =====
    printf("=== Cadastro de Emprestimo ===\n");

    printf("Data Emprestimo: ");
    fgets(data_emprestimo, sizeof(data_emprestimo), stdin);
    removerNovaLinha(data_emprestimo);

    printf("Data da devolução Prevista: ");
    fgets(data_devolucao, sizeof(data_devolucao), stdin);
    removerNovaLinha(data_devolucao);

    printf("ID do Livro a ser Emprestado: ");
    fgets(id_livro_fk, sizeof(id_livro_fk), stdin);
    removerNovaLinha(id_livro_fk);

    printf("Matrícula do Usuario (ID): ");
    fgets(id_usuario_fk, sizeof(id_usuario_fk), stdin);
    removerNovaLinha(id_usuario_fk);

    // ===== Conexão com o banco de dados =====
    const char *caminho_db = "database/BOOKSTACK.db";
    Database db = conectaDB(caminho_db);

    if (db.status != 1) {
        fprintf(stderr, "Erro ao conectar ao banco.\n");
        return 1;
    }

    // ===== Inserir Usuário =====
    char *idUsuario = cadUser(db.db, nome, sobrenome, cpf, numtelefone);
    if (idUsuario) {
        printf("Usuário cadastrado com sucesso. ID: %s\n", idUsuario);
        free(idUsuario);
    } else {
        fprintf(stderr, "Erro ao cadastrar usuário.\n");
    }

    // ===== Inserir Livro =====
    char *idLivro = addLivro(db.db, titulo, autor, ano, dispInt);
    if (idLivro) {
        printf("Livro cadastrado com sucesso. ID: %s\n", idLivro);
        free(idLivro);
    } else {
        fprintf(stderr, "Erro ao cadastrar livro.\n");
    }

    // ===== Registrar Empréstimo =====
    char *idEmp = regEmpLivro(db.db, data_emprestimo, data_devolucao, id_livro_fk, id_usuario_fk);
    if (idEmp) {
        printf("Livro emprestado com ID: %s\n", idEmp);
        free(idEmp);
    } else {
        fprintf(stderr, "Erro ao emprestar o livro.\n");
    }

    // ===== Listar Usuários =====
    listUser(db.db);

    // ===== Consultar Empréstimos =====
    consultEmp(db.db);

    // ===== Fechar conexão com o banco =====
    discDB(&db);

    return 0; // Fim do programa
}