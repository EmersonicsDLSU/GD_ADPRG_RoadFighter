#include "UIButton.h"
#include "TextureManager.h"
#include <iostream>
#include "Renderer.h"
#include "UIButtonInputController.h"


UIButton::UIButton(string name, sf::Texture* normalTexture, sf::Texture* pressedTexture) : AGameObject(name)
{
	this->normalTexture = normalTexture;
	this->pressedTexture = pressedTexture;
}

UIButton::~UIButton()
{
	AGameObject::~AGameObject();
}

void UIButton::initialize()
{
	sprite = new sf::Sprite();
	sprite->setTexture(*this->normalTexture);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("Button");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);
}

void UIButton::setButtonListener(ButtonListener* listener)
{
	//assign input controller
	this->listener = listener;
	UIButtonInputController* inputController = new UIButtonInputController("UI_InputController", this->listener);
	this->attachComponent(inputController);
}

void UIButton::changeButtonToNormal()
{
	this->sprite->setTexture(*this->normalTexture);

}

void UIButton::changeButtonToPressed()
{
	this->sprite->setTexture(*this->pressedTexture);
}

sf::FloatRect UIButton::getLocalBounds() {
	return this->sprite->getLocalBounds();
}

sf::FloatRect UIButton::getGlobalBounds() {
	sf::FloatRect bounds = this->sprite->getGlobalBounds();
	bounds = this->getGlobalTransform().transformRect(bounds);
	return bounds;

}