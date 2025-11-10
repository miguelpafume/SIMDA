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
	m_age = static_cast<uint16_t>(randomNumber(25, 200));
	m_size = 0.6 + (1.2 - 0.6) * (m_age - 25) / (200 - 25); // Linear interpolation between 0.6m and 1.2m based on age
}

void Animal::generatePosition(double minX, double maxX, double minY, double maxY) {
	std::pair<double, double> newLocation;

	double x = randomNumber(minX, maxX);
	double y = randomNumber(minY, maxY);

	newLocation = { std::round(x * 100) / 100.0, std::round(y * 100) / 100.0 };

	m_location = newLocation;
	return;
}

void Animal::generateUniquePosition(double minX, double maxX, double minY, double maxY, const std::vector<Animal>& animals) {
	std::pair<double, double> newLocation;

	uint16_t attempts = 0;

	while (true) {
		double x = randomNumber(minX, maxX);
		double y = randomNumber(minY, maxY);
		newLocation = { std::round(x * 100) / 100.0, std::round(y * 100) / 100.0 };

		bool collision = false;

		// Collision detection
		for (const auto& animal : animals) {
			double dist = calcDistance(newLocation, animal.m_location);

			if (dist < animal.m_size / 2 + m_size / 2) {
				collision = true;
				attempts++;

				if (attempts > 100) {
					std::cout << "Aviso: Quantidade de tentativas exedidas para gerar posição única. Animal ID: " << m_id << " gerado com possivel colisão." << std::endl;
					generatePosition(minX, maxX, minY, maxY);
					return;
				}

				break;
			}
		}

		if (!collision) {
			m_location = newLocation;
			break;
		}
	}
}

void Animal::update() {
	m_temperature += std::round(randomNumber(-0.2, 0.2) * 10) / 10;
	if (m_temperature < 37.2) m_temperature = 37.2;
	if (m_temperature > 40.4) m_temperature = 40.4;

	m_activity += static_cast<uint16_t>(randomNumber(-5, 5));
	if (m_activity > 100) m_activity = 100;

	m_heartRate += static_cast<uint16_t>(randomNumber(-5, 5));
	if (m_heartRate < 55) m_heartRate = 55;
	if (m_heartRate > 150) m_heartRate = 150;
}