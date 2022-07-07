#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
class AGameObject; //perform forward declaration to avoid circular import dependency

class AComponent
{
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3 };
	AComponent(string name, ComponentType type);
	virtual ~AComponent();

	void attachOwner(AGameObject* owner);
	void detachOwner();
	AGameObject* getOwner();
	ComponentType getType();
	string getName();

	void setDeltaTime(sf::Time deltaTime);
	virtual void perform() = 0; //performs the associated action.

protected:
	AGameObject* owner;
	ComponentType type;
	string name;
	sf::Time deltaTime;
};