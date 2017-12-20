#ifndef CELL_H
#define CELL_H

/*!
 * \enum cellContent
 * \brief the possible content of a cell
 */
typedef enum {Black,White,Empty} cellContent; 

/*! @class Cell
   * @brief Class for one board's cell. It can be either Black, White or Empty.
   *
   *  allow to get / set / switch (toggle) content
   */
class Cell{
public:
	Cell();
	~Cell();
	void setContent(cellContent content);
	/*!
	 *  @brief get the content of a Cell
	 *
	 *  @param  none
	 *  @return the current content of the cell
	 */
	cellContent getContent() const {
		return this->content;
	}
	cellContent switchContent();
private:
	cellContent content;		/*<! the content of this cell */
};

#endif /* CELL_H */
