#include "json.hpp"
using json = nlohmann::json;

#include "Util.hpp"
#include "Animal.hpp"
#include "AI.hpp"

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <thread>

// Global constants
const char* RISK_STRINGS[] = { "NORMAL", "BAIXO", "MEDIO", "ALTO", "UNKNOWN" };
constexpr double PEN_SIZE_X = 15.0;
constexpr double PEN_SIZE_Y = 15.0;

// Display animal details to console
void showDetails(const Animal& animal) {
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Suíno ID: " << animal.getId() << " | RISCO: " << RISK_STRINGS[animal.m_risk] << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2); // 2 decimals precision
    std::cout << "Dados Coletados:" << std::endl;
    std::cout << "- Idade: " << animal.m_age << " dias" << std::endl;
    std::cout << "- Temperatura Corporal: " << animal.m_temperature << " °C" << std::endl;
    std::cout << "- Nível de Atividade: " << animal.m_activity << " %" << std::endl;
    std::cout << "- Batimento Cardíaco: " << animal.m_heartRate << " BMP" << std::endl;
    std::cout << "- Posição: " << animal.m_location.first << " X | " << animal.m_location.second << " Y" << std::endl;
    std::cout << "- Distanciamento Social: " << animal.m_socialDistance << " m" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "\n";
}

void exportJson(const std::vector<Animal>& animals, const std::string filename) {
    json jsonArray;

    for (const Animal& animal : animals) {
        json animalJson;

        animalJson["id"] = animal.getId();
        animalJson["risk"] = RISK_STRINGS[animal.m_risk];

        animalJson["age"] = animal.m_age;
        animalJson["temperature"] = animal.m_temperature;
        animalJson["bpm"] = animal.m_heartRate;
        animalJson["activity"] = animal.m_activity;
        animalJson["social_distance"] = animal.m_socialDistance;

        jsonArray.push_back(animalJson);
    }

    try {
        std::ofstream file(filename);

        if (file.is_open()) {
            file << std::setw(4) << jsonArray << std::endl;
            file.close();
            std::cout << "Dados exportados para " << filename << std::endl;
        } else {
            std::cerr << "ERRO: Não foi possível abrir o arquivo para escrita: " << filename << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "ERRO ao escrever o arquivo JSON: " << e.what() << std::endl;
    }
}

int main() {
	// Prepare cmd for UNICODE output
    system("chcp 1250");

    AI ai;

	// Creates healthy swines for training
    std::vector<Animal> swinesHealthy;

    for (int i = 0; i < 50; i++) {
        Animal swine(NORMAL);
        swine.generatePosition(0.0, PEN_SIZE_X, 0.0, PEN_SIZE_Y);
        swinesHealthy.push_back(swine);
    }

    ai.setSocialDistances(swinesHealthy);
    ai.trainModel(swinesHealthy);

	// DON'T DO THIS
    Animal* tempSwine = new Animal();
    tempSwine->resetIdCounter();
    delete tempSwine;

	// Creates random swines for analysis
    std::vector<Animal> swinesRandom;
	
    for (int i = 0; i < 50; i++) {
        Animal swine(RANDOM);
        swine.generateUniquePosition(0.0, PEN_SIZE_X, 0.0, PEN_SIZE_Y, swinesRandom);
        swinesRandom.push_back(swine);
    }

	const auto delayDuration = std::chrono::milliseconds(5000);

    while (true) {
        system("cls");

        // Read & output ascii art
	    std::vector<char> art = readFile("D:\\SIMDA\\ascii.txt");
        for (const char& c : art) {
		    std::cout << c;
        }
	    std::cout << "\n\n";

        ai.setSocialDistances(swinesRandom);

        // Analyze swines and gives them a score & risk level
        for (Animal& swine : swinesRandom) {
            if (swine.m_risk == HIGH && swine.m_lastIteration < 5) {
                swine.m_lastIteration++;
                continue;
            }

            swine.m_score = ai.detectScore(swine);
            swine.m_risk = ai.detectRisk(swine);
            swine.m_lastIteration = 0;
        }

        for (Animal& swine : swinesRandom) {
            showDetails(swine);
        }

        exportJson(swinesRandom, "SimdaAnalysis.json");

		// Update swines data and reposition them
        for (Animal& swine : swinesRandom) {
            swine.update();
            swine.generateUniquePosition(0.0, PEN_SIZE_X, 0.0, PEN_SIZE_Y, swinesRandom);
		}

		std::this_thread::sleep_for(delayDuration);
    }

	return 0;
}