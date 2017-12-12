#ifndef POSITION_H
#define POSITION_H

#include <string>

/*!
 * @class Position
 * @brief class that handle position on grid
 *
 */
class Position {
	public:
		Position();
		Position(int x, int y);
		std::string toString() const;
		static Position positionFromString(std::string s);
		void increment(int xAdd, int yAdd);
		Position incrementedBy(int xAdd, int yAdd) const;
		bool isValid() const;
		int getX() const;
		int getY() const;
	private:
		int x;
		int y;
};

#endif /* POSITION_H */
