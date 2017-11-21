#include "Cell.h"
//#include <iostream>     // for std::cout

using namespace std;

Cell::Cell(){
//	cout<< "constructeur de Cell" << endl;
	this->content=Empty;
}

Cell::~Cell(){
//	cout << "destructeur de Cell" << endl;
}

void Cell::setContent(cellContent content){
	this->content = content;
}
cellContent Cell::getContent(){
	return this->content;
}

cellContent Cell::switchContent()
{
	this->content = (this->content==Black?White:Black);
	//cout<<"contentcell"<<content<<endl;
	return this->getContent();
}
