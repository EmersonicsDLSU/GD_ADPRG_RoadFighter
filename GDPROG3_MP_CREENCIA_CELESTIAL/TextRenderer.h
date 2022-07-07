#pragma once
#include "Renderer.h"
class TextRenderer :
	public Renderer
{
public:
	TextRenderer(sf::Text* text, std::string name, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness, 
		float size, std::string defaultText);
	static TextRenderer* CreateText(sf::Text* textDrawable, std::string name, const sf::Color& fillColor, const sf::Color& outlineColor,
		float outlineThickness, float size, std::string defaultText);
};

