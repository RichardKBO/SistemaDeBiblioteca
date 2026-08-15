#include "Usuario.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "Livro.h"

Usuario::Usuario(const std::string &nome, const std::string &cpf)
    :nome(nome), cpf(cpf)
{
    if (nome.empty())
    {
        throw std::invalid_argument("O nome de usuário é obrigatório.");
    }
    if (cpf.empty())
    {
        throw std::invalid_argument("O CPF do usuário é obrigatório.");
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

void Usuario::listarLivros() const
{
    for (const auto& livro : livrosEmprestados_)
    {
        std::cout <<"Título: " << livro->getTitulo() <<"\n";
        std::cout <<"Autor: " << livro->getAutor() <<"\n";
        std::cout <<"ISBN: " << livro->getISBN() <<"\n";
    }
}

