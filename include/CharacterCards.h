#include "SpriteManager.h"
#include "StatBar.h"
#include "Character.h"

#ifndef CHARACTERCARDS_H
#define CHARACTERCARDS_H
class CharacterCards
{
	private:
		sf::Font font;

		SpriteManager image;
		SpriteManager background;

		sf::Text name;
		sf::Text desc;

		sf::Text str;
		sf::Text def;
		sf::Text agi;

		StatBar hp;
		StatBar mana;

	public:
		CharacterCards();
		void setupText(sf::Text, sf::Font, int = 30);
		void setupCard(Character);

		void drawAll(sf::RenderWindow&);
};
#endif
