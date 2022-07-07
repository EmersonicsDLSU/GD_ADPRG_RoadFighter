#include "GameSystem.h"
#include "SamplePopupScreen.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "AirplanePlayer.h"
#include "PlayerInputController.h"
#include "BGMovement.h"
#include "BGObject.h"
#include <iostream>
#include "HUDScreen.h"
#include "SFXManager.h"
#include "finishObject.h"
#include "Game.h"

int GameSystem::gameScore = 0;
int GameSystem::currentLevel = 1;

GameSystem::GameSystem(string name) : AComponent(name, Script)
{

}

GameSystem::~GameSystem()
{

}

void GameSystem::addListLane(EmptyGameObject* lane, std::string carType)
{
	if(carType == "normal")
	{
		this->listLane1.push_back(lane);
	}
	else if (carType == "bonus")
	{
		this->listLane2.push_back(lane);
	}
	else if (carType == "truck")
	{
		this->listLane3.push_back(lane);
	}
	else if (carType == "oil")
	{
		this->listLane4.push_back(lane);
	}
}

bool GameSystem::checkLanes()
{
	for (EmptyGameObject* a : listLane1)
	{
		if (a->isEnabled())
			return false;
	}
	for (EmptyGameObject* a : listLane2)
	{
		if (a->isEnabled())
			return false;
	}
	for (EmptyGameObject* a : listLane3)
	{
		if (a->isEnabled())
			return false;
	}
	for (EmptyGameObject* a : listLane4)
	{
		if (a->isEnabled())
			return false;
	}
	return true;
}

void GameSystem::randomOpenListLane()
{
	srand(time(NULL));
	vector<int>sample;
	int randomNum;
	while (sample.size() != 2)
	{
		randomNum = rand() % 4;
		if (sample.size() == 1 && sample[0] == randomNum)
		{
			continue;
		}
		sample.push_back(randomNum);
	}

	openLanes(sample);
}

void GameSystem::openLanes(vector<int>sample)
{
	//oil + normal
	if (percentage >= 10.0f && percentage < 20.0f)
	{
		this->listLane1[sample[0]]->setEnabled(true);
		this->listLane4[sample[1]]->setEnabled(true);
		return;
	}
	//truck + normal
	else if (percentage >= 20.0f && percentage < 30.0f)
	{
		this->listLane1[sample[0]]->setEnabled(true);
		this->listLane4[sample[1]]->setEnabled(true);
		return;
	}
	//truck + normal
	else if (percentage >= 30.0f && percentage < 40.0f)
	{
		this->listLane1[sample[0]]->setEnabled(true);
		this->listLane3[sample[1]]->setEnabled(true);
		return;
	}
	//bonus + normal
	else if (percentage >= 40.0f && percentage < 50.0f)
	{
		this->listLane1[sample[0]]->setEnabled(true);
		this->listLane2[sample[1]]->setEnabled(true);
		return;
	}
	//truck + normal
	else if (percentage >= 50.0f && percentage < 60.0f)
	{
		this->listLane1[sample[0]]->setEnabled(true);
		this->listLane3[sample[1]]->setEnabled(true);
		return;
	}
	//oil + normal
	else if (percentage >= 60.0f && percentage < 70.0f)
	{
		this->listLane1[sample[0]]->setEnabled(true);
		this->listLane4[sample[1]]->setEnabled(true);
		return;
	}
	//bonus + normal
	else if (percentage >= 70.0f && percentage < 80.0f)
	{
		this->listLane1[sample[0]]->setEnabled(true);
		this->listLane2[sample[1]]->setEnabled(true);
		return;
	}
	//truck
	else if (percentage >= 80.0f && percentage < 95.0f)
	{
		for (int i : sample)
			this->listLane3[i]->setEnabled(true);
		return;
	}
	else
	//should check the percentage of the minimap
	for (int i : sample)
	{
		this->listLane1[i]->setEnabled(true);
	}
}

void GameSystem::resetGameSystem()
{
	gameScore = 0;
	bgmove = false;
	startfuel = false;
	fuel = 100.0f;
	speedMeter = 0.0f;
	bgSpeed = 0.0f;
	enemySpeed = 0.0f;
	kmTaken = 0.0f;
	percentage = 0;
}

