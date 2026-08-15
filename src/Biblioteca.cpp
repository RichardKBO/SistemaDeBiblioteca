#include "Biblioteca.h"
#include "Usuario.h"

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

//Lógica pra gerenciamento das classes.

void Biblioteca::adicionarLivro(std::unique_ptr<Livro> livro)
{
    livros_.push_back(std::move(livro));
}
void Biblioteca::listarLivros() const
{
    std::cout <<"===============================================\n";

    for (const auto& livro : livros_)
    {
        std::cout <<"Título: " << livro->getTitulo() <<"\n";
        std::cout <<"Autor: " << livro->getAutor() <<"\n";
        std::cout <<"ISBN: " << livro->getISBN() <<"\n";

        livro->mostrarDetalhes();

        std::cout <<"===============================================\n";
    }
}

void Biblioteca::buscarLivro(const std::string &isbn) const
{
    for (const auto& livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            std::cout <<"Título: " << livro->getTitulo() <<"\n";
            std::cout <<"Autor: " << livro->getAutor() <<"\n";
            std::cout <<"ISBN: " << livro->getISBN() <<"\n";

            livro->mostrarDetalhes();

            std::cout <<"===============================================\n";

            return;
        }
    }
    throw std::invalid_argument("O livro não foi encontrado.");
}

void Biblioteca::emprestarLivro(const std::string& isbn, Usuario& usuario)
{
    for (const auto& livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            std::cout <<"Livro emprestado: " <<"\n";
            std::cout <<"Título: " << livro->getTitulo() <<"\n";
            std::cout <<"Autor: " << livro->getAutor() <<"\n";
            std::cout <<"ISBN: " << livro->getISBN() <<"\n";

            livro->emprestar();

            usuario.adicionarLivro(livro.get());

            std::cout <<"===============================================\n";

            return;
        }
    }
    throw std::invalid_argument("Livro não encontrado.");
}

void Biblioteca::devolverLivro(const std::string &isbn, Usuario& usuario)
{
    for (const auto& livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            std::cout <<"Livro devolvido: " <<"\n";
            std::cout <<"Título: " << livro->getTitulo() <<"\n";
            std::cout <<"Autor: " << livro->getAutor() <<"\n";
            std::cout <<"ISBN: " << livro->getISBN() <<"\n";

            if (!usuario.possuiLivro(livro.get()))
            {
                throw std::invalid_argument("O usuário não possui este livro.");
            }
            livro->devolver();

            usuario.devolverLivro(livro.get());

            std::cout <<"===============================================\n";

            return;
        }
    }
    throw std::invalid_argument("Livro não encontrado.");
}
