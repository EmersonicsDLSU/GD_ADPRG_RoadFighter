#include "InstructionsMenu.h"
#include "QuitScreen.h"
#include "UIText.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "Renderer.h"
#include "SceneManager.h"

InstructionsMenu::InstructionsMenu(string name) : AGameObject(name), ButtonListener()
{
}

InstructionsMenu::~InstructionsMenu()
{
	AGameObject::~AGameObject();
}

void InstructionsMenu::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	Renderer* renderer = new Renderer("QuitScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* button = new UIButton("button_1", btnNormal, btnPressed);
	button = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(150, 200);
	button->getTransformable()->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_2Text = new UIText("text_2");
	button->attachChild(button_2Text);
	button_2Text->setPosition(0, 0);
	button_2Text->setSize(80);
	button_2Text->setText("BACK");

	UIText* displayText = new UIText("displayText");
	this->attachChild(displayText);
	displayText->setPosition(0, -40);
	displayText->setSize(25);
	displayText->setText("INSTRUCTIONS \n D - Low Speed Acceleration \n F - High Speed Acceleration \n Arrow Keys - Steering");

	//ApplicationManager::getInstance()->pauseApplication();
}

void InstructionsMenu::onButtonClick(UIButton* button)
{

}

void InstructionsMenu::onButtonReleased(UIButton* button)
{
	if (button->getName() == "button_1") {
		//ApplicationManager::getInstance()->resumeApplication();
		GameObjectManager::getInstance()->deleteObject(this);
	}
}


void InstructionsMenu::markMainMenuQuit()
{
	this->forMainMenu = true;
}

void InstructionsMenu::markGameQuit()
{
	this->forMainMenu = false;
}