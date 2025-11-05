#include "AI.hpp"

void AI::trainModel(const std::vector<Animal>& animals) {
	std::vector<double> tempTotal;
	std::vector<double> activityTotal;
	std::vector<double> socialDistTotal;

	for (const Animal& animal : animals) {
		tempTotal.push_back(animal.m_temperature);
		activityTotal.push_back(animal.m_activity);
		socialDistTotal.push_back(animal.m_socialDistance);
	}

	m_tempAverage = averageFromVector(tempTotal);
	m_activityAverage = averageFromVector(activityTotal);
	m_socialDistAverage = averageFromVector(socialDistTotal);

	m_tempDeviation = deviationFromVector(animals, m_tempAverage);
	m_activityDeviation = deviationFromVector(animals, m_activityAverage);
	m_socialDistDeviation = deviationFromVector(animals, m_socialDistAverage);
}

void AI::detectRisk(const std::vector<Animal>& animals) {
	for (Animal animal : animals) {
		if (animal.m_score >= m_highScore) {
			animal.m_risk = HIGH;
		}
		else if (animal.m_score >= m_mediumScore) {
			animal.m_risk = MEDIUM;
		}
		else if (animal.m_score >= m_lowScore) {
			animal.m_risk = LOW;
		}
		else {
			animal.m_risk = NORMAL;
		}
	}
}
