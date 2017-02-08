all: game

game: main.o Textbox.o Npc.o Player.o Mouse.o Map.o
	g++ main.o Textbox.o Npc.o Player.o Mouse.o Map.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./sfml-app

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Textbox.o: include/Textbox.h include/Textbox.cpp
	g++ -std=c++11 -c include/Textbox.cpp

Npc.o: include/Npc.h include/Npc.cpp
	g++ -std=c++11 -c include/Npc.cpp

Player.o: include/Player.h include/Player.cpp
	g++ -std=c++11 -c include/Player.cpp

Mouse.o: include/Mouse.h include/Mouse.cpp
	g++ -std=c++11 -c include/Mouse.cpp

Map.o: include/Map.h include/Map.cpp
	g++ -std=c++11 -c include/Map.cpp
