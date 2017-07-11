#ifndef BATTLEOVERLAY_H
#define BATTLEOVERLAY_H

class BattleOverlay
{
	private:
		sf::Texture bgTexture;
		sf::RectangleShape bgSprite;

		sf::Font font;

		sf::Text battleLog;
		sf::Text currentCharDesc;
		sf::Text damageNumbers;
	public:
		BattleOverlay();
		void showCurrentCharDesc();
		void updateBattleLog();
		void drawAll(sf::RenderWindow&);
};

#endif
