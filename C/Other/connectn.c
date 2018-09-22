//purpose: like Connect-4 except instead of having the board be a constant 6 X 7 we will allow the user to enter the size of the board they would like to play on.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "doard.h"

//take the argument to create the board, and make each unit a star
void create_board(int rows, int columns,int **A){
	int i,j,k;
	k=rows-1;
	
	for(i=0;i<rows;++i){
	for(j=0;j<columns;++j){
		A[i][j]='*';
		}
	}	

	for(i=0;i<rows-1;++i){
	--k;
	A[i][0]=k;
	}
	A[rows-1][0]=' ';

	for(j=1;j<columns;++j){
		A[rows-1][j]=j-1;
	}

}


//print out the board row by row and col by col
void print_board(int rows,int columns, int** A){
	int i,j;
	
	for(i=0;i<rows;++i){
	for(j=0;j<columns;++j){
	if(((j==0 ) && (i != (rows-1)))||((i==(rows-1))&&(j!=0))){
	printf("%2d ", A[i][j]);
	}
	else{
	printf("%2c ", A[i][j]);
	}
	}
	printf("\n");
	}
}

// after the game is done, free the space
void destroy_board(int rows,int columns,int** A){
	int i;
	for(i=0;i<columns;++i){
		free(A[i]);
	}
	free(A);
}


void play_game(int rows,int columns,int numForWin,int** A){

	int i,userInput,userNum;
	bool gameOver=false;
	bool gameWon=false;
	int playValid=0;
	
	//as long as the game is not over, let the game play
	while(!gameOver && !gameWon){
		//as long as the game is a valid play, let the game play
		//else, keep asking
		while(playValid==0){
		printf("Enter a column between 0 and %d to play in: ",columns-2);
		scanf("%d",&userInput);	
		playValid=play_valid(userInput,rows,columns,A);	
		//if playvalid return 1, token X 	
		if(playValid==1){
			userNum=1;
			for(i=rows-1;i>=0;--i){
			if(A[i][userInput+1]=='*'){
				A[i][userInput+1]='X';
				break;
				}
			}
			//update the board, and check the winning condition		
			print_board(rows,columns,A);
			gameOver=game_over(rows,columns,A);
			gameWon=game_won(rows,columns,userNum,numForWin,A);
			break;
			}	
		}
		
		//if game over or there is a tie game, then do the following
		if(gameOver || gameWon){
			if(gameOver && !gameWon){
				printf("Tie game!\n");
				break;}
			//if game won, print the following
			else{
				printf("Player 1 Won!\n");
				break;
			}
		}


		playValid=0;
		while(playValid==0){
		printf("Enter a column between 0 and %d to play in: ",columns-2);
	   	scanf("%d", &userInput);
		playValid=play_valid(userInput,rows,columns,A);
		if(playValid==1){
	        	userNum=2;
			for(i=rows-1;i>=0;--i){
			if(A[i][userInput+1]=='*'){
				A[i][userInput+1]='O';
				break;
			}
			}		
			print_board(rows,columns,A);
			gameOver=game_over(rows,columns,A);
			gameWon=game_won(rows, columns, userNum,numForWin, A);
			break;
			}	
		}	
		if(gameOver || gameWon){
			if(gameOver && !gameWon){
				printf("Tie game!\n");
				break;}
			else{
				printf("Player 2 Won!\n");
				break;
			}
		}

		playValid=0;
	}
}


// if all the space are filled, then game is over
bool game_over(int rows,int columns,int** A){
	int i,j;
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
		if(A[i][j]=='*'){	
			return false;	
		}
	}
	}
	return true;
}

//put the winning condition into game won function
bool game_won(int rows,int columns,int userNum,int numForWin,int** A){
	bool rowWin=false;
	bool columnWin=false;
	bool diagWin=false;
	bool rightdiagWin=false;

	char userAlpha;

	
	if(userNum==1){
		userAlpha='X';
	}
	else{
		userAlpha='O';
	}
	//put the winning check function into
	rowWin=row_win(rows,columns,userAlpha,numForWin,A);
	columnWin=column_win(rows, columns, userAlpha, numForWin, A);
	diagWin=diag_win(rows, columns, userAlpha, numForWin, A);
	rightdiagWin=rightdiag_win(rows, columns, userAlpha, numForWin, A);

	if(rowWin || columnWin || diagWin || rightdiagWin){
		return true;
	}

	else{
	return false;
	}
}


bool row_win(int rows,int columns,int userAlpha,int numForWin,int** A){
	int i,j,k,l;
	if(numForWin>=rows){
		return false;}
	else{
	for(i=0;i<rows;i++){
		for(j=0;j<columns-numForWin+1;++j){
			l=0;
			//if the following add up to the winning number, then return true
			for(k=0;k<numForWin;++k){
				if( A[i][j+k]==userAlpha){
				++l;}
			}
			if(l==numForWin){	
			return true;}
			}
	}
	}
	return false;
}


bool column_win(int rows,int columns,int userAlpha,int numForWin,int** A){
	int i,j,k,l;
	if(numForWin>=columns){
		return false;}
	else{	
	for(i=0;i<columns;i++){
		for(j=0;j<rows-numForWin;++j){
			l=0;
			for(k=0;k<numForWin;++k){
				if(A[j+k][i]==userAlpha){
				++l;}
			}
			if(l==numForWin){	
			return true;}
			}
	}
	}
	return false;
}

bool diag_win(int rows,int columns,int userAlpha,int numForWin,int** A){
	int i,j,k,l;
	if(numForWin>=columns || numForWin>=rows){
		return false;}
	else{	
	for(i=0;i<rows-numForWin;i++){
		for(j=0;j<columns-numForWin+1;++j){
			l=0;
			for(k=0;k<numForWin;++k){
				if(A[i+k][j+k]==userAlpha){
				++l;}
			}
			if(l==numForWin){	
			return true;}
			}
	}
	}
	return false;
}

bool rightdiag_win(int rows,int columns,int userAlpha,int numForWin,int** A){
	int i,j,k,l;
	if(numForWin>=columns || numForWin>=rows){
		return false;}
	else{	
	for(i=0;i<rows-numForWin;i++){
		for(j=columns;j>numForWin-1;--j){
			l=0;
			for(k=0;k<numForWin;++k){
				//move from left to right
				if(A[i+k][j-k]==userAlpha){
				++l;}
			}
			if(l==numForWin){	
			return true;}
			}
	}
	}
	return false;
}


int play_valid(int userInput, int rows, int columns, int** A){
	int playValid=0;
	//if the user input is greater than the col or is negative, return invalid
	if((userInput < columns-1) && (userInput > -1)){
		if(A[0][userInput+1]=='*'){
			playValid = 1; 
			return playValid;
		}
		else{
		playValid = 0;
		return playValid;
		}
	}
	else{
	playValid=0;	
	return playValid;
	}
}



