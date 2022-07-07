#pragma once
#include <stddef.h>
#include <SFML/System.hpp>
#include <unordered_map>
#include <vector>
#include "AGameObject.h"

typedef std::unordered_map<std::string, AGameObject*> HashTable;
typedef std::vector<AGameObject*> List;

class GameObjectManager : sf::NonCopyable
{

public:
    static GameObjectManager* getInstance();
    AGameObject* findObjectByName(std::string name);
    List getAllObjects();
    int activeObjects();
    void processInput(sf::Event event);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow* window);
    void addObject(AGameObject* window);
    void deleteObject(AGameObject* gameObject);
    void deleteObjectByName(std::string name);
    void deleteAllObjectsInScene();

private:
    // set constructor to private
    GameObjectManager() {};
    static GameObjectManager* sharedInstance;

    HashTable gameObjectMap;
    List gameObjectList;
};

