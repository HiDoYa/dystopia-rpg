#include <SFML/Graphics.hpp>

#ifndef TEXTBOX_H
#define TEXTBOX_H

class Textbox 
{
	private:
		int textSpeed;
		sf::RectangleShape rec;
		sf::Font font;
		int recSize;
		sf::Text text;
		sf::Text name;
	public:
		Textbox(sf::RenderWindow&);
		void setFont(sf::String);
		void setText(sf::String);
		void setName(sf::String);
		sf::RectangleShape getBox();
		sf::Text getText();
		sf::Text getName();
		void drawAll(sf::RenderWindow&);
		void openBox();
		void closeBox();
		void nextText();
};

#endif
