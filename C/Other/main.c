#include <stdio.h>
#include <stdlib.h>
#include "doard.h"


int main(int argc, char* argv[]){
	int rows,columns,numForWin;
	int i;
	
	//if argc is less than four, not enough
	if(argc < 4){
	printf("Not enough arguments entered\n");	
	printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
	exit(0);
	}
	//if argc is more than four, too many
	if(argc > 4){
	printf("Too many arguments entered\n");
	printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
	exit(0);	
	} 
	if(argc == 4){
	rows = atoi(argv[1]);
	columns = atoi(argv[2]);
	numForWin = atoi(argv[3]);
	

	//increment row and col by one
	++rows; ++columns;	

	int** A=(int**)malloc((rows+10)*sizeof(int*));
	for(i=0;i<rows;i++){
	A[i]=(int*)malloc((columns+10)*sizeof(int));
	}
	
	create_board(rows,columns,A);
	print_board(rows,columns,A);
        play_game(rows,columns,numForWin,A);
	}
	return 0;	
}



