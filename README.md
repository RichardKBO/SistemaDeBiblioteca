# 📚 Sistema de Biblioteca

![C++](https://img.shields.io/badge/C++-23-blue)
![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-green)

Sistema de gerenciamento de uma biblioteca desenvolvido em C++, com o objetivo de aplicar conceitos de Programação Orientada a Objetos, STL, gerenciamento de memória, herança, polimorfismo, exceções, validação de dados, regras de negócio e gerenciamento de empréstimos.

O projeto está sendo desenvolvido de forma incremental, utilizando **Issues, Branches, Commits e Pull Requests** para organizar a evolução do sistema.

---

## 🎯 Objetivo

O sistema permite realizar operações de gerenciamento de livros, usuários e empréstimos, incluindo:

* Cadastro de livros físicos e ebooks
* Listagem de livros
* Busca de livros por ISBN
* Empréstimo de livros
* Devolução de livros
* Cadastro de usuários
* Listagem de usuários
* Busca de usuários
* Remoção de usuários
* Remoção de livros
* Controle de disponibilidade dos livros
* Controle de livros emprestados por usuário
* Limite de empréstimos por usuário
* Histórico de empréstimos
* Registro de datas de empréstimo e devolução
* Validação de dados
* Tratamento de exceções

---

## 🛠️ Tecnologias

* C++
* C++23
* CMake
* CLion
* Standard Template Library (STL)

---

# 🏗️ Estrutura do sistema

## 📖 Livro

Classe base responsável pelas características comuns dos livros.

### Principais atributos

* Título
* Autor
* ISBN
* Disponibilidade

A classe utiliza polimorfismo para permitir diferentes tipos de livros.

### Principais operações

* Emprestar livro
* Devolver livro
* Mostrar detalhes
* Consultar disponibilidade

---

## 📕 LivroFisico

Classe derivada de `Livro`.

Possui como característica específica:

* Quantidade de páginas

---

## 💻 Ebook

Classe derivada de `Livro`.

Possui como característica específica:

* Tamanho do arquivo

---

## 👤 Usuario

Representa um usuário cadastrado no sistema.

### Possui

* Nome
* CPF
* Número de cadastro
* Livros emprestados

### Principais operações

* Adicionar livro
* Devolver livro
* Verificar posse de livro
* Listar livros emprestados
* Verificar se pode realizar novo empréstimo
* Verificar se possui livros emprestados

### Limite de empréstimos

Cada usuário pode possuir no máximo **3 livros emprestados simultaneamente**.

Caso o limite seja atingido, o sistema lança uma exceção e impede um novo empréstimo.

---

## 🏛️ Biblioteca

Classe responsável pelo gerenciamento dos livros, usuários e empréstimos.

### Principais operações

* Adicionar livro
* Cadastrar usuário
* Buscar usuário
* Remover usuário
* Listar usuários
* Listar livros
* Buscar livro
* Remover livro
* Emprestar livro
* Devolver livro
* Buscar empréstimo
* Listar histórico de empréstimos

---

## 📋 Emprestimo

Classe responsável por representar um empréstimo realizado no sistema.

Cada empréstimo possui:

* Número de cadastro do usuário
* ISBN do livro
* Data do empréstimo
* Data de devolução

A biblioteca mantém um histórico através de:

```cpp
std::vector<Emprestimo>
```

Os registros permanecem no histórico mesmo após a devolução, permitindo consultar empréstimos anteriores.

---

# 📚 Empréstimos

O processo de empréstimo possui diversas validações para garantir o cumprimento das regras de negócio.

Antes de realizar um empréstimo, o sistema verifica:

1. Se o livro existe.
2. Se o usuário existe.
3. Se o usuário já possui o livro.
4. Se o usuário atingiu o limite de 3 livros emprestados.
5. Se o livro está disponível.

Após todas as validações:

1. O livro é marcado como indisponível.
2. O livro é associado ao usuário.
3. O usuário passa a possuir o livro em sua lista de empréstimos.
4. Um registro de `Emprestimo` é criado.
5. A data do empréstimo é registrada.

O sistema impede que um livro indisponível seja emprestado novamente.

---

# 🔄 Devolução

Quando um livro é devolvido:

1. O sistema procura o livro através do ISBN.
2. Verifica se o usuário possui o livro.
3. Localiza o empréstimo ativo correspondente ao usuário e ao ISBN.
4. Registra a data de devolução.
5. O livro volta a ficar disponível.
6. O livro é removido da lista de empréstimos do usuário.

O registro permanece no histórico após a devolução.

---

# 📜 Histórico de empréstimos

O sistema mantém um histórico dos empréstimos realizados.

Cada registro contém:

```text
Número de cadastro
ISBN
Data de empréstimo
Data de devolução
```

Um empréstimo ainda ativo possui a data de devolução vazia.

### Exemplo de empréstimo ativo

```text
===============================================
HISTÓRICO DE EMPRÉSTIMOS
===============================================

Número de cadastro: 1001
ISBN: ISBN-13. 978-8576572152
Data de empréstimo: 26/08/2026
Data de devolução:
===============================================
```

### Exemplo após a devolução

```text
===============================================
HISTÓRICO DE EMPRÉSTIMOS
===============================================

Número de cadastro: 1001
ISBN: ISBN-13. 978-8576572152
Data de empréstimo: 26/08/2026
Data de devolução: 27/08/2026
===============================================
```

---

## 🔎 Busca de empréstimo ativo

O sistema permite localizar um empréstimo ativo através de:

* Número de cadastro do usuário
* ISBN do livro

A busca considera apenas empréstimos que ainda não possuem data de devolução.

Isso permite diferenciar um empréstimo atual de registros anteriores do mesmo usuário e livro.

---

# 🗑️ Regras de remoção

O sistema possui regras para impedir a remoção de objetos que ainda estejam envolvidos em empréstimos.

## Remoção de usuário

Um usuário que possui livros emprestados **não pode ser removido**.

```text
Remover usuário
      |
      v
Possui livros emprestados?
      |
   +--+--+
   |     |
  Sim   Não
   |     |
 Erro   Remover
```

## Remoção de livro

Um livro que está emprestado **não pode ser removido**.

```text
Remover livro
      |
      v
Livro está emprestado?
      |
   +--+--+
   |     |
  Sim   Não
   |     |
 Erro   Remover
```

Essas regras evitam inconsistências entre usuários, livros e empréstimos.

---

# 💾 Gerenciamento de memória

O sistema utiliza `std::unique_ptr` para representar a propriedade dos objetos.

### Exemplo

```cpp
biblioteca.adicionarLivro(
    std::make_unique<LivroFisico>(
        "Jurassic Park",
        "Michael Crichton",
        "ISBN-13. 978-8576572152",
        true,
        528
    )
);
```

Os livros são armazenados pela biblioteca através de:

```cpp
std::vector<std::unique_ptr<Livro>>
```

Os usuários seguem o mesmo princípio de gerenciamento de propriedade.

O uso de `std::unique_ptr` permite que a biblioteca seja responsável pelo ciclo de vida dos objetos, evitando gerenciamento manual de memória com `new` e `delete`.

---

# 🧾 Validação de usuários

O cadastro de usuários possui regras de validação.

## Nome

O nome não pode estar vazio.

## Número de cadastro

O número de cadastro:

* Deve ser maior que zero.
* Não pode estar associado a outro usuário.

## CPF

O CPF deve:

* Possuir exatamente 11 caracteres.
* Conter somente números.
* Possuir dígitos verificadores válidos.
* Não estar associado a outro usuário.

A validação dos caracteres utiliza `std::all_of`:

```cpp
std::all_of(
    cpf.begin(),
    cpf.end(),
    [](char caractere)
    {
        return std::isdigit(
            static_cast<unsigned char>(caractere)
        );
    }
);
```

---

# 📕 Validação de livros

O ISBN é utilizado como identificador do livro.

O sistema:

* Permite buscar livros através do ISBN.
* Impede o cadastro de livros com ISBN duplicado.
* Utiliza o ISBN para realizar empréstimos.
* Utiliza o ISBN para realizar devoluções.
* Utiliza o ISBN para localizar empréstimos.
* Utiliza o ISBN para remover livros.

---

# 🖥️ Interface

O sistema possui uma interface de console com as seguintes operações:

```text
1. Listar livros.
2. Buscar livro.
3. Emprestar livro.
4. Devolver livro.
5. Listar meus livros.
6. Cadastrar livro.
7. Cadastrar usuário.
8. Listar usuários.
9. Remover usuário.
10. Remover livro.
11. Listar histórico de empréstimos.
0. Sair.
```

As operações são protegidas por tratamento de exceções:

```cpp
try
{
    // operação
}
catch (const std::invalid_argument& e)
{
    std::cerr << "Erro: " << e.what() << "\n";
}
```

Dessa forma, erros de validação e regras de negócio podem ser tratados sem encerrar o programa imediatamente.

---

# 🧠 Conceitos praticados

Durante o desenvolvimento foram utilizados os seguintes conceitos:

## Programação Orientada a Objetos

* Classes
* Encapsulamento
* Herança
* Polimorfismo
* Classes abstratas
* Métodos virtuais
* `override`
* Destrutores virtuais
* Composição

## Gerenciamento de memória

* Ponteiros
* `std::unique_ptr`
* `std::make_unique`
* `std::move`

## STL

* `std::vector`
* `std::find`
* `std::find_if`
* `std::all_of`
* Lambdas
* Iteradores
* Algoritmos da STL

## C++ moderno

* `const`
* `auto`
* Referências
* Smart pointers
* `override`

## Tratamento e validação

* Exceções
* `try`
* `catch`
* `std::invalid_argument`
* Validação de CPF
* Validação de ISBN
* Regras de negócio

## Organização

* Separação entre arquivos `.h` e `.cpp`
* Separação de responsabilidades
* Modelagem de classes
* Controle de estado
* Histórico de operações

---

# 🌳 Desenvolvimento com Git

O desenvolvimento do projeto é organizado através de **Issues, Branches, Commits e Pull Requests**.

Cada funcionalidade ou correção é desenvolvida em uma branch específica.

### Fluxo utilizado

```text
Issue
  ↓
Branch
  ↓
Implementação
  ↓
Commit
  ↓
Pull Request
  ↓
Merge
  ↓
main
```

Esse processo permite acompanhar a evolução do projeto e manter um histórico organizado das alterações.

---

# 🚀 Próximos passos

O próximo objetivo do desenvolvimento é melhorar o gerenciamento das datas dos empréstimos.

## 📅 Data atual automática

Atualmente, as datas utilizadas pelo sistema são definidas manualmente.

A próxima implementação será responsável por obter automaticamente a data atual do sistema.

A funcionalidade deverá:

* Registrar automaticamente a data do empréstimo.
* Registrar automaticamente a data da devolução.
* Eliminar a necessidade de informar manualmente essas datas.
* Manter o formato utilizado atualmente pelo histórico.

---

## 🔮 Outras melhorias planejadas

* Melhorar a interface do console.
* Melhorar a validação de entradas.
* Permitir seleção dinâmica de usuários.
* Adicionar confirmações para operações destrutivas.
* Implementar persistência dos dados.
* Melhorar a separação entre interface e lógica de negócio.
* Adicionar testes automatizados.
* Avaliar a utilização de banco de dados em versões futuras.

---

# 📊 Status

**Versão 2.0 — Em desenvolvimento.**

## Funcionalidades implementadas

* [x] Cadastro de livros físicos
* [x] Cadastro de ebooks
* [x] Listagem de livros
* [x] Busca de livros por ISBN
* [x] Remoção de livros
* [x] Cadastro de usuários
* [x] Listagem de usuários
* [x] Busca de usuários
* [x] Remoção de usuários
* [x] Empréstimo de livros
* [x] Devolução de livros
* [x] Controle de disponibilidade
* [x] Controle de livros emprestados
* [x] Limite de 3 empréstimos por usuário
* [x] Verificação da existência do usuário
* [x] Histórico de empréstimos
* [x] Registro da data de empréstimo
* [x] Registro da data de devolução
* [x] Busca de empréstimo ativo
* [x] Validação de CPF
* [x] Validação de ISBN
* [x] Regras para remoção de usuários
* [x] Regras para remoção de livros
* [x] Tratamento de exceções
* [x] Gerenciamento de memória com `std::unique_ptr`

## Próxima implementação

* [ ] Data atual automática

## Futuras melhorias

* [ ] Persistência dos dados
* [ ] Testes automatizados
* [ ] Banco de dados
* [ ] Melhorias na interface
* [ ] Melhorias na validação

---

# 👨‍💻 Autor

**Richard Kawan Barbosa Oliveira**

Projeto desenvolvido como prática de aprendizado e aplicação de conceitos de **C++ e Programação Orientada a Objetos**.

## 🔗 Contato

* LinkedIn: [Richard K. B. Oliveira](https://www.linkedin.com/in/richard-k-b-oliveira-9a1a3b287/)
* GitHub: [RichardKBO](https://github.com/RichardKBO)

**Em busca de Estágio em C++ / Desenvolvimento de Software — Remoto ou Ituiutaba/MG**

---

# 🛠️ Como compilar

## Pré-requisitos

* C++23
* CMake 4.3+
* Compilador C++ compatível

## Compilação

Clone o repositório:

```bash
git clone https://github.com/RichardKBO/SistemaDeBiblioteca.git
```

Entre no diretório:

```bash
cd SistemaDeBiblioteca
```

Crie o diretório de build:

```bash
mkdir build
cd build
```

Configure o projeto:

```bash
cmake ..
```

Compile:

```bash
cmake --build .
```

Execute o programa gerado pelo CMake.

---

# 📁 Estrutura básica

```text
SistemaDeBiblioteca/
│
├── include/
│   ├── Biblioteca.h
│   ├── Ebook.h
│   ├── Emprestimo.h
│   ├── Livro.h
│   ├── LivroFisico.h
│   └── Usuario.h
│
├── src/
│   ├── Biblioteca.cpp
│   ├── Ebook.cpp
│   ├── Emprestimo.cpp
│   ├── Livro.cpp
│   ├── LivroFisico.cpp
│   ├── Usuario.cpp
│   └── main.cpp
│
├── CMakeLists.txt
└── README.md
```

---

## 📌 Observação

Este projeto está em desenvolvimento contínuo.

As funcionalidades são implementadas gradualmente, testadas e integradas ao projeto através do Git e GitHub.

O objetivo é utilizar o projeto como prática contínua de **C++, Programação Orientada a Objetos, STL, gerenciamento de memória, validação de dados, regras de negócio e desenvolvimento de software**.

Novas funcionalidades serão adicionadas conforme a evolução do projeto.
