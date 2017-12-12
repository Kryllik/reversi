#include "Cell.h"
//#include <iostream>     // for std::cout

using namespace std;


/*!
 *  @brief Cell's constructor
 *
 *  Construct a cell and assign 'Empty' to it
 *
 *  @param none
 */
Cell::Cell(){
//	cout<< "constructeur de Cell" << endl;
	this->content=Empty;
}

/*!
 *  @brief Cell's destructor
 *
 *  @param none
 */
Cell::~Cell(){
//	cout << "destructeur de Cell" << endl;
}

/*!
 *  @brief set the content of a Cell
 *
 *  @param  content : the content to assign to the cell
 *  @return none
 */
void Cell::setContent(const cellContent content){
	this->content = content;
}

/*!
 *  @brief get the content of a Cell
 *
 *  @param  none
 *  @return the current content of the cell
 */
cellContent Cell::getContent() const {
	return this->content;
}

/*!
 *  @brief switch (toggle) the content of a cell
 *
 *  @param  none
 *  @return the new content of the cell
 */
cellContent Cell::switchContent()
{
	this->content = (this->content==Black?White:Black);
	return this->getContent();
}
