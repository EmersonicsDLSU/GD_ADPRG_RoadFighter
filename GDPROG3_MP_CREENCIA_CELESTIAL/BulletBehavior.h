
#pragma once
#include "AComponent.h"
class BulletBehavior : public AComponent
{
public:
	enum BulletMovementType { Delay = 0, Forward = 1, SlowForward = 2, Side = 3 };

	BulletBehavior(string name);
	void perform();
	void configure(float delay);
	void reset();

private:
	const float SPEED_MULTIPLIER = 100.0f;
	BulletMovementType movementType = Forward;
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
};
