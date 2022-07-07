#pragma once
#include "AComponent.h"
//class for simply storing the event data. may be expanded to handle basic controls.
class GenericInputController : public AComponent
{
public:
	GenericInputController(string name);
	~GenericInputController();

	void perform();
	void assignEvent(sf::Event event);

protected:
	sf::Event event;
};


