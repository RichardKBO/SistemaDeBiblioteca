#include "Biblioteca.h"
#include "LivroFisico.h"
#include "Ebook.h"
#include "Usuario.h"
#include <windows.h>
#include <stdexcept>
#include <iostream>

//Testes em comentário, remova as barras de comentário e teste a vontade.

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    try
    {
        Biblioteca biblioteca;
        Usuario primeiroUsuario("Richard", "12345678912");
        Usuario segundoUsuario("Lucas", "23456789121");

        biblioteca.adicionarLivro(std::make_unique<LivroFisico>("Jurassic Park", "Michael Crichton", "ISBN-13. 978-8576572152", true, 528));
        biblioteca.adicionarLivro(std::make_unique<LivroFisico>("Dom Casmurro", "Machado de Assis", "ISBN-13. 978-8594318602", true, 230));
        biblioteca.adicionarLivro(std::make_unique<Ebook>("C++ The Programming language", "Bjarne Stroustrup", "ISBN-13. 978-0201889543", true, 1040));
        biblioteca.adicionarLivro(std::make_unique<Ebook>("Core Java", "Cay S. Horstmann e Gary Cornell", "ISBN-13. 978-8576053576", true, 800));

        //biblioteca.emprestarLivro("ISBN-13. 978-8576053576", primeiroUsuario);

        //primeiroUsuario.listarLivros();

        //biblioteca.emprestarLivro("ISBN-13. 978-8576572152", segundoUsuario);

        //biblioteca.devolverLivro("ISBN-13. 978-8576053576", primeiroUsuario);
        //biblioteca.devolverLivro("ISBN-13. 978-8576572152", segundoUsuario);

        //biblioteca.listarLivros();

    }
    catch (const std::invalid_argument& e)
    {
        std::cerr <<"Erro: " << e.what() <<"\n";
    }
    return 0;
}
