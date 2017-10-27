//Header de Pawn.cpp


#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

//susing namespace std::pair;
 
class Pawn{
	public:
		Pawn();
		~Pawn();
		void setColor();
		bool getColor();
	private:
		std::pair<int,int> position;
		bool color;
		void switchColor();
};
