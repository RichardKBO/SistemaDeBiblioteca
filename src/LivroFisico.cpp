#include "LivroFisico.h"
#include <iostream>

#include <stdexcept>

LivroFisico::LivroFisico(const std::string &titulo, const std::string &autor, const std::string &isbn, bool disponibilidade, int quantidadeDePaginas)
    :Livro(titulo, autor, isbn, disponibilidade),
     quantidadeDePaginas(quantidadeDePaginas)
{
    if (quantidadeDePaginas <= 0)
    {
        throw std::invalid_argument("A quantidade de páginas deve ser maior que zero.");
    }
}

//Lógica de negócio para Biblioteca.

void LivroFisico::emprestar()
{
    if (disponibilidade)
    {
        disponibilidade = false;
    }
    else
    {
        throw std::invalid_argument("Livro indisponível para empréstimo.");
    }
}

void LivroFisico::devolver()
{
    if (!disponibilidade)
    {
        disponibilidade = true;
    }
    else
    {
        std::cout <<"Livro disponível para empréstimo." <<"\n";
    }
}

void LivroFisico::mostrarDetalhes() const
{
    std::cout <<"Quantidade de páginas: " << quantidadeDePaginas <<"\n";
    if (disponibilidade)
    {
        std::cout <<"Disponível." <<"\n";
    }
    else
    {
        std::cerr <<"Indisponível." <<"\n";
    }
}
