#include "animal.hpp"

#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

std::vector<char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("FAILED TO OPEN FILE: " + filename);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> content(fileSize);

    file.seekg(0);
    file.read(content.data(), fileSize);

    file.close();

    return content;
}

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
    system("chcp 1250");
    system("cls");
	std::vector<char> art = readFile("D:\\SIMDA\\ascii.txt");

    for (const char& c : art) {
		std::cout << c;
    }

	std::cout << "\n\n";

    std::vector<double> averages;
    double averageTotal = 0;
    int qtd = 0;

    for (int i = 0; i < 50; i++) {
        double average = 0;
        std::vector<Animal> swines{ 20 };
        for (Animal& swine : swines) {
            showDetails(swine);
            swine.detectAnomaly();
            average += swine.m_score;
            std::cout << "\n";
            qtd++;
        }
        double batchAverage = std::round((average / swines.size()) * 100) / 100;
		averageTotal += batchAverage;
        averages.push_back(batchAverage);
    }

    std::cout << "Score médio dos suínos: " << averageTotal / 50 << std::endl;
    for (size_t i = 0; i < averages.size(); i++) {
        std::cout << "Score médio do lote " << i + 1 << ": " << averages[i] << std::endl;
	}
    std::cout << "Qtd suínos: " << qtd << std::endl;

	return 0;
}