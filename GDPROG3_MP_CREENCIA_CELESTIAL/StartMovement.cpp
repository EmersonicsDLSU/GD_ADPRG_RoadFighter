#include "StartMovement.h"
#include "AGameObject.h"
#include <iostream>
#include "GameSystem.h"
#include "GameObjectManager.h"
#include "PlayerInputController.h"
#include "AirplanePlayer.h"
#include "ProgressCarObject.h"

StartMovement::StartMovement(string name) : AComponent(name, Script)
{
}

void StartMovement::perform()
{
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;

	Collider* coll = (Collider*)player->findComponentByName("Airplane_col");

	PlayerInputController* pi = (PlayerInputController*)player->findComponentByName("MyPlayerInput");

	ProgressCarObject* pco = (ProgressCarObject*)this->owner;

	GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");

	if (gs->percentage < 3 && pi->isD())
	{
		this->owner->getTransformable()->move(0, (SPEED * (gs->speedMeter / 224.0f)) * deltaTime.asSeconds());
	}
	else if(gs->percentage < 3 && pi->isF())
	{
		this->owner->getTransformable()->move(0, (SPEED * (gs->speedMeter / 400.0f)) * deltaTime.asSeconds());
	}
	else if (gs->percentage >= 3)
	{
		GameObjectManager::getInstance()->deleteObject(this->owner);
	}


}