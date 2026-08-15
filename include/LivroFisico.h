#pragma once
#include "Livro.h"

class LivroFisico : public Livro
{
private:
    int quantidadeDePaginas;
public:
    LivroFisico(const std::string& titulo, const std::string& autor, const std::string& isbn, bool disponibilidade, int quantidadeDePaginas);

    void emprestar() override;
    void devolver() override;

    void mostrarDetalhes() const override;
};