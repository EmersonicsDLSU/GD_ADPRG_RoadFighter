#pragma once
#include "AGameObject.h"
class UIText :
	public AGameObject
{
public:
	UIText(string name);
	~UIText();
	void initialize();
	void setText(string text);
	string getText();
	void setSize(unsigned int size);
private:
	sf::Text* text;
};

