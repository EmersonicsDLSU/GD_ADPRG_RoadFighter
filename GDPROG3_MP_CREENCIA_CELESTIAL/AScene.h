#pragma once
#include "AGameObject.h"

//deals with loading of resources, and loading of objects, then registering them to object manager.
//also does the opposite, unloading.
class AScene
{
public:
	AScene(string sceneName);
	~AScene();

	virtual void onLoadResources() = 0;
	virtual void onLoadObjects() = 0;

	virtual void onUnloadResources() = 0;
	virtual void onUnloadObjects();

	string getSceneName();

protected:
	void registerObject(AGameObject* object); //IMPORTANT: This must be called for every object to be loaded/unloaded.
	string sceneName;
};
