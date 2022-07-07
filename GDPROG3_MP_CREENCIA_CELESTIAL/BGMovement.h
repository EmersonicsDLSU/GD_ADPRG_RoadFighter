#pragma once
#include "AComponent.h"
class BGMovement : public AComponent
{
public:
	BGMovement(string name);
	~BGMovement();
	void setBGSpeed(float speed);
	float getBGSpeed();
	void perform();

private:
	float SPEED_MULTIPLIER = 1000.0f;
};