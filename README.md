📚 Sistema de Biblioteca

![C++](https://img.shields.io/badge/C++-23-blue)
![CMake](https://img.shields.io/badge/CMake-4.3+-green)
![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

Sistema de gerenciamento de uma biblioteca desenvolvido em C++, com o objetivo de aplicar conceitos de Programação Orientada a Objetos, STL, gerenciamento de memória, herança, polimorfismo, exceções, validação de dados, regras de negócio e gerenciamento de empréstimos.

O projeto está sendo desenvolvido de forma incremental, utilizando **Issues, Branches, Commits e Pull Requests** para organizar a evolução do sistema.

---

📊 Status

**Versão 2.0 — Em desenvolvimento.**

Funcionalidades implementadas

* [x] Cadastro de livros físicos e ebooks, listagem, busca e remoção
* [x] Cadastro, listagem, busca e remoção de usuários
* [x] Empréstimo, devolução, controle de disponibilidade e limite de 3 livros
* [x] Histórico de empréstimos com data automática via `std::chrono`
* [x] Validação de CPF, ISBN, nome e regras de negócio
* [x] Hierarquia de exceções customizadas e gerenciamento com `unique_ptr`

---

🛠️ Tecnologias

* C++23, CMake, CLion, STL (`vector`, `find_if`, `all_of`, lambdas, smart pointers)

---

🛠️ Como compilar

```bash
git clone https://github.com/RichardKBO/SistemaDeBiblioteca.git
cd SistemaDeBiblioteca
cmake -B build
cmake --build build
./build/SistemaDeBiblioteca
*Pré-requisitos:* Compilador com C++23, CMake 4.3+

---

📁 Estrutura básica
SistemaDeBiblioteca/
├── include/ (Biblioteca.h, Livro.h, LivroFisico.h, Ebook.h, Usuario.h, Emprestimo.h, Exception.h)
├── src/ (Implementações + Interface.cpp + main.cpp)
├── CMakeLists.txt
└── README.md
---

🎯 Objetivo

O sistema permite realizar operações de gerenciamento de livros, usuários e empréstimos, incluindo:

- Cadastro de livros físicos e ebooks
- Listagem de livros
- Busca de livros por ISBN
- Empréstimo de livros
- Devolução de livros
- Cadastro de usuários
- Listagem de usuários
- Busca de usuários
- Remoção de usuários
- Remoção de livros
- Controle de disponibilidade dos livros
- Controle de livros emprestados por usuário
- Limite de empréstimos por usuário
- Histórico de empréstimos
- Registro automático de datas de empréstimo e devolução
- Validação de dados
- Hierarquia de exceções customizadas
- Tratamento de exceções

---

🏗️ Estrutura do sistema

📖 Livro
Classe base responsável pelas características comuns dos livros.
Principais atributos
- Título, Autor, ISBN, Disponibilidade
A classe utiliza polimorfismo para permitir diferentes tipos de livros.
Principais operações
- Emprestar livro, Devolver livro, Mostrar detalhes, Consultar disponibilidade

📕 LivroFisico
Classe derivada de `Livro`. Característica: Quantidade de páginas com validação própria.

💻 Ebook
Classe derivada de `Livro`. Característica: Tamanho do arquivo com validação própria.

👤 Usuario
Representa um usuário cadastrado.
Possui: Nome, CPF, Número de cadastro, Livros emprestados
Principais operações
- Adicionar livro, Devolver livro, Verificar posse, Listar emprestados, Verificar se pode emprestar
Limite de empréstimos
Cada usuário pode possuir no máximo *3 livros emprestados simultaneamente*.

🏛️ Biblioteca
Classe responsável pelo gerenciamento dos livros, usuários e empréstimos.
Principais operações
- Adicionar livro, Cadastrar usuário, Buscar usuário, Remover usuário, Listar usuários, Listar livros, Buscar livro, Remover livro, Emprestar livro, Devolver livro, Buscar empréstimo, Listar histórico

📋 Emprestimo
Classe responsável por representar um empréstimo.
Cada empréstimo possui: Número de cadastro do usuário, ISBN do livro, Data do empréstimo, Data de devolução
A biblioteca mantém um histórico através de `std::vector<Emprestimo>`

---

📚 Empréstimos
Antes de realizar um empréstimo, o sistema verifica:
1. Se o livro existe. 2. Se o usuário existe. 3. Se o usuário já possui o livro.
4. Se o usuário atingiu o limite de 3 livros. 5. Se o livro está disponível.
Após: 1. Marca indisponível 2. Associa ao usuário 3. Adiciona na lista 4. Cria registro `Emprestimo` 5. Registra data atual

🔄 Devolução
1. Procura livro pelo ISBN. 2. Verifica se usuário possui. 3. Localiza empréstimo ativo. 4. Registra data de devolução. 5. Marca disponível. 6. Remove da lista do usuário. O registro permanece no histórico.

📅 Gerenciamento de datas
Utiliza `std::chrono`, `std::time`, `std::tm`. Formato `DD/MM/AAAA`.

📜 Histórico de empréstimos
Cada registro contém Número de cadastro, ISBN, Data de empréstimo, Data de devolução. Empréstimo ativo possui data de devolução vazia.

⚠️ Hierarquia de exceções
std::exception
 ├── std::runtime_error -> BibliotecaException -> [LivroNaoEncontrado, ISBNDuplicado, LimiteEmprestimos, etc]
 ├── std::out_of_range -> BibliotecaRangeException -> [QuantidadeDePaginasInvalida, TamanhoArquivoInvalido, etc]
 └── std::invalid_argument -> BibliotecaInvalidaException -> [EntradaInvalida, TipoInvalido, etc]
Implementado em `include/Exception.h` e `src/Exception.cpp`

🗑️ Regras de remoção
Usuário com livros emprestados não pode ser removido. Livro emprestado não pode ser removido.

💾 Gerenciamento de memória
Uso de `std::unique_ptr`:
biblioteca.adicionarLivro(std::make_unique<LivroFisico>("Jurassic Park", "Michael Crichton", "ISBN-13. 978-8576572152", true, 528));
Armazenado em `std::vector<std::unique_ptr<Livro>>`

🧾 Validação de usuários
Nome não vazio, Cadastro > 0 e único, CPF 11 dígitos numéricos com dígitos verificadores válidos e único. Usa `std::all_of` + lambda.

📕 Validação de livros
ISBN como identificador único, usado para busca, empréstimo, devolução e remoção. Título, autor e ISBN com validações próprias.

🖥️ Interface
1. Listar livros. 2. Buscar livro. 3. Emprestar livro. 4. Devolver livro.
5. Listar meus livros. 6. Cadastrar livro. 7. Cadastrar usuário.
8. Listar usuários. 9. Remover usuário. 10. Remover livro.
11. Listar histórico de empréstimos. 0. Sair.
🧠 Conceitos praticados
POO, Gerenciamento de memória (`unique_ptr`, `make_unique`, `move`), STL, C++ moderno (`const`, `auto`, `override`, `chrono`), Tratamento e validação, Organização por `.h/.cpp`, Issues e PRs

🌳 Desenvolvimento com Git
Fluxo: Issue -> Branch -> Implementação -> Commit -> Pull Request -> Merge -> main

🚀 Próximos passos
- Centralização e padronização das validações
- Melhorias na arquitetura, persistência, testes automatizados e banco de dados

👨‍💻 Autor
*Richard Kawan Barbosa Oliveira*
Projeto desenvolvido como prática de aprendizado e aplicação de conceitos de *C++ e POO*.
🔗 Contato
- LinkedIn: https://www.linkedin.com/in/richard-k-b-oliveira-9a1a3b287/
- GitHub: https://github.com/RichardKBO
*Em busca de Estágio em C++ / Desenvolvimento de Software — Remoto ou Ituiutaba/MG*

---

📌 Observação
Este projeto está em desenvolvimento contínuo. As funcionalidades são implementadas gradualmente, testadas e integradas através do Git e GitHub.
