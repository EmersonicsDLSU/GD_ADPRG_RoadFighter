#include "BGObject.h"
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "BGMovement.h"

BGObject::BGObject(std::string name, std::string bgName) : AGameObject(name), bgName(bgName) {}

void BGObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture(bgName));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	sprite->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 10));
	getTransformable()->setPosition(0, -Game::WINDOW_HEIGHT * 7);

	BGMovement* movement = new BGMovement("BG_Movement");
	this->attachComponent(movement);

	Renderer* renderer = new Renderer("BG");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	/*//For level 2 texture
	//assign texture
	sf::Sprite* sprite2 = new sf::Sprite();
	sprite2->setTexture(*TextureManager::getInstance()->getTexture("road_2"));
	sf::Vector2u textureSize = sprite2->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	sprite->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 10));
	getTransformable()->setPosition(0, -Game::WINDOW_HEIGHT * 7);

	BGMovement* movement2 = new BGMovement("BG_Movement2");
	this->attachComponent(movement2);

	Renderer* renderer2 = new Renderer("BG2");
	renderer->assignDrawable(sprite2);
	this->attachComponent(renderer);

	//For level 3 texture
	//assign texture
	sf::Sprite* sprite3 = new sf::Sprite();
	sprite3->setTexture(*TextureManager::getInstance()->getTexture("road_3"));
	sf::Vector2u textureSize = sprite3->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	sprite3->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 10));
	getTransformable()->setPosition(0, -Game::WINDOW_HEIGHT * 7);

	BGMovement* movement3 = new BGMovement("BG_Movement3");
	this->attachComponent(movement3);

	Renderer* renderer3 = new Renderer("BG3");
	renderer->assignDrawable(sprite2);
	this->attachComponent(renderer);*/
}

