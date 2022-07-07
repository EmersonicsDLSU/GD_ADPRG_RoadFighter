#include "AComponent.h"

AComponent::AComponent(string name, ComponentType type) {
	this->name = name;
	this->owner = NULL;
	this->type = type;
}

AComponent::~AComponent() {
	this->owner = NULL;
	this->type = NotSet;
}

//parent
AGameObject* AComponent::getOwner()
{
	return this->owner;
}

AComponent::ComponentType AComponent::getType() {
	return this->type;
}

string AComponent::getName()
{
	return this->name;
}

void AComponent::setDeltaTime(sf::Time deltaTime)
{
	this->deltaTime = deltaTime;
}

void AComponent::attachOwner(AGameObject* object) {
	this->owner = object;
}

void AComponent::detachOwner() {
	//if object owner gets detached. then component must also be deleted.
	delete this;
}
