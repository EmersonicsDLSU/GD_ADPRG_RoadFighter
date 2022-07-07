#pragma once
#include "APoolable.h"
#include "CollisionListener.h"
class UtilityBullet : public APoolable, public CollisionListener
{
public:
	UtilityBullet(string name);
	void initialize();
	void onRelease();
	void onActivate();
	APoolable* clone();
	sf::Sprite* sprite;
	void applyPhysics(Collider* coll);

public:
	bool isDestroyed();

private:
	int counter = 0;
public:
	bool bulletDestroyed = false;
};