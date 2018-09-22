// 
// Board.cpp
//
//
// NAME: Jessica Au
// SID: 998941022
//

#include "Board.h"
#include "Tetromino.h"
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;


// function to add a tetromino to the board. this function also checks to see
// if a tetromino will fit on the board and if it will over with any
// existing tetrominos on the board.
void Board::addTetromino(char type, int x, int y, int orientation){

	vector<Tetromino *>::const_iterator iter;

	Tetromino* newItem = Tetromino::makeTetromino(type, x, y, orientation);
	if (fits_on_board(*newItem))
	{

		for (iter = tList.begin(); iter != tList.end(); iter++)
		{
			if ((*iter)->Tetromino::overlap(*newItem))
				throw invalid_argument("overlap");
		}

		tList.push_back(newItem);
	}

	else 
		throw invalid_argument("does not fit on the board");

}

// bool function to see if the tetromino will fit on the board.
bool Board::fits_on_board(const Tetromino &t) const
{
	for (int i = 0; i <4; i++)
	{
		if ((t.getX(i)) > size_x)
			return false;

		if ((t.getY(i)) > size_y)
			return false;
	}

	return true;
}

// function to draw the board and call each individual tetromino's draw function.
void Board::draw(void) const 
{

	vector<Tetromino *>::const_iterator iter;

	cout << "<?xml version=\"1.0\" encoding=\"utf-8\"  standalone=\"no\"?>" << endl;
	cout << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" " << endl;
	cout << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"> " << endl;
	cout << "<svg width=\"570\" height=\"570\" viewBox=\"0 0 550 550\" " << endl;
	cout << "xmlns=\"http://www.w3.org/2000/svg\" " << endl;
	cout << "xmlns:xlink=\"http://www.w3.org/1999/xlink\" >" << endl;
	cout << "<g transform=\"matrix(1,0,0,-1,50,550)\">" << endl;
	cout << "<rect fill=\"white\" stroke=\"black\" x=\"0\" y=\"0\"  width=" << "\"" << size_x*50 << "\"" << " height=" << "\"" << size_y*50 << "\"" << "/>" << endl;

	for (iter = tList.begin(); iter != tList.end(); iter++)
	{
		(*iter)->Tetromino::draw();

	}
	cout << "</g>" << endl;
	cout << "</svg>" << endl;

}

