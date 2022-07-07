#include "SFXManager.h"
#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance() {
	//initialize only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new SFXManager();
	}
	return sharedInstance;
}

void SFXManager::loadAll()
{
	loadAudio("winsound", "Media/sounds/win.wav");
	loadAudio("MainMenuBG", "Media/sounds/MainMenu.wav");
	loadAudio("Collide", "Media/sounds/Collide.wav");
	loadAudio("Start", "Media/sounds/Start.wav");
	loadAudio("Car", "Media/sounds/Car.wav");
	loadAudio("bgmusic", "Media/sounds/ingamebg.wav");


}


void SFXManager::loadAudio(std::string key, std::string path) {
	sf::SoundBuffer* sound = new sf::SoundBuffer();
	sf::Sound* audio = new sf::Sound();
	sound->loadFromFile(path);
	audio->setBuffer(*sound);
	soundMap[key] = audio;
}

sf::Sound* SFXManager::getSound(std::string key) {
	if (soundMap[key] != NULL) {
		return soundMap[key];
	}
	else {
		std::cout << "No Audio found for " << key;
		return NULL;
	}
}

void SFXManager::playSound(std::string key)
{
	SFXManager::getInstance()->getSound(key)->play();
	SFXManager::getInstance()->soundVolume(key, 40); // default volume = 40
}

void SFXManager::pauseSound(std::string key)
{
	SFXManager::getInstance()->getSound(key)->pause();
}

void SFXManager::stopSound(std::string key)
{
	SFXManager::getInstance()->getSound(key)->stop();
}

void SFXManager::soundVolume(std::string key, int vol)
{
	SFXManager::getInstance()->getSound(key)->setVolume(vol);
}

void SFXManager::loopSound(std::string key, bool loop)
{
	SFXManager::getInstance()->getSound(key)->setLoop(loop);
}


