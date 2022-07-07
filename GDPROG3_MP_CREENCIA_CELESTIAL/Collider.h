#pragma once
#include "AComponent.h"
#include "CollisionListener.h"
#include "AGameObject.h"
class Collider : public AComponent {

public:
	enum colliderType {Player, Enemy, Utility};

	Collider(string name, sf::Sprite* sprite, colliderType collType);	//check

	void setCollisionListener(CollisionListener* listener);	//check

	void setChecked(bool flag);	//check
	bool isChecked();	//check

	void setOvertake(bool flag);	//check
	bool getOvertake();	//check

	bool willCollide(Collider* another);	//check
	void willOverTake(Collider* another);
	bool alreadyCollided();	//check
	void setAlreadyCollided(bool flag);	//check

	sf::FloatRect getGlobalBounds();	//check
	void setLocalBounds(sf::FloatRect localBounds);	//check
	void collisionEnter(AGameObject* gameObjects, colliderType type, Collider* coll);	
	void collisionExit(AGameObject* gameObjects);	
	colliderType collType;

	void perform();

private:
	const float SPEEDSKID = 100.0f;
	bool collided = false;
	bool checked = true;
	bool overtake = false;
	sf::Sprite* sprite;
	sf::FloatRect localBounds;
	CollisionListener* listener;

public:
	bool hitWall = false;

private:
	float playerPosX = 0.0f;
	float enemyPosX = 0.0f;
};