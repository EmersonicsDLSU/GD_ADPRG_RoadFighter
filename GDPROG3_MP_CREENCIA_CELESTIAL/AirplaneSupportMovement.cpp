#include "AirplaneSupportMovement.h"
#include "AGameObject.h"
#include <iostream>

AirplaneSupportMovement::AirplaneSupportMovement(string name) : AComponent(name, Script)
{
}

void AirplaneSupportMovement::perform()
{
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	if (moveLeft) {
		transformable->move(-this->SPEED * deltaTime.asSeconds(), 0);
	}
	else if (moveRight) {
		transformable->move(this->SPEED * deltaTime.asSeconds(), 0);
	}
	int x = transformable->getPosition().x;
	if (x >= 50) {
		this->moveLeft = true;
		this->moveRight = false;
	}
	if (x <= -50) {
		this->moveLeft = false;
		this->moveRight = true;
	}
}