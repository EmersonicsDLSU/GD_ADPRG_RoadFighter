#include "BonusCarObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "BonusCarBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "CollisionListener.h"
#include "GameObjectManager.h"
#include "ObjectPoolHolder.h"
#include "AirplanePlayer.h"
#include "HUDScreen.h"
#include "GameSystem.h"

int BonusCarObject::recentKillCount = 0;


BonusCarObject::BonusCarObject(string name, sf::Vector2f position, std::string laneType, std::string emptyGOtype) :
	APoolable(name), CollisionListener(), position(position), laneType(laneType), emptyGOtype(emptyGOtype)
{

}

void BonusCarObject::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("cars_sprite"));
	//JSON BELOW
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	int maxRow = (textureSize.y / TextureManager::getInstance()->parse1.getSheet("frames")["car1.png"]["sourceSize"]["h"].GetInt());
	int maxCol = (textureSize.x / TextureManager::getInstance()->parse1.getSheet("frames")["car1.png"]["sourceSize"]["w"].GetInt());
	textureSize.x /= maxCol;
	textureSize.y /= maxRow;
	sprite->setTextureRect(sf::IntRect(
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[3].c_str()]["frame"]["x"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[3].c_str()]["frame"]["y"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[3].c_str()]["frame"]["w"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[3].c_str()]["frame"]["h"].GetInt()
	));
	// JSON ABOVE
	//change size
	sprite->setScale(sprite->getScale().x * 0.6f, sprite->getScale().y * 0.6f);
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	BonusCarBehavior* behavior = new BonusCarBehavior("EnemyBehavior");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

	this->sprite = renderer->mainSprite;

	//set a collider
	Collider* coll = new Collider("Enemy_col", sprite, Collider::Enemy);
	this->attachComponent(coll);
	PhysicsManager::getInstance()->trackObject(coll);
	coll->setCollisionListener(this);

}

void BonusCarObject::onRelease()
{

}

void BonusCarObject::onActivate()
{
	//reset state
	BonusCarBehavior* behavior = (BonusCarBehavior*)this->findComponentByName("EnemyBehavior");
	this->setPosition(position.x, position.y - 50);

	/* OLD
	//randomize
	this->getTransformable()->move(rand() % 300 - rand() % 300, 0);
	*/
	this->getTransformable()->move(0, 0);
}

APoolable* BonusCarObject::clone()
{
	APoolable* copyObj = new BonusCarObject(this->name, position, laneType, emptyGOtype);

	return copyObj;
}

void BonusCarObject::applyPhysics(Collider* coll)
{
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;

	//HUDScreen* hud = (HUDScreen*)GameObjectManager::getInstance()->findObjectByName("HUDScreen");

	//fuel +7 score + 1000 if hit  bonus car
	GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
	gs->fuel += 7;
	gs->gameScore += 1000;

	//turn of the lane
	EmptyGameObject* eg = (EmptyGameObject*)GameObjectManager::getInstance()->findObjectByName(this->emptyGOtype);
	eg->setEnabled(false);

	ObjectPoolHolder::getInstance()->getPool(laneType)->addObject();
	ObjectPoolHolder::getInstance()->getPool(laneType)->deletePoolable((APoolable*)this);

	/*//Kill count
	if (player != NULL && player->isCheck)
	{
		std::string killCountText = "Kill Count: ";
		killCountText.append(std::to_string(++player->killCount));
		//hud->killCount_Text->setText(killCountText);
		recentKillCount = player->killCount;
	}
	else if (player == NULL)
	{
		std::string killCountText = "Kill Count: ";
		killCountText.append(std::to_string(recentKillCount));
		//hud->killCount_Text->setText(killCountText);
		recentKillCount = 0;
	}
	else
	{
		std::string killCountText = "Kill Count: ";
		killCountText.append(std::to_string(recentKillCount));
		//hud->killCount_Text->setText(killCountText);
	}*/
}

