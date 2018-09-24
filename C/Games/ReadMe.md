# Games

## MineSweeper
__Scripted in C__
Final project for Programming and Problem solving course in collaboration with 3 other members, Winter 2015. 
We were asked to implement a functioning program to recreate the classic minesweeper game. 
Given a rectangular grid of tiles, we initialize and hide some mines under these tiles. 
The goal is to mark all the tiles containing mines and unconver all other tiles not containing any mines. 
Uncovering a tile containig a mine will cause you to lose the game. 
Uncovering a tile without a hidden mine, will tell you how many mines are hidden in its surrounding 8 tiles. 
#### Contains: condition.c, main.c, play_game.c, mine_board.h

## Tetris
__Scripted in C++__
Final Project for Software Development and Object-Oriented Programming course, Fall 2015.
We were asked to implement a functioning program recreating the game, Tetris. 
Initializing a certain board size, we create tetrominos (https://en.wikipedia.org/wiki/Tetromino) as they are read.
We have functions in order to add the tetromino, checks to see if it will fit on the board, and if it would overlap with any exisiting tetromino.
That said, we also implemented rotate functions in order to rotate the tetrominos clockwise.

#### Contains: Board.cpp, Tetris.cpp, Tetromino.cpp, Tetromino.h, Board.h
