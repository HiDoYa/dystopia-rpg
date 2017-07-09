#include <memory>

#ifndef MAPMENU_H
#define MAPMENU_H

class MapMenu
{
	private:
		sf::Texture bgTexture;
		sf::RectangleShape bgSprite;

		std::vector<std::shared_ptr<sf::ClickButton>> menuChoices;
	public:
};

#endif
