#pragma once

#include <string>
#include <vector>

struct LivroSnapshot
{
    std::string tipo;
    std::string titulo;
    std::string autor;
    std::string isbn;
    bool disponivel = true;
    int paginas = 0;
    double tamanhoArquivo = 0.0;
};

struct UsuarioSnapshot
{
    std::string nome;
    std::string cpf;
    int numeroDeCadastro = 0;
    std::vector<std::string> livrosEmprestados;
};

struct EmprestimoSnapshot
{
    int numeroDeCadastroUsuario = 0;
    std::string isbn;
    std::string dataEmprestimo;
    std::string dataDevolucao;
};

struct BibliotecaSnapshot
{
    std::vector<LivroSnapshot> livros;
    std::vector<UsuarioSnapshot> usuarios;
    std::vector<EmprestimoSnapshot> historico;
};
