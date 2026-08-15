#pragma once
#include "Livro.h"

#include <string>

class Ebook : public Livro
{
private:
    double tamanhoArquivo;
public:
    Ebook(const std::string& titulo, const std::string& autor, const std::string& isbn, bool disponibilidade, double tamanhoArquivo);

    void emprestar() override;
    void devolver() override;

    void mostrarDetalhes() const override;
};