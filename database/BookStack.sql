PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE tbl_Usuarios(
    ID_Usuario_PK VARCHAR(10) NOT NULL PRIMARY KEY, -- Chave primária do usuário
    Nome VARCHAR(100),                              -- Nome do usuário
    Sobrenome VARCHAR(100),                         -- Sobrenome do usuário
    CPF VARCHAR(14)                                 -- CPF do usuário
);

CREATE TABLE tbl_TelefoneUsuario(
    ID_Telefone_PK VARCHAR(10) NOT NULL PRIMARY KEY, -- Chave primária do telefone
    NumTelefone VARCHAR(14),                         -- Número de telefone
    ID_Usuario_FK VARCHAR(10),                       -- Chave estrangeira para o usuário
    FOREIGN KEY(ID_Usuario_FK) REFERENCES tbl_Usuarios(ID_Usuario_PK) -- Restrição de integridade referencial
);

CREATE TABLE tbl_Livros(
    ID_Livro_PK VARCHAR(10) NOT NULL PRIMARY KEY, -- Chave primária do livro
    Titulo VARCHAR(100),                          -- Título do livro
    Autor VARCHAR(100),                           -- Autor do livro
    Ano VARCHAR(4),                               -- Ano de publicação
    Disponibilidade INTEGER                       -- Disponibilidade (1 = disponível, 0 = indisponível)
);

CREATE TABLE tbl_Emprestimos(
    ID_Emprestimo_PK VARCHAR(10) NOT NULL PRIMARY KEY, -- Chave primária do empréstimo
    Data_Emprestimo DATE,                              -- Data do empréstimo
    Data_Devolucao DATE,                               -- Data prevista para devolução
    Data_Devolucao_Real DATE,                          -- Data real de devolução
    ID_Livro_FK VARCHAR(10),                           -- Chave estrangeira para o livro
    ID_Usuario_FK VARCHAR(10),                         -- Chave estrangeira para o usuário
    FOREIGN KEY(ID_Livro_FK) REFERENCES tbl_Livros(ID_Livro_PK),      -- Restrição de integridade referencial
    FOREIGN KEY(ID_Usuario_FK) REFERENCES tbl_Usuarios(ID_Usuario_PK)  -- Restrição de integridade referencial
);
COMMIT;
