#include <SFML/Graphics.hpp>
#include <iostream>

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
	//allowChoice = false;
}

//Gets the converted vector, deals with animation/textbox calls, and deals with multiple textboxes
//TODO Only allow speak when the player is facing TOWARDS the npc instead of just collision
void Npc::speak(std::vector<bool>& event, Textbox& box, MapPlayer& player)
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
				if(getChoiceFlag()[i])
				{
					switch(box.choiceBoxDisp(name, getText()[i], getChoiceDisp()[i], getChoiceOne()[i], getChoiceTwo()[i], getChoiceOneDisp()[i], getChoiceTwoDisp()[i], cond, speaking))
					{
						case 0:
							//Choice box is not completed yet
							break;
						case 1:
							//Change assuming the first choice
							for(int chgCounter = 0; chgCounter < getChgOneNum()[i].size(); chgCounter++)
							{
								event[getChgOneNum()[chgCounter][i]] = getChgOneBool()[chgCounter][i];
							}
							break;
						case 2:
							//Change assuming the second choice
							for(int chgCounter = 0; chgCounter < getChgOneNum()[i].size(); chgCounter++)
							{
								event[getChgTwoNum()[chgCounter][i]] = getChgTwoBool()[chgCounter][i];
							}
							break;
					}
				}
				else if(box.textHandler(name, getText()[i], cond, speaking))
				{
						for(int chgCounter = 0; chgCounter < getChgNum()[i].size(); chgCounter++)
						{
							event[getChgNum()[chgCounter][i]] = getChgCheck()[chgCounter][i];
						}
				}
				break;
			}
		}
	}
}

void Npc::collision(MapPlayer& player)
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
