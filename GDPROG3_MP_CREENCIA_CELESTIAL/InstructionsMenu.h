#pragma once
#include "UIButtonInputController.h"
class InstructionsMenu : public AGameObject, public ButtonListener
{
public:
	InstructionsMenu(string name);
	~InstructionsMenu();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);

	void markMainMenuQuit();
	void markGameQuit();

private:
	bool forMainMenu = false;

};
