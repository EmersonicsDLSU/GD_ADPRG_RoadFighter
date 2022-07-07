#include "PlayerInputController.h"
#include "AirplanePlayer.h"
#include "BGObject.h"
#include "BGMovement.h"
#include "GameObjectManager.h"
#include "GameSystem.h"
#include "SFXManager.h"
PlayerInputController::PlayerInputController(string name) : GenericInputController(name)
{

}

PlayerInputController::~PlayerInputController()
{
	GenericInputController::~GenericInputController();
}

void PlayerInputController::perform()
{
	AirplanePlayer* player = (AirplanePlayer*)this->owner;
	if (player == NULL)
		return;
	if (event.type == sf::Event::KeyPressed && player->isCheck) {
		keyFlag = true;
	}
	else if (event.type == sf::Event::KeyReleased) {
		keyFlag = false;
		GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
		gs->bgmove = false;	//turns off the backgroundScrolling
		gs->enemySpeed = 8.0f;
	}
	switch (event.key.code) {
	case sf::Keyboard::D:
		if (!keyFlag)
		{
			GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
			gs->startfuel = false;	//turns off the forward playerMovement
		}
		this->accelerateD = keyFlag;
		break;
	case sf::Keyboard::F:
		if (!keyFlag)
		{
			GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
			gs->startfuel = false;	//turns off the forward playerMovement
		}
		this->accelerateF = keyFlag;
		break;
	case sf::Keyboard::Left:
		this->moveLeft = keyFlag;
		break;
	case sf::Keyboard::Right:
		this->moveRight = keyFlag;
		break;
	case sf::Keyboard::Enter:
		this->pauseGame = keyFlag;
		break;
	}
}

bool PlayerInputController::isD()
{
	return this->accelerateD;
}

bool PlayerInputController::isF()
{
	return this->accelerateF;
}

bool PlayerInputController::isLeft()
{
	return this->moveLeft;
}

bool PlayerInputController::isRight()
{
	return this->moveRight;
}

bool PlayerInputController::isPause()
{
	return this->pauseGame;
}