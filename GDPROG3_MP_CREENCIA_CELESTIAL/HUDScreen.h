#pragma once
#include "AGameObject.h"
#include "UIButtonInputController.h"
#include "UIText.h"

class HUDScreen : public AGameObject, public ButtonListener
{
public:
	HUDScreen(string name);
	~HUDScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button); 

	std::string killCountText;
	UIText* killCount_Text;

	std::string lifeCountText;
	UIText* lifeCount_Text;

	std::string fuelCountText;
	UIText* fuelCount_Text;

	std::string scoreCountText;
	UIText* scoreCount_Text;

	std::string speedCountText;
	UIText* speedCount_Text;


private:
	sf::Sprite* sprite;
};

