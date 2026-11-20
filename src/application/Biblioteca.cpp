#include "application/Biblioteca.h"
#include "application/BibliotecaSnapshot.h"
#include "application/IBibliotecaRepository.h"
#include "application/IRelogio.h"
#include "domain/Usuario.h"
#include "domain/Emprestimo.h"
#include "domain/Exception.h"
#include "domain/LivroFisico.h"
#include "domain/Ebook.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

Biblioteca::Biblioteca(IBibliotecaRepository &repositorio, IRelogio &relogio)
    : repositorio_(repositorio), relogio_(relogio)
{
    carregarDados();
}

BibliotecaSnapshot Biblioteca::criarSnapshot() const
{
    BibliotecaSnapshot snapshot;

    for (const auto &livro : livros_)
    {
        LivroSnapshot livroSnapshot;
        livroSnapshot.titulo = livro->getTitulo();
        livroSnapshot.autor = livro->getAutor();
        livroSnapshot.isbn = livro->getISBN();
        livroSnapshot.disponivel = livro->getDisponibilidade();

        if (const auto fisico = dynamic_cast<const LivroFisico *>(livro.get()))
        {
            livroSnapshot.tipo = "fisico";
            livroSnapshot.paginas = fisico->getQuantidadeDePaginas();
        }
        else if (const auto ebook = dynamic_cast<const Ebook *>(livro.get()))
        {
            livroSnapshot.tipo = "ebook";
            livroSnapshot.tamanhoArquivo = ebook->getTamanhoArquivo();
        }

        snapshot.livros.push_back(std::move(livroSnapshot));
    }

    for (const auto &usuario : usuarios_)
    {
        UsuarioSnapshot usuarioSnapshot;
        usuarioSnapshot.nome = usuario->getNome();
        usuarioSnapshot.cpf = usuario->getCpf();
        usuarioSnapshot.numeroDeCadastro = usuario->getNumeroDeCadastro();
        for (const Livro *livro : usuario->getLivrosEmprestados())
        {
            usuarioSnapshot.livrosEmprestados.push_back(livro->getISBN());
        }
        snapshot.usuarios.push_back(std::move(usuarioSnapshot));
    }

    for (const Emprestimo &emprestimo : historico_)
    {
        snapshot.historico.push_back({
            emprestimo.getNumeroDeCadastroUsuario(),
            emprestimo.getIsbn(),
            emprestimo.getDataEmprestimo(),
            emprestimo.getDataDevolucao()
        });
    }

    return snapshot;
}

void Biblioteca::salvarDados() const
{
    repositorio_.salvar(criarSnapshot());
}

void Biblioteca::carregarDados()
{
    const BibliotecaSnapshot snapshot = repositorio_.carregar();

    livros_.clear();
    usuarios_.clear();
    historico_.clear();

    for (const LivroSnapshot &livroSnapshot : snapshot.livros)
    {
        if (livroSnapshot.tipo == "fisico")
        {
            livros_.push_back(std::make_unique<LivroFisico>(
                livroSnapshot.titulo,
                livroSnapshot.autor,
                livroSnapshot.isbn,
                livroSnapshot.disponivel,
                livroSnapshot.paginas
            ));
        }
        else if (livroSnapshot.tipo == "ebook")
        {
            livros_.push_back(std::make_unique<Ebook>(
                livroSnapshot.titulo,
                livroSnapshot.autor,
                livroSnapshot.isbn,
                livroSnapshot.disponivel,
                livroSnapshot.tamanhoArquivo
            ));
        }
        else
        {
            throw BibliotecaException("Tipo de livro desconhecido no arquivo de persistência.");
        }
    }

    for (const UsuarioSnapshot &usuarioSnapshot : snapshot.usuarios)
    {
        auto usuario = std::make_unique<Usuario>(
            usuarioSnapshot.nome,
            usuarioSnapshot.cpf,
            usuarioSnapshot.numeroDeCadastro
        );

        for (const std::string &isbn : usuarioSnapshot.livrosEmprestados)
        {
            usuario->adicionarLivro(buscarLivro(isbn));
        }
        usuarios_.push_back(std::move(usuario));
    }

    for (const EmprestimoSnapshot &emprestimoSnapshot : snapshot.historico)
    {
        historico_.emplace_back(
            emprestimoSnapshot.numeroDeCadastroUsuario,
            emprestimoSnapshot.isbn,
            emprestimoSnapshot.dataEmprestimo,
            emprestimoSnapshot.dataDevolucao
        );
    }
}

void Biblioteca::adicionarLivro(std::unique_ptr<Livro> livro)
{
    for (const auto &livroExistente : livros_)
    {
        if (livroExistente->getISBN() == livro->getISBN())
        {
            throw ISBNDuplicadoException("Já existe um livro com esse ISBN.");
        }
    }
    livros_.push_back(std::move(livro));
    salvarDados();
}

void Biblioteca::cadastrarUsuario(std::unique_ptr<Usuario> usuario)
{
    const auto cadastroExistente = std::find_if(
        usuarios_.begin(), usuarios_.end(),
        [&usuario](const auto &existente)
        {
            return existente->getNumeroDeCadastro() == usuario->getNumeroDeCadastro();
        });

    if (cadastroExistente != usuarios_.end())
    {
        throw UsuarioDuplicadoException("Já existe um usuário com esse número de cadastro.");
    }

    const auto cpfExistente = std::find_if(
        usuarios_.begin(), usuarios_.end(),
        [&usuario](const auto &existente)
        {
            return existente->getCpf() == usuario->getCpf();
        });

    if (cpfExistente != usuarios_.end())
    {
        throw CPFJaCadastradoException("Já existe um usuário com esse CPF.");
    }

    usuarios_.push_back(std::move(usuario));
    salvarDados();
}

