#include "Character.h"
#include <memory>

#ifndef PERSIST_H
#define PERSIST_H

//TODO UNFINISHED AND UNUSED
class PersistHandle
{
	private:
		std::shared_ptr<Character> target;
		std::shred_ptr<Skill> skill;

		std::vector<bool> reapplyCheck;
		std::vector<int> amount;
		std::vector<int> numTurns;
	public:
		void persistPush(std::shared_ptr<Character>, std::shared_ptr<Skill>);
		//TODO How would this work?
		void setAmount(int, int);
};

#endif
