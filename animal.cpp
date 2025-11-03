#include "animal.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

/*
CALC FOR STANDARD DEVIATION
sigma = sqrt((x1 - average)^2 + (x2 - average)^2 +... / N-1)
*/

constexpr double AVERAGE_TEMPERATURE = 38.9;
constexpr uint16_t TEMPERATURE_WEIGHT = 8;
double TEMPERATURE_DEVIATION = std::sqrt((std::pow((38.6 - AVERAGE_TEMPERATURE), 2) + std::pow((38.9 - AVERAGE_TEMPERATURE), 2) + std::pow((39.2 - AVERAGE_TEMPERATURE), 2)) / (3 - 1));

constexpr uint16_t AVERAGE_ACTIVITY = 80;
constexpr uint16_t ACTIVITY_WEIGHT = 5;
double ACTIVITY_DEVIATION = std::sqrt((std::pow(70 - AVERAGE_ACTIVITY, 2) + std::pow(80 - AVERAGE_ACTIVITY, 2) + std::pow(90 - AVERAGE_ACTIVITY, 2)) / (3 - 1));

template <typename T>
int calcDeviationScore(T value, T average, double sigma, int weight) {
	T deviation = std::abs(value - average);

	if (sigma == 0.0) return 0; // Prevent division by zero
	
	// If within standard deviation, return negative weight (no anomaly)
	if ((double)deviation <= sigma) {
		return static_cast<int16_t>(-weight);
	}

	return static_cast<int16_t>(deviation / sigma * weight);
}

Animal::Animal(Risk risk) : m_risk{ risk } {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<uint16_t> randomId(1, 9999);

	std::uniform_real_distribution<double> randomTemperature(37.0, 40.0);
	std::uniform_int_distribution<int> randomActivity(50, 100);
	std::uniform_int_distribution<int> randomAge(4, 240);

	m_temperature = std::round(randomTemperature(gen) * 10) / 10;
	m_activity = static_cast<uint16_t>(randomActivity(gen));
	m_id = static_cast<uint16_t>(randomId(gen));
	m_age = static_cast<uint16_t>(randomAge(gen));
}

void Animal::detectAnomaly() {
	int16_t score = 0;

	// Temperature anomaly detection
	int16_t temperatureScore = calcDeviationScore(m_temperature, AVERAGE_TEMPERATURE, TEMPERATURE_DEVIATION, TEMPERATURE_WEIGHT);
	score += temperatureScore;
	std::cout << "Pontos por Desvio de Temperatura: " << temperatureScore << std::endl; // DEBUG

	// Activity anomaly detection
	int16_t activityScore = calcDeviationScore(m_activity, AVERAGE_ACTIVITY, ACTIVITY_DEVIATION, ACTIVITY_WEIGHT);
	score += activityScore;
	std::cout << "Pontos por Desvio de Atividade: " << activityScore << std::endl; // DEBUG

	std::cout << "Pontuação Total de Anomalia: " << score << std::endl; // DEBUG
}