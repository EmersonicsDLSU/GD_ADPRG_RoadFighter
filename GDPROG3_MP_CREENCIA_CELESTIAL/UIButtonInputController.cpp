#include "UIButtonInputController.h"
#include <iostream>

UIButtonInputController::UIButtonInputController(string name, ButtonListener* buttonListener) : GenericInputController(name)
{
	this->buttonListener = buttonListener;
}

UIButtonInputController::~UIButtonInputController()
{
	AComponent::~AComponent();
}

void UIButtonInputController::perform() {

	UIButton* button = (UIButton*)this->getOwner();
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && this->pressed) {
		this->pressed = false;
		button->changeButtonToNormal();
		this->buttonListener->onButtonReleased(button);
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		//check if button is within mouse coord
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::FloatRect bounds = button->getGlobalBounds();

		//std::cout << "Mouse X: " << mousePos.x << " Y: " << mousePos.y << "\n";
		//std::cout << "Bounds X: " << bounds.left << " Y: " << bounds.top << "\n";

		if (bounds.contains(mousePos)) {
			this->pressed = true;
			button->changeButtonToPressed();
			this->buttonListener->onButtonClick(button);
		}
	}


}