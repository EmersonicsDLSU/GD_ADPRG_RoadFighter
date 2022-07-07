#pragma once

#include "Renderer.h"

class ARendererFactory
{
public:
	virtual Renderer* createSprite(string name, string resourceName) = 0;
	virtual Renderer* createCircle(string name, float radius) = 0;
};

