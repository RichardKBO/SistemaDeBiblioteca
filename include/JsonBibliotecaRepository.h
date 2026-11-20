#pragma once

#include "IBibliotecaRepository.h"

#include <string>

class JsonBibliotecaRepository final : public IBibliotecaRepository
{
private:
    std::string caminhoArquivo_;

public:
    explicit JsonBibliotecaRepository(std::string caminhoArquivo = "biblioteca.json");

    [[nodiscard]] BibliotecaSnapshot carregar() const override;
    void salvar(const BibliotecaSnapshot &snapshot) const override;
};
