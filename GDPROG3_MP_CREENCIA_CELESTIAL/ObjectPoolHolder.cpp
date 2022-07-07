
#include "ObjectPoolHolder.h"

string ObjectPoolHolder::ENEMY_POOL1_TAG = "EnemyPool1";
string ObjectPoolHolder::ENEMY_POOL2_TAG = "EnemyPool2";
string ObjectPoolHolder::ENEMY_POOL3_TAG = "EnemyPool3";
string ObjectPoolHolder::ENEMY_POOL4_TAG = "EnemyPool4";

string ObjectPoolHolder::BONUS_POOL1_TAG = "BonusEnemyPool1";
string ObjectPoolHolder::BONUS_POOL2_TAG = "BonusEnemyPool2";
string ObjectPoolHolder::BONUS_POOL3_TAG = "BonusEnemyPool3";
string ObjectPoolHolder::BONUS_POOL4_TAG = "BonusEnemyPool4";

string ObjectPoolHolder::TRUCK_POOL1_TAG = "TruckEnemyPool1";
string ObjectPoolHolder::TRUCK_POOL2_TAG = "TruckEnemyPool2";
string ObjectPoolHolder::TRUCK_POOL3_TAG = "TruckEnemyPool3";
string ObjectPoolHolder::TRUCK_POOL4_TAG = "TruckEnemyPool4";

string ObjectPoolHolder::OIL_POOL1_TAG = "OilEnemyPool1";
string ObjectPoolHolder::OIL_POOL2_TAG = "OilEnemyPool2";
string ObjectPoolHolder::OIL_POOL3_TAG = "OilEnemyPool3";
string ObjectPoolHolder::OIL_POOL4_TAG = "OilEnemyPool4";

string ObjectPoolHolder::BULLET_POOL_TAG = "BulletPool";

ObjectPoolHolder* ObjectPoolHolder::sharedInstance = NULL;

ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new ObjectPoolHolder();
	}

	return sharedInstance;
}

void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
	this->poolMap[pool->getTag()] = pool;
}

void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
	this->poolMap.erase(pool->getTag());
	delete pool;
}

GameObjectPool* ObjectPoolHolder::getPool(string tag)
{
	return this->poolMap[tag];
}