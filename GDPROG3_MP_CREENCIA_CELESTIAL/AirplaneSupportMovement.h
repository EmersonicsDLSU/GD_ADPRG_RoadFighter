#pragma once
#include "AComponent.h"
class AirplaneSupportMovement : public AComponent
{

public:
	AirplaneSupportMovement(string name);
	void perform();
	bool moveLeft = false;
	bool moveRight = false;

private:
	const float SPEED = 50.0f;

};

