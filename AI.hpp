#pragma once

#include "Util.hpp"
#include "Animal.hpp"
#include <queue>

class AI {
public:
	AI() = default;
	~AI() = default;

	const uint16_t m_tempWeight = 5;
	const uint16_t m_activityWeight = 3;
	const uint16_t m_socialDistWeight = 2;
	const uint16_t m_heartRateWeight = 4;

	double m_tempAverage = 0;
	double m_activityAverage = 0;
	double m_socialDistAverage = 0;
	double m_heartRateAverage = 0;

	double m_tempDeviation = 0;
	double m_activityDeviation = 0;
	double m_socialDistDeviation = 0;
	double m_heartRateDeviation = 0;

	double m_highScore = 70;
	double m_mediumScore = 50;
	double m_lowScore = 30;

	void trainModel(const std::vector<Animal>& animals);
	void setSocialDistances(std::vector<Animal>& animals);
	double detectScore(const Animal& animals);
	Risk detectRisk(const Animal& animal);
};