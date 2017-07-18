#ifndef DIALOGUE_H
#define DIALOGUE_H

class Dialogue
{
	private:
		//!!!! NOTE !!!!! check for condition FIRST and then checks for choiceCheck
		//Text checks sequentially; Most latest text for npc must come FIRST
		
		//**** TRAD TEXT *****
		//Stores all texts
		std::vector<std::string> text;
		//Stores all the conditions (flag number)
		std::vector<std::vector<int>> condition;
		//Stores whether the condition is looking for a true or false
		std::vector<std::vector<bool>> conditionCheck;
		//Stores what number to change
		std::vector<std::vector<int>> chgNum;
		//Stores to change the event to true or to false
		std::vector<std::vector<bool>> chgCheck;

		//0 is ally, 2 is skill
		std::vector<std::vector<int>> giveType;
		std::vector<std::vector<int>> giveId;
		

		//******* CHOICES TEXT *******
		//Stores whether to show choice
		std::vector<bool> choiceFlag;
		//Stores text for each choice
		std::vector<std::string> choiceDisp;
		std::vector<std::string> choiceOne;
		std::vector<std::string> choiceTwo;
		std::vector<std::string> choiceOneDisp;
		std::vector<std::string> choiceTwoDisp;
		//Stores which state to change after choice
		std::vector<std::vector<int>> chgOneNum;
		std::vector<std::vector<int>> chgTwoNum;
		//Stores whether the condition is going to change to a true or false
		std::vector<std::vector<bool>> chgOneBool;
		std::vector<std::vector<bool>> chgTwoBool;

	public:
		Dialogue();
		//******** PUSH ********
		void pushNextText();
		void pushText(std::string);
		void pushCondition(int);
		void pushConditionCheck(bool);
		void pushChgNum(int);
		void pushChgCheck(bool);

		void pushGiveType(int);
		void pushGiveId(int);

		//******** CHOICE SPECIFIC ********
		void curChoiceTrue();
		void pushChoice(std::string);
		void pushChoiceOne(std::string);
		void pushChoiceTwo(std::string);
		void pushChoiceOneDisp(std::string);
		void pushChoiceTwoDisp(std::string);
		void pushChgOneNum(int);
		void pushChgTwoNum(int);
		void pushChgOneBool(bool);
		void pushChgTwoBool(bool);

		//***** ACCESSORS ***********
		std::vector<std::string> getText();
		std::vector<std::vector<int>> getCondition();
		std::vector<std::vector<bool>> getConditionCheck();
		std::vector<std::vector<int>> getChgNum();
		std::vector<std::vector<bool>> getChgCheck();

		std::vector<std::vector<int>> getGiveType();
		std::vector<std::vector<int>> getGiveId();
		
		std::vector<bool> getChoiceFlag();
		std::vector<std::string> getChoiceDisp();
		std::vector<std::string> getChoiceOne();
		std::vector<std::string> getChoiceTwo();
		std::vector<std::string> getChoiceOneDisp();
		std::vector<std::string> getChoiceTwoDisp();
		std::vector<std::vector<int>> getChgOneNum();
		std::vector<std::vector<int>> getChgTwoNum();
		std::vector<std::vector<bool>> getChgOneBool();
		std::vector<std::vector<bool>> getChgTwoBool();
};

#endif
