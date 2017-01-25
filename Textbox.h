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
		Textbox();
		void setFont(sf::String);
		void setFontSize(int);
		void setName(sf::String);
		void openBox();
		void closeBox();
		void updateText(sf::String);
		void nextText();
		sf::RectangleShape getBox();
		void getText();
};

#endif
