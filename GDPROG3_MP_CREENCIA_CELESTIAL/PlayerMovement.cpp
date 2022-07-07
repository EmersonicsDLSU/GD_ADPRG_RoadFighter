#include "PlayerMovement.h"
#include "AGameObject.h"
#include "PlayerInputController.h"
#include <iostream>
#include "QuitScreen.h"
#include "GameObjectManager.h"
#include "BGMovement.h"
#include "BGObject.h"
#include "BGObject2.h"
#include "BGObject3.h"
#include "GameSystem.h"]
#include "SamplePopupScreen.h"
#include "ApplicationManager.h"
#include "AirplanePlayer.h"
#include "SFXManager.h"

PlayerMovement::PlayerMovement(string name) : AComponent(name, Script)
{

}

PlayerMovement::~PlayerMovement()
{
	AComponent::~AComponent();
}

void PlayerMovement::perform()
{
	PlayerInputController* inputController = (PlayerInputController*)this->getOwner()->getComponentsOfType(ComponentType::Input)[0];
	sf::Transformable* playerTransformable = this->getOwner()->getTransformable();
	Collider* coll = (Collider*)this->owner->findComponentByName("Airplane_col");

	
	if (playerTransformable == NULL || inputController == NULL) {
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	sf::Vector2f offset(0.0f, 0.0f);
	
	//for minAcceleration
	if (inputController->isD() && coll->isChecked()) {
		//tweak gameSystem; moving bg and fuel start
		GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
		gs->bgmove = true;
		gs->startfuel = true;
		gs->speedMeter += LOW_ACCE_SPEED; //sets the lowest accelerationSpeed
		gs->bgSpeed = BG_LOW_SPEED * (gs->speedMeter / 224.0f); //sets the maxSpeed for the BG
		gs->enemySpeed = 8.0f * (gs->speedMeter / 224.0f); //sets the speed for the enemies
		gs->kmTaken += 1 * (gs->speedMeter / 224.0f); //km covered by the MC
		Dpress = true;
		//physics accelaration
		if (inputController->isRight()) {
			offset.x += this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
		else if (inputController->isLeft()) {
			offset.x -= this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
	}
	//for maxAcceleration
	else if (inputController->isF() && coll->isChecked()) {
		//tweak gameSystem; moving bg and fuel start
		GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
		gs->bgmove = true;
		gs->startfuel = true;
		gs->speedMeter += HIGH_ACCE_SPEED; //sets the highest accelerationSpeed
		gs->bgSpeed = BG_HIGH_SPEED * (gs->speedMeter / 400.0f); //sets the maxSpeed for the BG
		gs->enemySpeed = 12.0f * (gs->speedMeter / 400.0f); //sets the speed for the enemies
		gs->kmTaken += 2 * (gs->speedMeter / 400.0f); //km covered by the MC
		Fpress = true;
		//physics accelaration
		if (inputController->isRight()) {
			offset.x += this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
		else if (inputController->isLeft()) {
			offset.x -= this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
	}

	if (inputController->isRight() && coll->isChecked()) {
		offset.x += this->SPEED_MULTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (inputController->isLeft() && coll->isChecked()) {
		offset.x -= this->SPEED_MULTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (inputController->isPause()) {
		QuitScreen* quitScreen = new QuitScreen("quitScreen");
		quitScreen->markGameQuit();
		GameObjectManager::getInstance()->addObject(quitScreen);
	}


	//railings; checks if the MC hits the railings
	float posX = this->owner->getTransformable()->getPosition().x;
	float posY = this->owner->getTransformable()->getPosition().y;
	if (posX <= leftRail.x)
	{
		AirplanePlayer* car = (AirplanePlayer*)this->owner;
		if (car == NULL)
			return;
		//car->isDestroyed = true;
		coll->hitWall = true;
		coll->setChecked(false);
		car->isCheck = false;
		SFXManager::getInstance()->pauseSound("Car"); // stop the car audio
		GameSystem* gsz = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
		gsz->fuel -= 5;
	}
	else if (posX >= rightRail.x)
	{
		AirplanePlayer* car = (AirplanePlayer*)this->owner;
		if (car == NULL)
			return;
		//car->isDestroyed = true;
		coll->hitWall = true;
		coll->setChecked(false);
		car->isCheck = false;
		SFXManager::getInstance()->pauseSound("Car"); // stop the car audio
		GameSystem* gsz = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
		gsz->fuel -= 5;
	}


	//Start Fuel
	/*if (startfuel == true)
	{
		
		fuel -= deltaTime.asSeconds()*2;
		cout << fuel << endl;

		if (fuel <= 0)
		{
			startfuel == false;
			SamplePopupScreen* popScreen = new SamplePopupScreen("samplePopupScreen");
			GameObjectManager::getInstance()->addObject(popScreen);
			ApplicationManager::getInstance()->pauseApplication();
			fuel = 100.0f;
		}
	}*/
}