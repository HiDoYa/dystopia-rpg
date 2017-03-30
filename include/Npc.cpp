#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dialogue.h"
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
void Npc::speak(std::vector<bool>& event, Textbox& box, Player& player)
{
	bool cond = !player.getMoving() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(colliding)
	{
		for(int i = 0; i < getCondition().size(); i++)
		{
			bool allowText = true;
			for(int j = 0; j < getCondition()[i].size(); j++)
			{
				if(event[getCondition()[j][i]] != getConditionCheck()[j][i])
				{
					allowText = false;
				}
			}

			if(allowText)
			{
				box.textHandler(name, getText()[i], cond, speaking);
				break;
			}
		}
	}

//	if(colliding)
//	{
//		//box.textHandler(name, str, cond, speaking);
//	}

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
