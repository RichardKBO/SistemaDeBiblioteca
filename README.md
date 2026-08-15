# Sistema de Biblioteca

Meu primeiro projeto de sistema de biblioteca em C++.

Estou desenvolvendo este projeto para praticar Programação Orientada a Objetos e melhorar minha organização de código em projetos C++.

## O que o sistema faz

* Cadastra livros físicos e ebooks
* Lista os livros da biblioteca
* Busca livros pelo ISBN
* Permite emprestar livros
* Permite devolver livros
* Controla a disponibilidade dos livros
* Controla quais livros cada usuário possui

## O que pratiquei neste projeto

* Classes e objetos
* Herança
* Polimorfismo
* Classes abstratas
* Encapsulamento
* Métodos `virtual` e `override`
* `std::vector`
* `std::unique_ptr`
* Ponteiros
* `std::find`
* Iterators
* Exceções com `std::invalid_argument`
* Separação entre arquivos `.h` e `.cpp`
* Organização de um projeto com CMake

## Estrutura do projeto

```text
SistemaDeBiblioteca/
├── include/
│   ├── Biblioteca.h
│   ├── Ebook.h
│   ├── Livro.h
│   ├── LivroFisico.h
│   └── Usuario.h
│
├── src/
│   ├── Biblioteca.cpp
│   ├── Ebook.cpp
│   ├── Livro.cpp
│   ├── LivroFisico.cpp
│   ├── Usuario.cpp
│   └── main.cpp
│
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Tecnologias

* C++
* CMake
* CLion

## Sobre o projeto

Este é um projeto de estudo. Ainda estou aprendendo C++ e Programação Orientada a Objetos, então pretendo melhorar e adicionar novas funcionalidades conforme avanço nos estudos.
