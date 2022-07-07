#pragma once
#include "AComponent.h"
class ProgressCarBehavior : public AComponent
{

public:
	ProgressCarBehavior(string name);
	void perform();
	bool moveprogress = false;
	bool stopprogress = false;

private:
	const float SPEED = 16.0f;
	const float STOP = 0.0f;

};
