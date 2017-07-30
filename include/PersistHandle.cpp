#include <iostream>
#include "Persist.h"

PersistHandle::PersisntHandle()
{
	for(int i = 0; i < 4; i++)
	{
		reapplyCheck.push_back(false);
		amount.push_back(0);
		numTurns.push_back(0);
	}
}

void PersistHandle::persistPush(std::shared_ptr<Character> target, std::shared_ptr<Skill> skill)
{
	for(int i = 0; i < 4; i++)
	{
		int reapply = skill->getReapplyTurn()[i];
		if(reapply > 0)
		{
			reapplyCheck[i] = true;
			numTurns[i] = reapply;
		}
	}
}

void PersisntHandle::setAmount(int amountInp, int ndx)
{
	amount[ndx] = amountInp;
}
