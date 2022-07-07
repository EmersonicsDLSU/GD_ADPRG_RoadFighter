#include "AGameObject.h"
#include <iostream>
#include "GenericInputController.h"
#include "Renderer.h"

AGameObject::AGameObject(std::string name) {

	this->name = name;
}

AGameObject::~AGameObject() {

	for (int i = 0; i < this->childList.size(); i++) {
		delete this->childList[i];
	}

	for (int i = 0; i < this->componentList.size(); i++) {
		delete this->componentList[i];
	}

	this->childList.clear(); this->childList.shrink_to_fit();
	this->componentList.clear(); this->componentList.shrink_to_fit();

	if (this->parent != NULL) {
		this->parent = NULL; //do not call delete this->parent! Creates a stack overflow.
	}
}

std::string AGameObject::getName() {
	return name;
}
void AGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) {
	if (!this->isEnabled()) {
		return;
	}

	std::vector<AComponent*> componentList = this->getComponentsOfType(AComponent::ComponentType::Renderer);

	renderStates.transform = renderStates.transform * this->transformable.getTransform();

	for (int j = 0; j < componentList.size(); j++) {
		Renderer* renderer = (Renderer*)componentList[j];
		renderer->assignTargetWindow(targetWindow);
		renderer->setRenderStates(renderStates);
		renderer->perform();
	}
	for (int i = 0; i < this->childList.size(); i++) {
		this->childList[i]->draw(targetWindow, renderStates);
	}
}

void AGameObject::processInput(sf::Event event)
{
	if (!this->isEnabled()) {
		return;
	}
	std::vector<AComponent*> componentList = this->getComponentsOfType(AComponent::ComponentType::Input);
	for (int j = 0; j < componentList.size(); j++) {
		GenericInputController* inputController = (GenericInputController*)componentList[j];
		inputController->assignEvent(event);
		inputController->perform();
	}
	for (int i = 0; i < this->childList.size(); i++) {
		this->childList[i]->processInput(event);
	}
}

void AGameObject::update(sf::Time deltaTime) {
	if (!this->isEnabled()) {
		return;
	}
	std::vector<AComponent*> componentList = this->getComponentsOfType(AComponent::ComponentType::Script);
	for (int j = 0; j < componentList.size(); j++) {
		componentList[j]->setDeltaTime(deltaTime);
		componentList[j]->perform();
	}

	for (int i = 0; i < this->childList.size(); i++) {
		childList[i]->update(deltaTime);
	}
}

void AGameObject::attachChild(AGameObject* child) {
	this->childList.push_back(child);
	child->parent = this;
	child->initialize(); //initialize when attaching to child
}

void AGameObject::detachChild(AGameObject* child)
{
	int index = -1;
	for (int i = 0; i < this->childList.size(); i++) {
		if (this->childList[i] == child) {
			index = i;
		}
	}

	if (index != -1) {
		this->childList.erase(this->childList.begin() + index);
	}
}

void AGameObject::setPosition(float x, float y)
{
	this->transformable.setPosition(x, y);
}

sf::Transformable* AGameObject::getTransformable() {
	return &this->transformable;
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			this->componentList[i]->detachOwner();
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

//returns the first component by name
AComponent* AGameObject::findComponentByName(string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

//returns the first component by name and type
AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}

//returns all components of a given type
std::vector<AComponent*> AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	std::vector<AComponent*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}
//recursive implementation. also searches in its children
std::vector<AComponent*> AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	std::vector<AComponent*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < this->childList.size(); i++) {
		foundList = this->getComponentsRecursiveProper(this->childList[i], type, foundList);
	}

	return foundList;
}

std::vector<AComponent*> AGameObject::getComponentsRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList)
{
	std::vector<AGameObject*> children = object->childList;

	for (int i = 0; i < object->componentList.size(); i++) {
		if (object->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < children.size(); i++) {
		this->getComponentsRecursiveProper(children[i], type, foundList);
	}

	return foundList;
}

sf::FloatRect AGameObject::getLocalBounds() {
	throw "getLocalBounds() not yet implemented!";
}

sf::FloatRect AGameObject::getGlobalBounds() {
	throw "gtLocalBounds() not implemented!";
}

sf::Transform AGameObject::getGlobalTransform() {
	AGameObject* parentObj = this;
	vector<AGameObject*> parentList;
	while (parentObj != NULL) {
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();
	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;
	for (int i = startIdx; i >= 0; i--) {
		transform = transform * parentList[i]->getTransformable()->getTransform();
	}
	return transform;
}

AGameObject* AGameObject::getParent() {
	return this->parent;
}

void AGameObject::setEnabled(bool flag)
{
	this->enabled = flag;
}

bool AGameObject::isEnabled()
{
	return this->enabled;
}