#include <memory>

#include <SFML/Graphics.hpp>
#ifndef CLASSBUTTON_H
#define CLASSBUTTON_H

class ClickButton
{
	private:
		//TODO Add sound when clicked
		//0 for rect, 1 for circle
		int type;

		sf::Font font;
		sf::Text text;
		sf::Texture texture;
		sf::RectangleShape rect;
		sf::CircleShape circ;
	public:
		ClickButton();
		ClickButton(int);
		
		void setType(int);

		sf::Text* getText();
		sf::RectangleShape* getRect();
		sf::CircleShape* getCirc();

		//Text inside button
		void centerText();

		//Col1 is for selected, col2 is for deselected colors
		//Texture1 and texture2 is for image names
		bool mouseInButton(sf::Color, sf::Color, sf::RenderWindow&);
		bool mouseInButton(std::string, std::string, sf::RenderWindow&);
		bool mouseClickedInButton(sf::Color, sf::Color, sf::RenderWindow&);
		bool mouseClickedInButton(std::string, std::string, sf::RenderWindow&);

		void drawAll(sf::RenderWindow&);
};

#endif
