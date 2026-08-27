#pragma once
#include <string>

class Emprestimo
{
    int numeroDeCadastroUsuario_;
    std::string isbn_;
    std::string dataEmprestimo_;
    std::string dataDevolucao_;

public:
    Emprestimo(
        int numeroDeCadastroUsuario,
        const std::string& isbn,
        const std::string& dataEmprestimo
    );

    void registrarDevolucao(const std::string& dataDevolucao);

    [[nodiscard]] int getNumeroDeCadastroUsuario() const;
    [[nodiscard]] std::string getIsbn() const;
    [[nodiscard]] std::string getDataEmprestimo() const;
    [[nodiscard]] std::string getDataDevolucao() const;
};