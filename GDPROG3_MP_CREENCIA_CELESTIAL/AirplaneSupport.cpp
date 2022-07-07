#include "AirplaneSupport.h"
#include "TextureManager.h"
#include "AirplaneSupportMovement.h"
#include "Renderer.h"

AirplaneSupport::AirplaneSupport(std::string name) :AGameObject(name)
{
}

void AirplaneSupport::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("raptor"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setPosition(0, 0);

	//assign components
	AirplaneSupportMovement* logicComponent = new AirplaneSupportMovement("AirplaneSupportMovement_1");
	this->attachComponent(logicComponent);

	Renderer* renderer = new Renderer("SupportSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

}
