
#pragma once
#include "AComponent.h"
#include "EmptyGameObject.h"
//class handling N enemy airplanes. communicates with object pool
class EnemySwarmHandler : public AComponent
{
public:
	EnemySwarmHandler(int numEnemies, string name, EmptyGameObject* empty, std::string laneType, float interval, std::string emptyGOtype, std::string carType);
	~EnemySwarmHandler();
	void perform();
	std::string laneType;

public:
	float SPAWN_INTERVAL = 0.2f;
private:
	float ticks = 0.0f;
};