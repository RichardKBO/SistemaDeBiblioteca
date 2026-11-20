#pragma once

#include <string>

class IRelogio
{
public:
    virtual ~IRelogio() = default;

    [[nodiscard]] virtual std::string obterDataAtual() const = 0;
};
