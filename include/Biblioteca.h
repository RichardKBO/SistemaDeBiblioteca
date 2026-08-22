#pragma once

//Essa classe irá gerenciar as outras.

#include <memory>
#include <vector>
#include <string>

#include <Livro.h>
class Usuario;
class Biblioteca
{
private:
    std::vector<std::unique_ptr<Livro>> livros_;
    std::vector<std::unique_ptr<Usuario>> usuarios_;
public:
    void adicionarLivro(std::unique_ptr<Livro> livro);
    void cadastrarUsuario(std::unique_ptr<Usuario> usuario);
    [[nodiscard]]Usuario* buscarUsuario(int numeroDeCadastro) const;
    bool removerUsuario(int numeroDeCadastro);
    void listarUsuarios() const;

    void listarLivros() const;

    void emprestarLivro(const std::string& isbn, Usuario& usuario);
    void devolverLivro(const std::string& isbn, Usuario& usuario);
    void buscarLivro(const std::string& isbn) const;
};
