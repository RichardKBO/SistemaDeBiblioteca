cmake_minimum_required(VERSION 3.20)

project(SistemaDeBiblioteca LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

find_package(nlohmann_json 3.11 QUIET)
if(NOT nlohmann_json_FOUND)
    FetchContent_Declare(
            nlohmann_json
            URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
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
        src/JsonBibliotecaRepository.cpp
        src/RelogioSistema.cpp
        include/BibliotecaSnapshot.h
        include/IBibliotecaRepository.h
        include/IRelogio.h
        include/JsonBibliotecaRepository.h
        include/RelogioSistema.h
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