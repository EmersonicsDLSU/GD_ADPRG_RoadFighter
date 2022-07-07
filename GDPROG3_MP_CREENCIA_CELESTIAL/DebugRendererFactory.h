#pragma once
#include "Renderer.h"
#include "ARendererFactory.h"
class DebugRendererFactory:
	public ARendererFactory
{
public:

	Renderer* createSprite(string name, string resourceName);
	Renderer* createCircle(string name, float radius);
};

