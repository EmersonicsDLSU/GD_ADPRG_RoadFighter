#include "EmptyGameObject.h"

EmptyGameObject::EmptyGameObject(string name, sf::Vector2f position) : AGameObject(name), position(position)
{

}

EmptyGameObject::~EmptyGameObject()
{
	AGameObject::~AGameObject();
}

void EmptyGameObject::initialize()
{
	this->setPosition(position.x, position.y);
}