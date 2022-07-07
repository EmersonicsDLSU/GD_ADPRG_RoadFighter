#pragma once
#include "AComponent.h"
class finishBehavior : public AComponent
{

public:
	finishBehavior(string name);
	void perform();


private:
	const float SPEED = 700.0f;
	const float STOP = 0.0f;

};
