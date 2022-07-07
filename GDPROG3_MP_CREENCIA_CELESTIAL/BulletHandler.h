
#pragma once
#include "AComponent.h"
//class handling N enemy airplanes. communicates with object pool
class BulletHandler : public AComponent
{
public:
	BulletHandler(int numEnemies, string name);
	~BulletHandler();
	void perform();

private:
	const float SPAWN_INTERVAL = 0.5f;
	float ticks = 0.0f;
};