#ifndef STATBAR_H
#define STATBAR_H
class StatBar
{
	private:
		int current;
		int max;

		int sizeX;
		int sizeY;

		//0 is above, 1 is below, 2 is inside
		int labelPos;
		
		sf::Font font;
		sf::Text label;

		sf::RectangleShape currentRect;
		sf::RectangleShape maxRect;
	public:
		StatBar();
		void setLabelPos(int);
		void setLabelSize(int);
		sf::RectangleShape* getCurrentRect();
		sf::RectangleShape* getMaxRect();
		sf::Text* getLabel();
		void setMaxSize(sf::Vector2f);
		//setPosition must be used after text character size and box size
		void setPosition(sf::Vector2f);
		void setStats(int, int, std::string = "");
		void updateSize();
		void drawAll(sf::RenderWindow&);
};
#endif
