#pragma once
#include "domain/Livro.h"

#include <string>

class Ebook : public Livro
{
private:
    double tamanhoArquivo;

public:
    Ebook(const std::string &titulo, const std::string &autor, const std::string &isbn, bool disponibilidade,
          double tamanhoArquivo);

    [[nodiscard]] double getTamanhoArquivo() const;

    void emprestar() override;

    void devolver() override;

    void mostrarDetalhes() const override;
};
