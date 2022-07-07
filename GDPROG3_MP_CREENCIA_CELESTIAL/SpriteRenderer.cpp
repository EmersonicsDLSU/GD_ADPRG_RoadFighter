#include "SpriteRenderer.h"
#include "TextureManager.h"

SpriteRenderer::SpriteRenderer(string name, string textureName) : Renderer(name) {
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture(textureName));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	//sprite->setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 1, textureSize.x, textureSize.y));
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->assignDrawable(sprite);
	this->mainSprite = sprite;
}
