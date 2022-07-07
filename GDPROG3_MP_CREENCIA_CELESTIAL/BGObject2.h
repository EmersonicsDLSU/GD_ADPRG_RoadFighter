#pragma once
#include "AGameObject.h"
class BGObject2 : public AGameObject
{
public:
	BGObject2(std::string name);
	void initialize();
private:
	const float SPEED_MULTIPLIER = 100.0f;
};

