# 📚 Sistema de Biblioteca

![C++](https://img.shields.io/badge/C++-23-blue)
![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-green)

Sistema de gerenciamento de uma biblioteca desenvolvido em C++, com o objetivo de aplicar conceitos de Programação Orientada a Objetos, STL, gerenciamento de memória, herança, polimorfismo, exceções, validação de dados, regras de negócio e gerenciamento de empréstimos.

O projeto está sendo desenvolvido de forma incremental, utilizando **Issues, Branches, Commits e Pull Requests** para organizar a evolução do sistema.

---

## 🎯 Objetivo

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
- Validação de dados
- Tratamento de exceções

---

## 🛠️ Tecnologias

- C++
- C++23
- CMake
- CLion
- Standard Template Library (STL)

---

# 🏗️ Estrutura do sistema

## 📖 Livro

Classe base responsável pelas características comuns dos livros.

Principais atributos:

- Título
- Autor
- ISBN
- Disponibilidade

A classe utiliza polimorfismo para permitir diferentes tipos de livros.

Principais operações:

- Emprestar livro
- Devolver livro
- Mostrar detalhes
- Consultar disponibilidade

---

## 📕 LivroFisico

Classe derivada de `Livro`.

Possui como característica específica:

- Quantidade de páginas

---

## 💻 Ebook

Classe derivada de `Livro`.

Possui como característica específica:

- Tamanho do arquivo

---

## 👤 Usuario

Representa um usuário cadastrado no sistema.

Possui:

- Nome
- CPF
- Número de cadastro
- Livros emprestados

Principais operações:

- Adicionar livro
- Devolver livro
- Verificar posse de livro
- Listar livros emprestados
- Verificar se pode realizar novo empréstimo
- Verificar se possui livros emprestados

### Limite de empréstimos

Cada usuário pode possuir no máximo **3 livros emprestados simultaneamente**.

Caso o limite seja atingido, o sistema lança uma exceção e impede um novo empréstimo.

---

## 🏛️ Biblioteca

Classe responsável pelo gerenciamento dos livros, usuários e empréstimos.

Principais operações:

- Adicionar livro
- Cadastrar usuário
- Buscar usuário
- Remover usuário
- Listar usuários
- Listar livros
- Buscar livro
- Remover livro
- Emprestar livro
- Devolver livro
- Buscar empréstimo
- Listar histórico de empréstimos

---

## 📋 Emprestimo

Classe responsável por representar um empréstimo realizado no sistema.

Cada empréstimo possui:

- Número de cadastro do usuário
- ISBN do livro
- Data do empréstimo
- Data de devolução

A biblioteca mantém um histórico através de:

```cpp
std::vector<Emprestimo>
