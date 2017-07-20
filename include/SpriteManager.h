#include <SFML/Graphics.hpp>

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

class SpriteManager
{
	private:
		//For all sprites
		sf::Sprite sprite;
		sf::Texture texture;
	public:
		SpriteManager();

		//Mutators
		//TODO make another class wrapping spritemanager that includes battle sprites
		void setTextureSprite(std::string);
		void setTextureRect(int, int);
		void setTextureRect(int, int, int);
		void setScale(float, float);
		void setPosition(int, int);

		//Accessors
		sf::Sprite* getSprite();
		sf::Vector2f getPosition();

		//Etc
		void drawSprite(sf::RenderWindow&);
};

#endif
