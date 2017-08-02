#include "ClickButton.h"
#include <SFML/Audio.hpp>

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

		//Choices
		ClickButton choiceOne;
		ClickButton choiceTwo;
		bool choiceBoxOpen;
		bool displayChoiceBoxes;
		int currentChoice;
		int newZero;
		bool tempBool;

		//Stores text split up
		std::vector<std::string> sVec;
		int textNum;

		//Music
		sf::Music mu;
		
		//Box size and position
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
		//****** ACCESSORS *********
		void setFont(sf::String);
		void setName(sf::String);
		void setText(sf::String);
		
		//****** MUTATORS *********
		sf::Text getName();
		sf::Text getText();

		//******* UTILITY *********
		void updatePosition(sf::View);
		void readFromScript(std::string);
		void drawAll(sf::RenderWindow&);

		//*** PRETEXT *********
		void convertText(std::string, std::vector<std::string>&);
		void openBox();

		//**** DURING TEXT *********
		void animateText(std::string);
		bool textHandler(sf::String, sf::String, bool, bool&);
		int choiceBoxDisp(std::string, std::string, std::string,
				  std::string, std::string, std::string,
				  std::string, bool, bool&, sf::RenderWindow& win);
		bool makeChoice(sf::RenderWindow&);

		//****** POST TEXT *********
		void closeBox();
		bool nextText();
};

#endif
