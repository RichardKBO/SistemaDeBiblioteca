cmake_minimum_required(VERSION 4.3)

project(SistemaDeBiblioteca)

set(CMAKE_CXX_STANDARD 23)

add_executable(SistemaDeBiblioteca
        src/main.cpp
        src/Livro.cpp
        src/Biblioteca.cpp
        src/LivroFisico.cpp
        src/Ebook.cpp
        src/Usuario.cpp
        include/Emprestimo.h
        src/Emprestimo.cpp
)

target_include_directories(SistemaDeBiblioteca PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)