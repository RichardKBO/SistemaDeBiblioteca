#include "Exception.h"


//Classes com exceptions base
BibliotecaException::BibliotecaException(const std::string &mensagem)
    :runtime_error(mensagem)
{
}

BibliotecaRangeException::BibliotecaRangeException(const std::string &mensagem)
    :out_of_range(mensagem)
{
}

BibliotecaInvalidaException::BibliotecaInvalidaException(const std::string &mensagem)
    :invalid_argument(mensagem)
{
}

//Validações de livros em Biblioteca.cpp

LivroNaoEncontradoException::LivroNaoEncontradoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

ISBNDuplicadoException::ISBNDuplicadoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

LivroJaPossuiException::LivroJaPossuiException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

LimiteEmprestimosException::LimiteEmprestimosException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

LivroIndisponivelException::LivroIndisponivelException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

EmprestimoNaoEncontradoException::EmprestimoNaoEncontradoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

LivroEmprestadoException::LivroEmprestadoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

//Validações de usuários em Biblioteca.cpp

UsuarioNaoEncontradoException::UsuarioNaoEncontradoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

UsuarioDuplicadoException::UsuarioDuplicadoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

UsuarioComEmprestimosException::UsuarioComEmprestimosException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

UsuarioNaoPossuiEsseLivroException::UsuarioNaoPossuiEsseLivroException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

//Validações Emprestimos.h/.cpp

DataEmprestimoInvalidaException::DataEmprestimoInvalidaException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

DataDevolucaoException::DataDevolucaoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

CPFJaCadastradoException::CPFJaCadastradoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

//Validações Usuario.h/.cpp

NomeUsuarioInvalidoException::NomeUsuarioInvalidoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

CPFInvalidoException::CPFInvalidoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

NumeroDeCadastroInvalidoException::NumeroDeCadastroInvalidoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

//Validações de Livros.h/.cpp

TituloInvalidoException::TituloInvalidoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

AutorInvalidoException::AutorInvalidoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

ISBNInvalidoException::ISBNInvalidoException(const std::string &mensagem)
    :BibliotecaException(mensagem)
{
}

//Validações LivroFisico.h/.cpp

QuantidadeDePaginasInvalidaException::QuantidadeDePaginasInvalidaException(const std::string &mensagem)
    :BibliotecaRangeException(mensagem)
{
}

//Validações Ebook.h/.cpp

TamanhoArquivoInvalidoException::TamanhoArquivoInvalidoException(const std::string &mensagem)
    :BibliotecaRangeException(mensagem)
{
}

//Validações de entrada

EntradaInvalidaException::EntradaInvalidaException(const std::string &mensagem)
    :BibliotecaInvalidaException(mensagem)
{
}

TipoInvalidoException::TipoInvalidoException(const std::string &mensagem)
    :BibliotecaInvalidaException(mensagem)
{
}

OpcaoInvalidaException::OpcaoInvalidaException(const std::string &mensagem)
    :BibliotecaRangeException(mensagem)
{
}

DadoInvalidoException::DadoInvalidoException(const std::string &mensagem)
    :BibliotecaInvalidaException(mensagem)
{
}