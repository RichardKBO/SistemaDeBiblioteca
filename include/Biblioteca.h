#pragma once

//Essa classe irá gerenciar as outras.

#include <memory>
#include <vector>
#include <string>

#include <Livro.h>
#include "Emprestimo.h"
#include "Usuario.h"

class Usuario;
class IBibliotecaRepository;
class IRelogio;
struct BibliotecaSnapshot;

class Biblioteca
{
private:
    std::vector<std::unique_ptr<Livro> > livros_;
    std::vector<std::unique_ptr<Usuario> > usuarios_;
    std::vector<Emprestimo> historico_;
    IBibliotecaRepository &repositorio_;
    IRelogio &relogio_;

    void carregarDados();
    void salvarDados() const;
    [[nodiscard]] BibliotecaSnapshot criarSnapshot() const;

public:
    Biblioteca(IBibliotecaRepository &repositorio, IRelogio &relogio);

    void adicionarLivro(std::unique_ptr<Livro> livro);

    void cadastrarUsuario(std::unique_ptr<Usuario> usuario);

    [[nodiscard]] Usuario *buscarUsuario(int numeroDeCadastro) const;

    Emprestimo *buscarEmprestimo(int numeroDeCadastroUsuario, const std::string &isbn);

    bool removerUsuario(int numeroDeCadastro);

    void listarUsuarios() const;

    [[nodiscard]]Livro* emprestarLivro(const std::string &isbn, Usuario &usuario);

    bool removerLivro(const std::string &isbn);

    [[nodiscard]]Livro* devolverLivro(const std::string &isbn, Usuario &usuario);

    Livro* buscarLivro(const std::string &isbn) const;

    void listarHistorico() const;

    [[nodiscard]] const std::vector<std::unique_ptr<Usuario>>& getUsuarios() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Livro>>& getLivros() const;
};
