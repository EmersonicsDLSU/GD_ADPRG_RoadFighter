
#pragma once
#include "AComponent.h"
class TruckObjectBehavior : public AComponent
{
public:
	enum EnemyMovementType { Delay = 0, Forward = 1, SlowForward = 2, Side = 3 };

	TruckObjectBehavior(string name);
	void perform();
	void configure(float delay);

	bool isDestroyed = false;

private:
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;

private:
	void changeSpawnInterval();
	float RandomFloat(float a, float b);
};
