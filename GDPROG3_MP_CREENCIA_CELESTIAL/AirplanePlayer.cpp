#include "AirplanePlayer.h"
#include <iostream>
#include "Game.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "GameObjectManager.h"
#include "ObjectPoolHolder.h"
#include "SamplePopupScreen.h"
#include "HUDScreen.h"
#include "GameSystem.h"
#include "ApplicationManager.h"

AirplanePlayer::AirplanePlayer(string name) : AGameObject(name), CollisionListener(){

}

void AirplanePlayer::initialize() {
	std::cout << "Declared as " << this->getName() << "\n";

    this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT - 150);

    PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
    this->attachComponent(inputController);

    PlayerMovement* movement = new PlayerMovement("MyMovement");
    this->attachComponent(movement);

    // Renderer* renderer = Renderer::Create("AirplanePlayerRenderer", "eagle", RendererType::Sprite);
    ARendererFactory* factory = new RendererFactory();
    Renderer* renderer = factory->createSprite("AirplanePlayerRenderer", "car2");
    //change size
    renderer->mainSprite->setScale(renderer->mainSprite->getScale().x * 0.6f, renderer->mainSprite->getScale().y * 0.6f);

    this->attachComponent(renderer);
    this->sprite = renderer->mainSprite;

    Collider* coll = new Collider("Airplane_col", renderer->mainSprite, Collider::Player);
    this->attachComponent(coll);
    PhysicsManager::getInstance()->trackObject(coll);
	coll->setCollisionListener(this);
}


void AirplanePlayer::applyPhysics(Collider* coll)
{
    if (coll->getOwner() == NULL)
        return;

    PlayerInputController* pc = (PlayerInputController*)this->findComponentByName("MyPlayerInput");
    pc->keyFlag = false;
    /*
    HUDScreen* hud = (HUDScreen*)GameObjectManager::getInstance()->findObjectByName("HUDScreen");

    std::string lifeCountText = "Lives: ";
    lifeCountText.append(std::to_string(--this->life));
    hud->lifeCount_Text->setText(lifeCountText);
    */

    //recentKillCount = this->killCount;
    
    //PopUp
    if (this->life <= 0 || isDestroyed)
    {
        GameObjectManager::getInstance()->deleteObject(coll->getOwner());
        SamplePopupScreen* popScreen = new SamplePopupScreen("samplePopupScreen", "gameOver");
        GameObjectManager::getInstance()->addObject(popScreen);
        PlayerInputController* inputController = (PlayerInputController*)this->findComponentByName("MyPlayerInput");
        ApplicationManager::getInstance()->pauseApplication();
    }
}