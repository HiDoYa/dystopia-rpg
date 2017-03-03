OBJ = main.o Textbox.o SpriteManage.o Map.o Npc.o Player.o Enemy.o  Battle.o UIOverlay.o MainMenu.o StateManager.o
all: game

game: $(OBJ)
	g++ $(OBJ) -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./sfml-app -g

main.o: main.cpp
	g++ -std=c++11 -c $<

Battle.o: include/Battle.cpp
	g++ -std=c++11 -c $<

Enemy.o: include/Enemy.cpp
	g++ -std=c++11 -c $<

Player.o: include/Player.cpp
	g++ -std=c++11 -c $<

MainMenu.o: include/MainMenu.cpp
	g++ -std=c++11 -c $<

Map.o: include/Map.cpp
	g++ -std=c++11 -c $<

Npc.o: include/Npc.cpp
	g++ -std=c++11 -c $<

SpriteManage.o: include/SpriteManage.cpp
	g++ -std=c++11 -c $<

StateManager.o: include/StateManager.cpp
	g++ -std=c++11 -c $<
	
Textbox.o: include/Textbox.cpp
	g++ -std=c++11 -c $<

UIOverlay.o: include/UIOverlay.cpp
	g++ -std=c++11 -c $<
