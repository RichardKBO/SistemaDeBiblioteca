#include "Livro.h"
#include "Exception.h"

Livro::Livro(const std::string &titulo, const std::string &autor, const std::string &isbn, bool disponibilidade)
    : titulo(titulo),
      autor(autor),
      ISBN(isbn),
      disponibilidade(disponibilidade)
{
    //Verificações e disparada de excepts.

    if (titulo.empty())
    {
        throw TituloInvalidoException("O título do livro não pode permanecer vazio.");
    }
    if (autor.empty())
    {
        throw AutorInvalidoException("O nome do autor não pode permanecer vazio.");
    }
    if (isbn.empty())
    {
        throw ISBNInvalidoException("O ISBN não pode permanecer vazio.");
    }
}

std::string Livro::getAutor() const
{
    return autor;
}

std::string Livro::getTitulo() const
{
    return titulo;
}

std::string Livro::getISBN() const
{
    return ISBN;
}

bool Livro::getDisponibilidade() const
{
    if (disponibilidade == true)
    {
        return "Disponibilidade: Diponível";
    } else
    {
        return "Disponibilidade: Indisponivel";
    }
}
