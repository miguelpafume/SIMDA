#include "animal.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <concepts>

/*
CALC FOR STANDARD DEVIATION
sigma = sqrt((x1 - average)^2 + (x2 - average)^2 +... / N-1)
*/

constexpr double AVG_TEMP = 38.9;
constexpr uint16_t TEMP_WEIGHT = 10;
double TEMP_DEVIATION = std::sqrt((std::pow((38.6 - AVG_TEMP), 2) + std::pow((38.9 - AVG_TEMP), 2) + std::pow((39.2 - AVG_TEMP), 2)) / (3 - 1));

constexpr uint16_t AVG_ACTIVITY = 80;
constexpr uint16_t ACTIVITY_WEIGHT = 7;
double ACT_DEVIATION = std::sqrt((std::pow(75 - AVG_ACTIVITY, 2) + std::pow(80 - AVG_ACTIVITY, 2) + std::pow(85 - AVG_ACTIVITY, 2)) / (3 - 1));

constexpr double AVG_SOCIAL_DIST = 1;
constexpr double SOCIAL_DIST_WEIGHT = 5;
double SOCIAL_DIST_DEVIATION = std::sqrt((std::pow(0.56 - AVG_ACTIVITY, 2) + std::pow(1 - AVG_ACTIVITY, 2) + std::pow(1.41 - AVG_ACTIVITY, 2)) / (3 - 1));

template <typename T>
int16_t calcDeviationScore(T value, T average, double sigma, uint16_t weight) {
	T deviation = std::abs(value - average);

	if (sigma == 0.0) return 0; // Prevent division by zero
	
	// If within standard deviation, return negative weight (healthy)
	if ((double)deviation <= sigma) {
		return static_cast<int16_t>(-weight);
	}

	return static_cast<int16_t>(deviation / sigma * weight);
}

int randomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> randomNum(min, max);
	return randomNum(gen);
}

double randomNumber(double min, double max) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<double> randomNum(min, max);
	return randomNum(gen);
}

int randomNumberInterval(int minA, int maxA, int minB, int maxB) {
	if (randomNumber(0, 1) == 0) {
		return randomNumber(minA, maxA);
	} else {
		return randomNumber(minB, maxB);
	}
}

double randomNumberInterval(double minA, double maxA, double minB, double maxB) {
	if (randomNumber(0, 1) == 0) {
		return randomNumber(minA, maxA);
	} else {
		return randomNumber(minB, maxB);
	}
}

Animal::Animal(Risk risk) : m_risk{ risk } {
	switch (risk) {
	case NORMAL:
		m_activity = static_cast<uint16_t>(randomNumber(70, 90));
		m_temperature = static_cast<double>(std::round(randomNumber(38.6, 39.2) * 10) / 10);
		break;
	case LOW:
		m_activity = static_cast<uint16_t>(randomNumberInterval(70, 75, 85, 90));
		m_temperature = static_cast<double>(std::round(randomNumberInterval(38.2, 38.6, 39.2, 39.6) * 10) / 10);
		break;
	case MEDIUM:
		m_activity = static_cast<uint16_t>(randomNumberInterval(65, 70, 90, 95));
		m_temperature = static_cast<double>(std::round(randomNumberInterval(37.8, 38.2, 39.6, 40.0) * 10) / 10);
		break;
	case HIGH:
		m_activity = static_cast<uint16_t>(randomNumberInterval(60, 65, 95, 100));
		m_temperature = static_cast<double>(std::round(randomNumberInterval(37.2, 37.8, 40.0, 40.4) * 10) / 10);
		break;
	case RANDOM:
		m_activity = static_cast<uint16_t>(randomNumber(60, 100));
		m_temperature = static_cast<double>(std::round(randomNumber(37.2, 40.4) * 10) / 10);
		break;
	}

	m_id = static_cast<uint16_t>(randomNumber(1, 9999));
	m_age = static_cast<uint16_t>(randomNumber(4, 240));
}

void Animal::detectAnomaly() {
	int16_t score = 0;

	// Temperature anomaly detection
	if (m_age < 45) {

	} else if (m_age > 160) {

	} else {

	}

	int16_t temperatureScore = calcDeviationScore(m_temperature, AVG_TEMP, TEMP_DEVIATION, TEMP_WEIGHT);
	score += temperatureScore;
	std::cout << "Pontos por Desvio de Temperatura: " << temperatureScore << std::endl; // DEBUG

	// Activity anomaly detection
	int16_t activityScore = calcDeviationScore(m_activity, AVG_ACTIVITY, ACT_DEVIATION, ACTIVITY_WEIGHT);
	score += activityScore;
	std::cout << "Pontos por Desvio de Atividade: " << activityScore << std::endl; // DEBUG

	std::cout << "Pontuação Total de Anomalia: " << score << std::endl; // DEBUG

	m_score = score;
}