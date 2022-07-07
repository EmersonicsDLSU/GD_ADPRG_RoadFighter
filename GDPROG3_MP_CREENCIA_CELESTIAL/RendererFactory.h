#pragma once
#include "ARendererFactory.h"
class RendererFactory :
    public ARendererFactory
{
public:
	Renderer* createSprite(string name, string resourceName);
	Renderer* createCircle(string name, float radius);
};

