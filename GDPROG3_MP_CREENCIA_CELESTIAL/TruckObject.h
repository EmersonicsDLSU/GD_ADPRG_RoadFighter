#pragma once
#include "APoolable.h"
#include "CollisionListener.h"
class TruckObject : public APoolable, public CollisionListener
{
public:
	TruckObject(string name, sf::Vector2f position, std::string laneType, std::string emptyGOtype);
	void initialize();
	void onRelease();
	void onActivate();
	APoolable* clone();
	void applyPhysics(Collider* collider);
	sf::Sprite* sprite;
	static bool once;
	std::string laneType;
	std::string emptyGOtype;

private:
	int counter = 0;
	static int recentKillCount;
	sf::Vector2f position;
};
