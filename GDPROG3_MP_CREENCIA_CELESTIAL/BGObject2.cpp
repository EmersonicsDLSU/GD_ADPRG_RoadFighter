#include "BGObject2.h"
#include "BGObject.h"
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "BGMovement.h"

BGObject2::BGObject2(std::string name) : AGameObject(name) {}

void BGObject2::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//For level 2 texture
	//assign texture
	sf::Sprite* sprite2 = new sf::Sprite();
	sprite2->setTexture(*TextureManager::getInstance()->getTexture("road_2"));
	sf::Vector2u textureSize = sprite2->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	sprite->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 10));
	getTransformable()->setPosition(0, -Game::WINDOW_HEIGHT * 7);

	BGMovement* movement = new BGMovement("BG_Movement2");
	this->attachComponent(movement);

	Renderer* renderer2 = new Renderer("BG2");
	renderer2->assignDrawable(sprite2);
	this->attachComponent(renderer2);

	
}

