#include "Biblioteca.h"
#include "Interface.h"
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

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Biblioteca biblioteca;

    Interface interface(biblioteca);

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
                    interface.listarLivros();
                    break;
                }

                case 2:
                {
                   interface.buscarLivro();
                    break;
                }
                case 3:
                {
                    interface.emprestarLivro();
                    break;
                }
                case 4:
                {
                    interface.devolverLivro();
                    break;
                }
                case 5:
                {
                    interface.listarMeusLivros();
                    break;
                }
                case 6:
                {
                    interface.cadastrarLivro();
                    break;
                }
                case 7:
                {
                    interface.cadastrarUsuario();
                    break;
                }
                case 8:
                {
                    interface.listarUsuarios();
                    break;
                }
                case 9:
                {
                    interface.removerUsuario();
                    break;
                }

                case 10:
                {
                    interface.removerLivro();
                    break;
                }
                case 11:
                {
                    interface.listarHistorico();
                    break;
                }
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
