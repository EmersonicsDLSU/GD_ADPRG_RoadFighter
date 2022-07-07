#include "ProgressBar.h"
#include"AGameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "ARendererFactory.h"
#include "RendererFactory.h"

ProgressBar::ProgressBar(string name) : AGameObject(name) {

}

void ProgressBar::initialize() {
    std::cout << "Declared as " << this->getName() << "\n";

    this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT - 150);

    // Renderer* renderer = Renderer::Create("AirplanePlayerRenderer", "eagle", RendererType::Sprite);
    ARendererFactory* factory = new RendererFactory();
    Renderer* renderer = factory->createSprite("ProgressBarRenderer", "progressbar");
    //change size
   renderer->mainSprite->setScale(renderer->mainSprite->getScale().x * 0.7f, renderer->mainSprite->getScale().y * 1.0f);

    this->attachComponent(renderer);
    this->sprite = renderer->mainSprite;
}