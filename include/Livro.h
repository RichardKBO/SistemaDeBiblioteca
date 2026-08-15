#pragma once
#include <string>

//Classe abstrata pra implementação nas classes filhas.

class Livro
{
protected:
    std::string titulo;
    std::string autor;
    std::string ISBN; //International Standard Book Number.
    bool disponibilidade;
public:
    Livro(const std::string& titulo, const std::string& autor, const std::string& isbn, bool disponibilidade);

    [[nodiscard]] std::string getTitulo() const;
    [[nodiscard]] std::string getAutor() const;
    [[nodiscard]] std::string getISBN() const;
    [[nodiscard]] bool getDisponibilidade() const;

    virtual void emprestar() = 0;
    virtual void devolver() = 0;

    virtual void mostrarDetalhes() const {}

    virtual ~Livro() = default;
};