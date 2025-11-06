#include "Animal.hpp"

uint16_t Animal::s_nextId = 1;

Animal::Animal(Risk risk) : m_risk{ risk } {
	switch (risk) {
	case NORMAL:
		m_activity = static_cast<uint16_t>(randomNumber(70, 90));
		m_temperature = std::round(randomNumber(38.6, 39.2) * 10) / 10;
		m_heartRate = static_cast<uint16_t>(randomNumber(75, 95));
		break;
	case LOW:
		m_activity = static_cast<uint16_t>(randomNumberInterval(70, 75, 85, 90));
		m_temperature = std::round(randomNumberInterval(38.2, 38.6, 39.2, 39.6) * 10) / 10;
		m_heartRate = static_cast<uint16_t>(randomNumberInterval(65, 70, 95, 100));
		break;
	case MEDIUM:
		m_activity = static_cast<uint16_t>(randomNumberInterval(65, 70, 90, 95));
		m_temperature = std::round(randomNumberInterval(37.8, 38.2, 39.6, 40.0) * 10) / 10;
		m_heartRate = static_cast<uint16_t>(randomNumberInterval(60, 70, 95, 110));
		break;
	case HIGH:
		m_activity = static_cast<uint16_t>(randomNumberInterval(60, 65, 95, 100));
		m_temperature = std::round(randomNumberInterval(37.2, 37.8, 40.0, 40.4) * 10) / 10;
		m_heartRate = static_cast<uint16_t>(randomNumberInterval(55, 65, 115, 125));
		break;
	case RANDOM:
		m_activity = static_cast<uint16_t>(randomNumber(60, 100));
		m_temperature = std::round(randomNumber(37.2, 40.4) * 10) / 10;
		m_heartRate = static_cast<uint16_t>(randomNumber(55, 150));
		break;
	}

	m_location = { std::round(randomNumber(0.0, 10.0) * 100) / 100, std::round(randomNumber(4.0, 6.0) * 100) / 100 };

	m_id = s_nextId;
	s_nextId++;
	m_age = static_cast<uint16_t>(randomNumber(15, 200));
}

void Animal::generatePosition(double minX, double maxX, double minY, double maxY) {
	std::pair<double, double> newLocation;

	double x = randomNumber(minX, maxX);
	double y = randomNumber(minY, maxY);

	newLocation = { std::round(x * 100) / 100.0, std::round(y * 100) / 100.0 };

	m_location = newLocation;
	return;
}

void Animal::generateUniquePosition(double minX, double maxX, double minY, double maxY, const std::vector<Animal>& animals, const double minDistance) {
	std::pair<double, double> newLocation;

	while (true) {
		double x = randomNumber(minX, maxX);
		double y = randomNumber(minY, maxY);
		newLocation = { std::round(x * 100) / 100.0, std::round(y * 100) / 100.0 };

		bool collision = false;

		// Collision detection
		for (const auto& animal : animals) {
			double dist = calcDistance(newLocation, animal.m_location);

			if (dist < minDistance) {
				collision = true;
				break;
			}
		}

		if (!collision) {
			m_location = newLocation;
			break;
		}
	}
}