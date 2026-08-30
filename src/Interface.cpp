#include "Interface.h"
#include "Biblioteca.h"
#include "LivroFisico.h"
#include "Ebook.h"
#include "Usuario.h"

#include <stdexcept>
#include <iostream>
#include <memory>
#include <limits>

Interface::Interface(Biblioteca &biblioteca)
    :biblioteca(biblioteca)
{
}

int Interface::lerNumeroInteiro(const std::string &mensagem)
{
    int valor;

    std::cout << mensagem;

    if (!(std::cin >> valor))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw std::invalid_argument("Valor inválido.");
    }
    return valor;
}

double Interface::lerNumeroDouble(const std::string &mensagem)
{
    double valor;
    std::cout << mensagem;

    if (!(std::cin >> valor))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw std::invalid_argument("Valor inválido.");
    }
    return valor;
}
//Livros
void Interface::cadastrarLivro()
{
    int tipo;

    std::cout << "\n";
    std::cout << "==== CADASTRAR LIVRO ====\n";
    std::cout << "1 - Livro físico." << "\n";
    std::cout << "2 - Ebook." << "\n";
    tipo = lerNumeroInteiro("Escolha um tipo: ");


    switch (tipo)
    {
        case 1:
        {
            std::string titulo;
            std::string autor;
            std::string isbn;
            int paginas;

            std::cout << "\n";

            std::cout << "Digite o título: ";
            std::getline(std::cin >> std::ws, titulo);

            std::cout << "Digite o nome do autor: ";
            std::getline(std::cin >> std::ws, autor);

            std::cout << "Digite o ISBN: ";
            std::getline(std::cin >> std::ws, isbn);

            paginas = lerNumeroInteiro("Digite o número de páginas: ");

            if (paginas <= 0)
            {
                throw std::out_of_range("O número de páginas deve ser maior que zero.");
            }

            biblioteca.adicionarLivro(std::make_unique<LivroFisico>(titulo, autor, isbn, true, paginas));

            std::cout << "Livro cadastrado com sucesso." << "\n";

            break;
        }

        case 2:
        {
            std::string titulo;
            std::string autor;
            std::string isbn;
            double tamanhoDoArquivo;

            std::cout << "\n";

            std::cout << "Digite o título: ";
            std::getline(std::cin >> std::ws, titulo);

            std::cout << "Digite o nome do autor: ";
            std::getline(std::cin >> std::ws, autor);

            std::cout << "Digite o ISBN: ";
            std::getline(std::cin >> std::ws, isbn);

            tamanhoDoArquivo = lerNumeroDouble("Digite o tamanho do arquivo: ");

            if (tamanhoDoArquivo <= 0)
            {
                throw std::out_of_range("O tamanho do arquivo precisa ser maior que zero.");
            }

            biblioteca.adicionarLivro(std::make_unique<Ebook>(titulo, autor, isbn, true, tamanhoDoArquivo));

            std::cout << "Ebook cadastrado." << "\n";
            break;
        }

        default:
            throw std::invalid_argument("Tipo de livro inválido.");
    }
}

void Interface::buscarLivro()
{
    std::string isbn;

    std::cout << "Digite o ISBN: ";
    std::getline(std::cin >> std::ws, isbn);

    biblioteca.buscarLivro(isbn);
}

void Interface::listarMeusLivros()
{
    int numeroDeCadastro;

    numeroDeCadastro = lerNumeroInteiro("Digite o número de cadastro: ");

  Usuario* usuario = biblioteca.buscarUsuario(numeroDeCadastro);

    usuario->listarLivros();
}

void Interface::listarLivros()
{
    biblioteca.listarLivros();
}

void Interface::emprestarLivro()
{
    std::string isbn;

    std::cout << "Digite o ISBN: ";
    std::getline(std::cin >> std::ws, isbn);

    int numeroDeCadastro = lerNumeroInteiro("Digite o número de cadastro: ");

    Usuario *usuario = biblioteca.buscarUsuario(numeroDeCadastro);

    biblioteca.emprestarLivro(isbn, *usuario);
}

void Interface::devolverLivro()
{
    std::string isbn;

    std::cout << "Digite o ISBN: ";
    std::getline(std::cin >> std::ws, isbn);

    int numeroDeCadastro = lerNumeroInteiro("Digite o número de cadastro: ");

    Usuario *usuario = biblioteca.buscarUsuario(numeroDeCadastro);

    biblioteca.devolverLivro(isbn, *usuario);
}

void Interface::removerLivro()
{
    std::string isbn;

    std::cout << "Digite o ISBN: ";
    std::getline(std::cin >> std::ws, isbn);

    if (biblioteca.removerLivro(isbn))
    {
        std::cout << "Livro removido com sucesso." << "\n";
    } else
    {
        std::cout << "Livro não encontrado." << "\n";
    }
}

//Usuários
void Interface::cadastrarUsuario()
{
    int opcao;

    std::cout << "=== CADASTRAR USUÁRIO ===\n";

    std::cout << "1. Cadastrar." << "\n";
    std::cout << "0. Sair." << "\n";
    std::cout << "Escolha uma opção: ";
    if (!(std::cin >> opcao))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw std::invalid_argument("Digite apenas números.");
    }

    switch (opcao)
    {
        case 1:
        {
            std::string nome;
            std::string cpf;
            int numerodecadastro;

            std::cout << "=== CADASTRO DE USUÁRIO ===\n";

            std::cout << "Digite o nome de usuário: ";
            std::getline(std::cin >> std::ws, nome);

            std::cout << "Digite o CPF do usuário: ";
            std::cin >> cpf;

            numerodecadastro = lerNumeroInteiro("Digite o número de cadastro: ");

            biblioteca.cadastrarUsuario(std::make_unique<Usuario>(nome, cpf, numerodecadastro));

            std::cout << "Usuário cadastrado." << "\n";

            break;
        }
        default:
            throw std::invalid_argument("Dado inválido.");
    }
}

void Interface::listarUsuarios()
{
    biblioteca.listarUsuarios();
}

void Interface::removerUsuario()
{
    int numeroDeCadastro = lerNumeroInteiro("Digite o número de cadastro: ");

    if (biblioteca.removerUsuario(numeroDeCadastro))
    {
        std::cout << "Usuário removido com sucesso." << "\n";
    } else
    {
        std::cout << "Usuário não encontrado." << "\n";
    }
}

void Interface::listarHistorico()
{
    biblioteca.listarHistorico();
}
