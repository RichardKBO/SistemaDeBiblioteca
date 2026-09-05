#include "Interface.h"
#include "Biblioteca.h"
#include "LivroFisico.h"
#include "Ebook.h"
#include "Usuario.h"
#include "Exception.h"

#include <iostream>
#include <memory>
#include <limits>

char Interface::lerConfirmacao()
{
    char confirmacao;

    if (!(std::cin >> confirmacao))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw OpcaoInvalidaException("Selecione uma opção válida.");
    }
    confirmacaoValida(confirmacao);

    return confirmacao;
}

void Interface::confirmacaoValida(char confirmacao)
{
    if (confirmacao != 's' && confirmacao != 'S' && confirmacao != 'n' && confirmacao != 'N')
    {
        throw OpcaoInvalidaException("Digite uma opção válida.");
    }
}

Interface::Interface(Biblioteca &biblioteca)
    :biblioteca(biblioteca)
{
}

void Interface::mostrarCabecalho(const std::string& titulo)
{
    std::cout <<"=======================\n";
    std::cout <<"  "<< titulo <<" \n";
    std::cout <<"=======================\n";
}

int Interface::lerNumeroInteiro(const std::string &mensagem)
{
    int valor;

    std::cout << mensagem;

    if (!(std::cin >> valor))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw EntradaInvalidaException("Valor inválido.");
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

        throw EntradaInvalidaException("Valor inválido.");
    }
    return valor;
}

std::string Interface::lerISBN()
{
    std::string isbn;

    std::cout <<"Digite o ISBN: ";
    std::getline(std::cin >> std::ws, isbn);

    return isbn;
}

//Livros
void Interface::cadastrarLivro()
{
    int tipo;

    mostrarCabecalho("CADASTRAR LIVRO");


    std::cout << "\n";
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

            biblioteca.adicionarLivro(std::make_unique<Ebook>(titulo, autor, isbn, true, tamanhoDoArquivo));

            std::cout << "Ebook cadastrado." << "\n";
            break;
        }

        default:
            throw TipoInvalidoException("Tipo de livro inválido.");
    }
}

void Interface::buscarLivro()
{
    mostrarCabecalho("BUSCAR LIVRO");

    std::string isbn = lerISBN();

    biblioteca.buscarLivro(isbn);
}

void Interface::listarMeusLivros()
{
   mostrarCabecalho("LISTA DO USUÁRIO");

    Usuario* usuario = selecionarUsuario();

    usuario->listarLivros();
}

void Interface::listarLivros()
{
    mostrarCabecalho("LISTAR LIVROS");

    biblioteca.listarLivros();
}

void Interface::emprestarLivro()
{
    mostrarCabecalho("EMPRÉSTIMO");

    std::string isbn = lerISBN();

    Usuario *usuario = selecionarUsuario();

    biblioteca.emprestarLivro(isbn, *usuario);
}

void Interface::devolverLivro()
{
    mostrarCabecalho("DEVOLVER LIVRO");

    std::string isbn = lerISBN();

    Usuario *usuario = selecionarUsuario();

    biblioteca.devolverLivro(isbn, *usuario);
}

void Interface::removerLivro()
{
    mostrarCabecalho("REMOVER LIVRO");

    std::string isbn = lerISBN();

    //Verifica se o livro existe
    biblioteca.buscarLivro(isbn);

    std::cout << "Deseja realmente remover o livro com ISBN " << isbn << " ? (s/n): " << "\n";

    char confirmacao = lerConfirmacao();

    if (confirmacao == 's' || confirmacao == 'S')
    {
        if (biblioteca.removerLivro(isbn))
        {
            std::cout <<"Livro removido com sucesso." <<"\n";
        }
        else
        {
            throw LivroNaoEncontradoException("Livro não encontrado.");
        }
    }
    else if (confirmacao == 'n' || confirmacao == 'N')
    {
        std::cout <<"Operação cancelada." <<"\n";
    }
}

//Usuários
void Interface::cadastrarUsuario()
{
    mostrarCabecalho("CADASTRAR USUÁRIO");

    std::cout <<"\n";
    std::cout << "1. Cadastrar." << "\n";
    std::cout << "0. Sair." << "\n";
    int opcao = lerNumeroInteiro("Selecione uma opção: ");

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
            throw DadoInvalidoException("Dado inválido.");
    }
}

void Interface::listarUsuarios()
{
    mostrarCabecalho("LISTAR USUÁRIOS");

    std::cout <<"\n";

    biblioteca.listarUsuarios();
}

void Interface::removerUsuario()
{
    mostrarCabecalho("REMOVER USUÁRIO");

    std::cout <<"\n";

    Usuario* usuario = selecionarUsuario();

    std::cout <<"Usuário selecionado: " << usuario->getNome() <<"\n";
    std::cout <<"Número de cadastro: " << usuario->getNumeroDeCadastro() <<"\n";

    std::cout <<"Deseja realmente remover esse usuário? (s/n): ";

    char confirmacao = lerConfirmacao();

    if (confirmacao == 's' || confirmacao == 'S')
    {
        if (biblioteca.removerUsuario(usuario->getNumeroDeCadastro()))
        {
            std::cout <<"Usuário removido com sucesso" <<"\n";
        }
        else
        {
            throw UsuarioNaoEncontradoException("Usuário não encontrado");
        }
    }
    else if (confirmacao == 'n' || confirmacao == 'N')
    {
        std::cout <<"Operação cancelada." <<"\n";
    }

}

void Interface::listarHistorico()
{
   mostrarCabecalho("LISTAR HISTÓRICO");

    biblioteca.listarHistorico();
}

Usuario *Interface::selecionarUsuario()
{
    const auto& usuarios = biblioteca.getUsuarios();

    if (usuarios.empty())
    {
        throw UsuarioNaoEncontradoException("Não existem usuários cadastrados.");
    }

    mostrarCabecalho("SELECIONAR USUÁRIO");

    for (std::size_t i = 0; i < usuarios.size(); i++)
    {
        std::cout << i + 1 << ". " << usuarios[i]->getNome()
        << " - Cadastro: " << usuarios[i]->getNumeroDeCadastro() <<
            "\n";
    }

    const int opcao = lerNumeroInteiro("Escolha o usuário: ");

    if (opcao < 1 || opcao > static_cast<int>(usuarios.size()))
    {
        throw OpcaoInvalidaException("Usuário inválido.");
    }
    return usuarios[opcao - 1].get();
}
