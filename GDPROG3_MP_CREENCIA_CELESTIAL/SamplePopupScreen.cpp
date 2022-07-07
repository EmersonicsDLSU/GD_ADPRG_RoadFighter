#include "SamplePopupScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "ApplicationManager.h"
#include "Renderer.h"
#include "SFXManager.h"
#include "GameSystem.h"
#include "GameObjectManager.h"

SamplePopupScreen::SamplePopupScreen(string name, std::string popType) :AGameObject(name), ButtonListener(), popType(popType)
{

}

SamplePopupScreen::~SamplePopupScreen()
{
	AGameObject::~AGameObject();
}

void SamplePopupScreen::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	//sprite->setColor(sf::Color::Cyan);
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	this->getTransformable()->setScale(0.5f, 0.5f);

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* button = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(0, 100);
	button->getTransformable()->setScale(0.5f, 0.5f);
	button->setButtonListener(this);

	SFXManager::getInstance()->stopSound("bgmusic");

	if (this->popType == "gameOver")
	{
		UIText* button_1Text = new UIText("text_1");
		button->attachChild(button_1Text);
		button_1Text->setPosition(0, -20);
		button_1Text->setSize(70);
		button_1Text->setText("Play Again");

		UIText* displayText = new UIText("displayText");
		this->attachChild(displayText);
		displayText->setPosition(0, -100);
		displayText->setSize(60);
		displayText->setText("Game Over!");
	}
	else if (this->popType == "win")
	{
		UIText* button_1Text = new UIText("text_1");
		button->attachChild(button_1Text);
		button_1Text->setPosition(0, -20);
		button_1Text->setSize(70);
		button_1Text->setText("Next Level");

		UIText* displayText = new UIText("displayText");
		this->attachChild(displayText);
		displayText->setPosition(0, -100);
		displayText->setSize(60);
		displayText->setText("CHECKPOINT");
	}


}

void SamplePopupScreen::onButtonClick(UIButton* button)
{

}

void SamplePopupScreen::onButtonReleased(UIButton* button)
{
	GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
	if(this->popType == "gameOver")
	{
		GameObjectManager::getInstance()->deleteObject(this);
		SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
		gs->resetGameSystem();
		//ApplicationManager::getInstance()->resumeApplication()
	}
	else if (this->popType == "win" && GameSystem::currentLevel == 2)
	{
		SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE2_NAME);
		ApplicationManager::getInstance()->resumeApplication();
		GameObjectManager::getInstance()->deleteObject(this);
	}
	else if (this->popType == "win" && GameSystem::currentLevel == 3)
	{
		SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE3_NAME);
		ApplicationManager::getInstance()->resumeApplication();
		GameObjectManager::getInstance()->deleteObject(this);
	}
	else if (this->popType == "win" && GameSystem::currentLevel == 4)
	{
		SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
		gs->resetGameSystem();
		GameObjectManager::getInstance()->deleteObject(this);
	}
}