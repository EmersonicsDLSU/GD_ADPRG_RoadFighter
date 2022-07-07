#pragma once

#include "GenericInputController.h"
#include "ButtonListener.h"
#include "UIButton.h"

class UIButtonInputController : public GenericInputController
{
public:
	UIButtonInputController(string name, ButtonListener* buttonListener);
	~UIButtonInputController();

	void perform();

private:
	ButtonListener* buttonListener;
	bool pressed = false;
};



