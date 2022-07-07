
#pragma once
#include "AComponent.h"
class PlayerMovement : public AComponent
{
public:
	PlayerMovement(string name);
	~PlayerMovement();
	void perform();
	bool Dpress = false;
	bool Fpress = false;

public:
	sf::Vector2f leftRail{ 337.0f, 0 };
	sf::Vector2f rightRail{ 757.0f, 0 };

private:
	const float SPEED_MULTIPLIER = 100.0f;
	const float LOW_ACCE_SPEED = 2.5f;
	const float HIGH_ACCE_SPEED = 7.5f;
	const float BG_LOW_SPEED = 1000.0f;
	const float BG_HIGH_SPEED = 1500.0f;
};