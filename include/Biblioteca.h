#pragma once

//Essa classe irá gerenciar as outas.

#include <memory>
#include <vector>
#include <string>

#include <Livro.h>
class Usuario;
class Biblioteca
{
private:
    std::vector<std::unique_ptr<Livro>> livros_;
public:
    void adicionarLivro(std::unique_ptr<Livro> livro);

    void listarLivros() const;

    void emprestarLivro(const std::string& isbn, Usuario& usuario);
    void devolverLivro(const std::string& isbn, Usuario& usuario);
    void buscarLivro(const std::string& isbn) const;
};
