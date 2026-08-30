#include "Emprestimo.h"
#include "Exception.h"

#include <stdexcept>

Emprestimo::Emprestimo(
    int numeroDeCadastroUsuario,
    const std::string &isbn,
    const std::string &dataEmprestimo
)
    : numeroDeCadastroUsuario_(numeroDeCadastroUsuario),
      isbn_(isbn),
      dataEmprestimo_(dataEmprestimo)
{
    if (dataEmprestimo.empty())
    {
        throw DataEmprestimoInvalidaException("A data de empréstimo não pode ficar vazia.");
    }
}

int Emprestimo::getNumeroDeCadastroUsuario() const
{
    return numeroDeCadastroUsuario_;
}

std::string Emprestimo::getIsbn() const
{
    return isbn_;
}

std::string Emprestimo::getDataEmprestimo() const
{
    return dataEmprestimo_;
}

void Emprestimo::registrarDevolucao(const std::string &dataDevolucao)
{
    if (dataDevolucao.empty())
    {
        throw DataDevolucaoException("A data de devolução não pode permanecer vazia.");
    }

    dataDevolucao_ = dataDevolucao;
}

std::string Emprestimo::getDataDevolucao() const
{
    return dataDevolucao_;
}
