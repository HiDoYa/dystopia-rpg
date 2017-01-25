#include <string>

#ifndef TEXTBOX
#define TEXTBOX

class Textbox 
{
	private:
		double boxWidth;
		double boxHeight;
		double fontSize;
		double textSpeed;
		std::string text;
	public:
		void openBox();
		void closeBox();
		void updateText(std::string);
		void nextText();
};

#endif
