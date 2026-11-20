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
        src/domain/Livro.cpp
        src/domain/LivroFisico.cpp
        src/domain/Ebook.cpp
        src/domain/Usuario.cpp
        src/domain/Emprestimo.cpp
        src/domain/Exception.cpp
        src/application/Biblioteca.cpp
        src/infrastructure/JsonBibliotecaRepository.cpp
        src/infrastructure/RelogioSistema.cpp
        src/presentation/Interface.cpp
)

target_include_directories(SistemaDeBiblioteca PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain
        ${CMAKE_CURRENT_SOURCE_DIR}/include/application
        ${CMAKE_CURRENT_SOURCE_DIR}/include/infrastructure
        ${CMAKE_CURRENT_SOURCE_DIR}/include/presentation
)

target_link_libraries(SistemaDeBiblioteca PRIVATE nlohmann_json::nlohmann_json)