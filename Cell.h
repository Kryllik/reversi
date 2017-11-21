#ifndef CELL_H
#define CELL_H

/*!
 * \enum cellContent
 * \brief the possible content of a cell
 */
typedef enum {Black,White,Empty} cellContent; 

/*! \class Cell
   * \brief Class for one board's cell. It can be either Black, White or Empty.
   *
   *  allow to get / set / switch (toggle) content
   */
class Cell{
public:
	Cell();
	~Cell();
	void setContent(cellContent content);
	cellContent getContent() const;
	cellContent switchContent();
private:
	cellContent content;
};

#endif /* CELL_H */
