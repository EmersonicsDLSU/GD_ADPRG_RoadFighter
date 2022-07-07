
#pragma once
#include "AComponent.h"
#include "EmptyGameObject.h"
//class handling N enemy airplanes. communicates with object pool
class GameSystem : public AComponent
{
public:
	GameSystem(string name);
	~GameSystem();
	void perform();

public:
	static int gameScore;
	bool bgmove = false;
	bool startfuel = false;
	float fuel = 100.0f;
	float speedMeter = 0.0f;
	float bgSpeed;
	float enemySpeed;
	float kmTaken = 0.0f;
	int percentage = 0;
	float road1Km = 5000.0f;

public:
	void addListLane(EmptyGameObject* lane, std::string carType);
	void resetGameSystem();

private:
	vector<EmptyGameObject*> listLane1;	//normal
	vector<EmptyGameObject*> listLane2;	//bonus
	vector<EmptyGameObject*> listLane3;	//truck
	vector<EmptyGameObject*> listLane4;	//oil spill

private:
	void openLanes(vector<int>sample);
	void randomOpenListLane();
	bool checkLanes();

private:
	float maxLowAcce = 224.0f;
	float maxHighAcce = 400.0f;
	bool onceSound = false;

public:
	static int currentLevel;
	
};