#pragma once
#include "AGameObject.h"
#include "UIButtonInputController.h"
class SamplePopupScreen : public AGameObject, public ButtonListener
{
public:
	SamplePopupScreen(string name, std::string popType);
	~SamplePopupScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);

private:
	std::string popType;
};

