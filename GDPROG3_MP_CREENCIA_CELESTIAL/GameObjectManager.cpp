#include "GameObjectManager.h"
#include <iostream>
#include "GenericInputController.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance() {
	if (sharedInstance == NULL) {
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}


AGameObject* GameObjectManager::findObjectByName(std::string name) {
	if (gameObjectMap[name] != NULL){ 
		return gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

List GameObjectManager::getAllObjects() {
	return gameObjectList;
}

int GameObjectManager::activeObjects() {
	return gameObjectList.size();
}


void GameObjectManager::processInput(sf::Event event) {
	for (int i = 0; i < gameObjectList.size(); i++) {
		gameObjectList[i]->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime){
	// std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < gameObjectList.size(); i++) {
		gameObjectList[i]->update(deltaTime); 
	}

}


void GameObjectManager::draw(sf::RenderWindow* window) {
	for (int i = 0; i < gameObjectList.size(); i++) {
		gameObjectList[i]->draw(window, sf::RenderStates::Default);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	gameObjectMap[gameObject->getName()] = gameObject;
	gameObjectList.push_back(gameObject);
	gameObject->initialize();
}


void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	std::string key = gameObject->getName();
	delete gameObject;
	gameObjectMap.erase(key);
	gameObjectList.erase(std::remove(gameObjectList.begin(), gameObjectList.end(), gameObject), gameObjectList.end());
	gameObjectList.shrink_to_fit();

}

void GameObjectManager::deleteObjectByName(std::string name) {
	AGameObject* object = findObjectByName(name);

	if (object != NULL) {
		deleteObject(object);
	}
}


void GameObjectManager::deleteAllObjectsInScene()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		delete this->gameObjectList[i];
	}

	this->gameObjectList.clear(); this->gameObjectList.shrink_to_fit();
	this->gameObjectMap.clear();
}
