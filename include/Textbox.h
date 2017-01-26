#include <SFML/Graphics.hpp>

#ifndef TEXTBOX_H
#define TEXTBOX_H

class Textbox 
{
	private:
		sf::RectangleShape rec;
		sf::Font font;
		sf::Text text;
		sf::Text name;
		double textSpeed;
		int recSize;
	public:
		Textbox(sf::RenderWindow&);
		void setFont(sf::String);
		void setText(sf::String);
		void setName(sf::String);
		void setRecSize(int);
		void setTextSpeed(double);
		sf::RectangleShape getBox();
		sf::Text getText();
		sf::Text getName();
		void drawAll(sf::RenderWindow&);
		void animateText();
		void openBox();
		void closeBox();
		void nextText();
};

#endif
