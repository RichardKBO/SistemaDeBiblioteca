#pragma once

#include <string>
#include <vector>

/*
 * O ponteiro inteligente (unique_ptr) faz com que Biblioteca(classe que gerencia as outras)
 * seja "dona" da classe abstrata (Livro), podendo apenas referenciar por ponteiro(*)
 * a classe Livro.
 */

class Livro;
class Usuario
{
private:
    std::string nome;
    std::string cpf;
    int numeroDeCadastro;
    std::vector<Livro*> livrosEmprestados_; //Collection com ponteiro de referência.
public:
    Usuario(const std::string& nome, const std::string& cpf, int numerodecadastro);

    [[nodiscard]] std::string getNome() const;
    [[nodiscard]] std::string getCpf() const;
    [[nodiscard]] int getNumeroDeCadastro() const;

    void adicionarLivro(Livro* livro);
    bool devolverLivro(Livro* livro);
    bool possuiLivro(Livro* livro) const;
    bool possuiLivrosEmprestados() const;

    void listarLivros() const;
};