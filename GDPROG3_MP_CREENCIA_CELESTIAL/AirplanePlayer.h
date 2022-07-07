
#pragma once
#include "AGameObject.h"
#include "CollisionListener.h"
#include "Collider.h"
#include <iostream>

using namespace std;

class AirplanePlayer : public AGameObject, public CollisionListener
{
public:
	AirplanePlayer(string name);
	void initialize();
	sf::Sprite* sprite;
	void applyPhysics(Collider* coll);

public:
	int life = 3;
	int killCount = 0;

public:
	float inviDuration = 1.5f;
	float blinkDuration = 0.2f;
	bool isCheck = true;

public:
	bool isDestroyed = false;

private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

};

