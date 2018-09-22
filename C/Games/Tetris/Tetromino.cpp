//
// Tetromino.cpp
//
// Based on given Tetromino_hw2.cpp
//
// NAME: Jessica Au
// SID: 998941022
// 

#include "Tetromino.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// function to print the location of each tetromino.
void Tetromino::print(void) const
{
  cout << name() << " at";
  for ( int i = 0; i < 4; i++ )
    cout << " (" << x[i] << "," << y[i] << ")";
    cout << endl; 

}

int Tetromino::getX(int i) const {
  return x[i];

}

int Tetromino::getY(int i) const { 
  return y[i];

}

// function to check if a tetromino is overlapping another
bool Tetromino::overlap(const Tetromino &t) const
{
  for ( int i = 0; i < 4; i++ )
  {
    for ( int j = 0; j < 4; j++ )
    {
      if ( x[i] == t.x[j] && y[i] == t.y[j] )
        return true;

    }

  }

  return false;
}


// function to color in the tetromino a certain color.
void Tetromino::draw(void) const {


  cout << "<rect fill=" << "\"" << color() << "\"" << " stroke=\"black\" x=" << "\"" << x[0]*50 << "\"" << " y=" << "\"" << y[0]*50 << "\"" << " width=\"50\" height=\"50\"/>" << endl;
  cout << "<rect fill=" << "\"" << color() << "\"" << " stroke=\"black\" x=" << "\"" << x[1]*50 << "\"" << " y=" << "\"" << y[1]*50 << "\"" << " width=\"50\" height=\"50\"/>" << endl;
  cout << "<rect fill=" << "\"" << color() << "\"" << " stroke=\"black\" x=" << "\"" << x[2]*50 << "\"" << " y=" << "\"" << y[2]*50 << "\"" << " width=\"50\" height=\"50\"/>" << endl;
  cout << "<rect fill=" << "\"" << color() << "\"" << " stroke=\"black\" x=" << "\"" << x[3]*50 << "\"" << " y=" << "\"" << y[3]*50 << "\"" << " width=\"50\" height=\"50\"/>" << endl;

}

// function to rotate the tetromino 90 degrees however many times the user wants. [0-3]
void Tetromino::rotate(int nrot)
{
  for ( int irot = 0; irot < nrot; irot++ )
    for ( int i = 1; i < 4; i++ )
    {
      const int dx = x[i] - x[0];
      const int dy = y[i] - y[0];
      x[i] = x[0] - dy;
      y[i] = y[0] + dx;

    }
}

// makes the tetromino, checks for invalid orientation and char
Tetromino *Tetromino::makeTetromino(char type, int posx, int posy,
 int orientation)
{
  if ( orientation < 0 || orientation > 3 )
    throw invalid_argument("invalid orientation");

  if ( type == 'I' )
    return new I(posx,posy,orientation);
  else if ( type == 'O' )
    return new O(posx,posy,orientation);
  else if ( type == 'T' )
    return new T(posx,posy,orientation);
  else if ( type == 'J' )
    return new J(posx,posy,orientation);
  else if ( type == 'L' )
    return new L(posx,posy,orientation);
  else if ( type == 'S' )
    return new S(posx,posy,orientation);
  else if ( type == 'Z' )
    return new Z(posx,posy,orientation);
  else
    throw invalid_argument("invalid type");

  return 0;
}

//builds an I tetromino
I::I(int posx, int posy, int orientation)
{

  x[0] = posx + 0; y[0] = posy + 0;
  x[1] = posx + 0; y[1] = posy + 1;
  x[2] = posx + 0; y[2] = posy + 2;
  x[3] = posx + 0; y[3] = posy + 3;
  rotate(orientation);

}

//builds an O tetromino
O::O(int posx, int posy, int orientation)
{

  x[0] = posx + 0; y[0] = posy + 0;
  x[1] = posx + 1; y[1] = posy + 0;
  x[2] = posx + 0; y[2] = posy + 1;
  x[3] = posx + 1; y[3] = posy + 1;
  rotate(orientation);

}

//builds a T tetromino
T::T(int posx, int posy, int orientation)
{
  x[0] = posx + 0; y[0] = posy + 0;
  x[1] = posx - 1; y[1] = posy + 1;
  x[2] = posx + 0; y[2] = posy + 1;
  x[3] = posx + 1; y[3] = posy + 1;
  rotate(orientation);

}

//builds a J tetromino
J::J(int posx, int posy, int orientation)
{

  x[0] = posx + 0; y[0] = posy + 0;
  x[1] = posx + 1; y[1] = posy + 0;
  x[2] = posx + 1; y[2] = posy + 1;
  x[3] = posx + 1; y[3] = posy + 2;
  rotate(orientation);

}

// builds an L tetromino
L::L(int posx, int posy, int orientation)
{

  x[0] = posx + 0; y[0] = posy + 0;
  x[1] = posx + 1; y[1] = posy + 0;
  x[2] = posx + 0; y[2] = posy + 1;
  x[3] = posx + 0; y[3] = posy + 2;
  rotate(orientation);

}

//builds an S tetromino
S::S(int posx, int posy, int orientation)
{

  x[0] = posx + 0; y[0] = posy + 0;
  x[1] = posx + 1; y[1] = posy + 0;
  x[2] = posx + 1; y[2] = posy + 1;
  x[3] = posx + 2; y[3] = posy + 1;
  rotate(orientation);

}

//builds a Z tetromino
Z::Z(int posx, int posy, int orientation)
{

  x[0] = posx + 0; y[0] = posy + 0;
  x[1] = posx + 1; y[1] = posy + 0;
  x[2] = posx - 1; y[2] = posy + 1;
  x[3] = posx + 0; y[3] = posy + 1;
  rotate(orientation);

}

//functions to return the which tetromino is which
char I::name(void) const { return 'I'; }


char O::name(void) const { return 'O'; }


char T::name(void) const { return 'T'; }


char J::name(void) const { return 'J'; }


char L::name(void) const { return 'L'; }


char S::name(void) const { return 'S'; }


char Z::name(void) const { return 'Z'; }


// functions to assign a color to a tetromino
const char* I::color() const {

  const char* colstr = "cyan";
  return colstr;

}

const char* O::color() const {

 const char* colstr = "yellow";
  return colstr;

}

const char* T::color() const {

const char* colstr = "purple";
  return colstr;


}

const char* J::color() const {

 const char* colstr = "blue";
  return colstr;


}

const char* L::color() const {
  const char* colstr = "orange";
  return colstr;


}

const char* S::color() const {
  const char* colstr = "lime";
  return colstr;


}

const char* Z::color() const {

 const char* colstr = "red";
  return colstr;

}


