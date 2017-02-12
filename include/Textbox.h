#include <SFML/Audio.hpp>
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
		sf::Text nextPrompt;
		bool open;

		//Music
		sf::Music mu;
		
		//Box size and position
		int width;
		int height;
		int posX;
		int posY;

		//All for animating text
		sf::Clock clock;
		sf::Time time;
		float currentTime;
		float lastTime;
		int textSpeed;
		int textIndex;
		sf::String animText;

	public:
		Textbox(sf::View&);
		void setFont(sf::String);
		void setName(sf::String);
		void setText(sf::String);
		void setTextSpeed(int);
		void updatePosition(sf::View);
		sf::Text getName();
		sf::Text getText();
		bool getOpen();
		void drawAll(sf::RenderWindow&);
		void convertText(std::string, std::vector<std::string>&);
		void animateText(std::string);
		void openBox();
		void closeBox();
		bool nextText();
};

#endif
