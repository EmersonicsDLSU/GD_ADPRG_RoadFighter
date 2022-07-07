#include "HUDScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "UIText.h"
#include "QuitScreen.h"
#include "GameObjectManager.h"
#include "Renderer.h"
#include "AirplanePlayer.h"
#include "GameSystem.h"

HUDScreen::HUDScreen(string name) : AGameObject(name), ButtonListener()
{

}

HUDScreen::~HUDScreen()
{
	AGameObject::~AGameObject();
}

void HUDScreen::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("hud_bg"));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(Game::WINDOW_WIDTH - 240, Game::WINDOW_HEIGHT - 50);

	Renderer* renderer = new Renderer("HUDScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");
	UIButton* quitBtn = new UIButton("quitBtn", btnNormal, btnPressed);
	this->attachChild(quitBtn);
	quitBtn->setPosition(170, 0);
	quitBtn->getTransformable()->setScale(0.15f, 0.15f);
	quitBtn->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	//do not make as a button child. difficult to position
	quitBtn->attachChild(button_1Text);
	button_1Text->setPosition(0, 0);
	button_1Text->setSize(120);
	button_1Text->setText("QUIT");

	/*GameSystem* game= (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
	cout << game->percentage << endl;
	if (game->start == true)
	{
		UIText* startText = new UIText("text_2");
		quitBtn->attachChild(startText);
		startText->setPosition(-500, 0);
		startText->setSize(120);
		startText->setText("Start");
	}


	if (game->finish == true)
	{
		UIText* finishText = new UIText("text_6");
		quitBtn->attachChild(finishText);
		finishText->setPosition(0, 0);
		finishText->setSize(120);
		finishText->setText("FINISH");

	}*/


	/*killCount_Text = new UIText("text_2");
	this->attachChild(killCount_Text);
	killCount_Text->setPosition(0, 0);
	killCount_Text->setSize(20);
	killCountText = "Kill Count: 0";
	killCount_Text->setText(killCountText);*/

	/*lifeCount_Text = new UIText("text_3");
	this->attachChild(lifeCount_Text);
	lifeCount_Text->setPosition(-650, -25);
	lifeCount_Text->setSize(50);
	lifeCountText = "Lives : 3";
	lifeCount_Text->setText(lifeCountText);*/

	fuelCount_Text = new UIText("text_3");
	this->attachChild(fuelCount_Text);
	fuelCount_Text->setPosition(120, -100 );
	fuelCount_Text->setSize(30);
	fuelCountText = "Fuel : 100";
	fuelCount_Text->setText(fuelCountText);

	scoreCount_Text = new UIText("text_4");
	this->attachChild(scoreCount_Text);
	scoreCount_Text->setPosition(120,-150);
	scoreCount_Text->setSize(25);
	scoreCountText = "Score : 0";
	scoreCount_Text->setText(scoreCountText);

	speedCount_Text = new UIText("text_5");
	this->attachChild(speedCount_Text);
	speedCount_Text->setPosition(120, -200);
	speedCount_Text->setSize(15);
	speedCountText = "Speed(Km/H) : 0";
	speedCount_Text->setText(speedCountText);


}

void HUDScreen::onButtonClick(UIButton* button)
{
}

void HUDScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "quitBtn") {

		QuitScreen* quitScreen = new QuitScreen("quitScreen");
		quitScreen->markGameQuit();
		GameObjectManager::getInstance()->addObject(quitScreen);
	}
}