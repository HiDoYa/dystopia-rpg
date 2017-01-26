main: main.cpp include/Textbox.cpp include/Npc.cpp
	g++ -std=c++11 -c main.cpp include/Textbox.cpp include/Npc.cpp
	g++ main.o Textbox.o Npc.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app


