#include "finishBehavior.h"
#include "StartMovement.h"
#include "AGameObject.h"
#include <iostream>
#include "GameSystem.h"
#include "GameObjectManager.h"
#include "PlayerInputController.h"
#include "AirplanePlayer.h"
#include "ProgressCarObject.h"
#include "finishObject.h"
#include "Game.h"

finishBehavior::finishBehavior(string name) : AComponent(name, Script)
{
}

void finishBehavior::perform()
{
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;

	Collider* coll = (Collider*)player->findComponentByName("Airplane_col");

	PlayerInputController* pi = (PlayerInputController*)player->findComponentByName("MyPlayerInput");

	finishObject* finish = (finishObject*)this->owner;

	GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
	
	if (gs->percentage < 97)
	{
		return;
	}
	else if (gs->percentage <= 101 && gs->percentage >= 97 )
	{
		cout << finish->getTransformable()->getPosition().x << ":" << finish->getTransformable()->getPosition().y << endl;
		if ( pi->isD())
		{
			this->owner->getTransformable()->move(0, (SPEED * (gs->speedMeter / 224.0f)) * deltaTime.asSeconds());
		}
		else if ( pi->isF())
		{
			this->owner->getTransformable()->move(0, (SPEED * (gs->speedMeter / 400.0f)) * deltaTime.asSeconds());
		}
	
	}

	finishObject* finishobject = (finishObject*)GameObjectManager::getInstance()->findObjectByName("finishObjectsprite");
	//display finish line
	if ( gs->percentage == 97)
	{
		
		finishobject->getTransformable()->setPosition(Game::WINDOW_WIDTH /2 + 32, 0);
	}
	

}