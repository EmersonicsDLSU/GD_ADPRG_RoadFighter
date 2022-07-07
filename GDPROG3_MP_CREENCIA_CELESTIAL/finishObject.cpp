#include "finishObject.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "AScene.h"
#include "finishBehavior.h"
#include "Collider.h"
#include "PhysicsManager.h"

finishObject::finishObject(std::string name) :AGameObject(name)
{
}

void finishObject::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("finish"));
	sprite->setScale(sprite->getScale().x * 1.28f, sprite->getScale().y * 2.0f);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	//assign components
	finishBehavior* movementfinish = new finishBehavior("finishMovement_1");
	this->attachComponent(movementfinish);
	
	Renderer* renderer = new Renderer("finishSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

}

