#include "infrastructure/JsonBibliotecaRepository.h"
#include "domain/Exception.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <utility>

using json = nlohmann::json;

JsonBibliotecaRepository::JsonBibliotecaRepository(std::string caminhoArquivo)
    : caminhoArquivo_(std::move(caminhoArquivo))
{
}

BibliotecaSnapshot JsonBibliotecaRepository::carregar() const
{
    std::ifstream arquivo(caminhoArquivo_);
    if (!arquivo)
    {
        return {};
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

    BibliotecaSnapshot snapshot;

    for (const auto &livroJson : dados.value("livros", json::array()))
    {
        LivroSnapshot livro;
        livro.tipo = livroJson.value("tipo", "");
        livro.titulo = livroJson.value("titulo", "");
        livro.autor = livroJson.value("autor", "");
        livro.isbn = livroJson.value("isbn", "");
        livro.disponivel = livroJson.value("disponivel", true);
        livro.paginas = livroJson.value("paginas", 0);
        livro.tamanhoArquivo = livroJson.value("tamanhoArquivo", 0.0);
        snapshot.livros.push_back(std::move(livro));
    }

    for (const auto &usuarioJson : dados.value("usuarios", json::array()))
    {
        UsuarioSnapshot usuario;
        usuario.nome = usuarioJson.value("nome", "");
        usuario.cpf = usuarioJson.value("cpf", "");
        usuario.numeroDeCadastro = usuarioJson.value("numeroDeCadastro", 0);

        for (const auto &isbnJson : usuarioJson.value("livrosEmprestados", json::array()))
        {
            usuario.livrosEmprestados.push_back(isbnJson.get<std::string>());
        }
        snapshot.usuarios.push_back(std::move(usuario));
    }

    for (const auto &emprestimoJson : dados.value("historico", json::array()))
    {
        EmprestimoSnapshot emprestimo;
        emprestimo.numeroDeCadastroUsuario =
            emprestimoJson.value("numeroDeCadastroUsuario", 0);
        emprestimo.isbn = emprestimoJson.value("isbn", "");
        emprestimo.dataEmprestimo = emprestimoJson.value("dataEmprestimo", "");
        emprestimo.dataDevolucao = emprestimoJson.value("dataDevolucao", "");
        snapshot.historico.push_back(std::move(emprestimo));
    }

    return snapshot;
}

void JsonBibliotecaRepository::salvar(const BibliotecaSnapshot &snapshot) const
{
    json dados;
    dados["livros"] = json::array();

    for (const auto &livro : snapshot.livros)
    {
        json livroJson{
            {"tipo", livro.tipo},
            {"titulo", livro.titulo},
            {"autor", livro.autor},
            {"isbn", livro.isbn},
            {"disponivel", livro.disponivel}
        };

        if (livro.tipo == "fisico")
        {
            livroJson["paginas"] = livro.paginas;
        }
        else if (livro.tipo == "ebook")
        {
            livroJson["tamanhoArquivo"] = livro.tamanhoArquivo;
        }
        dados["livros"].push_back(livroJson);
    }

    dados["usuarios"] = json::array();
    for (const auto &usuario : snapshot.usuarios)
    {
        dados["usuarios"].push_back({
            {"nome", usuario.nome},
            {"cpf", usuario.cpf},
            {"numeroDeCadastro", usuario.numeroDeCadastro},
            {"livrosEmprestados", usuario.livrosEmprestados}
        });
    }

    dados["historico"] = json::array();
    for (const auto &emprestimo : snapshot.historico)
    {
        dados["historico"].push_back({
            {"numeroDeCadastroUsuario", emprestimo.numeroDeCadastroUsuario},
            {"isbn", emprestimo.isbn},
            {"dataEmprestimo", emprestimo.dataEmprestimo},
            {"dataDevolucao", emprestimo.dataDevolucao}
        });
    }

    const std::filesystem::path caminho(caminhoArquivo_);
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
