#ifndef FILEREADER_H
#define FILEREADER_H

//Gets data from text files. Map class also reads from text files (for solely maps)
class FileReader
{
	private:
	public:
		//Game loading
		void loadAlly(std::vector<Character*>&);
		void loadSkill(std::vector<Skill>&);

		//Per each map
		void loadMapEnemies(std::vector<Character>&, std::string);
		void loadMainMapFile(std::string, std::vector<Character>&, std::vector<Character>&, int&, int&, int&, int&, int&, int&, int&);

		//Utility
		std::string getWholeText(std::ifstream&);
};

#endif
