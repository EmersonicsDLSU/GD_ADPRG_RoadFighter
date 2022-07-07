#pragma once
#include "AScene.h"
class MainMenuScene : public AScene
{
public:
	MainMenuScene();
	~MainMenuScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};