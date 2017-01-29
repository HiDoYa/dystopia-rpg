main: main.cpp include/Textbox.cpp include/Npc.cpp include/Player.cpp include/Environment.h
	g++ -std=c++11 -c main.cpp include/Textbox.cpp include/Npc.cpp include/Player.cpp include/Environment.cpp
	g++ main.o Textbox.o Npc.o Player.o Environment.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./sfml-app


