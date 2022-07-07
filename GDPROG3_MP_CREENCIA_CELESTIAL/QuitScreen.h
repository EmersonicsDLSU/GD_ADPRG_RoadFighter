#pragma once
#include "UIButtonInputController.h"
class QuitScreen : public AGameObject, public ButtonListener
{
public:
	QuitScreen(string name);
	~QuitScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);

	void markMainMenuQuit();
	void markGameQuit();

private:
	bool forMainMenu = false;

};
