#pragma once
#include <stdexcept>
#include <string>

//Classes com exception base.
class BibliotecaException : public std::runtime_error
{
public:
    BibliotecaException(const std::string& mensagem);
};

class BibliotecaRangeException : public std::out_of_range
{
public:
    BibliotecaRangeException(const std::string& mensagem);
};

class BibliotecaInvalidaException : public std::invalid_argument
{
public:
    BibliotecaInvalidaException(const std::string& mensagem);
};
//Validações de Livros em Biblioteca.cpp

class LivroNaoEncontradoException : public BibliotecaException
{
public:
    LivroNaoEncontradoException(const std::string& mensagem);
};

class ISBNDuplicadoException : public BibliotecaException
{
public:
    ISBNDuplicadoException(const std::string& mensagem);
};

class LivroJaPossuiException : public BibliotecaException
{
public:
    LivroJaPossuiException(const std::string& mensagem);
};

class LimiteEmprestimosException : public BibliotecaException
{
public:
    LimiteEmprestimosException(const std::string& mensagem);
};

class LivroIndisponivelException : public BibliotecaException
{
public:
    LivroIndisponivelException(const std::string& mensagem);
};

class EmprestimoNaoEncontradoException : public BibliotecaException
{
public:
    EmprestimoNaoEncontradoException(const std::string& mensagem);
};

//Validações dos usuários em Biblioteca.cpp

class UsuarioNaoEncontradoException : public BibliotecaException
{
public:
    UsuarioNaoEncontradoException(const std::string& mensagem);
};

class UsuarioDuplicadoException : public BibliotecaException
{
public:
    UsuarioDuplicadoException(const std::string& mensagem);
};

class UsuarioComEmprestimosException : public BibliotecaException
{
public:
    UsuarioComEmprestimosException(const std::string& mensagem);
};

class UsuarioNaoPossuiEsseLivroException : public BibliotecaException
{
public:
    UsuarioNaoPossuiEsseLivroException(const std::string& mensagem);
};

class LivroEmprestadoException : public BibliotecaException
{
public:
    LivroEmprestadoException(const std::string& mensagem);
};
class CPFJaCadastradoException : public BibliotecaException
{
public:
    CPFJaCadastradoException(const std::string& mensagem);
};


//Validações Emprestimos.h/.cpp

class DataEmprestimoInvalidaException : public BibliotecaException
{
public:
    DataEmprestimoInvalidaException(const std::string& mensagem);
};

class DataDevolucaoException : public BibliotecaException
{
public:
    DataDevolucaoException(const std::string& mensagem);
};

//Validações classe Usuario.h/.cpp

class NomeUsuarioInvalidoException : public BibliotecaException
{
public:
    NomeUsuarioInvalidoException(const std::string& mensagem);
};

class CPFInvalidoException : public BibliotecaException
{
public:
    CPFInvalidoException(const std::string& mensagem);
};

class NumeroDeCadastroInvalidoException : public BibliotecaException
{
public:
    NumeroDeCadastroInvalidoException(const std::string& mensagem);
};

//Validaçoes da classe Livro.h/.cpp

class TituloInvalidoException : public BibliotecaException
{
public:
    TituloInvalidoException(const std::string& mensagem);
};

class AutorInvalidoException : public BibliotecaException
{
public:
    AutorInvalidoException(const std::string& mensagem);
};

class ISBNInvalidoException : public BibliotecaException
{
public:
    ISBNInvalidoException(const std::string& mensagem);
};

//Validações LivroFisico.h/.cpp

class QuantidadeDePaginasInvalidaException : public BibliotecaRangeException
{
public:
    QuantidadeDePaginasInvalidaException(const std::string& mensagem);
};

//Validações Ebook.h/.cpp

class TamanhoArquivoInvalidoException : public BibliotecaRangeException
{
public:
    TamanhoArquivoInvalidoException(const std::string& mensagem);
};

//Validações de entrada

class EntradaInvalidaException : public BibliotecaInvalidaException
{
public:
    EntradaInvalidaException(const std::string& mensagem);
};

class TipoInvalidoException : public BibliotecaInvalidaException
{
public:
    TipoInvalidoException(const std::string& mensagem);
};

class OpcaoInvalidaException : public BibliotecaRangeException
{
public:
    OpcaoInvalidaException(const std::string& mensagem);
};

class DadoInvalidoException : public BibliotecaInvalidaException
{
public:
    DadoInvalidoException(const std::string& mensagem);
};