#pragma once
#include <SFML/Graphics.hpp>

class ApplicationManager
{
public:
	static void initialize(sf::RenderWindow* window);
	static ApplicationManager* getInstance();
	void applicationQuit();
	void pauseApplication();
	void resumeApplication();
	bool isPaused();

	enum GameState { Running = 0, Paused = 1 };

private:
	ApplicationManager() {};
	ApplicationManager(ApplicationManager const&) {};             // copy constructor is private
	ApplicationManager& operator=(ApplicationManager const&) {};  // assignment operator is private
	~ApplicationManager();
	static ApplicationManager* sharedInstance;

	sf::RenderWindow* window;
	GameState state;
};