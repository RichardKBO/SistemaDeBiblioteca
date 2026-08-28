#include "Ebook.h"
#include <stdexcept>
#include <iostream>

/* A lógica é a mesma que da Classe Livro físico
 * tento deixar o mais legivel possível para ser um código
 * auto documentado.
 */


Ebook::Ebook(const std::string &titulo, const std::string &autor, const std::string &isbn, bool disponibilidade, double tamanhoArquivo)
    :Livro(titulo, autor, isbn, disponibilidade),  tamanhoArquivo(tamanhoArquivo)
{
    if (tamanhoArquivo <= 0)
    {
        throw std::invalid_argument("O tamanho do arquivo deve ser maior que zero.");
    }
}

void Ebook::emprestar()
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

void Ebook::devolver()
{
    if (!disponibilidade)
    {
        disponibilidade = true;
    }
    else
    {
        std::cout <<"Livro disponível para empréstimo." << "\n";
    }
}

void Ebook::mostrarDetalhes() const
{
    std::cout <<"Tamanho do arquivo: " << tamanhoArquivo <<"\n";

    if (disponibilidade)
    {
        std::cout <<"Disponível." <<"\n";
    }
    else
    {
        std::cerr <<"Indisponível." <<"\n";
    }
}
