#include <SFML/Graphics.hpp>

#include "Npc.h"
#include "Player.h"
#include "SpriteManage.h"
#include "Textbox.h"

Npc::Npc()
{
	//Gets texture of sprite
	setTextureRect(0, 0);
	
	//Default for textbox
	textNum = 0;
	openBox = false;
	closeBox = false;

	//Initializes speaking bool
	speaking = false;
	colliding = false;
}

//Gets the converted vector, deals with animation/textbox calls, and deals with multiple textboxes
void Npc::speak(sf::String nm, sf::String str, Textbox& box, Player& player)
{
	if(colliding && !player.getMoving() &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		box.convertText(str, sVec);
		if(!box.getOpen() && textNum == 0)
		{
			openBox = true;
		}
	}

	if(openBox && textNum == 0)
	{
		speaking = true;
		box.openBox();
		if(box.getOpen())
		{
			textNum = 1;
		}
	}

	for(int i = 0; i < sVec.size(); i++)
	{
		if(textNum == i + 1)
		{
			openBox = false;
			box.setName(nm);
			box.animateText(sVec[i]);
			if(box.nextText())
			{
				if(sVec.size() == textNum)
				{
					textNum = -1;
				}
				else
				{
					textNum = i + 2;
				}
			}
		}
	}

	if(textNum == -1)
	{
		speaking = false;
		closeBox = true;
	}

	if(closeBox)
	{
		box.closeBox();
		if(!box.getOpen())
		{
			closeBox = false;
		}
		textNum = 0;
	}
}

bool Npc::getSpeaking()
{
	return speaking;
}

void Npc::collision(Player& player)
{
	colliding = player.collisionZones(getPosition().x / 64, getPosition().y / 64);
}
