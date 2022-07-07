#include "Collider.h"
#include "Renderer.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include "AirplanePlayer.h"
#include "EnemyAirplane.h"
#include "UtilityBullet.h"
#include "GameObjectManager.h"
#include "ObjectPoolHolder.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "CollisionListener.h"
#include "GameSystem.h"
#include "GameObjectManager.h"
#include <iostream>
#include "HUDScreen.h"
#include"SFXManager.h"
#include"Game.h"
#include "PlayerInputController.h"

Collider::Collider(string name, sf::Sprite* sprite, colliderType collType) : AComponent(name, Script), sprite(sprite), collType(collType)
{
	/*GameObjectPool* enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_POOL_TAG, new EnemyAirplane("enemy"), numEnemies, NULL);
	enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);*/
}

void Collider::setCollisionListener(CollisionListener* listener)
{
	this->listener = listener;
	
	/*PhysicsController* pc = new PhysicsController("Physics_Controller", this->listener);
	this->attachComponent(pc);*/
	
}

void Collider::setChecked(bool flag)
{
	this->checked = flag;
}

bool Collider::isChecked()
{
	return this->checked;
}

void Collider::setOvertake(bool flag)
{
	this->overtake = flag;
}

bool Collider::getOvertake()
{
	return this->overtake;
}

bool Collider::willCollide(Collider* another)
{
	if (this->getGlobalBounds().intersects(another->getGlobalBounds()) && (isChecked() && another->isChecked()))
	{
		SFXManager::getInstance()->playSound("Collide");
		SFXManager::getInstance()->soundVolume("Collide", 5);
		cout << "Collide" << endl;

		this->playerPosX = this->getOwner()->getTransformable()->getPosition().x;
		this->enemyPosX = another->getOwner()->getTransformable()->getPosition().x;

		return true;
	}
	return false;
}

void Collider::willOverTake(Collider* another)
{
	float playerPosY = this->getOwner()->getTransformable()->getPosition().y + this->getOwner()->getTransformable()->getScale().y / 2;
	float enemyPosY = another->getOwner()->getTransformable()->getPosition().y - this->getOwner()->getTransformable()->getScale().y / 2;

	if ((playerPosY <= enemyPosY) && (isChecked() && another->isChecked()) && !another->getOvertake())
	{
		GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
		gs->gameScore += 50;
		another->setOvertake(true);
		cout << "Overtake: " << gs->gameScore << endl;
	}
}

bool Collider::alreadyCollided()
{
	return this->collided;
}

void Collider::setAlreadyCollided(bool flag)
{
	this->collided = flag;
}

sf::FloatRect Collider::getGlobalBounds()
{
	sf::FloatRect bounds = this->sprite->getGlobalBounds();
	bounds = this->owner->getGlobalTransform().transformRect(bounds);
	return bounds;

	/*sf::FloatRect bounds = this->getOwner()->getGlobalBounds();
	bounds = this->owner->getGlobalTransform().transformRect(bounds);
	std::cout << bounds.left << ":" << bounds.top << endl;
	return bounds;*/
}

void Collider::setLocalBounds(sf::FloatRect localBounds)
{
	this->localBounds = localBounds;
}

//destroy objects
void Collider::collisionEnter(AGameObject* gameObjects, colliderType type, Collider* coll)
{

	this->listener->applyPhysics(coll);
}

void Collider::collisionExit(AGameObject* gameObjects)
{

}

void Collider::perform()
{
	if (this->collType == colliderType::Player && !isChecked())
	{
		//for side movement when hit

		AirplanePlayer* player = (AirplanePlayer*)this->owner;
		if (player == NULL)
			return;
		sf::Transformable* transformable = this->getOwner()->getTransformable();

		// reposition the character when hit
		if (hitWall)
		{
			player->getTransformable()->setPosition(sf::Vector2f(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT - 150));
			
		}
		else if (playerPosX <= enemyPosX)
		{
			//cout << "Hello" << endl;
			player->getTransformable()->move(-1 * SPEEDSKID * deltaTime.asSeconds(), 0);
			//player->getTransformable()->setRotation(45);
			transformable->rotate(10.0f);
			
		}
		else if (playerPosX > enemyPosX)
		{
			//cout << "World" << endl;
			player->getTransformable()->move(SPEEDSKID * deltaTime.asSeconds(), 0);
			//player->getTransformable()->setRotation(-45);
			transformable->rotate(10.0f);
		}
		
		//PlayerInputController* playerinput = (PlayerInputController*)this->owner;

		//for blinking
		player->blinkDuration -= this->deltaTime.asSeconds();
		/*if (player->inviDuration > 0)
		{
			playerinput->keyFlag = false;
		}*/
		if (player->blinkDuration <= 0)
		{
			sprite->setColor(sprite->getColor() == sf::Color::White ? sf::Color::Red : sf::Color::White);
			player->blinkDuration = 0.2f;
		}

		//cout << player->inviDuration << endl;
		player->inviDuration -= this->deltaTime.asSeconds();
		if (player->inviDuration <= 0)
		{
			player->inviDuration = 1.5f;
			sprite->setColor(sf::Color::White);
			setChecked(true);
			player->isCheck = true;
			this->hitWall = false;
			player->getTransformable()->setRotation(0);
			transformable->rotate(0.0f);
			//playerinput->keyFlag = true;
		}
		
	}
}
