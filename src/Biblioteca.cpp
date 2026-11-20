#include "Biblioteca.h"
#include "Usuario.h"
#include "Emprestimo.h"
#include "Exception.h"
#include "LivroFisico.h"
#include "Ebook.h"
#include <nlohmann/json.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

//Lógica pra gerenciamento das classes.


std::string obterDataAtual()
{
    const auto agora = std::chrono::system_clock::now();
    const std::time_t tempo = std::chrono::system_clock::to_time_t(agora);

    std::tm data{};

    localtime_r(&tempo, &data); //Linux / Mac

    //localtime_s(&data, &tempo); //Windows

    std::ostringstream resultado;

    resultado << std::setfill('0') << std::setw(2) << data.tm_mday << "/"
              << std::setw(2) << data.tm_mon + 1 << "/"
              << data.tm_year + 1900;

    return resultado.str();
}

Biblioteca::Biblioteca(const std::string &arquivoDados)
    : arquivoDados_(arquivoDados)
{
    carregarDados();
}

Biblioteca::~Biblioteca()
{
    try
    {
        salvarDados();
    }
    catch (...)
    {
    }
}

void Biblioteca::salvarDados() const
{
    json dados;
    dados["livros"] = json::array();

    for (const auto &livro : livros_)
    {
        json livroJson;
        livroJson["titulo"] = livro->getTitulo();
        livroJson["autor"] = livro->getAutor();
        livroJson["isbn"] = livro->getISBN();
        livroJson["disponivel"] = livro->getDisponibilidade();

        if (const auto fisico = dynamic_cast<const LivroFisico *>(livro.get()))
        {
            livroJson["tipo"] = "fisico";
            livroJson["paginas"] = fisico->getQuantidadeDePaginas();
        }
        else if (const auto ebook = dynamic_cast<const Ebook *>(livro.get()))
        {
            livroJson["tipo"] = "ebook";
            livroJson["tamanhoArquivo"] = ebook->getTamanhoArquivo();
        }

        dados["livros"].push_back(livroJson);
    }

    dados["usuarios"] = json::array();
    for (const auto &usuario : usuarios_)
    {
        json usuarioJson;
        usuarioJson["nome"] = usuario->getNome();
        usuarioJson["cpf"] = usuario->getCpf();
        usuarioJson["numeroDeCadastro"] = usuario->getNumeroDeCadastro();
        usuarioJson["livrosEmprestados"] = json::array();

        for (const Livro *livro : usuario->getLivrosEmprestados())
        {
            usuarioJson["livrosEmprestados"].push_back(livro->getISBN());
        }

        dados["usuarios"].push_back(usuarioJson);
    }

    dados["historico"] = json::array();
    for (const Emprestimo &emprestimo : historico_)
    {
        dados["historico"].push_back({
            {"numeroDeCadastroUsuario", emprestimo.getNumeroDeCadastroUsuario()},
            {"isbn", emprestimo.getIsbn()},
            {"dataEmprestimo", emprestimo.getDataEmprestimo()},
            {"dataDevolucao", emprestimo.getDataDevolucao()}
        });
    }

    const std::filesystem::path caminho(arquivoDados_);
    if (caminho.has_parent_path())
    {
        std::filesystem::create_directories(caminho.parent_path());
    }

    std::ofstream arquivo(caminho);
    if (!arquivo)
    {
        throw BibliotecaException("Não foi possível abrir o arquivo de persistência.");
    }

    arquivo << dados.dump(4) << '\n';
    if (!arquivo)
    {
        throw BibliotecaException("Não foi possível salvar os dados da biblioteca.");
    }
}