void GameSystem::perform()
{
	//Accessing Player and its components
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	if (player == NULL)
		return;

	//display score
	HUDScreen* hud = (HUDScreen*)GameObjectManager::getInstance()->findObjectByName("HUDScreen");
	std::string scoreCountText = "Score: ";
	scoreCountText.append(std::to_string(this->gameScore));
	hud->scoreCount_Text->setText(scoreCountText);

	//cout << percentage << endl;
	if (percentage >= 100) //change to you win pop up
	{
		SamplePopupScreen* popScreen = new SamplePopupScreen("samplePopupScreen", "win");
		GameObjectManager::getInstance()->addObject(popScreen);
		ApplicationManager::getInstance()->pauseApplication();
		SFXManager::getInstance()->stopSound("Car");
		listLane1.clear();
		listLane2.clear();
		listLane3.clear();
		listLane4.clear();
		currentLevel++; //next level
		return;
	}

	//condition if the fuel goes empty
	if (fuel <= 0)
	{
		startfuel == false;
		SamplePopupScreen* popScreen = new SamplePopupScreen("samplePopupScreen", "gameOver");
		GameObjectManager::getInstance()->addObject(popScreen);
		ApplicationManager::getInstance()->pauseApplication();
		SFXManager::getInstance()->stopSound("Car");
		fuel = 0.0f;
		listLane1.clear();
		listLane2.clear();
		listLane3.clear();
		listLane4.clear();
		return;
	}

	//Start Fuel
	if (startfuel == true)
	{
		//playCar sound
		if (!onceSound)
		{
			//cout << "Play" << endl;
			SFXManager::getInstance()->playSound("Car");
			SFXManager::getInstance()->soundVolume("Car", 30);
			SFXManager::getInstance()->loopSound("Car", true);
			onceSound = !onceSound;
		}

		if (player != NULL)
		{
			PlayerInputController* pc = (PlayerInputController*)player->findComponentByName("MyPlayerInput");
			//threshold for the lowestMaxAcce
			if (pc->isD() && speedMeter >= this->maxLowAcce)
			{
				this->speedMeter = 225.0f;
			}

			//threshold for the highestMaxAcce
			if (pc->isF() && speedMeter >= this->maxHighAcce)
			{
				this->speedMeter = 400.0f;
			}
		}

		//cout << "LANE= " << this->listLane[0]->isEnabled() << ":" << this->listLane[1]->isEnabled() << ":" << this->listLane[2]->isEnabled() << ":" << this->listLane[3]->isEnabled() << endl;

		//condition for opening the lanes; depends on the miniMap progress
		if (checkLanes())
		{
			randomOpenListLane();
		}

		//set the speed of the BG
		BGMovement* bm = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BGObject")->findComponentByName("BG_Movement");
		bm->setBGSpeed(bgSpeed);

	}
	//fuel off
	else
	{
		//stop Car sound
		if (onceSound)
		{
			//cout << "Stop" << endl;
			SFXManager::getInstance()->stopSound("Car");
			onceSound = !onceSound;
		}
		//lowers the speedMeter if one of the accelarations is not pressed
		this->speedMeter -= 15.5;
		//only sets it to 0 speed when MC is static
		if (this->speedMeter <= 0)
		{
			this->speedMeter = 0.0f;
		}
	}

	//runs fuel system; display fuel system
	std::string fuelCountText = "Fuel: ";
	fuelCountText.append(std::to_string((int)this->fuel));
	hud->fuelCount_Text->setText(fuelCountText);
	fuel -= deltaTime.asSeconds() * 2;

	//display speedometer
	HUDScreen* hud2 = (HUDScreen*)GameObjectManager::getInstance()->findObjectByName("HUDScreen");
	std::string speedCountText = "Speed(Km/H) : ";
	speedCountText.append(std::to_string((int)this->speedMeter));
	hud2->speedCount_Text->setText(speedCountText);

	//percentage
	percentage = (kmTaken / road1Km) * 100.0f;
	//cout << "KM: " << percentage << "%" << endl;

}