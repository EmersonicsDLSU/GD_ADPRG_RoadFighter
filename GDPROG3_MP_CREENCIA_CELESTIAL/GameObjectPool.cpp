#include "GameObjectPool.h"
#include <iostream>
#include "GameObjectManager.h"

GameObjectPool::GameObjectPool(string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent)
{
	this->tag = tag;
	this->objectCopy = poolableCopy;
	this->maxPoolSize = poolableSize;
	this->parent = parent;
}

GameObjectPool::~GameObjectPool()
{
	this->objectCopy = NULL;
	this->parent = NULL;
}
//initializes the object pool
void GameObjectPool::initialize()
{
	for (int i = 0; i < this->maxPoolSize; i++) {
		APoolable* poolableObject = this->objectCopy->clone();
		//instantiate object but disable it.
		if (this->parent != NULL) {
			this->parent->attachChild(poolableObject);
		}
		else {
			GameObjectManager::getInstance()->addObject(poolableObject);
		}
		poolableObject->setEnabled(false);
		this->availableObjects.push_back(poolableObject);
	}
}

void GameObjectPool::addObject()
{
	APoolable* poolableObject = this->objectCopy->clone();
	//instantiate object but disable it.
	if (this->parent != NULL) {
		this->parent->attachChild(poolableObject);
	}
	else {
		GameObjectManager::getInstance()->addObject(poolableObject);
	}
	poolableObject->setEnabled(false);
	this->availableObjects.push_back(poolableObject);
}

bool GameObjectPool::hasObjectAvailable(int requestSize)
{
	return requestSize <= this->availableObjects.size();
}

APoolable* GameObjectPool::requestPoolable()
{
	if (this->hasObjectAvailable(1)) {
		APoolable* poolableObject = this->availableObjects[this->availableObjects.size() - 1];
		this->availableObjects.erase(this->availableObjects.begin() + this->availableObjects.size() - 1);
		this->usedObjects.push_back(poolableObject);

		//std::cout << "Requested object. Available: " << this->availableObjects.size() << " Used: " << this->usedObjects.size() << "\n";
		this->setEnabled(poolableObject, true);
		return poolableObject;
	}
	else {
		//std::cout << " No more poolable " + this->objectCopy->getName() + " available! \n";
		return NULL;
	}
}

ObjectList GameObjectPool::requestPoolableBatch(int size)
{
	ObjectList returnList;
	if (this->hasObjectAvailable(size)) {
		for (int i = 0; i < size; i++) {
			returnList.push_back(this->requestPoolable());
		}
	}
	else {
		/*std::cout << "Insufficient " + this->objectCopy->getName() + " available in pool. Count is: " << this->availableObjects.size() <<
			" while requested is " << size << "!\n";*/
	}

	return returnList;
}

void GameObjectPool::releasePoolable(APoolable* poolableObject)
{
	//find object in used
	int index = -1;
	for (int i = 0; i < this->usedObjects.size(); i++) {
		if (this->usedObjects[i] == poolableObject) {
			index = i;
			break;
		}
	}

	//std::cout << "Poolable index in used: " << index << "\n";
	if (index > -1) {
		this->usedObjects.erase(this->usedObjects.begin() + index);
		this->availableObjects.push_back(poolableObject);
		this->setEnabled(poolableObject, false);
	}

}

void GameObjectPool::deletePoolable(APoolable* poolableObject)
{
	//find object in used
	int index = -1;
	for (int i = 0; i < this->usedObjects.size(); i++) {
		if (this->usedObjects[i] == poolableObject) {
			index = i;
			break;
		}
	}

	//std::cout << "Poolable index in used: " << index << "\n";
	if (index > -1) {
		this->usedObjects.erase(this->usedObjects.begin() + index);
		this->setEnabled(poolableObject, false);
		GameObjectManager::getInstance()->deleteObject(poolableObject);
	}

}

void GameObjectPool::releasePoolableBatch(ObjectList objectList)
{
	for (int i = 0; i < objectList.size(); i++) {
		this->releasePoolable(objectList[i]);
	}
}

string GameObjectPool::getTag()
{
	return this->tag;
}

void GameObjectPool::setEnabled(APoolable* poolableObject, bool flag)
{
	if (flag) {
		poolableObject->setEnabled(true);
		poolableObject->onActivate();
	}
	else {
		poolableObject->setEnabled(false);
		poolableObject->onRelease();
	}
}

int GameObjectPool::usedSize()
{
	return usedObjects.size();
}

int GameObjectPool::availableSize()
{
	return availableObjects.size();
}

