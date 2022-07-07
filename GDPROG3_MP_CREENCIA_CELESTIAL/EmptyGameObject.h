#pragma once
#include "AGameObject.h"
//represents an empty game object. use this to attach components that need to utilize the update() function, but not need to render
//a sprite
class EmptyGameObject : public AGameObject
{
public:
	EmptyGameObject(string name, sf::Vector2f);
	~EmptyGameObject();
	void initialize();
public:
	sf::Vector2f position;
};