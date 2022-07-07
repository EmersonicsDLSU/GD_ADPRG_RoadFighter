#pragma once
#include "APoolable.h"
#include "CollisionListener.h"
class EnemyAirplane : public APoolable, public CollisionListener
{
public:
	EnemyAirplane(string name, sf::Vector2f position, std::string laneType, std::string emptyGOtype);
	void initialize();
	void onRelease();
	void onActivate();
	APoolable* clone();
	void applyPhysics(Collider* coll);
	sf::Sprite* sprite;
	static bool once;
	std::string laneType;
	std::string emptyGOtype;

private:
	int counter = 0;
	static int recentKillCount;
	sf::Vector2f position;
};