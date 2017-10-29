//Header de Position.cpp

#include <string>

class Position {
	public:
		Position();
		Position(int x, int y);
		std::string toString();
		static Position positionFromString(std::string s);
		void increment(int xAdd, int yAdd);
		Position incrementedBy(int xAdd, int yAdd);
		bool isValid();
		int getX();
		int getY();
	private:
		int x;
		int y;
};
