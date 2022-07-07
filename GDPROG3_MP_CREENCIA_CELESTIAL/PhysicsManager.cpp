#include "PhysicsManager.h"
#include "ObjectPoolHolder.h"
#include "EnemyAirplane.h"
#include "AirplanePlayer.h"
#include "UtilityBullet.h"
#include "EnemyBehavior.h"
#include "BulletBehavior.h"
#include "GameObjectManager.h"
#include <iostream>

PhysicsManager* PhysicsManager::sharedInstance = NULL;
int PhysicsManager::x = 0;
int PhysicsManager::y = 0;
int PhysicsManager::z = 0;
int PhysicsManager::i = 0;

PhysicsManager* PhysicsManager::getInstance() {
	if (sharedInstance == NULL) {
		sharedInstance = new PhysicsManager("Physics_Manager");
	}

	return sharedInstance;
}


PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::clearTracks()
{
	trackedPlayer.clear();
	trackedEnemy.clear();
	trackedUtility.clear();
	forCleaningObjects.clear();
}

void PhysicsManager::initialize(string name, AGameObject* parent)
{
	PhysicsManager* pm = new PhysicsManager(name);
	parent->attachComponent(pm);
}

//suspicious
void PhysicsManager::destroy()
{
	sharedInstance = NULL; //delete sharedInstance;
}

void PhysicsManager::trackObject(Collider* object)
{
	if(object->collType == Collider::Player)
		this->trackedPlayer.push_back(object);
	else if (object->collType == Collider::Enemy)
	{
		this->trackedEnemy.push_back(object);
	}
	else if (object->collType == Collider::Utility)
	{
		this->trackedUtility.push_back(object);
	}
}

void PhysicsManager::untrackObject(Collider* object)
{
	/*//suspicous
	delete object;*/
	if (object->collType == Collider::Player)
	{
		AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
		if (player != NULL)
		{
			if (player->life <= 0)
			{
				sharedInstance->trackedPlayer.erase(std::remove(trackedPlayer.begin(), trackedPlayer.end(), object), trackedPlayer.end());
				sharedInstance->trackedPlayer.shrink_to_fit();
			}
		}
	}
	else if (object->collType == Collider::Enemy)
	{
		sharedInstance->trackedEnemy.erase(std::remove(trackedEnemy.begin(), trackedEnemy.end(), object), trackedEnemy.end());
		sharedInstance->trackedEnemy.shrink_to_fit();
	}
	else if (object->collType == Collider::Utility)
	{
		sharedInstance->trackedUtility.erase(std::remove(trackedUtility.begin(), trackedUtility.end(), object), trackedUtility.end());
		sharedInstance->trackedUtility.shrink_to_fit();
	}
	object->setAlreadyCollided(true);
	sharedInstance->forCleaningObjects.push_back(object);
}

//don't delete
void PhysicsManager::cleanUpObjects()
{
	
	for (i = 0; i < sharedInstance->forCleaningObjects.size(); i++) {
		sharedInstance->forCleaningObjects[i]->collisionEnter(sharedInstance->forCleaningObjects[i]->getOwner(), sharedInstance->forCleaningObjects[i]->collType, sharedInstance->forCleaningObjects[i]);
	}
	
	sharedInstance->forCleaningObjects.clear();
	sharedInstance->forCleaningObjects.shrink_to_fit();
}

void PhysicsManager::perform()
{
	//checks if the MC gets derailed on the road
	AirplanePlayer* player = (AirplanePlayer*)this->owner;
	if (player->isDestroyed)
	{
		sharedInstance->untrackObject(sharedInstance->trackedPlayer[0]);
	}

	//list of possible collisions; all objects
	if (sharedInstance->trackedPlayer.size() > 0)
	{
		for (x = 0 ; x < sharedInstance->trackedEnemy.size(); x++)
		{
			if (sharedInstance->trackedPlayer[0]->willCollide(sharedInstance->trackedEnemy[x]))
			{
				sharedInstance->untrackObject(sharedInstance->trackedPlayer[0]);
				sharedInstance->untrackObject(sharedInstance->trackedEnemy[x]);
				break;
			}
			sharedInstance->trackedPlayer[0]->willOverTake(sharedInstance->trackedEnemy[x]);
		}
	}
	if (sharedInstance->trackedEnemy.size() > 0 && sharedInstance->trackedUtility.size() > 0)
	{
		for (y = 0; y < sharedInstance->trackedUtility.size(); y++)
		{
			for (z = 0; z < sharedInstance->trackedEnemy.size(); z++)
			{
				if (sharedInstance->trackedUtility[y]->willCollide(sharedInstance->trackedEnemy[z]))
				{
					sharedInstance->untrackObject(sharedInstance->trackedUtility[y]);
					sharedInstance->untrackObject(sharedInstance->trackedEnemy[z]);
					break;
				}
			}
		}
	}

	if (sharedInstance->forCleaningObjects.size() > 0)
	{
		sharedInstance->cleanUpObjects();
	}

	/*
	GameObjectPool* sample1 = (GameObjectPool*)ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL1_TAG);
	GameObjectPool* sample2 = (GameObjectPool*)ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL2_TAG);
	GameObjectPool* sample3 = (GameObjectPool*)ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL3_TAG);
	GameObjectPool* sample4 = (GameObjectPool*)ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL4_TAG);
	cout << sample1->usedObjects.size() << ":" << sample2->usedObjects.size() << ":" << sample3->usedObjects.size() << ":" << sample4->usedObjects.size() << endl;*/
}
