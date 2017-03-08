class Player;

#ifndef MAP_H
#define MAP_H

class Map
{
	private:
		//Used to setup bitmaps
		sf::Sprite tileSprite;
		sf::Texture tileTexture;
		std::vector<std::vector<sf::Vector2i>> map;
		sf::Vector2i loadCounter;

		//Used to load maps
		sf::Vector2i maxCords;

		//Used to change maps
		std::vector<sf::Vector2i> changeMapCords;
		int newMapCounter;
		std::vector<int> newZoneNum;
		std::vector<int> newMapNum;

		int yDisp;
	public:
		Map();
		void setupAll(sf::String);
		void setupStatic(sf::String textureInp);
		void drawStatic(sf::RenderWindow&, sf::View);
		void drawStatic(sf::RenderWindow&, sf::View, int);
		void setupBitmap(std::string, sf::RenderWindow&);
		void drawBitmap(sf::RenderWindow&);
		void drawCollision(sf::RenderWindow&, Player&);
		bool newMap(Player&, int&, int&);
		void newMapCheck(Player&, int&, int&, int&, int&, bool&, int&);

		//Accessors for new map
		std::vector<sf::Vector2i> getNewMapCords();
		int getNewMapCounter();
		std::vector<int> getNewZoneNum();
		std::vector<int> getNewMapNum();
};

#endif
