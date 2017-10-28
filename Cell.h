//Header de Pawn.cpp


#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

//susing namespace std::pair;
 
typedef enum {Black,White,Empty} cellContent; 


class Cell{
	public:
		Cell();
		~Cell();
		void setContent(cellContent content);
		cellContent getContent();
	private:
		cellContent content;
		void switchColor();
};
