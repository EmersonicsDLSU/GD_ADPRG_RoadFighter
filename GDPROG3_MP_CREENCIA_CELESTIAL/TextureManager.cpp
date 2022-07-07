#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
		//initialize only when we need it
		if (sharedInstance == NULL) {
			sharedInstance = new TextureManager();
		}
		return sharedInstance;
}

void TextureManager::jsonLoad(std::string path)
{
	parse1.parseJson(path);
	listOfProperties = parse1.returnProperties();
	std::string sheetName = parse1.getSheet("meta")["image"].GetString();
	jsonTexture.loadFromFile("Media/Textures/cars_sprite.png");
	loadTexture("cars_sprite", "Media/Textures/cars_sprite.png");
}

void TextureManager::loadAll() {

	loadTexture("desert_bg", "Media/Textures/Desert.png");
	sf::Texture* bgTex1;
	bgTex1 = getTexture("desert_bg");
	bgTex1->setRepeated(true);

	loadTexture("road_1", "Media/Textures/newroad.png");
	sf::Texture* bgTex2;
	bgTex2 = getTexture("road_1");
	bgTex2->setRepeated(true);

	loadTexture("road_2", "Media/Textures/desertroad.png");
	sf::Texture* bgTex3;
	bgTex3 = getTexture("road_2");
	bgTex3->setRepeated(true);

	loadTexture("road_3", "Media/Textures/wateroad.png");
	sf::Texture* bgTex4;
	bgTex4 = getTexture("road_3");
	bgTex4->setRepeated(true);

	loadTexture("ui_bg", "Media/Textures/newtxtbx.png");
	loadTexture("btn_normal", "Media/Textures/newbt.png");
	loadTexture("btn_pressed", "Media/Textures/newbtpress.png");
	loadTexture("hud_bg", "Media/Textures/clear.png");
	loadTexture("title1_bg", "Media/Textures/TITLE.png");
	loadTexture("title2_bg", "Media/Textures/TITLE.png");
	loadTexture("car2", "Media/Textures/car2.png");
	loadTexture("progressbar", "Media/Textures/progressbar.png");
	loadTexture("finish", "Media/Textures/finishline.png");
	loadTexture("start", "Media/Textures/start.png");


}

void TextureManager::loadTexture(std::string key, std::string path) {
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textureMap[key] = texture;
}

sf::Texture* TextureManager::getTexture(std::string key) {
	if (textureMap[key] != NULL) {
		return textureMap[key];
	}
	else {
		std::cout << "No texture found for " << key;
		return NULL;
	}
}

void TextureManager::testFunction() {
	std::cout << "Hi, I'm single-ton ;D";
}