void Biblioteca::carregarDados()
{
    std::ifstream arquivo(arquivoDados_);
    if (!arquivo)
    {
        return;
    }

    json dados;
    try
    {
        arquivo >> dados;
    }
    catch (const json::parse_error &erro)
    {
        throw BibliotecaException("Arquivo de persistência inválido: " + std::string(erro.what()));
    }

    livros_.clear();
    usuarios_.clear();
    historico_.clear();

    if (dados.contains("livros"))
    {
        for (const auto &livroJson : dados["livros"])
        {
            const std::string tipo = livroJson.value("tipo", "");
            const std::string titulo = livroJson.at("titulo").get<std::string>();
            const std::string autor = livroJson.at("autor").get<std::string>();
            const std::string isbn = livroJson.at("isbn").get<std::string>();
            const bool disponivel = livroJson.value("disponivel", true);

            if (tipo == "fisico")
            {
                livros_.push_back(std::make_unique<LivroFisico>(
                    titulo, autor, isbn, disponivel, livroJson.at("paginas").get<int>()
                ));
            }
            else if (tipo == "ebook")
            {
                livros_.push_back(std::make_unique<Ebook>(
                    titulo, autor, isbn, disponivel, livroJson.at("tamanhoArquivo").get<double>()
                ));
            }
            else
            {
                throw BibliotecaException("Tipo de livro desconhecido no arquivo de persistência.");
            }
        }
    }

    if (dados.contains("usuarios"))
    {
        for (const auto &usuarioJson : dados["usuarios"])
        {
            auto usuario = std::make_unique<Usuario>(
                usuarioJson.at("nome").get<std::string>(),
                usuarioJson.at("cpf").get<std::string>(),
                usuarioJson.at("numeroDeCadastro").get<int>()
            );

            if (usuarioJson.contains("livrosEmprestados"))
            {
                for (const auto &isbnJson : usuarioJson["livrosEmprestados"])
                {
                    const std::string isbn = isbnJson.get<std::string>();
                    Livro *livro = buscarLivro(isbn);
                    usuario->adicionarLivro(livro);
                }
            }

            usuarios_.push_back(std::move(usuario));
        }
    }

    if (dados.contains("historico"))
    {
        for (const auto &emprestimoJson : dados["historico"])
        {
            historico_.emplace_back(
                emprestimoJson.at("numeroDeCadastroUsuario").get<int>(),
                emprestimoJson.at("isbn").get<std::string>(),
                emprestimoJson.at("dataEmprestimo").get<std::string>(),
                emprestimoJson.value("dataDevolucao", "")
            );
        }
    }
}

void Biblioteca::adicionarLivro(std::unique_ptr<Livro> livro)
{
    for (const auto& livroExistente : livros_)
    {
        //Tratamento para evitar ISBN's iguais.
        //Para saber sobre ISBN, consulte Livro.h

        if (livroExistente->getISBN() == livro->getISBN())
        {
            throw ISBNDuplicadoException("Já existe um livro com esse ISBN.");
        }
    }

    livros_.push_back(std::move(livro));
    salvarDados();
}

void Biblioteca::cadastrarUsuario(std::unique_ptr<Usuario> usuario)
{
    auto cadastroExistente = std::find_if(usuarios_.begin(), usuarios_.end(), [&usuario](const auto& usuarioExistente)
    {
        return usuarioExistente->getNumeroDeCadastro() == usuario->getNumeroDeCadastro();
    });

    if (cadastroExistente != usuarios_.end())
    {
        throw UsuarioDuplicadoException("Já existe um usuário com esse número de cadastro.");
    }

    auto cpfExistente = std::find_if(usuarios_.begin(), usuarios_.end(), [&usuario](const auto& usuarioExistente)
    {
        return usuarioExistente->getCpf() == usuario->getCpf();
    });

    if (cpfExistente != usuarios_.end())
    {
        throw CPFJaCadastradoException("Já existe um usuário com esse CPF.");
    }

    usuarios_.push_back(std::move(usuario));
    salvarDados();
}

Usuario* Biblioteca::buscarUsuario(int numeroDeCadastro) const // Função pra busca de usuários por número de cadastro.
{
    for (const auto& usuario : usuarios_)
    {
        if (usuario->getNumeroDeCadastro() == numeroDeCadastro)
        {
            return usuario.get();
        }
    }
    throw UsuarioNaoEncontradoException("Usuário não encontrado.");
}

const std::vector<std::unique_ptr<Usuario> > &Biblioteca::getUsuarios() const
{
    return usuarios_;
}

bool Biblioteca::removerUsuario(int numeroDeCadastro) // Função para remover usuários por número de cadastro.
{
    /*
     * Expressão lambda pra percorrer os cadastros e compara,
     * assim removendo o usuário.
     */
    auto it = std::find_if(usuarios_.begin(), usuarios_.end(), [numeroDeCadastro](const auto& usuario)
    {
        return usuario->getNumeroDeCadastro() == numeroDeCadastro;
    });

    if (it == usuarios_.end())
    {
        return false;
    }

    if ((*it)->possuiLivrosEmprestados()) //Se o usuário tem livros, não remove até que o devolva.
    {
        throw UsuarioComEmprestimosException("O usuário possui livros emprestados e não pode ser removido.");
    }

    usuarios_.erase(it);
    salvarDados();

    return true;
}

