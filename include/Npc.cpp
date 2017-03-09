#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Textbox.h"
#include "UIOverlay.h"

#include "Npc.h"

Npc::Npc()
{
	//Gets texture of sprite
	setTextureRect(0, 0);

	//Initializes speaking bool
	speaking = false;
	colliding = false;
}

//Gets the converted vector, deals with animation/textbox calls, and deals with multiple textboxes
void Npc::speak(sf::String nm, sf::String str, Textbox& box, Player& player)
{
	bool cond = colliding && !player.getMoving() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	box.textHandler(nm, str, cond, speaking);
	//test
}

bool Npc::getSpeaking()
{
	return speaking;
}

void Npc::collision(Player& player)
{
	colliding = player.collisionZones(getPosition().x / 64, getPosition().y / 64);
}
