# Arquitetura - BookStack (Refatorado)

## 📊 Diagrama de Camadas

```
┌─────────────────────────────────────────────────────────┐
│                    GUI (GTK4)                           │
│          src/view/gui.c + controllers/                  │
│  ┌─────────────┐  ┌─────────┐  ┌──────────────┐        │
│  │  Usuario    │  │  Livro  │  │ Emprestimo   │        │
│  │ Controller  │  │Controller│  │ Controller   │        │
│  └─────────────┘  └─────────┘  └──────────────┘        │
└─────────────────────────────────────────────────────────┘
           ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
┌─────────────────────────────────────────────────────────┐
│          DB Manager (Abstração)                         │
│      src/db/db_manager.c                                │
│  Interface unificada para operações de BD               │
│  • db_user_create(), db_user_list()                     │
│  • db_book_create(), db_book_list()                     │
│  • db_loan_create(), db_loan_list()                     │
└─────────────────────────────────────────────────────────┘
           ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
┌─────────────────────────────────────────────────────────┐
│        Model Layer (Operações por Entidade)             │
│            src/db/models/                               │
│  ┌──────────────┐  ┌──────────┐  ┌──────────────┐      │
│  │  usuarios.c  │  │ livros.c │  │emprestimos.c │      │
│  │(cadUser, ..) │  │(addLivro)│  │(regEmpLivro) │      │
│  └──────────────┘  └──────────┘  └──────────────┘      │
└─────────────────────────────────────────────────────────┘
           ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
┌─────────────────────────────────────────────────────────┐
│       Infrastructure (Conexão, IDs)                     │
│            src/db/                                      │
│  ┌──────────────────┐  ┌──────────────────┐            │
│  │ connection.c     │  │ id_generator.c   │            │
│  │(conectaDB, ..)   │  │(genIdPers)       │            │
│  └──────────────────┘  └──────────────────┘            │
└─────────────────────────────────────────────────────────┘
           ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
┌─────────────────────────────────────────────────────────┐
│                  SQLite3                                │
│         database/BOOKSTACK.db                           │
└─────────────────────────────────────────────────────────┘
```

## 📁 Estrutura de Pastas

```
src/
├── main.c                          ← Launcher da aplicação
│
├── view/
│   ├── gui.c / gui.h              ← Inicialização de UI
│   └── controllers/
│       ├── usuario_controller.c   ← Lógica de Usuários
│       ├── livro_controller.c     ← Lógica de Livros
│       └── emprestimo_controller.c← Lógica de Empréstimos
│
└── db/
    ├── db_manager.c / db_manager.h   ← **NOVA: Abstração centralizada**
    ├── connection.c / connection.h    ← Gerenciar conexão DB
    ├── id_generator.c / id_generator.h← Geração de IDs
    └── models/
        ├── usuarios.c / usuarios.h    ← CRUD Usuários (baixo nível)
        ├── livros.c / livros.h        ← CRUD Livros (baixo nível)
        └── emprestimos.c / emprestimos.h ← CRUD Empréstimos (baixo nível)
```

## 🔄 Fluxo de Execução (Exemplo: Cadastrar Usuário)

```
1. Usuário clica em "Cadastrar Usuário" (GUI)
   ↓
2. on_cadastrar_usuario() é chamado (usuario_controller.c)
   ↓
3. Controller extrai dados da UI (validação)
   ↓
4. Chama db_user_create(db, nome, sobrenome, cpf, telefone)
   ↓ (db_manager.c)
5. db_manager valida conexão e chama cadUser()
   ↓ (models/usuarios.c)
6. cadUser() executa SQL INSERT e retorna ID
   ↓
7. Controller exibe mensagem de sucesso + limpa campos
```

## 📌 Benefícios da Arquitetura

| Aspecto | Antes | Depois |
|---------|-------|--------|
| **Acoplamento** | Controllers → Models direto | Controllers → Manager → Models |
| **Manutenibilidade** | Múltiplas chamadas diretas | Interface unificada |
| **Reutilização** | Dificuldade em mudar BD | Fácil trocar SQLite → PostgreSQL |
| **Teste** | Difícil mockar DB | Fácil testar controller isolado |
| **Consistência** | Lógica espalhada | Centralizada em db_manager |

## ✅ O que db_manager oferece

```c
// Conexão
Database db = db_init("database/BOOKSTACK.db");
db_close(&db);

// Usuários
char* id = db_user_create(db, nome, sobrenome, cpf, telefone);
db_user_list(db);

// Livros
char* id = db_book_create(db, titulo, autor, ano, disponibilidade);
db_book_list(db);

// Empréstimos
char* id = db_loan_create(db, data_emp, data_dev, id_livro, id_user);
db_loan_list(db);
```

Todos com:
- ✅ Validação de conexão
- ✅ Tratamento de erro centralizado
- ✅ Interface consistente
- ✅ Documentação clara (comentários Doxygen)
