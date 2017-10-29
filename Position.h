//Header de Position.cpp

class Position {
	public:
		Position();
		Position(int l, int c);
		
		void increment(int lAdd, int cAdd);
		bool isValid();
		int getLine();
		int getCol();
	private:
		int line;
		int col;
};
