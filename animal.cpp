#include "animal.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

/*
CALC FOR STANDARD DEVIATION
sigma = sqrt((x1 - average)^2 + (x2 - average)^2 +... / N)
*/

constexpr double AVERAGE_TEMPERATURE = 38.9;
constexpr uint8_t TEMPERATURE_WEIGHT = 8;
float TEMPERATURE_DEVIATION = std::sqrt((std::pow((38.6 - AVERAGE_TEMPERATURE), 2) + std::pow((38.9 - AVERAGE_TEMPERATURE), 2) + std::pow((39.2 - AVERAGE_TEMPERATURE), 2)) / 3);

template <typename T>
int calcDeviationScore(T value, T average, double sigma, int weight) {
	T deviation = std::abs(value - average);

	if (sigma == 0.0) return 0; // Prevent division by zero
	if (deviation <= sigma) return 0; // No change if deviation is within expected range

	double deviationWeight = deviation / sigma;

	return static_cast<int16_t>(deviationWeight * weight);
}

Animal::Animal() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<double> distTemperature(37.0, 40.0);

	m_temperature = std::round(distTemperature(gen) * 10) / 10;
}

void Animal::detectAnomaly() {
	int16_t score = 0;

	// Temperature anomaly detection
	score += calcDeviationScore(m_temperature, AVERAGE_TEMPERATURE, TEMPERATURE_DEVIATION, TEMPERATURE_WEIGHT);
	std::cout << std::fixed << std::setprecision(5); // 5 decimals precision
	std::cout << "Pontos de Desvio de Temperatura: " << score << std::endl;
}