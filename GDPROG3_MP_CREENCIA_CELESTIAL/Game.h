#pragma once
#include "Entity.h"
#include "JSONParser.h"
#include <vector>
#include "JSONParser.h"
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Game {
    public: 
        static const int WINDOW_WIDTH = 1024;
        static const int WINDOW_HEIGHT = 768;
        const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

        Game();
        void run();
    private:
        void processEvents();
        void update(sf::Time);
        void render();
    private:
        sf::RenderWindow mWindow;
        std::vector<Entity*> entityList;
        static Game* sharedInstance;
};