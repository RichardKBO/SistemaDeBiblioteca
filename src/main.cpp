#include "Biblioteca.h"
#include "LivroFisico.h"
#include "Ebook.h"
#include "Usuario.h"

#include <clocale>
#include <stdexcept>
#include <iostream>
#include <limits>

/*
 * Criado por: Richard Kawan Barbosa Oliveira
 * Data: 21/08/2026
 *
 * Objetivo: Aplicar meus aprendizados e conhecimentos adquiridos,
 * e criar uma interface/Sistema de gerenciamento de uma biblioteca.
 *
 * Versão 2.0.
 */

int lerNumeroInteiro(const std::string& mensagem)
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

double lerNumeroDouble(const std::string& mensagem)
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

void cadastrarUsuario(Biblioteca &biblioteca)
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


void cadastrarLivro(Biblioteca &biblioteca)
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

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Biblioteca biblioteca;

    int opcao;

    do
    {
        try
        {
            //Adicionado opções pra facilitar navegação pela interface.

            std::cout << "\n";
            std::cout << "1. Listar livros." << "\n";
            std::cout << "2. Buscar livro." << "\n";
            std::cout << "3. Emprestar livro." << "\n";
            std::cout << "4. Devolver livro." << "\n";
            std::cout << "5. Listar meus livros." << "\n";
            std::cout << "6. Cadastrar livro." << "\n";
            std::cout << "7. Cadastrar usuário." << "\n";
            std::cout << "8. Listar usuário." << "\n";
            std::cout << "9. Remover usuário." << "\n";
            std::cout << "10. Remover livro." << "\n";
            std::cout << "11. Listar histórico de empréstimos." << "\n";
            std::cout << "0. Sair." << "\n";
            std::cout << "Escolha uma opção: " << "\n";
            if (!(std::cin >> opcao))
            {
                std::cin.clear();

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                throw std::invalid_argument("Digite apenas números.");
            }

            if (opcao < 0 || opcao > 11)
            {
                throw std::out_of_range("Opção inválida.");
            }

            switch (opcao)
            {
                case 1:
                {
                    biblioteca.listarLivros();
                    break;
                }

                case 2:
                {
                    std::string isbn;

                    std::cout << "Digite o ISBN: ";
                    std::getline(std::cin >> std::ws, isbn);

                    biblioteca.buscarLivro(isbn);
                    break;
                }
                case 3:
                {
                    std::string isbn;

                    std::cout << "Digite o ISBN: ";
                    std::getline(std::cin >> std::ws, isbn);

                    int numeroDeCadastro = lerNumeroInteiro("Digite o número de cadastro: ");

                    Usuario *usuario = biblioteca.buscarUsuario(numeroDeCadastro);

                    biblioteca.emprestarLivro(isbn, *usuario);

                    break;
                }

                case 4:
                {
                    std::string isbn;

                    std::cout << "Digite o ISBN: ";
                    std::getline(std::cin >> std::ws, isbn);

                    int numeroDeCadastro = lerNumeroInteiro("Digite o número de cadastro: ");

                    Usuario *usuario = biblioteca.buscarUsuario(numeroDeCadastro);

                    biblioteca.devolverLivro(isbn, *usuario);

                    break;
                }

                case 5:
                {
                    int numeroDeCadastro = lerNumeroInteiro("Digite o número de cadastro: ");

                    Usuario *usuario = biblioteca.buscarUsuario(numeroDeCadastro);

                    usuario->listarLivros();

                    break;
                }
                case 6:
                    cadastrarLivro(biblioteca);

                    break;

                case 7:
                    cadastrarUsuario(biblioteca);

                    break;

                case 8:
                    biblioteca.listarUsuarios();

                    break;
                case 9:
                {
                    int numeroDeCadastro = lerNumeroInteiro("Digite o número de cadastro: ");

                    if (biblioteca.removerUsuario(numeroDeCadastro))
                    {
                        std::cout << "Usuário removido com sucesso." << "\n";
                    } else
                    {
                        std::cout << "Usuário não encontrado." << "\n";
                    }

                    break;
                }

                case 10:
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

                    break;
                }
                case 11:
                    biblioteca.listarHistorico();

                    break;
                case 0:

                    break;
            }
        } catch (const std::invalid_argument &e)
        {
            std::cerr << "Erro: " << e.what() << "\n";
        }
        catch (const std::out_of_range& e)
        {
            std::cerr <<"Erro: " << e.what() <<"\n";
        }
    } while (opcao != 0);

    return 0;
}
