#pragma once
#include "AGameObject.h"
#include "UIButton.h"
#include "UIText.h"

class MainMenuScreen : public AGameObject, public ButtonListener
{
public:
	MainMenuScreen(string name);
	~MainMenuScreen();

	void initialize();

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};

