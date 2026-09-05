#pragma once
#include <string>


class Biblioteca;
class Usuario;

class Interface
{
private:
    Biblioteca&  biblioteca;

    int lerNumeroInteiro(const std::string& mensagem);
    double lerNumeroDouble(const std::string& mensagem);
    char lerConfirmacao();
    std::string lerISBN();

    void mostrarCabecalho(const std::string& titulo);
    void confirmacaoValida(char confirmacao);

public:
    explicit Interface(Biblioteca& biblioteca);

    void cadastrarUsuario();

    void emprestarLivro();

    void devolverLivro();

    void listarLivros();

    void buscarLivro();

    void listarUsuarios();

    void removerLivro();

    void removerUsuario();

    void cadastrarLivro();

    void listarHistorico();

    void listarMeusLivros();

    [[nodiscard]] Usuario* selecionarUsuario();
};
