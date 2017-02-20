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
		bool currentCompleted;

		//Music
		sf::Music mu;
		
		//Box size and position
		int width;
		int height;
		int posX;
		int posY;

		//Speed for closing/opening box
		int delayBoxSetup;
		
		//Time management
		sf::Clock clock;
		sf::Time time;
		float currentTime;

		//To skip text
		bool lastNotPressed;
		float lastTimeSkip;

		//For opening and closing box
		float lastTimeBox;

		//All for animating text
		float lastTimeLetter;
		int textSpeed;
		int textIndex;
		sf::String animText;

	public:
		Textbox();
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
