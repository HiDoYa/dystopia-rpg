#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Textbox.h"
#include "UIOverlay.h"

#include "Npc.h"

Npc::Npc()
{
	name = "default name";

	//Gets texture of sprite
	setTextureRect(0, 0);

	//Initializes speaking bool
	speaking = false;
	colliding = false;
}

//Gets the converted vector, deals with animation/textbox calls, and deals with multiple textboxes
//TODO Only allow speak when the player is facing TOWARDS the npc instead of just collision
void Npc::speak(sf::String nm, sf::String str, Textbox& box, Player& player)
{
	bool cond = !player.getMoving() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(colliding)
	{
		box.textHandler(nm, str, cond, speaking);
	}

	//TODO test
	//box.choiceBoxDisp("Hello", "Not Hello", cond, speaking);
}

void Npc::collision(Player& player)
{
	colliding = player.collisionZones(getPosition().x / 64, getPosition().y / 64);
}

//********* MUTATORS  *********
void Npc::setName(std::string inp)
{
	name = inp;
}

//********* ACCESSORS *********
bool Npc::getSpeaking()
{
	return speaking;
}

std::string Npc::getName()
{
	return name;
}
