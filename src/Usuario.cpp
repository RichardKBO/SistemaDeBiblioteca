#include "Usuario.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cctype>

#include "Interface.h"
#include "Livro.h"

bool cpfValido(const std::string &cpf)
{
    if (cpf.length() != 11)
    {
        return false;
    }

    if (!std::all_of(cpf.begin(), cpf.end(), [](char caractere)
    {
        return std::isdigit(static_cast<unsigned char>(caractere));
    }))
    {
        return false;
    }

    int soma = 0;

    //Primeiro digito verificador
    for (int i = 0; i < 9; ++i)
    {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int primeiroDigito = (soma * 10) % 11;

    if (primeiroDigito == 10)
    {
        primeiroDigito = 0;
    }

    if (primeiroDigito != cpf[9] - '0')
    {
        return false;
    }

    //Segundo digito verificador

    soma = 0;

    for (int i = 0; i < 10; ++i)
    {
        soma += (cpf[i] - '0') * (11 - i);
    }

    int segundoDigito = (soma * 10) % 11;

    if (segundoDigito == 10)
    {
        segundoDigito = 0;
    }

    if (segundoDigito != cpf[10] - '0')
    {
        return false;
    }
    return true;
}

Usuario::Usuario(const std::string &nome, const std::string &cpf, int numeroDeCadastro)
    :nome(nome), cpf(cpf),
     numeroDeCadastro(numeroDeCadastro)
{
    if (nome.empty())
    {
        throw std::invalid_argument("O nome de usuário é obrigatório.");
    }
    if (!cpfValido(cpf))
    {
        throw std::invalid_argument("O CPF do usuário é obrigatório.");
    }
    if (numeroDeCadastro <= 0)
    {
        throw std::invalid_argument("O número de cadastro deve ser maior que zero.");
    }
}

std::string Usuario::getNome() const
{
    return nome;
}

std::string Usuario::getCpf() const
{
    return cpf;
}

int Usuario::getNumeroDeCadastro() const
{
    return numeroDeCadastro;
}

//Lógica de negócio pra Usuário.

void Usuario::adicionarLivro(Livro *livro)
{
    livrosEmprestados_.push_back(livro);
}

bool Usuario::devolverLivro(Livro *livro)
{
    auto it = std::find(
        livrosEmprestados_.begin(), livrosEmprestados_.end(), livro);

    if (it != livrosEmprestados_.end())
    {
        livrosEmprestados_.erase(it);
        return true;
    }
    return false;
}

bool Usuario::possuiLivro(Livro *livro) const
{
    auto it = std::find(
        livrosEmprestados_.begin(), livrosEmprestados_.end(), livro);

    return it != livrosEmprestados_.end();
}

bool Usuario::possuiLivrosEmprestados() const
{
    return !livrosEmprestados_.empty();
}

bool Usuario::podeEmprestarLivro() const
{
    return livrosEmprestados_.size() < 3;
}

void Usuario::listarLivros() const
{
    for (const auto &livro: livrosEmprestados_)
    {
        std::cout << "Título: " << livro->getTitulo() << "\n";
        std::cout << "Autor: " << livro->getAutor() << "\n";
        std::cout << "ISBN: " << livro->getISBN() << "\n";
    }
}
