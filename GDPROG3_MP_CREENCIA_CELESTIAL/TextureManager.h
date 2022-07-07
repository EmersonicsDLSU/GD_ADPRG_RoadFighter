#pragma once
#include <SFML/Graphics.hpp>;
#include <unordered_map>
#include "JSONParser.h"
#include <string>
#include <vector>

class TextureManager
{
    public:
        static TextureManager* getInstance();
        void testFunction();

        void loadAll(); 
        void jsonLoad(std::string path);
        sf::Texture* getTexture(std::string);
    private:
        // set constructor to private
        TextureManager() {}; 
        // set copy contructor to private
        TextureManager(TextureManager const&) {};
        // assignment operator is private
        TextureManager& operator=(TextureManager const&){}; 
        static TextureManager* sharedInstance;

        void loadTexture(std::string,std::string);
        std::unordered_map<std::string, sf::Texture*> textureMap;

public:
    JSONParser parse1;
    std::vector<std::string> listOfProperties;
    sf::Texture jsonTexture;
};