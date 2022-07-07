#pragma once

class UIButton; //forward declaration to avoid circular dependency
class ButtonListener
{
public:
	virtual ~ButtonListener() {}

	virtual void onButtonClick(UIButton* button) = 0;
	virtual void onButtonReleased(UIButton* button) = 0;

protected:
	ButtonListener() {}
};