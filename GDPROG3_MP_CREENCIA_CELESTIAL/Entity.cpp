#include "Entity.h"
#include "TextureManager.h"

Entity::Entity() {};

void Entity::setTexture(sf::Texture texture) {
	mTexture = texture;
	mSprite.setTexture(mTexture);
}

sf::Sprite* Entity::getSprite(){
	return &mSprite;
}

void Entity::update() {
	if (clock.getElapsedTime().asMilliseconds() > 100) {
		
		sf::Texture* texture;
		std::string key = rootTexName + std::to_string(ctr);
		texture = TextureManager::getInstance()->getTexture(key);
		setTexture(*texture);

		ctr++;
		ctr %= frames;
		clock.restart();
	}
}