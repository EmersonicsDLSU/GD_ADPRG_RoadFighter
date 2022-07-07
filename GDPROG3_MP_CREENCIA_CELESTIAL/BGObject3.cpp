#include "BGObject3.h"
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "BGMovement.h"

BGObject3::BGObject3(std::string name) : AGameObject(name) {}

void BGObject3::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";


	//For level 3 texture
	//assign texture
	sf::Sprite* sprite3 = new sf::Sprite();
	sprite3->setTexture(*TextureManager::getInstance()->getTexture("road_3"));
	sf::Vector2u textureSize = sprite3->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	sprite3->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 10));
	getTransformable()->setPosition(0, -Game::WINDOW_HEIGHT * 7);

	BGMovement* movement = new BGMovement("BG_Movement");
	this->attachComponent(movement);

	Renderer* renderer3 = new Renderer("BG3");
	renderer3->assignDrawable(sprite3);
	this->attachComponent(renderer3);
}