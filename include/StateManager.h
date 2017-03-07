#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager
{
	private:
		int currentState;
		int currentBattleState;
		
		int startPosX;
		int startPosY;
		int currentZone;
		int currentMap;

		//Menu (state 0)
		bool menuLoaded;
		MainMenu mainMenu;

		//Map (state 1)
		bool mapLoaded;

		UIOverlay overlay;
		Textbox textbox;

		std::unique_ptr<Map> ground;
		std::unique_ptr<Map> background;
		std::unique_ptr<Map> collision;
		//Map foreground;

		std::vector<Npc> npc;
		Player player;

		//Map (state 2)
		bool battleLoaded;
		//TODO Think of how Battle class will be used for different battles (deleted vector?)
		Battle battle;

	public:
		StateManager();

		//Menu
		void allMenu(sf::RenderWindow&);
		void loadMenu();
		void updateMenu(sf::RenderWindow&);

		//Map
		void allMap(sf::RenderWindow&, sf::View&);
		void loadMap(sf::RenderWindow&);
		void updateMap(sf::RenderWindow&, sf::View&);
		void renderMap(sf::RenderWindow&, sf::View&);

		//Battle
		void allBattle(sf::RenderWindow&, sf::View&);
		void loadBattle(sf::RenderWindow&, sf::View&);
		void updateBattle(sf::RenderWindow&, sf::View&);
		void renderBattle(sf::RenderWindow&, sf::View&);

		//Accessors
		int getCurrentState();
};

#endif
