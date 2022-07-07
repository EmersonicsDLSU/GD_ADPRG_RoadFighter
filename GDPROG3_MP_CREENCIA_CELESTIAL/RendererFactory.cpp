
#include "RendererFactory.h"
#include "SpriteRenderer.h"

Renderer* RendererFactory::createSprite(string name, string resourceName) {
	return SpriteRenderer::CreateSprite(name, resourceName);
}

Renderer* RendererFactory::createCircle(string name, float radius) {
	Renderer* renderer = new Renderer(name);
	sf::CircleShape* drawable = new sf::CircleShape(radius);
	drawable->setOrigin(radius, radius);
	renderer->assignDrawable(drawable);
	return renderer;
}