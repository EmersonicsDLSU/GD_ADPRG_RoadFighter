
#pragma once
#include "AGameObject.h"
#include <iostream>

using namespace std;

class ProgressBar : public AGameObject
{
public:
	ProgressBar(string name);
	void initialize();
	sf::Sprite* sprite;
};