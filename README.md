---
📚 Sistema de Biblioteca

Sistema de gerenciamento de uma biblioteca desenvolvido em C++, com o objetivo de aplicar conceitos de Programação Orientada a Objetos, STL, gerenciamento de memória, herança, polimorfismo, exceções, validação de dados, regras de negócio e gerenciamento de empréstimos.

O projeto está sendo desenvolvido de forma incremental, utilizando Issues, Branches, Commits e Pull Requests para organizar a evolução do sistema.

---

📊 Status

Versão 2.0 — Em desenvolvimento.

Funcionalidades implementadas: Cadastro de livros físicos e ebooks, Listagem, Busca por ISBN, Remoção, Cadastro de usuários, Empréstimo, Devolução, Controle de disponibilidade, Limite de 3 livros, Histórico, Validação de CPF e ISBN, Hierarquia de exceções, Gerenciamento com unique_ptr.

Próxima: Centralização das validações e melhorias na arquitetura.
Futuras: Persistência, testes automatizados, banco de dados.

---

🛠️ Tecnologias

C++23, CMake 4.3+, CLion, STL (vector, find_if, all_of, lambdas, smart pointers)

---

Como compilar

git clone https://github.com/RichardKBO/SistemaDeBiblioteca.git
cd SistemaDeBiblioteca
cmake -B build
cmake --build build
./build/SistemaDeBiblioteca

Pré-requisitos: Compilador C++23, CMake 4.3+

---

Estrutura básica

SistemaDeBiblioteca/
include/ Biblioteca.h, Ebook.h, Emprestimo.h, Exception.h, Livro.h, LivroFisico.h, Usuario.h
src/ http://Biblioteca.cpp, http://Ebook.cpp, http://Emprestimo.cpp, http://Exception.cpp, http://Interface.cpp, http://Livro.cpp, http://LivroFisico.cpp, http://Usuario.cpp, http://main.cpp
http://CMakeLists.txt e http://README.md

---

Objetivo

Gerenciamento de livros, usuários e empréstimos: cadastro de físicos e ebooks, listagem, busca por ISBN, empréstimo, devolução, cadastro de usuários, remoção, controle de disponibilidade, limite por usuário, histórico, datas automáticas, validações e exceções customizadas.

Estrutura do sistema

Livro: classe base com Título, Autor, ISBN, Disponibilidade. Operações: Emprestar, Devolver, Mostrar detalhes, Consultar disponibilidade.

LivroFisico: derivado de Livro, com Quantidade de páginas e validação própria.

Ebook: derivado de Livro, com Tamanho do arquivo e validação própria.

Usuario: Nome, CPF, Número de cadastro, Livros emprestados. Operações: Adicionar livro, Devolver, Verificar posse, Listar emprestados. Limite de 3 livros.

Biblioteca: gerencia livros, usuários e empréstimos. Operações: Adicionar livro, Cadastrar/Buscar/Remover/Listar usuários, Listar/Buscar/Remover livros, Emprestar/Devolver, Buscar e Listar histórico.

Emprestimo: Número de cadastro, ISBN, Data de empréstimo, Data de devolução. Histórico em vector<Emprestimo>.

Empréstimos

Verifica: 1. Livro existe 2. Usuário existe 3. Usuário já possui livro 4. Limite de 3 livros 5. Livro disponível. Depois: Marca indisponível, Associa ao usuário, Cria registro Emprestimo, Registra data atual.

Devolução

1. Procura livro por ISBN 2. Verifica se usuário possui 3. Localiza empréstimo ativo 4. Registra data devolução 5. Marca disponível 6. Remove da lista do usuário. Registro permanece no histórico.

Datas

Usa std::chrono, std::time, std::tm. Formato DD/MM/AAAA automático.

Histórico

Contém Número de cadastro, ISBN, Data empréstimo, Data devolução. Ativo tem data devolução vazia.

Hierarquia de exceções

std::exception
- runtime_error -> BibliotecaException -> LivroNaoEncontrado, ISBNDuplicado, LivroJaPossui, LimiteEmprestimos, LivroIndisponivel, EmprestimoNaoEncontrado, UsuarioNaoEncontrado, UsuarioDuplicado, UsuarioComEmprestimos, UsuarioNaoPossuiEsseLivro, LivroEmprestado, DataEmprestimoInvalida, NomeUsuarioInvalido, CPFInvalido, NumeroDeCadastroInvalido, TituloInvalido, AutorInvalido, ISBNInvalido
- out_of_range -> BibliotecaRangeException -> QuantidadeDePaginasInvalida, TamanhoArquivoInvalido, OpcaoInvalida
- invalid_argument -> BibliotecaInvalidaException -> EntradaInvalida, TipoInvalido, DadoInvalido

Implementado em include/Exception.h e src/Exception.cpp

Regras de remoção

Usuário com livros emprestados não pode ser removido. Livro emprestado não pode ser removido.

Gerenciamento de memória

Usa std::unique_ptr e make_unique. Biblioteca armazena vector<unique_ptr<Livro>> sendo dona dos objetos, evitando new/delete manual.

Exemplo: http://biblioteca.adicionarLivro(make_unique<LivroFisico>("Jurassic Park", "Michael Crichton", "ISBN-13. 978-8576572152", true, 528));

Validação

Nome não vazio, Cadastro >0 e único, CPF 11 dígitos numéricos com dígitos verificadores. Validação com std::all_of + lambda. ISBN como identificador único.

Interface

1. Listar livros 2. Buscar livro 3. Emprestar livro 4. Devolver livro 5. Listar meus livros 6. Cadastrar livro 7. Cadastrar usuário 8. Listar usuários 9. Remover usuário 10. Remover livro 11. Listar histórico 0. Sair

Protegida por try/catch da hierarquia criada.

Conceitos praticados

POO: Classes, Encapsulamento, Herança, Polimorfismo, override, destrutor virtual, composição.
Memória: unique_ptr, make_unique, move.
STL: vector, find, find_if, all_of, Lambdas.
C++ moderno: const, auto, referências, chrono.
Validação: exceções, regras de negócio, datas automáticas.
Organização: Separação .h/.cpp, Issues e PRs.

Git

Fluxo: Issue -> Branch -> Implementação -> Commit -> Pull Request -> Merge -> main

Próximos passos

Melhorar interface, centralizar validações, seleção dinâmica de usuários, confirmações para operações destrutivas, persistência, testes, banco de dados.

Autor

Richard Kawan Barbosa Oliveira - Projeto de aprendizado C++ e POO.
LinkedIn: Richard K. B. Oliveira
GitHub: RichardKBO
Em busca de Estágio em C++ / Desenvolvimento de Software — Remoto ou Ituiutaba/MG

Observação: projeto em desenvolvimento contínuo via Git e GitHub.
---
