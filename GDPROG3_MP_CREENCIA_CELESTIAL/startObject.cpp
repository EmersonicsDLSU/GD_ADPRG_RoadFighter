#include "startObject.h"
#include "finishObject.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "StartMovement.h"


startObject::startObject(std::string name) :AGameObject(name)
{
}

void startObject::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("start"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setPosition(0, 0);


	//assign components
	StartMovement* movementstart = new StartMovement("StartMovement_1");
	this->attachComponent(movementstart);

	Renderer* renderer = new Renderer("startSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

}