void Biblioteca::listarUsuarios() const
{

    for (const auto& usuario : usuarios_)
    {
        std::cout <<"Nome: " << usuario->getNome() <<"\n";
        std::cout <<"CPF: " << usuario->getCpf() <<"\n";
        std::cout <<"Número de cadastro: " << usuario->getNumeroDeCadastro() <<"\n";

        std::cout <<"=======================\n";
    }
}

const std::vector<std::unique_ptr<Livro> > &Biblioteca::getLivros() const
{
    return livros_;
}

Livro* Biblioteca::buscarLivro(const std::string &isbn) const
{
    for (const auto& livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            return livro.get();
        }
    }
    throw LivroNaoEncontradoException("O livro não foi encontrado.");
}

void Biblioteca::listarHistorico() const
{
    for (const auto& emprestimo : historico_)
    {
        std::cout <<"Número de cadastro: " << emprestimo.getNumeroDeCadastroUsuario() <<"\n";
        std ::cout <<"ISBN: " << emprestimo.getIsbn() <<"\n";
        std::cout <<"Data de empréstimo: " << emprestimo.getDataEmprestimo() <<"\n";
        std::cout <<"Data de devolução: " << emprestimo.getDataDevolucao() <<"\n";

        std::cout <<"=======================\n";
    }
}

Livro* Biblioteca::emprestarLivro(const std::string& isbn, Usuario& usuario)
{
    for (const auto& livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            if (usuario.possuiLivro(livro.get()))
            {
                throw LivroJaPossuiException("O usuário já possui esse livro.");
            }

            if (!usuario.podeEmprestarLivro())
            {
                throw LimiteEmprestimosException("O usuário atingiu o limite de 3 livros emprestados.");
            }

            if (!livro->getDisponibilidade())
            {
                throw LivroIndisponivelException("O livro não está disponível.");
            }

            livro->emprestar();

            usuario.adicionarLivro(livro.get());

            historico_.emplace_back(
                usuario.getNumeroDeCadastro(),
                livro->getISBN(),
                obterDataAtual()
                );

            salvarDados();
            return livro.get();
        }
    }
    throw LivroNaoEncontradoException("Livro não encontrado.");
}

bool Biblioteca::removerLivro(const std::string &isbn)
{
    auto it = std::find_if(livros_.begin(), livros_.end(), [&isbn](const auto& livro)
    {
       return livro->getISBN() == isbn;
    });

    if (it == livros_.end())
    {
        return false;
    }

    if (!(*it)->getDisponibilidade())
    {
        throw LivroEmprestadoException("O livro está emprestado e não pode ser removido.");
    }

    livros_.erase(it);
    salvarDados();

    return true;
}

Emprestimo *Biblioteca::buscarEmprestimo(int numeroDeCadastroUsuario, const std::string &isbn)
{
    for (auto& emprestimo : historico_)
    {
        if (emprestimo.getNumeroDeCadastroUsuario() == numeroDeCadastroUsuario &&
            emprestimo.getIsbn() == isbn &&
            emprestimo.getDataDevolucao().empty()
            )
        {
            return &emprestimo;
        }
    }
    throw EmprestimoNaoEncontradoException("Empréstimo não encontrado.");
}

Livro* Biblioteca::devolverLivro(const std::string &isbn, Usuario& usuario)
{
    for (const auto& livro : livros_)
    {
        if (livro->getISBN() == isbn)
        {
            if (!usuario.possuiLivro(livro.get()))
            {
                throw UsuarioNaoPossuiEsseLivroException("O usuário não possui este livro.");
            }

            Emprestimo* emprestimo = buscarEmprestimo(usuario.getNumeroDeCadastro(), isbn);
            emprestimo->registrarDevolucao(obterDataAtual());

            livro->devolver();

            usuario.devolverLivro(livro.get());
            salvarDados();

            return livro.get();
        }
    }
    throw LivroNaoEncontradoException("Livro não encontrado.");
}
