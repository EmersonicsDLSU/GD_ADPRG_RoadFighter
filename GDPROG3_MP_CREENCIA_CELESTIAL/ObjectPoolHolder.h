#pragma once
#include "GameObjectPool.h"
#include <unordered_map>

typedef std::unordered_map<string, GameObjectPool*> PoolMap;

//class that holds N object pools for easier retrieval
class ObjectPoolHolder
{
public:
	//pool names
	static string ENEMY_POOL1_TAG;
	static string ENEMY_POOL2_TAG;
	static string ENEMY_POOL3_TAG;
	static string ENEMY_POOL4_TAG;
	static string BULLET_POOL_TAG;
	static string BONUS_POOL1_TAG;
	static string BONUS_POOL2_TAG;
	static string BONUS_POOL3_TAG;
	static string BONUS_POOL4_TAG;
	static string TRUCK_POOL1_TAG;
	static string TRUCK_POOL2_TAG;
	static string TRUCK_POOL3_TAG;
	static string TRUCK_POOL4_TAG;
	static string OIL_POOL1_TAG;
	static string OIL_POOL2_TAG;
	static string OIL_POOL3_TAG;
	static string OIL_POOL4_TAG;

	static ObjectPoolHolder* getInstance();

	void registerObjectPool(GameObjectPool* pool);
	void unregisterObjectPool(GameObjectPool* pool);
	GameObjectPool* getPool(string tag);

private:
	ObjectPoolHolder() {};
	ObjectPoolHolder(ObjectPoolHolder const&) {};             // copy constructor is private
	ObjectPoolHolder& operator=(ObjectPoolHolder const&) {};  // assignment operator is private
	static ObjectPoolHolder* sharedInstance;

	PoolMap poolMap;


};
