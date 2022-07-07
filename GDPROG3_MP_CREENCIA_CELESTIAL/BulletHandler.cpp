#include "BulletHandler.h"
#include "AirplanePlayer.h"
#include "PlayerInputController.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "UtilityBullet.h"

BulletHandler::BulletHandler(int numBullets, string name) : AComponent(name, Script)
{
	//suspicious owner
	GameObjectPool* bulletPool = new GameObjectPool(ObjectPoolHolder::BULLET_POOL_TAG, new UtilityBullet("bullet"), numBullets, this->getOwner());
	bulletPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(bulletPool);
}

BulletHandler::~BulletHandler()
{

}

void BulletHandler::perform()
{
	/*AirplanePlayer* player = (AirplanePlayer*)this->owner;
	PlayerInputController* controller = (PlayerInputController*)player->findComponentByName("MyPlayerInput");
	if (controller->isFireProject())
	{
		GameObjectPool* bulletPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BULLET_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			bulletPool->requestPoolable();
		}
	}
	else
	{
		this->ticks = 0.0f;
	}*/
}

