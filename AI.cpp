#include "AI.hpp"

// "Train" the AI model by calculating averages and deviations from an healthy batch of animals
void AI::trainModel(const std::vector<Animal>& animals) {
	std::vector<double> tempTotal;
	std::vector<double> activityTotal;
	std::vector<double> socialDistTotal;
	std::vector<double> heartRateTotal;

	for (const Animal& animal : animals) {
		tempTotal.push_back(animal.m_temperature);
		activityTotal.push_back(animal.m_activity);
		socialDistTotal.push_back(animal.m_socialDistance);
		heartRateTotal.push_back(animal.m_heartRate);
	}

	m_tempAverage = averageFromVector(tempTotal);
	m_activityAverage = averageFromVector(activityTotal);
	m_socialDistAverage = averageFromVector(socialDistTotal);
	m_heartRateAverage = averageFromVector(heartRateTotal);

	m_tempDeviation = deviationFromVector(tempTotal, m_tempAverage);
	m_activityDeviation = deviationFromVector(activityTotal, m_activityAverage);
	m_socialDistDeviation = deviationFromVector(socialDistTotal, m_socialDistAverage);
	m_heartRateDeviation = deviationFromVector(heartRateTotal, m_heartRateAverage);
}

// Calculate and set social distances for each animal in the batch using the 5 closest animals to it
void AI::setSocialDistances(std::vector<Animal>& animals) {
	for (Animal& animal : animals) {
		double socialDistance = 0.0;

		std::vector<double> distances;

		for (const Animal& otherAnimal : animals) {
			if (animal.getId() != otherAnimal.getId()) {
				double dist = calcDistance(animal.m_location, otherAnimal.m_location);

				distances.push_back(dist);
			}
		}

		std::sort(distances.begin(), distances.end());

		// Calculate average of 5 closest distances
		for (uint16_t i = 0; i < 5; i++) {
			socialDistance += distances[i];
		}

		animal.m_socialDistance = std::round(socialDistance / 5 * 100) / 100;
	}
}

double AI::detectScore(const Animal& animal) {
	int16_t score = 0;
	double tempAverage = m_tempAverage;
	double activityAverage = m_activityAverage;
	double socialDistAverage = m_socialDistAverage;
	double heartRateAverage = m_heartRateAverage;

	// Change averages based on age
	if (animal.m_age < 60) {
		tempAverage += 0.3;
		activityAverage += 5;
		socialDistAverage -= 0.2;
		heartRateAverage += 15;
	} else if (animal.m_age > 180) {
		tempAverage -= 0.2;
		activityAverage -= 10;
		socialDistAverage += 0.2;
		heartRateAverage -= 10;
	}

	// Change averages based on activity
	if (animal.m_activity > 90) {
		tempAverage += 0.5;
		socialDistAverage -= 0.2;
		heartRateAverage += 5;
	} else if (animal.m_activity < 70) {
		tempAverage -= 0.5;
		socialDistAverage += 0.2;
		heartRateAverage -= 5;
	}

	// Temperature anomaly detection
	int16_t temperatureScore = calcDeviationScore(animal.m_temperature, tempAverage, m_tempDeviation, m_tempWeight);
	score += temperatureScore;

	// Activity anomaly detection
	int16_t activityScore = calcDeviationScore(animal.m_activity, activityAverage, m_activityDeviation, m_activityWeight);
	score += activityScore;

	// Social distance anomaly detection
	int16_t socialDistanceScore = calcDeviationScore(animal.m_socialDistance, socialDistAverage, m_socialDistDeviation, m_socialDistWeight, false);
	score += socialDistanceScore;

	// Heart rate anomaly detection
	int16_t heartRateScore = calcDeviationScore(animal.m_heartRate, heartRateAverage, m_heartRateDeviation, m_heartRateWeight);
	score += heartRateScore;

	return score;
}

Risk AI::detectRisk(const Animal& animal) {
	if (animal.m_score >= m_highScore) {
		return HIGH;
	} else if (animal.m_score >= m_mediumScore) {
		return MEDIUM;
	} else if (animal.m_score >= m_lowScore) {
		return LOW;
	} else {
		return NORMAL;
	}
}