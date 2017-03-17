#ifndef SPRITEMANAGE_H
#define SPRITEMANAGE_H

class SpriteManage
{
	private:
		sf::Sprite sprite;
		sf::Texture texture;
	public:
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
