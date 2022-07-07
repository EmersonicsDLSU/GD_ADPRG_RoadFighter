#include "OilBehavior.h"
#include "AGameObject.h"
#include <iostream>
#include "Game.h";
#include "GameObjectManager.h";
#include "ObjectPoolHolder.h"
#include "OilObject.h"
#include "EnemySwarmHandler.h"
#include "GameObjectManager.h"
#include "GameSystem.h"
#include "Collider.h"
#include "AirplanePlayer.h"
#include "PlayerInputController.h"

OilBehavior::OilBehavior(string name) : AComponent(name, Script)
{

}

void OilBehavior::perform()
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
	OilObject* ep = (OilObject*)this->owner;
	Collider* coll = (Collider*)ep->findComponentByName("Enemy_col");

	if (player != NULL)
	{
		//move backward or forward for the enemies
		transformable->move(0, (pc->isD() || pc->isF()) ? gs->enemySpeed : 0);
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

void OilBehavior::changeSpawnInterval()
{
	srand(time(NULL));
	OilObject* ep = (OilObject*)this->owner;
	if (ep->laneType == ObjectPoolHolder::OIL_POOL1_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager13")->findComponentByName("SwarmHandler13");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
	else if (ep->laneType == ObjectPoolHolder::OIL_POOL2_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager14")->findComponentByName("SwarmHandler14");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
	else if (ep->laneType == ObjectPoolHolder::OIL_POOL3_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager15")->findComponentByName("SwarmHandler15");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
	else if (ep->laneType == ObjectPoolHolder::OIL_POOL4_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager16")->findComponentByName("SwarmHandler16");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
}

float OilBehavior::RandomFloat(float a, float b)
{
	srand(time(NULL));
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void OilBehavior::configure(float delay)
{
	this->delay += delay;
}
