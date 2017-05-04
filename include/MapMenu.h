#ifndef MAPMENU_H
#define MAPMENU_H

class MapMenu
{
	private:
		sf::Texture bgTexture;
		sf::RectangleShape bgSprite;

		std::vector<sf::Text> menuChoice;
		std::Vector<sf::RectangleSHape> menuChoiceBoxes;

		sf::RectangleShape currentSelection;
	public:
};

#endif
