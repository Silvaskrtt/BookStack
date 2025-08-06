# BookStack

BookStack é um sistema de gerenciamento de biblioteca com interface gráfica desenvolvida em GTK4 e banco de dados SQLite. O sistema permite o cadastro e consulta de usuários, livros e empréstimos, facilitando o controle do acervo e das movimentações da biblioteca.

## Funcionalidades

- **Cadastro de Usuários:** Nome, sobrenome, CPF e telefone.
- **Cadastro de Livros:** Título, autor, ano e disponibilidade.
- **Registro de Empréstimos:** Data de empréstimo, devolução prevista, vínculo entre livro e usuário.
- **Listagem e Consulta:** Usuários e empréstimos podem ser consultados via interface ou terminal.
- **Interface Gráfica Moderna:** Utilizando GTK4, com telas separadas para cada módulo.
- **Banco de Dados Local:** Utiliza SQLite, fácil de portar e sem necessidade de servidor externo.

## Estrutura do Projeto

```
.
├── Makefile
├── README
├── assets/
│   └── style.css
├── build/
│   ├── BookStack.exe
│   └── obj/
├── database/
│   ├── BOOKSTACK.db
│   └── BookStack.sql
├── include/
│   ├── database.h
│   ├── models.h
│   ├── sqlite3.h
│   └── sqlite3ext.h
├── lib/
│   ├── sqlite3.c
│   ├── sqlite3.def
│   └── sqlite3.dll
├── src/
│   ├── book_window.ui
│   ├── database.c
│   ├── emp_window.ui
│   ├── gui.c
│   ├── main.c
│   ├── main_window.ui
│   └── users_window.ui
└── .vscode/
    ├── c_cpp_properties.json
    └── settings.json
```

## Como Compilar

Certifique-se de ter o [GTK4](https://www.gtk.org/) e o [SQLite3](https://www.sqlite.org/) instalados.

No terminal, execute:

```sh
minGW32-make
```

O executável será gerado em `build/BookStack.exe`.

## Como Executar

Após compilar, execute ou diretamente:

```sh
./build/BookStack.exe
```

## Banco de Dados

- O banco de dados SQLite está em `database/BOOKSTACK.db`.
- O script de criação das tabelas está em `database/BookStack.sql`.
- IDs são gerados automaticamente com prefixos (`USR`, `LIV`, `EMP`, etc).

## Principais Arquivos

- [src/gui.c](src/gui.c): Interface gráfica e callbacks dos botões.
- [src/database.c](src/database.c): Funções de acesso e manipulação do banco de dados.
- [include/database.h](include/database.h): Headers das funções de banco.
- [assets/style.css](assets/style.css): Estilos visuais da interface.
- [src/main.c](src/main.c): Versão de linha de comando para testes e depuração.

## Licença

Projeto acadêmico, livre para uso educacional.

---

Desenvolvido por Murilo Chagas
