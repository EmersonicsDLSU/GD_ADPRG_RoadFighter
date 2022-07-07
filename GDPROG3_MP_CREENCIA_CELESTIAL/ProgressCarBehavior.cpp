#include "ProgressCarBehavior.h"
#include "AGameObject.h"
#include <iostream>
#include "GameSystem.h"
#include "GameObjectManager.h"
#include "PlayerInputController.h"
#include "AirplanePlayer.h"
#include "ProgressCarObject.h"

ProgressCarBehavior::ProgressCarBehavior(string name) : AComponent(name, Script)
{
}

void ProgressCarBehavior::perform()
{
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;

	Collider* coll = (Collider*)player->findComponentByName("Airplane_col");

	PlayerInputController* pi = (PlayerInputController*)player->findComponentByName("MyPlayerInput");

	ProgressCarObject* pco = (ProgressCarObject*)this->owner;

	GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");

	if (gs->startfuel == true && coll->isChecked() && gs->percentage < 100)
	{
		if (pi->isD())
		{
			pco->getTransformable()->move(0, -(SPEED * (gs->speedMeter / 224.0f)) * deltaTime.asSeconds());
		}
		if (pi->isF())
		{
			pco->getTransformable()->move(0, -(SPEED * (gs->speedMeter / 400.0f)) * deltaTime.asSeconds());
		}
	}
	else if (gs->percentage >= 100 || gs->fuel <= 0 || !gs->startfuel || !coll->isChecked())
	{
		pco->getTransformable()->move(0, 0);
	}

	
}