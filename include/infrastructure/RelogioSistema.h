#pragma once

#include "application/IRelogio.h"

class RelogioSistema final : public IRelogio
{
public:
    [[nodiscard]] std::string obterDataAtual() const override;
};
