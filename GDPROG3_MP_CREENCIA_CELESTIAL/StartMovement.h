#pragma once
#include "AComponent.h"
class StartMovement : public AComponent
{

public:
	StartMovement(string name);
	void perform();
	

private:
	const float SPEED = 600.0f;
	const float STOP = 0.0f;

};
