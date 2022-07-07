#include "BonusCarBehavior.h"
#include "AGameObject.h"
#include <iostream>
#include "Game.h";
#include "GameObjectManager.h";
#include "ObjectPoolHolder.h"
#include "BonusCarObject.h"
#include "EnemySwarmHandler.h"
#include "GameObjectManager.h"
#include "GameSystem.h"
#include "Collider.h"
#include "AirplanePlayer.h"
#include "PlayerInputController.h"

BonusCarBehavior::BonusCarBehavior(string name) : AComponent(name, Script)
{

}

void BonusCarBehavior::perform()
{
	this->ticks += this->deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	//New update

	//gets the gameObjects and components
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;
	PlayerInputController* pc = (PlayerInputController*)player->findComponentByName("MyPlayerInput");
	GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
	BonusCarObject* ep = (BonusCarObject*)this->owner;
	Collider* coll = (Collider*)ep->findComponentByName("Enemy_col");

	if (player != NULL)
	{
		//move backward or forward for the enemies
		transformable->move(0, (pc->isD() || pc->isF()) ? gs->enemySpeed : -gs->enemySpeed);
	}

	if (coll->getOvertake())
	{
		//turn of the lane
		EmptyGameObject* eg = (EmptyGameObject*)GameObjectManager::getInstance()->findObjectByName(ep->emptyGOtype);
		eg->setEnabled(false);
	}

	//check if position is out of bounds, we can delete/return to pool
	if (transformable->getPosition().y > Game::WINDOW_HEIGHT + 50 || transformable->getPosition().y < -75 || isDestroyed || ObjectPoolHolder::getInstance()->getPool(ep->laneType)->usedSize() > 1) {
		ObjectPoolHolder::getInstance()->getPool(ep->laneType)->releasePoolable((APoolable*)this->getOwner());
		//set overtake to false again
		coll->setOvertake(false);
		//turn of the lane
		EmptyGameObject* eg = (EmptyGameObject*)GameObjectManager::getInstance()->findObjectByName(ep->emptyGOtype);
		eg->setEnabled(false);
		//random spawnInterval
		changeSpawnInterval();
	}

}

void BonusCarBehavior::changeSpawnInterval()
{
	srand(time(NULL));
	BonusCarObject* ep = (BonusCarObject*)this->owner;
	if (ep->laneType == ObjectPoolHolder::BONUS_POOL1_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager5")->findComponentByName("SwarmHandler5");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
	else if (ep->laneType == ObjectPoolHolder::BONUS_POOL2_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager6")->findComponentByName("SwarmHandler6");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
	else if (ep->laneType == ObjectPoolHolder::BONUS_POOL3_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager7")->findComponentByName("SwarmHandler7");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
	else if (ep->laneType == ObjectPoolHolder::BONUS_POOL4_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager8")->findComponentByName("SwarmHandler8");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
}

float BonusCarBehavior::RandomFloat(float a, float b)
{
	srand(time(NULL));
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void BonusCarBehavior::configure(float delay)
{
	this->delay += delay;
}
