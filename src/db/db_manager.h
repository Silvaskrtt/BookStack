#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "connection.h"

/*
 * DB Manager - Camada de abstração centralizada para operações de banco de dados
 * 
 * Propósito: Fornecer interface unificada para toda manipulação de dados,
 * permitindo que controllers (GUI, CLI) não precisem conhecer detalhes 
 * de implementação ou chamar múltiplas funções espalhadas.
 */

// ========== GERENCIAMENTO DE CONEXÃO ==========

/**
 * Inicializa conexão com o banco de dados
 * @param db_path Caminho do arquivo de banco de dados
 * @return Estrutura Database com status de conexão
 */
Database db_init(const char *db_path);

/**
 * Fecha conexão com o banco de dados
 * @param db Estrutura Database a ser encerrada
 */
void db_close(Database *db);

// ========== OPERAÇÕES COM USUÁRIOS ==========

/**
 * Cadastra novo usuário no sistema
 * @param db Conexão com banco de dados
 * @param nome Nome do usuário
 * @param sobrenome Sobrenome do usuário
 * @param cpf CPF do usuário
 * @param telefone Telefone de contato
 * @return ID do usuário criado (deve ser liberado com free())
 */
char* db_user_create(Database db, const char *nome, const char *sobrenome, 
                     const char *cpf, const char *telefone);

/**
 * Lista todos os usuários cadastrados
 * @param db Conexão com banco de dados
 */
void db_user_list(Database db);

// ========== OPERAÇÕES COM LIVROS ==========

/**
 * Cadastra novo livro no sistema
 * @param db Conexão com banco de dados
 * @param titulo Título do livro
 * @param autor Autor do livro
 * @param ano Ano de publicação
 * @param disponibilidade 1 se disponível, 0 caso contrário
 * @return ID do livro criado (deve ser liberado com free())
 */
char* db_book_create(Database db, const char *titulo, const char *autor, 
                     const char *ano, int disponibilidade);

/**
 * Lista todos os livros cadastrados
 * @param db Conexão com banco de dados
 */
void db_book_list(Database db);

// ========== OPERAÇÕES COM EMPRÉSTIMOS ==========

/**
 * Registra novo empréstimo de livro
 * @param db Conexão com banco de dados
 * @param data_emprestimo Data do empréstimo (formato YYYY-MM-DD)
 * @param data_devolucao Data prevista de devolução (formato YYYY-MM-DD)
 * @param id_livro ID do livro sendo emprestado
 * @param id_usuario ID do usuário solicitante
 * @return ID do empréstimo criado (deve ser liberado com free())
 */
char* db_loan_create(Database db, const char *data_emprestimo, 
                     const char *data_devolucao, const char *id_livro, 
                     const char *id_usuario);

/**
 * Lista todos os empréstimos registrados
 * @param db Conexão com banco de dados
 */
void db_loan_list(Database db);

#endif // DB_MANAGER_H
