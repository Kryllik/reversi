/*
 * Class for one board's cell. It can be either Black, White or Empty.
 *
 */

#ifndef CELL_H
#define CELL_H


typedef enum {Black,White,Empty} cellContent; 


class Cell{
	public:
		Cell();
		~Cell();
		void setContent(cellContent content);
		cellContent getContent();
		cellContent switchContent();
	private:
		cellContent content;
};

#endif /* CELL_H */
