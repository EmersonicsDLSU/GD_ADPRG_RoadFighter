#include "EnemySwarmHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyAirplane.h"
#include "BonusCarObject.h"
#include "TruckObject.h"
#include "OilObject.h"
#include <iostream>

EnemySwarmHandler::EnemySwarmHandler(int numEnemies, string name, EmptyGameObject* empty, std::string laneType,
	float interval, std::string emptyGOtype, std::string carType) :
	AComponent(name, Script), laneType(laneType), SPAWN_INTERVAL(interval)
{
	if(carType == "normal")
	{
		GameObjectPool* enemyPool = new GameObjectPool(laneType, new EnemyAirplane("enemy", empty->position, laneType, emptyGOtype), numEnemies, NULL);
		enemyPool->initialize();
		ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	}
	else if (carType == "bonus")
	{
		GameObjectPool* enemyPool = new GameObjectPool(laneType, new BonusCarObject("enemy", empty->position, laneType, emptyGOtype), numEnemies, NULL);
		enemyPool->initialize();
		ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	}
	else if (carType == "truck")
	{
		GameObjectPool* enemyPool = new GameObjectPool(laneType, new TruckObject("enemy", empty->position, laneType, emptyGOtype), numEnemies, NULL);
		enemyPool->initialize();
		ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	}
	else if (carType == "oil")
	{
		GameObjectPool* enemyPool = new GameObjectPool(laneType, new OilObject("enemy", empty->position, laneType, emptyGOtype), numEnemies, NULL);
		enemyPool->initialize();
		ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	}

}

EnemySwarmHandler::~EnemySwarmHandler()
{

}

void EnemySwarmHandler::perform()
{
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(laneType);
	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks > SPAWN_INTERVAL) {
		this->ticks = 0.0f;
		enemyPool->requestPoolable();
	}
}