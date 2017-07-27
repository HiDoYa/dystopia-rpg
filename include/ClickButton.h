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
		bool hover;
		bool mouseInside;

		//For the map
		int viewX;
		int viewY;

		sf::Font font;
		sf::Text text;
		sf::Text hoverText;
		sf::Texture texture;
		sf::RectangleShape rect;
		sf::CircleShape circ;
	public:
		ClickButton();
		ClickButton(int);
		
		//0 = rect, 1 = circ
		void setType(int);
		void setHoverText(bool);

		//TODO Do hovertext
		//TODO Create gradient overlay over texture (if hovered, skill button is greyed out a bit?)
		sf::Text* getHoverText();
		sf::Text* getText();
		sf::Texture* getTexture();
		sf::RectangleShape* getRect();
		sf::CircleShape* getCirc();

		//Text inside button
		void centerText();
		void centerHoverHorizontal();

		//TODO Greyed out if inactive option?
		//TODO Toggle (keep in a certain color if clicked and take away the color if some other condition is met)

		//Col1 is for selected, col2 is for deselected colors
		//Texture1 and texture2 is for image names
		bool mouseInButton(sf::RenderWindow&);
		bool mouseInButton(sf::Color, sf::Color, sf::RenderWindow&);
		bool mouseInButton(std::string, std::string, sf::RenderWindow&);
		bool mouseClickedInButton(sf::Color, sf::Color, sf::RenderWindow&);
		bool mouseClickedInButton(std::string, std::string, sf::RenderWindow&);

		void updatePositionMap(int, int, sf::View);
		void setPositionHover(int, int, sf::View);
		void drawAll(sf::RenderWindow&);
};

#endif