Usuario *Biblioteca::buscarUsuario(int numeroDeCadastro) const
{
    for (const auto &usuario : usuarios_)
    {
        if (usuario->getNumeroDeCadastro() == numeroDeCadastro)
        {
            return usuario.get();
        }
    }
    throw UsuarioNaoEncontradoException("Usuário não encontrado.");
}

const std::vector<std::unique_ptr<Usuario> > &Biblioteca::getUsuarios() const
{
    return usuarios_;
}

const std::vector<std::unique_ptr<Livro> > &Biblioteca::getLivros() const
{
    return livros_;
}

Livro *Biblioteca::buscarLivro(const std::string &isbn) const
{
    for (const auto &livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            return livro.get();
        }
    }
    throw LivroNaoEncontradoException("O livro não foi encontrado.");
}

bool Biblioteca::removerUsuario(int numeroDeCadastro)
{
    auto usuario = std::find_if(
        usuarios_.begin(), usuarios_.end(),
        [numeroDeCadastro](const auto &existente)
        {
            return existente->getNumeroDeCadastro() == numeroDeCadastro;
        });

    if (usuario == usuarios_.end())
    {
        return false;
    }
    if ((*usuario)->possuiLivrosEmprestados())
    {
        throw UsuarioComEmprestimosException(
            "O usuário possui livros emprestados e não pode ser removido.");
    }

    usuarios_.erase(usuario);
    salvarDados();
    return true;
}

void Biblioteca::listarUsuarios() const
{
    for (const auto &usuario : usuarios_)
    {
        std::cout << "Nome: " << usuario->getNome() << "\n";
        std::cout << "CPF: " << usuario->getCpf() << "\n";
        std::cout << "Número de cadastro: " << usuario->getNumeroDeCadastro() << "\n";
        std::cout << "=======================\n";
    }
}

void Biblioteca::listarHistorico() const
{
    for (const Emprestimo &emprestimo : historico_)
    {
        std::cout << "Número de cadastro: " << emprestimo.getNumeroDeCadastroUsuario() << "\n";
        std::cout << "ISBN: " << emprestimo.getIsbn() << "\n";
        std::cout << "Data de empréstimo: " << emprestimo.getDataEmprestimo() << "\n";
        std::cout << "Data de devolução: " << emprestimo.getDataDevolucao() << "\n";
        std::cout << "=======================\n";
    }
}

Livro *Biblioteca::emprestarLivro(const std::string &isbn, Usuario &usuario)
{
    for (const auto &livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            if (usuario.possuiLivro(livro.get()))
            {
                throw LivroJaPossuiException("O usuário já possui esse livro.");
            }
            if (!usuario.podeEmprestarLivro())
            {
                throw LimiteEmprestimosException(
                    "O usuário atingiu o limite de 3 livros emprestados.");
            }
            if (!livro->getDisponibilidade())
            {
                throw LivroIndisponivelException("O livro não está disponível.");
            }

            livro->emprestar();
            usuario.adicionarLivro(livro.get());
            historico_.emplace_back(
                usuario.getNumeroDeCadastro(),
                livro->getISBN(),
                relogio_.obterDataAtual()
            );
            salvarDados();
            return livro.get();
        }
    }
    throw LivroNaoEncontradoException("Livro não encontrado.");
}

bool Biblioteca::removerLivro(const std::string &isbn)
{
    auto livro = std::find_if(
        livros_.begin(), livros_.end(),
        [&isbn](const auto &existente)
        {
            return existente->getISBN() == isbn;
        });

    if (livro == livros_.end())
    {
        return false;
    }
    if (!(*livro)->getDisponibilidade())
    {
        throw LivroEmprestadoException(
            "O livro está emprestado e não pode ser removido.");
    }

    livros_.erase(livro);
    salvarDados();
    return true;
}

Emprestimo *Biblioteca::buscarEmprestimo(
    int numeroDeCadastroUsuario,
    const std::string &isbn)
{
    for (Emprestimo &emprestimo : historico_)
    {
        if (emprestimo.getNumeroDeCadastroUsuario() == numeroDeCadastroUsuario &&
            emprestimo.getIsbn() == isbn &&
            emprestimo.getDataDevolucao().empty())
        {
            return &emprestimo;
        }
    }
    throw EmprestimoNaoEncontradoException("Empréstimo não encontrado.");
}

Livro *Biblioteca::devolverLivro(const std::string &isbn, Usuario &usuario)
{
    for (const auto &livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            if (!usuario.possuiLivro(livro.get()))
            {
                throw UsuarioNaoPossuiEsseLivroException(
                    "O usuário não possui este livro.");
            }

            Emprestimo *emprestimo =
                buscarEmprestimo(usuario.getNumeroDeCadastro(), isbn);
            emprestimo->registrarDevolucao(relogio_.obterDataAtual());
            livro->devolver();
            usuario.devolverLivro(livro.get());
            salvarDados();
            return livro.get();
        }
    }
    throw LivroNaoEncontradoException("Livro não encontrado.");
}
