#pragma once
#include "AScene.h"
#include "EmptyGameObject.h"
#include "EnemySwarmHandler.h"
class GameScene : public AScene
{
public:
	GameScene();
	~GameScene();

	void onLoadResources();
	void onLoadObjects();
	void onUnloadObjects();
	void onUnloadResources();

private:
	float RandomFloat(float a, float b);
	void instantiateEnemySpawn(EmptyGameObject* eg, int size, std::string handlerName,
		std::string poolName, float random, std::string EOName, std::string carType);
	vector<std::string> poolContainer;
	void unLoadPool();
};