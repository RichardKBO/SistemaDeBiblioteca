cmake_minimum_required(VERSION 4.3)

project(SistemaDeBiblioteca)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

find_package(nlohmann_json 3.11 QUIET)
if(NOT nlohmann_json_FOUND)
    FetchContent_Declare(
            nlohmann_json
            URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

add_executable(SistemaDeBiblioteca
        src/main.cpp
        src/Livro.cpp
        src/Biblioteca.cpp
        src/LivroFisico.cpp
        src/Ebook.cpp
        src/Usuario.cpp
        include/Emprestimo.h
        src/Emprestimo.cpp
        include/Interface.h
        src/Interface.cpp
        include/Exception.h
        src/Exception.cpp
)

target_include_directories(SistemaDeBiblioteca PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(SistemaDeBiblioteca PRIVATE nlohmann_json::nlohmann_json)