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
		std::string tempChoiceText;
		sf::RectangleShape choiceRect;
		bool choiceBoxOpen;
		int currentChoice;

		//Stores text split up
		std::vector<std::string>sVec;
		int textNum = 0;

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
		void setTextSpeed(int);
		
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
		void textHandler(sf::String, sf::String, bool, bool&);
		void choiceBoxDisp(std::string, std::string, bool, bool&);
		void makeChoice();

		//****** POST TEXT *********
		void closeBox();
		bool nextText();
};

#endif
