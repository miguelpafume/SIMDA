#pragma once

#include "Util.hpp"
#include "Animal.hpp"
#include <queue>

class AI {
public:
	AI() = default;
	~AI() = default;

	const uint16_t m_tempWeight = 10;
	const uint16_t m_activityWeight = 7;
	const uint16_t m_socialDistWeight = 5;

	double m_tempAverage = 0;
	double m_activityAverage = 0;
	double m_socialDistAverage = 0;

	double m_tempDeviation = 0;
	double m_activityDeviation = 0;
	double m_socialDistDeviation = 0;

	double m_highScore = 80;
	double m_mediumScore = 50;
	double m_lowScore = 25;

	void trainModel(const std::vector<Animal>& animals);
	void setSocialDistances(std::vector<Animal>& animals);
	double detectScore(const Animal& animals);
	Risk detectRisk(const Animal& animal);
};