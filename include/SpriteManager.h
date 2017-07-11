#include <SFML/Graphics.hpp>

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

class SpriteManager
{
	private:
		//For all sprites
		sf::Sprite sprite;
		sf::Texture texture;

		//For battle
		int length;
		sf::Font font;
		sf::Text name;
		sf::RectangleShape maxHpBar;
		sf::RectangleShape currentHpBar;
		sf::RectangleShape maxManaBar;
		sf::RectangleShape currentManaBar;
	public:
		SpriteManager();

		//Mutators
		void setName(std::string);
		void setHpBar(int, int);
		void setManaBar(int, int);

		void setTextureSprite(std::string);
		void setTextureRect(int, int);
		void setTextureRect(int, int, int);
		void setScale(float, float);
		void setPosition(int, int);

		//Accessors
		sf::Sprite getSprite();
		sf::Vector2f getPosition();

		//Etc
		bool mouseInSprite(sf::RenderWindow&);
		void drawSprite(sf::RenderWindow&);
		void updatePositionBattle();
		void drawSpriteBattle(sf::RenderWindow&);
		void moveSprite(int, int);
};

#endif
