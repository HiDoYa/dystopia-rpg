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
		int recSize;
		
		//Window sizes
		int width;
		int height;

		//All for animating text
		sf::Clock clk;
		sf::Time tme;
		int textSpeed;
		double currentTime;
		double lastTime;
		int textIndex;
		sf::String animText;

	public:
		Textbox(sf::RenderWindow&);
		void setFont(sf::String);
		void setText(sf::String);
		void setName(sf::String);
		void setTextSpeed(int);
		sf::RectangleShape getBox();
		sf::Text getText();
		sf::Text getName();
		void drawAll(sf::RenderWindow&);
		//TODO Unfinished 
		sf::String convertText(sf::String);
		void animateText(sf::String);
		void openBox();
		void closeBox();
		void nextText();
};

#endif
