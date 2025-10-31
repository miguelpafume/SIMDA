#include "animal.hpp"

#include <iostream>
#include <random>
#include <vector>
#include <iomanip>

// chcp 1250

void showDetails(const Animal& animal) {
    //std::cout << "--------------------------------------------------------" << std::endl;
    //std::cout << "Suíno ID: " << animal.m_id << " | **RISCO: " << animal.status_risco << "**" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2); // 2 decimals precision
    std::cout << "Dados Coletados:" << std::endl;
    std::cout << "- Temperatura Corporal: " << animal.m_temperature << " °C" << std::endl;
    std::cout << "- Nível de Atividade:   " << animal.m_activity << " %" << std::endl;
    //std::cout << "--------------------------------------------------------" << std::endl;
    //std::cout << "Mensagem do SIMDA: " << animal.mensagem << std::endl;
    std::cout << "\n";
}

int main() {
    std::vector<Animal> swines{ 5 };

    for (Animal& swine : swines) {
        showDetails(swine);
		swine.detectAnomaly();
        std::cout << "\n";
    }

	return 0;
}