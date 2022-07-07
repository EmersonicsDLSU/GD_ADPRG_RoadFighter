#include "AScene.h"
#include "GameObjectManager.h"

AScene::AScene(string sceneName)
{
	this->sceneName = sceneName;
}

AScene::~AScene()
{

}

void AScene::onUnloadObjects()
{
	GameObjectManager::getInstance()->deleteAllObjectsInScene();
}

string AScene::getSceneName()
{
	return this->sceneName;
}

void AScene::registerObject(AGameObject* object)
{
	GameObjectManager::getInstance()->addObject(object);
}