# 📚 Sistema de Biblioteca

![C++](https://img.shields.io/badge/C++-23-blue)
![CMake](https://img.shields.io/badge/CMake-4.3+-green)
![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

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
* Registro automático de datas de empréstimo e devolução
* Validação de dados
* Validação de confirmações para operações destrutivas
* Hierarquia de exceções customizadas
* Tratamento de exceções

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

A quantidade de páginas possui validação própria através de uma exceção específica.

---

## 💻 Ebook

Classe derivada de `Livro`.

Possui como característica específica:

* Tamanho do arquivo

O tamanho do arquivo possui validação própria através de uma exceção específica.

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

A classe também concentra diversas regras de negócio relacionadas ao relacionamento entre livros, usuários e empréstimos.

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
5. A data atual do sistema é registrada automaticamente.

O sistema impede que um livro indisponível seja emprestado novamente.

---

# 🔄 Devolução

Quando um livro é devolvido:

1. O sistema procura o livro através do ISBN.
2. Verifica se o usuário possui o livro.
3. Localiza o empréstimo ativo correspondente ao usuário e ao ISBN.
4. Registra automaticamente a data atual como data de devolução.
5. O livro volta a ficar disponível.
6. O livro é removido da lista de empréstimos do usuário.

O registro permanece no histórico após a devolução.

---

# 📅 Gerenciamento de datas

O sistema utiliza a data atual do computador para registrar as operações de empréstimo e devolução.

A função responsável por obter a data atual utiliza recursos da biblioteca padrão do C++:

```cpp
std::chrono
std::time
std::tm
```

A data é apresentada no formato:

```text
DD/MM/AAAA
```

### Exemplo

```text
Data de empréstimo: 30/08/2026
Data de devolução: 30/08/2026
```

Dessa forma, não é necessário que o usuário informe manualmente as datas.

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

# 🔎 Busca de empréstimo ativo

O sistema permite localizar um empréstimo ativo através de:

* Número de cadastro do usuário
* ISBN do livro

A busca considera apenas empréstimos que ainda não possuem data de devolução.

Isso permite diferenciar um empréstimo atual de registros anteriores do mesmo usuário e livro.

---

# ⚠️ Hierarquia de exceções

O projeto possui uma hierarquia própria de exceções para representar diferentes tipos de erros e regras de negócio.

As exceções específicas herdam de classes base próprias:

```text
std::exception
    │
    ├── std::runtime_error
    │       │
    │       └── BibliotecaException
    │               ├── LivroNaoEncontradoException
    │               ├── ISBNDuplicadoException
    │               ├── LivroJaPossuiException
    │               ├── LimiteEmprestimosException
    │               ├── LivroIndisponivelException
    │               ├── EmprestimoNaoEncontradoException
    │               ├── UsuarioNaoEncontradoException
    │               ├── UsuarioDuplicadoException
    │               ├── UsuarioComEmprestimosException
    │               ├── UsuarioNaoPossuiEsseLivroException
    │               ├── LivroEmprestadoException
    │               ├── DataEmprestimoInvalidaException
    │               ├── NomeUsuarioInvalidoException
    │               ├── CPFInvalidoException
    │               ├── NumeroDeCadastroInvalidoException
    │               ├── TituloInvalidoException
    │               ├── AutorInvalidoException
    │               └── ISBNInvalidoException
    │
    ├── std::out_of_range
    │       │
    │       └── BibliotecaRangeException
    │               ├── QuantidadeDePaginasInvalidaException
    │               ├── TamanhoArquivoInvalidoException
    │               └── OpcaoInvalidaException
    │
    └── std::invalid_argument
            │
            └── BibliotecaInvalidaException
                    ├── EntradaInvalidaException
                    ├── TipoInvalidoException
                    └── DadoInvalidoException
```

Essa estrutura permite agrupar exceções por categoria e tratá-las de maneira mais organizada.

### Exemplo

```cpp
try
{
    interface.cadastrarUsuario();
}
catch (const BibliotecaInvalidaException& e)
{
    std::cerr << "Erro: " << e.what() << "\n";
}
catch (const BibliotecaRangeException& e)
{
    std::cerr << "Erro: " << e.what() << "\n";
}
catch (const BibliotecaException& e)
{
    std::cerr << "Erro: " << e.what() << "\n";
}
```

As classes de exceção são implementadas em:

```text
include/Exception.h
src/Exception.cpp
```

A criação dessa hierarquia permite que o sistema utilize exceções semanticamente específicas em vez de lançar diretamente `std::runtime_error`, `std::invalid_argument` ou `std::out_of_range` em todas as situações.

---

# 🗑️ Operações destrutivas

O sistema possui proteções adicionais para operações que podem remover dados permanentemente.

Antes da remoção de um livro ou usuário, o sistema solicita uma confirmação explícita:

```text
Deseja realmente remover esse usuário? (s/n):
```

ou:

```text
Deseja realmente remover o livro com ISBN ... ? (s/n):
```

A confirmação aceita somente:

```text
s
S
n
N
```

Qualquer outro caractere gera uma `OpcaoInvalidaException`.

A validação é centralizada através da função:

```cpp
void Interface::confirmacaoValida(char confirmacao)
```

Isso evita duplicação da mesma regra em diferentes operações da interface.

### Fluxo de confirmação

```text
Operação de remoção
        |
        v
Solicita confirmação
        |
        v
Valida entrada
    /       \
   /         \
s/S           n/N
 |             |
 v             v
Executa       Cancela
remoção       operação
```

---

# 🚫 Regras de remoção

Além da confirmação, o sistema possui regras para impedir a remoção de objetos que ainda estejam envolvidos em empréstimos.

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

As situações de CPF inválido e CPF já cadastrado são tratadas por exceções específicas.

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

Além disso, título, autor e ISBN possuem validações próprias.

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

As operações são protegidas por tratamento de exceções através da hierarquia criada pelo projeto:

```cpp
try
{
    // operação
}
catch (const BibliotecaInvalidaException& e)
{
    std::cerr << "Erro: " << e.what() << "\n";
}
catch (const BibliotecaRangeException& e)
{
    std::cerr << "Erro: " << e.what() << "\n";
}
catch (const BibliotecaException& e)
{
    std::cerr << "Erro: " << e.what() << "\n";
}
```

Dessa forma, diferentes categorias de erros podem ser tratadas de maneira organizada sem encerrar o programa imediatamente.

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
* `std::chrono`

## Tratamento e validação

* Exceções
* `try`
* `catch`
* Hierarquia de exceções customizadas
* `std::runtime_error`
* `std::invalid_argument`
* `std::out_of_range`
* Validação de CPF
* Validação de ISBN
* Validação de entradas
* Validação de confirmações
* Regras de negócio
* Registro automático de datas

## Organização

* Separação entre arquivos `.h` e `.cpp`
* Separação de responsabilidades
* Modelagem de classes
* Controle de estado
* Histórico de operações
* Organização por Issues e Pull Requests

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

O próximo objetivo do desenvolvimento é continuar aprimorando a arquitetura e a qualidade do sistema.

Algumas melhorias planejadas:

* Melhorar a interface do console.
* Melhorar a centralização e organização das validações.
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
* [x] Registro automático da data de empréstimo
* [x] Registro automático da data de devolução
* [x] Busca de empréstimo ativo
* [x] Validação de CPF
* [x] Validação de ISBN
* [x] Validação de entradas
* [x] Validação de confirmações
* [x] Confirmação para operações destrutivas
* [x] Regras para remoção de usuários
* [x] Regras para remoção de livros
* [x] Hierarquia de exceções customizadas
* [x] Tratamento de exceções
* [x] Gerenciamento de memória com `std::unique_ptr`

## Próxima implementação

* [ ] Melhorias na arquitetura do sistema
* [ ] Melhorias na interface do console

## Futuras melhorias

* [ ] Persistência dos dados
* [ ] Testes automatizados
* [ ] Banco de dados
* [ ] Melhorias na interface

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
│   ├── Exception.h
│   ├── Interface.h
│   ├── Livro.h
│   ├── LivroFisico.h
│   └── Usuario.h
│
├── src/
│   ├── Biblioteca.cpp
│   ├── Ebook.cpp
│   ├── Emprestimo.cpp
│   ├── Exception.cpp
│   ├── Interface.cpp
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

O objetivo é utilizar o projeto como prática contínua de **C++, Programação Orientada a Objetos, STL, gerenciamento de memória, validação de dados, regras de negócio, tratamento de exceções e desenvolvimento de software**.

Novas funcionalidades serão adicionadas conforme a evolução do projeto.
