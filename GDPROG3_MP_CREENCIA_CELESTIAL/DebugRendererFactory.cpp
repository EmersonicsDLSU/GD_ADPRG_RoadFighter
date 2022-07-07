#include "DebugRendererFactory.h"
#include "SpriteRenderer.h"
Renderer* DebugRendererFactory::createSprite(string name, string resourceName) {
	Renderer* renderer = new Renderer(name);
	sf::CircleShape* drawable = new sf::CircleShape(20.0);
	drawable->setFillColor(sf::Color::Red);
	drawable->setOrigin(20.0, 20.0);
	renderer->assignDrawable(drawable);
	return renderer;
}
Renderer* DebugRendererFactory::createCircle(string name, float radius) {
	Renderer* renderer = new Renderer(name);
	sf::CircleShape* drawable = new sf::CircleShape(radius);
	drawable->setOrigin(radius, radius);
	renderer->assignDrawable(drawable);
	return renderer;
}
