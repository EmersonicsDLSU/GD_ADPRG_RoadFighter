#include "BGMovement.h"
#include "Game.h"
#include "AGameObject.h"
#include "GameSystem.h"
#include "GameObjectManager.h"
#include "Collider.h"
#include "AirplanePlayer.h"
BGMovement::BGMovement(string name) : AComponent(name, Script)
{

}

BGMovement::~BGMovement()
{
	AComponent::~AComponent();
}

void BGMovement::setBGSpeed(float speed)
{
	this->SPEED_MULTIPLIER = speed;
}

float BGMovement::getBGSpeed()
{
	return this->SPEED_MULTIPLIER;
}

void BGMovement::perform()
{
	//access components
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;
	Collider* coll = (Collider*)player->findComponentByName("Airplane_col");
	GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
	//make BG scroll slowly
	if (gs->bgmove == true && coll->isChecked())
	{
		sf::Vector2f offset(0.0f, 0.0f);
		offset.y += SPEED_MULTIPLIER;
		this->getOwner()->getTransformable()->move(offset * deltaTime.asSeconds());


		sf::Vector2f localPos = this->getOwner()->getTransformable()->getPosition();
		if (localPos.y * deltaTime.asSeconds() > 0) {
			//reset position
			this->getOwner()->getTransformable()->setPosition(0, -Game::WINDOW_HEIGHT * 7);
		}
	}
}