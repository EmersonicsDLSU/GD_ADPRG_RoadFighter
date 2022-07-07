#pragma once
#include "GenericInputController.h"

class PlayerInputController : public GenericInputController
{
public:
	PlayerInputController(string name);
	~PlayerInputController();

	void perform();
	bool isD();
	bool isF();
	bool isLeft();
	bool isRight();
	bool isPause();
	bool keyFlag = false;

private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool accelerateD = false;
	bool accelerateF = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool pauseGame = false;
};
