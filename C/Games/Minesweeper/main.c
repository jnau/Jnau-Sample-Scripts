#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "mine_board.h"


int main(int argc, char* argv[]){
	int row, col, numMine, timeSeed;
	int i;
	
	//if argc is less than four, not enough
	if(argc < 4){
	printf("Not enough arguments. Usage:\n");	
	printf("./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
	exit(0);
	}

	//if argc is more than four, too many
	else if(argc > 5){
	printf("Too many arguments. Usage:\n");
	printf("./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
	exit(0);	
	} 

	else{
		if(argc == 4){
			row = atoi(argv[1]);
			col = atoi(argv[2]);
			numMine = atoi(argv[3]);
			timeSeed = (unsigned int)time(NULL);
		}

			
		if(argc == 5){
			row = atoi(argv[1]);
			col = atoi(argv[2]);
			numMine = atoi(argv[3]);
			timeSeed = atoi(argv[4]);
		}
	}
	
	++row;
	++col;
	
	
	//increment row and col by one

	Mine playBoard;
	playBoard.row = row;
	playBoard.col = col;
   	playBoard.numMines=numMine;
	playBoard.rand_seed=timeSeed;
	playBoard.graph = (int **)malloc((row+10) * sizeof(int *));
	for (i = 0; i < row; i++){
		 playBoard.graph[i] = (int *)malloc((col+10) * sizeof(int));
		
	}
	
	

	Mine ansBoard;
	ansBoard.row = row;
	ansBoard.col = col;
	ansBoard.numMines=numMine;
	ansBoard.rand_seed=timeSeed;

	ansBoard.graph = (int **)malloc((row+10) * sizeof(int *));
	ansBoard.status=(bool**)malloc((row+10) * sizeof(bool *));
	for (i = 0; i < row; i++){
		ansBoard.graph[i] = (int *)malloc((col+10) * sizeof(int));
		ansBoard.status[i]=(bool*)malloc((row+10) * sizeof(bool));
	}



	create_play_board(playBoard);
	
	create_answer_board(ansBoard);

	printf("There are %d mines left\n",ansBoard.numMines);
	print_board(playBoard);
	
	play_game(ansBoard,playBoard);

	destroy_board(playBoard);
	destroy_board(ansBoard);
	
		

	return 0;	

}


