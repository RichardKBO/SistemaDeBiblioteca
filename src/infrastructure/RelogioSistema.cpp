#include "infrastructure/RelogioSistema.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string RelogioSistema::obterDataAtual() const
{
    const auto agora = std::chrono::system_clock::now();
    const std::time_t tempo = std::chrono::system_clock::to_time_t(agora);
    std::tm data{};
    localtime_r(&tempo, &data);

    std::ostringstream resultado;
    resultado << std::setfill('0') << std::setw(2) << data.tm_mday << "/"
              << std::setw(2) << data.tm_mon + 1 << "/"
              << data.tm_year + 1900;
    return resultado.str();
}
