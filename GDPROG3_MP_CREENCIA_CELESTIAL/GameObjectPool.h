#pragma once
#include "APoolable.h"
#include <vector>
#include <queue>

typedef std::vector<APoolable*> ObjectList;

class GameObjectPool
{
public:
	GameObjectPool(string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent);
	~GameObjectPool();
	void initialize();
	bool hasObjectAvailable(int requestSize);
	APoolable* requestPoolable();
	ObjectList requestPoolableBatch(int size);

	void releasePoolable(APoolable* poolableObject);
	void releasePoolableBatch(ObjectList objectList);

	void addObject();

	string getTag();

	int usedSize();
	int availableSize();
	void deletePoolable(APoolable* poolableObject);


private:
	string tag;
	APoolable* objectCopy = NULL;
	AGameObject* parent = NULL;
	int maxPoolSize = 20; //default;
public:
	ObjectList availableObjects;
	ObjectList usedObjects;

	void setEnabled(APoolable* poolableObject, bool flag);
};

