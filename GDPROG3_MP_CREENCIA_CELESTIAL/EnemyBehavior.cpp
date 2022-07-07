#include "EnemyBehavior.h"
#include "AGameObject.h"
#include <iostream>
#include "Game.h";
#include "GameObjectManager.h";
#include "ObjectPoolHolder.h"
#include "EnemyAirplane.h"
#include "EnemySwarmHandler.h"
#include "GameObjectManager.h"
#include "GameSystem.h"
#include "Collider.h"
#include "AirplanePlayer.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"

EnemyBehavior::EnemyBehavior(string name) : AComponent(name, Script)
{

}

void EnemyBehavior::perform()
{
	this->ticks += this->deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	//New update

	//gets the gameObjects and components
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;
	PlayerMovement* pm = (PlayerMovement*)player->findComponentByName("MyPlayerInput");
	PlayerInputController* pc = (PlayerInputController*)player->findComponentByName("MyPlayerInput");
	GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
	EnemyAirplane* ep = (EnemyAirplane*)this->owner;
	Collider* coll = (Collider*)ep->findComponentByName("Enemy_col");

	if (player != NULL)
	{
		float moveX;
		//move backward or forward for the enemies
		if (ep->getTransformable()->getPosition().x < Game::WINDOW_WIDTH / 2 && ep->getTransformable()->getPosition().x >= 337.0f)
		{
			moveX = 50; //moves to the right
		}
		if (ep->getTransformable()->getPosition().x >= Game::WINDOW_WIDTH / 2 && ep->getTransformable()->getPosition().x <= 757.0f)
		{
			//ep->getTransformable()->getPosition().x >= pm->rightRail.x
			moveX = -50; //moves to the left
		}
		transformable->move((pc->isD() || pc->isF()) ? moveX * deltaTime.asSeconds() : 0, (pc->isD() || pc->isF()) ? gs->enemySpeed : -gs->enemySpeed);
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

void EnemyBehavior::changeSpawnInterval()
{
	srand(time(NULL));
	EnemyAirplane* ep = (EnemyAirplane*)this->owner;
	if (ep->laneType == ObjectPoolHolder::ENEMY_POOL1_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager1")->findComponentByName("SwarmHandler1");
		//es->SPAWN_INTERVAL = RandomFloat(1,5);
	}
	else if (ep->laneType == ObjectPoolHolder::ENEMY_POOL2_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager2")->findComponentByName("SwarmHandler2");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
	else if (ep->laneType == ObjectPoolHolder::ENEMY_POOL3_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager3")->findComponentByName("SwarmHandler3");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
	else if (ep->laneType == ObjectPoolHolder::ENEMY_POOL4_TAG)
	{
		EnemySwarmHandler* es = (EnemySwarmHandler*)GameObjectManager::getInstance()->findObjectByName("EnemiesManager4")->findComponentByName("SwarmHandler4");
		//es->SPAWN_INTERVAL = RandomFloat(1, 5);
	}
}

float EnemyBehavior::RandomFloat(float a, float b)
{
	srand(time(NULL));
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void EnemyBehavior::configure(float delay)
{
	this->delay += delay;
}
