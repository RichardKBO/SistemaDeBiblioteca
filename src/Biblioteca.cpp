#include "Biblioteca.h"
#include "Usuario.h"
#include "Emprestimo.h"

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

//Lógica pra gerenciamento das classes.


std::string obterDataAtual()
{
    const auto agora = std::chrono::system_clock::now();
    const std::time_t tempo = std::chrono::system_clock::to_time_t(agora);

    std::tm data{};

    localtime_r(&tempo, &data);

    std::ostringstream resultado;

    resultado << std::setfill('0') << std::setw(2) << data.tm_mday << "/"
              << std::setw(2) << data.tm_mon + 1 << "/"
              << data.tm_year + 1900;

    return resultado.str();
}

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

void Biblioteca::listarHistorico() const
{
    std::cout <<"===============================================\n";
    std::cout <<"HISTÓRICO DE EMPRÉSTIMOS\n";
    std::cout <<"===============================================\n";

    for (const auto& emprestimo : historico_)
    {
        std::cout <<"Número de cadastro: " << emprestimo.getNumeroDeCadastroUsuario() <<"\n";
        std ::cout <<"ISBN: " << emprestimo.getIsbn() <<"\n";
        std::cout <<"Data de empréstimo: " << emprestimo.getDataEmprestimo() <<"\n";
        std::cout <<"Data de devolução: " << emprestimo.getDataDevolucao() <<"\n";

        std::cout <<"===============================================\n";
    }
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

            if (usuario.possuiLivro(livro.get()))
            {
                throw std::invalid_argument("O usuário já possui esse livro.");
            }

            if (!usuario.podeEmprestarLivro())
            {
                throw std::invalid_argument("O usuário atingiu o limite de 3 livros emprestados.");
            }

            if (!livro->getDisponibilidade())
            {
                throw std::invalid_argument("O livro não está disponível.");
            }

            livro->emprestar();

            usuario.adicionarLivro(livro.get());

            historico_.emplace_back(
                usuario.getNumeroDeCadastro(),
                livro->getISBN(),
                obterDataAtual()
                );

            std::cout <<"===============================================\n";

            return;
        }
    }
    throw std::invalid_argument("Livro não encontrado.");
}

bool Biblioteca::removerLivro(const std::string &isbn)
{
    auto it = std::find_if(livros_.begin(), livros_.end(), [&isbn](const auto& livro)
    {
       return livro->getISBN() == isbn;
    });

    if (it == livros_.end())
    {
        return false;
    }

    if (!(*it)->getDisponibilidade())
    {
        throw std::invalid_argument("O livro está emprestado e não pode ser removido.");
    }

    livros_.erase(it);

    return true;
}

Emprestimo *Biblioteca::buscarEmprestimo(int numeroDeCadastroUsuario, const std::string &isbn)
{
    for (auto& emprestimo : historico_)
    {
        if (emprestimo.getNumeroDeCadastroUsuario() == numeroDeCadastroUsuario &&
            emprestimo.getIsbn() == isbn &&
            emprestimo.getDataDevolucao().empty()
            )
        {
            return &emprestimo;
        }
    }
    throw std::invalid_argument("Empréstimo não encontrado.");
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

            Emprestimo* emprestimo = buscarEmprestimo(usuario.getNumeroDeCadastro(), isbn);
            emprestimo->registrarDevolucao(obterDataAtual());

            livro->devolver();

            usuario.devolverLivro(livro.get());

            std::cout <<"===============================================\n";

            return;
        }
    }
    throw std::invalid_argument("Livro não encontrado.");
}


