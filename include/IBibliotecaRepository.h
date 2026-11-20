#pragma once

#include "BibliotecaSnapshot.h"

class IBibliotecaRepository
{
public:
    virtual ~IBibliotecaRepository() = default;

    [[nodiscard]] virtual BibliotecaSnapshot carregar() const = 0;
    virtual void salvar(const BibliotecaSnapshot &snapshot) const = 0;
};
