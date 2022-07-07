#include "QuitScreen.h"
#include "UIText.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "GameSystem.h"

QuitScreen::QuitScreen(string name) : AGameObject(name), ButtonListener()
{
}

QuitScreen::~QuitScreen()
{
	AGameObject::~AGameObject();
}

void QuitScreen::initialize()
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
	this->attachChild(button);
	button->setPosition(-150,  150);
	button->getTransformable()->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(0, 0);
	button_1Text->setSize(80);
	button_1Text->setText("YES");

	button = new UIButton("button_2", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(150, 150);
	button->getTransformable()->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_2Text = new UIText("text_2");
	button->attachChild(button_2Text);
	button_2Text->setPosition(0, 0);
	button_2Text->setSize(80);
	button_2Text->setText("NO");

	UIText* displayText = new UIText("displayText");
	this->attachChild(displayText);
	displayText->setPosition(0, -100);
	displayText->setSize(30);
	displayText->setText("Are you sure you want \n to quit the game?");

	ApplicationManager::getInstance()->pauseApplication();
}

void QuitScreen::onButtonClick(UIButton* button)
{

}

void QuitScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "button_1") {
		if (this->forMainMenu) {
			ApplicationManager::getInstance()->applicationQuit();
		}
		else {
			SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
			ApplicationManager::getInstance()->resumeApplication();
			GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
			gs->resetGameSystem();
			GameObjectManager::getInstance()->deleteObject(this);
		}
	}
	else if (button->getName() == "button_2") {
		ApplicationManager::getInstance()->resumeApplication();
		GameObjectManager::getInstance()->deleteObject(this);
	}
}


void QuitScreen::markMainMenuQuit()
{
	this->forMainMenu = true;
}

void QuitScreen::markGameQuit()
{
	this->forMainMenu = false;
}