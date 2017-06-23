#ifndef EVENT_H
#define EVENT_H

class Event
{
	private:
	public:
		void addItem(int);
		void removeItem(int);

		void addSkill(int, int);

		void cutscene(int);

		void panCamera(int, int);
		
		void teleport(int, int);
};
#endif
