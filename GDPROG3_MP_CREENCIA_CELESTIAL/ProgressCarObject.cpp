
#include "TextureManager.h"
#include "ProgressCarBehavior.h"
#include "Renderer.h"
#include "ProgressCarObject.h"

ProgressCarObject::ProgressCarObject(std::string name) :AGameObject(name)
{
}

void ProgressCarObject::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("cars_sprite"));
	//JSON BELOW
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	int maxRow = (textureSize.y / TextureManager::getInstance()->parse1.getSheet("frames")["car1.png"]["sourceSize"]["h"].GetInt());
	int maxCol = (textureSize.x / TextureManager::getInstance()->parse1.getSheet("frames")["car1.png"]["sourceSize"]["w"].GetInt());
	textureSize.x /= maxCol;
	textureSize.y /= maxRow;
	sprite->setTextureRect(sf::IntRect(
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[5].c_str()]["frame"]["x"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[5].c_str()]["frame"]["y"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[5].c_str()]["frame"]["w"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[5].c_str()]["frame"]["h"].GetInt()
	));
	// JSON ABOVE
	//change size
	sprite->setScale(sprite->getScale().x * 0.5f, sprite->getScale().y * 0.5f);
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setPosition(0, 0);

	//assign components
	ProgressCarBehavior* movement = new ProgressCarBehavior("ProgressCarMovement_1");
	this->attachComponent(movement);

	Renderer* renderer = new Renderer("progressSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

}
