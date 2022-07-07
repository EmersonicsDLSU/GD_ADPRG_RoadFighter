#pragma once
#include "AGameObject.h"
class BGObject3 : public AGameObject
{
public:
	BGObject3(std::string name);
	void initialize();
private:
	const float SPEED_MULTIPLIER = 100.0f;
};


