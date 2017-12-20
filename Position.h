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
		static Position positionFromString(std::string s, bool &ok);
		void increment(int xAdd, int yAdd);
		Position incrementedBy(int xAdd, int yAdd) const;
		bool isValid() const;
		/*!
		 *  @brief get the X of the Position
		 *
		 *  @param none
		 *  @return this.x
		 */
		int getX() const {
			return x;
		}

		/*!
		 *  @brief get the Y of the Position
		 *
		 *  @param none
		 *  @return this.y
		 */
		int getY() const {
			return y;
		}
	private:
		int x;
		int y;
};

#endif /* POSITION_H */
