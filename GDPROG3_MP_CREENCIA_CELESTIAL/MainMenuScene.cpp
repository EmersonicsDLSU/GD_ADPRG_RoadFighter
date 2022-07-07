#include "MainMenuScene.h"
#include "MainMenuScreen.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include <iostream>

MainMenuScene::MainMenuScene() : AScene("MainMenuScene")
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::onLoadResources()
{

}

void MainMenuScene::onLoadObjects()
{
	std::cout << "Main menu scene initialized! \n";
	MainMenuScreen* menuScreen = new MainMenuScreen("MainMenuScreen");
	this->registerObject(menuScreen);
}

void MainMenuScene::onUnloadResources()
{
	AScene::onUnloadObjects();
}