#include <SFML/Graphics.hpp>

class Entity
{
	public:
		Entity();
		void setTexture(sf::Texture texture);
		sf::Sprite* getSprite();
		void update();
		std::string rootTexName;
		int frames;
	private:
		sf::Texture mTexture;
		sf::Sprite mSprite;
		sf::Clock clock;
		int ctr = 0;

};
