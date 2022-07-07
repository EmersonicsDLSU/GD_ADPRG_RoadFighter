#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

class SFXManager
{
public:
	static SFXManager* getInstance();
	void loadAll();
	sf::Sound* getSound(std::string);
	void playSound(std::string);
	void pauseSound(std::string);
	void soundVolume(std::string key,int vol);
	void stopSound(std::string);
	void loopSound(std::string key, bool loop);


private:
	SFXManager() {};
	SFXManager(SFXManager const&) {};             // copy constructor is private
	SFXManager& operator=(SFXManager const&) {};  // assignment operator is private
	~SFXManager();
	static SFXManager* sharedInstance;
	
	void loadAudio(std::string, std::string);
	std::unordered_map<std::string, sf::Sound*> soundMap;
};
