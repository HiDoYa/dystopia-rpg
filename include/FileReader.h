#include <memory>
#include "Item.h"
#include "Npc.h"

#ifndef FILEREADER_H
#define FILEREADER_H

//Gets data from text files. Map class also reads from text files (for solely maps)
class FileReader
{
	private:
	public:
		FileReader();
		//Game loading
		void loadAlly(std::vector<std::shared_ptr<Character>>&);
		void loadSkill(std::vector<std::shared_ptr<Skill>>&);
		void loadItem(std::vector<std::shared_ptr<Item>>&);

		//Per each map
		void loadMapEnemies(std::vector<std::shared_ptr<Character>>&, std::string);
		void loadMainMapFile(std::string,
				     std::vector<std::shared_ptr<Npc>>&,
				     std::vector<std::shared_ptr<Character>>&,
				     int&,int&, int&, int&, int&, int&, int&);

		//Utility
		std::string getWholeText(std::ifstream&);
};

#endif
