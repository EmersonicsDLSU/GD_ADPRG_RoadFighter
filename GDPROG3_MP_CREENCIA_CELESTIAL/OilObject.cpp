#include "OilObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "OilBehavior.h"
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
#include "Collider.h"

int OilObject::recentKillCount = 0;


OilObject::OilObject(string name, sf::Vector2f position, std::string laneType, std::string emptyGOtype) :
	APoolable(name), CollisionListener(), position(position), laneType(laneType), emptyGOtype(emptyGOtype)
{

}

void OilObject::initialize()
{//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("cars_sprite"));
	//JSON BELOW
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	int maxRow = (textureSize.y / TextureManager::getInstance()->parse1.getSheet("frames")["car1.png"]["sourceSize"]["h"].GetInt());
	int maxCol = (textureSize.x / TextureManager::getInstance()->parse1.getSheet("frames")["car1.png"]["sourceSize"]["w"].GetInt());
	textureSize.x /= maxCol;
	textureSize.y /= maxRow;
	sprite->setTextureRect(sf::IntRect(
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[4].c_str()]["frame"]["x"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[4].c_str()]["frame"]["y"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[4].c_str()]["frame"]["w"].GetInt(),
		TextureManager::getInstance()->parse1.getSheet("frames")[TextureManager::getInstance()->listOfProperties[4].c_str()]["frame"]["h"].GetInt()
	));
	// JSON ABOVE
	//change size
	sprite->setScale(sprite->getScale().x * 0.8f, sprite->getScale().y * 0.8f);
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	/*this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	//randomize
	this->getTransformable()->move(rand() % 300 - rand() % 300, 0);*/
	//this->getTransformable()->setRotation(180); //must face towards player

	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	OilBehavior* behavior = new OilBehavior("EnemyBehavior");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

	this->sprite = renderer->mainSprite;

	//set a collider
	Collider* coll = new Collider("Enemy_col", sprite, Collider::Enemy);
	this->attachComponent(coll);
	PhysicsManager::getInstance()->trackObject(coll);
	coll->setCollisionListener(this);

}

void OilObject::onRelease()
{

}

void OilObject::onActivate()
{
	//reset state
	OilBehavior* behavior = (OilBehavior*)this->findComponentByName("EnemyBehavior");
	this->setPosition(position.x, position.y - 50);

	/* OLD
	//randomize
	this->getTransformable()->move(rand() % 300 - rand() % 300, 0);
	*/
	this->getTransformable()->move(0, 0);
}

APoolable* OilObject::clone()
{
	APoolable* copyObj = new OilObject(this->name, position, laneType, emptyGOtype);

	return copyObj;
}

void OilObject::applyPhysics(Collider* coll)
{
	//access components
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;
	Collider* collPlayer = (Collider*)player->findComponentByName("Airplane_col");

	//set player collider to false
	collPlayer->setChecked(false);
	player->isCheck = false;

	//turn of the lane
	EmptyGameObject* eg = (EmptyGameObject*)GameObjectManager::getInstance()->findObjectByName(this->emptyGOtype);
	eg->setEnabled(false);

	//adds a new object to the pool and lane
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

