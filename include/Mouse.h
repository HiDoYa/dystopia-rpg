#include <SFML/Graphics.hpp>

#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{
	private:
		sf::Sprite sprite;
		sf::Texture textureDefault;
		sf::Texture textureTalk;
	public:
		Mouse();
		void useDefaultMouse();
		void useTalkMouse();
		void setScale(int);
		void setPosition(int, int); 
		sf::Sprite getSprite();
		sf::Texture getTextureDefault();
		sf::Texture getTextureTalk();
};

#endif
