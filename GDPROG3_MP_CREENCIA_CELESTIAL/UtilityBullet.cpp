#include "UtilityBullet.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "AirplanePlayer.h"
#include "BulletBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "ObjectPoolHolder.h"


UtilityBullet::UtilityBullet(string name) : APoolable(name), CollisionListener()
{

}

void UtilityBullet::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("bullet"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;
	this->setPosition(player->getTransformable()->getPosition().x, player->getTransformable()->getPosition().y);

	/*
	//randomize
	this->getTransformable()->move(rand() % 300 - rand() % 300, 0);
	this->getTransformable()->setRotation(180); //must face towards player*/


	Renderer* renderer = new Renderer("bulletSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	BulletBehavior* behavior = new BulletBehavior("BulletBehavior");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

	this->sprite = sprite;

	Collider* coll = new Collider("Bullet_col", sprite, Collider::Utility);
	this->attachComponent(coll);
	PhysicsManager::getInstance()->trackObject(coll);
	coll->setCollisionListener(this);
}

void UtilityBullet::onRelease()
{

}

void UtilityBullet::onActivate()
{
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;
	//reset state
	BulletBehavior* behavior = (BulletBehavior*)this->findComponentByName("EnemyBehavior");
	behavior->reset();
	this->setPosition(player->getTransformable()->getPosition().x, player->getTransformable()->getPosition().y);
	/*//randomize
	this->getTransformable()->move(rand() % 300 - rand() % 300, 0);*/
}

APoolable* UtilityBullet::clone()
{
	APoolable* copyObj = new UtilityBullet(this->name);

	return copyObj;
}

bool UtilityBullet::isDestroyed()
{
	return bulletDestroyed;
}

void UtilityBullet::applyPhysics(Collider* coll)
{
	GameObjectManager::getInstance()->deleteObject(coll->getOwner());
	ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BULLET_POOL_TAG)->addObject();
}