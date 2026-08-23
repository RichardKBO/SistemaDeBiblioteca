#include "Biblioteca.h"
#include "Usuario.h"

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>

//Lógica pra gerenciamento das classes.

void Biblioteca::adicionarLivro(std::unique_ptr<Livro> livro)
{
    for (const auto& livroExistente : livros_)
    {
        //Tratamento para evitar ISBN's iguais.
        //Para saber sobre ISBN, consulte Livro.h

        if (livroExistente->getISBN() == livro->getISBN())
        {
            throw std::invalid_argument("Já existe um livro com esse ISBN.");
        }
    }

    livros_.push_back(std::move(livro));
}

void Biblioteca::cadastrarUsuario(std::unique_ptr<Usuario> usuario)
{
    auto cadastroExistente = std::find_if(usuarios_.begin(), usuarios_.end(), [&usuario](const auto& usuarioExistente)
    {
        return usuarioExistente->getNumeroDeCadastro() == usuario->getNumeroDeCadastro();
    });

    if (cadastroExistente != usuarios_.end())
    {
        throw std::invalid_argument("Já existe um usuário com esse número de cadastro.");
    }

    auto cpfExistente = std::find_if(usuarios_.begin(), usuarios_.end(), [&usuario](const auto& usuarioExistente)
    {
        return usuarioExistente->getCpf() == usuario->getCpf();
    });

    if (cpfExistente != usuarios_.end())
    {
        throw std::invalid_argument("Já existe um usuário com esse número de cadastro.");
    }

    usuarios_.push_back(std::move(usuario));
}

Usuario* Biblioteca::buscarUsuario(int numeroDeCadastro) const // Função pra busca de usuários por número de cadastro.
{
    for (const auto& usuario : usuarios_)
    {
        if (usuario->getNumeroDeCadastro() == numeroDeCadastro)
        {
            return usuario.get();
        }
    }
    throw std::invalid_argument("Usuário não encontrado.");
}

bool Biblioteca::removerUsuario(int numeroDeCadastro) // Função para remover usuários por número de cadastro.
{
    /*
     * Expressão lambda pra percorrer os cadastros e compara,
     * assim removendo o usuário.
     */
    auto it = std::find_if(usuarios_.begin(), usuarios_.end(), [numeroDeCadastro](const auto& usuario)
    {
        return usuario->getNumeroDeCadastro() == numeroDeCadastro;
    });

    if (it == usuarios_.end())
    {
        return false;
    }

    if ((*it)->possuiLivrosEmprestados()) //Se o usuário tem livros, não remove até que o devolva.
    {
        throw std::invalid_argument("O usuário possui livros emprestados e não pode ser removido.");
    }

    usuarios_.erase(it);

    return true;
}

void Biblioteca::listarUsuarios() const
{
    std::cout <<"===============================================\n";
    std::cout <<" USUÁRIOS CADASTRADOS." <<"\n";
    std::cout <<"===============================================\n";

    for (const auto& usuario : usuarios_)
    {
        std::cout <<"Nome: " << usuario->getNome() <<"\n";
        std::cout <<"CPF: " << usuario->getCpf() <<"\n";
        std::cout <<"Número de cadastro: " << usuario->getNumeroDeCadastro() <<"\n";

        std::cout <<"===============================================\n";
    }
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
            std::cout <<"\nTítulo: " << livro->getTitulo() <<"\n";
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
            std::cout <<"\nTítulo: " << livro->getTitulo() <<"\n";
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


