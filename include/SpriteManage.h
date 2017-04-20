#ifndef SPRITEMANAGE_H
#define SPRITEMANAGE_H

class SpriteManage
{
	private:
		sf::Sprite sprite;
		sf::Texture texture;
	public:
		//TODO If battle sprite (rather than map sprite), then draw health and mana bars above as well as name
		//Mutators
		void setTextureSprite(sf::String);
		void setTextureRect(int, int);
		void setTextureRect(int, int, int);
		void setScale(float, float);
		void setPosition(int, int);

		//Accessors
		sf::Sprite getSprite();
		sf::Vector2f getPosition();

		//Etc
		void drawSprite(sf::RenderWindow&);
		void moveSprite(int, int);
};

#endif
