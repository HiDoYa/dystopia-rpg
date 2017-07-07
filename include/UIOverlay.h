#ifndef UIOVERLAY_H
#define UIOVERLAY_H

class UIOverlay
{
	private:
		//Mainwrapper
		sf::Texture mainWrapperTexture;
		sf::Sprite mainWrapperSprite;

		//Font Used
		sf::Font font;

		//Exp bar and level indicator
		sf::CircleShape levelNumWrapper;
		sf::Text levelText;

		//Equipped skills
		std::vector<sf::Texture> skillIconTextures;
		std::vector<sf::CircleShape> skillIcons;

		//Currency and other data
		sf::Text currencyText;
	public:
		UIOverlay();

		//Mutators
		void setPosition(sf::View);
		void setCurrency(int);
		void setLevel(int);

		//Etc
		void drawAll(sf::RenderWindow&);
};

#endif
