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
		/*!
		 *  @brief move current position by xAdd, yAdd
		 *
		 *  @param xAdd : position's x increment value (can be < 0)
		 *  @param yAdd : position's y increment value (can be < 0)
		 *  @return none
		 */
		void increment(const int xAdd, const int yAdd) {
			x+=xAdd;
			y+=yAdd;
		}

		/*!
		 *  @brief create a new position instance translated from this by (xAdd, yAdd)
		 *
		 *  @param xAdd : position's x increment value (can be < 0)
		 *  @param yAdd : position's y increment value (can be < 0)
		 *  @return a new Position instance
		 */
		Position incrementedBy(const int xAdd, const int yAdd) const {
			return Position(x+xAdd,y+yAdd);
		}

		/*!
		 *  @brief check if our position is valid
		 *  0:0 (user cannot play during this turn) is considered as an invalid position
		 *
		 *  @param none
		 *  @return true if our position is valid
		 */
		bool isValid() const {
			return  (x>=1 && x<=8 && y>=1 && y<=8) ; /* first row:first column is 1:1 */
		}
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
