# Sistema de Biblioteca

Sistema de gerenciamento de uma biblioteca desenvolvido em C++, com o objetivo de aplicar conceitos de Programação Orientada a Objetos, STL, gerenciamento de memória, herança, polimorfismo, exceções e validação de dados.

## Objetivo

O sistema permite realizar operações básicas de gerenciamento de livros e usuários, incluindo:

* Cadastro de livros físicos e ebooks
* Listagem de livros
* Busca de livros por ISBN
* Empréstimo de livros
* Devolução de livros
* Cadastro de usuários
* Listagem de usuários
* Busca de usuários
* Remoção de usuários
* Controle de disponibilidade dos livros
* Controle de livros emprestados por usuário
* Validação de dados

## Tecnologias

* C++
* C++23
* CMake
* CLion
* Standard Template Library (STL)

## Estrutura do sistema

### Livro

Classe base responsável pelas características comuns dos livros.

Principais atributos:

* Título
* Autor
* ISBN
* Disponibilidade

A classe utiliza polimorfismo para permitir diferentes tipos de livros.

### LivroFisico

Classe derivada de `Livro`.

Possui como característica específica:

* Quantidade de páginas

### Ebook

Classe derivada de `Livro`.

Possui como característica específica:

* Tamanho do arquivo

### Usuario

Representa um usuário cadastrado no sistema.

Possui:

* Nome
* CPF
* Número de cadastro
* Livros emprestados

Principais operações:

* Adicionar livro
* Devolver livro
* Verificar posse de livro
* Listar livros emprestados

### Biblioteca

Responsável pelo gerenciamento dos livros e usuários.

Principais operações:

* Adicionar livro
* Cadastrar usuário
* Buscar usuário
* Remover usuário
* Listar usuários
* Listar livros
* Buscar livro
* Emprestar livro
* Devolver livro

## Gerenciamento de memória

O sistema utiliza `std::unique_ptr` para representar a propriedade dos objetos.

Exemplo:

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

## Empréstimos

Quando um livro é emprestado:

1. O sistema procura o livro pelo ISBN.
2. O livro verifica sua disponibilidade.
3. O livro é marcado como indisponível.
4. O livro é associado ao usuário.
5. O usuário passa a possuir o livro em sua lista de empréstimos.

Quando o livro é devolvido:

1. O sistema procura o livro pelo ISBN.
2. Verifica se o usuário possui o livro.
3. O livro volta a ficar disponível.
4. O livro é removido da lista de empréstimos do usuário.

O sistema impede que um livro indisponível seja emprestado novamente.

## Validação de usuários

O cadastro de usuários possui algumas regras de validação.

### Nome

O nome não pode estar vazio.

### Número de cadastro

O número de cadastro deve ser maior que zero e não pode estar associado a outro usuário.

### CPF

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

## Validação de livros

O ISBN é utilizado como identificador do livro.

O sistema realiza a busca através do ISBN e impede o cadastro de livros com identificadores duplicados.

## Interface

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

## Conceitos praticados

Durante o desenvolvimento foram utilizados os seguintes conceitos:

* Classes
* Encapsulamento
* Herança
* Polimorfismo
* Classes abstratas
* Métodos virtuais
* `override`
* Referências
* Ponteiros
* `std::unique_ptr`
* `std::make_unique`
* `std::vector`
* Lambdas
* `std::find`
* `std::find_if`
* `std::all_of`
* Iteradores
* Algoritmos da STL
* Exceções
* `const`
* Separação entre arquivos `.h` e `.cpp`
* Separação de responsabilidades
* Regras de negócio
* Validação de dados

## Próximos passos

O próximo objetivo do desenvolvimento é melhorar o gerenciamento de usuários.

Uma das próximas regras será impedir que um usuário seja removido enquanto possuir livros emprestados.

Regra:

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

Outras melhorias planejadas:

* Melhorar a interface do console.
* Melhorar a validação de entradas.
* Permitir seleção dinâmica de usuários.
* Adicionar confirmações para operações destrutivas.
* Implementar persistência dos dados.
* Melhorar a separação entre interface e lógica de negócio.
* Adicionar testes automatizados.
* Avaliar a utilização de banco de dados em versões futuras.

## Status

Versão 2.0 — Em desenvolvimento.

O sistema atualmente possui gerenciamento de livros, usuários, empréstimos e devoluções, além de validações básicas e matemáticas para os dados dos usuários.

## Autor

Richard Kawan Barbosa Oliveira

Projeto desenvolvido como prática de aprendizado e aplicação de conceitos de C++ e Programação Orientada a Objetos.
