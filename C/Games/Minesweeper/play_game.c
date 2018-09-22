#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "mine_board.h"



	
void play_game(Mine aBoard,Mine pBoard){
	int i,j;
	int urow,ucol,uact,uquestion,umark,umine;
	bool playValid=false;
	bool gameover=false;
	bool gamewon=false;


	//if the game is still playing
	while(!gameover || !gamewon){
		printf("Enter row a row between 0-%d and a column between 0-%d: ",aBoard.row-2,aBoard.col-2);
		scanf("%d %d",&urow,&ucol);	
		playValid=play_valid(aBoard,pBoard,urow,ucol);	
		//not vaild, keep asking
		while(!playValid){
			printf("Enter row a row between 0-%d and a column between 0-%d: ",aBoard.row-2,aBoard.col-2);
			scanf("%d %d",&urow,&ucol);
			playValid=play_valid(aBoard,pBoard,urow,ucol);	
		}
		
		//promt input
		if(playValid){
			if(pBoard.graph[pBoard.row-urow-2][ucol+1]=='#'){
				printf("Enter Action\n");
				printf("0. Reveal\n");
				printf("1. Question\n");
				printf("2. Mark\n");
				printf("3. Cancel\n");
				printf("Action: ");
				scanf("%d",&uact);

				//reveal the mine
				if (uact==0){
					pBoard.graph[pBoard.row-urow-2][ucol+1]=aBoard.graph[pBoard.row-urow-2][ucol+1];
					gameover=game_over(pBoard,urow,ucol);
					//check gameover condition
					if(gameover){
						print_board(aBoard);
						printf("You Lost :(\n");
						exit(0);
					}

					//if the surrounding is zero, then keep opening the tiles, until a non-zero
					if(pBoard.graph[pBoard.row-urow-2][ucol+1]=='0'){	
						for (i=0;i<aBoard.row;++i){
							for(j=0;j<aBoard.col;++j){
								aBoard.status[i][j]=false;
								}
						}		
						aBoard.status[aBoard.row-urow-2][ucol+1]=true;
						reveal(aBoard, pBoard, pBoard.row-urow-2, ucol+1);
						for (i=0;i<aBoard.row;++i){
							for(j=0;j<aBoard.col;++j){
								aBoard.status[i][j]=false;
							}
						}
					}
					
					//winning condtion check
					umine=umine_num(pBoard);
					gamewon=game_won(pBoard,aBoard,umine);
					if(gamewon){
						print_board(aBoard);
						printf("You Won!!\n");
						exit(0);
					}
					printf("There are %d mines left\n",pBoard.numMines-umine);
					print_board(pBoard);
				}

				//place a question mark
				else if(uact==1){
					pBoard.graph[pBoard.row-urow-2][ucol+1]='?';
					umine=umine_num(pBoard);
					printf("There are %d mines left\n",pBoard.numMines-umine);
					print_board(pBoard);

				}

				//place a ! mark, if num ! == num_mine, then game won
				else if(uact==2){	 				
					pBoard.graph[pBoard.row-urow-2][ucol+1]='!';
					umine=umine_num(pBoard);
					gamewon=game_won(pBoard,aBoard,umine);
					if(gamewon){
						print_board(aBoard);
						printf("You Won!!\n");
						exit(0);
					}
					
					printf("There are %d mines left\n",pBoard.numMines-umine);
					print_board(pBoard);

				}

				else if(uact==3){
					play_game(aBoard,pBoard);
				}
				
			}

			else if(pBoard.graph[pBoard.row-urow-2][ucol+1]=='?'){
					printf("Enter Action\n");
					printf("0. UnQuestion\n");
					printf("1. Cancel\n");
					printf("Action: ");
					scanf("%d", &uquestion);
					if(uquestion==0){
						pBoard.graph[pBoard.row-urow-2][ucol+1]='#';
						umine=umine_num(pBoard);
						printf("There are %d mines left\n",pBoard.numMines-umine);
						print_board(pBoard);	
					}
					else{
						play_game(aBoard,pBoard);
					}
			}

			else if(pBoard.graph[pBoard.row-urow-2][ucol+1]=='!'){
					printf("Enter Action\n");
					printf("0. UnMark\n");
					printf("1. Cancel\n");
					printf("Action: ");
					scanf("%d", &umark);
					if(umark==0){
						pBoard.graph[pBoard.row-urow-2][ucol+1]='#';
						umine=umine_num(pBoard);
						printf("There are %d mines left\n",pBoard.numMines-umine);
						print_board(pBoard);

						
					}
					else if(umark==1){
						play_game(aBoard,pBoard);
					}
			}
		}
				
		umine=umine_num(pBoard);
		gamewon=game_won(pBoard,aBoard,umine);
		gameover=game_over(pBoard,urow,ucol);
		playValid=false;
		
		

	}
}


void reveal(Mine aboard, Mine pboard, int row, int col){
	int k,l;


	for(k=-1;k<2;++k){
		for(l=-1;l<2;++l){
				if(row+k<0 || col+l <0 || row+k>aboard.row-1 || col>aboard.col){
					continue;
				}


				else{	
			
					if(aboard.status[row+k][col+l]){
						continue;
					}
					else{	
						if(pboard.graph[row+k][col+l]=='!' || pboard.graph[row+k][col+l] == '?'){
							aboard.status[row+k][col+l]=true;
							continue;	
						}
						
						else if(aboard.graph[row+k][col+l] > '0' && aboard.graph[row+k][col+l]< '9'){
							if(pboard.graph[row+k][col+l] == '?'){
								pboard.graph[row+k][col+l] = '?';
								continue;
							}
							else{
								pboard.graph[row+k][col+l]=aboard.graph[row+k][col+l];
								aboard.status[row+k][col+l]=true;
								continue;
							}


						}
	
						else if(aboard.graph[row+k][col+l]=='0'){
							if(pboard.graph[row+k][col+l] == '?'){
								pboard.graph[row+k][col+l] = '?';
								continue;
							}
							else{
								pboard.graph[row+k][col+l]=aboard.graph[row+k][col+l];
								aboard.status[row+k][col+l]=true;
								reveal(aboard,pboard,row+k,col+l);
								continue;
							}
							
						}

						
					}
				}
		}
	}
}

void create_play_board(Mine board) {


	int i,j;
	int k = board.row - 1;

        for (i = 0; i < board.row; i++) {
		 for (j = 0; j < board.col; j++){
		 	board.graph [i][j] = '#'; 
		 }
	}


	for(i = 0; i < board.row - 1; ++i){
		--k;
		board.graph [i][0]=k;
		}
	
	board.graph [board.row-1][0]=' ';

	for(j=1;j<board.col;++j){
		board.graph [board.row-1][j]=j-1;
	}



}

void create_answer_board(Mine board){
	
	int i,j,k,l;
	int m=0;
	int row,col;
	int num=board.row - 1;

	for(i = 0; i < board.row - 1; ++i){
		--num;
		board.graph [i][0]=num;
		}
	
	board.graph [board.row-1][0]=' ';

	for(j=1;j<board.col;++j){
		board.graph [board.row-1][j]=j-1;
	}
		srand(board.rand_seed);
	
		for(i=0;i<board.numMines;++i){
			row=rand()%(board.row-1);
			col=rand()%(board.col-1);
			
			if(board.graph[board.row-row-2][col+1]!='*'){
				board.graph[board.row-row-2][col+1]='*';
				printf("Placing mine at %d, %d\n",row,col); 
			}
			else if(board.graph[board.row-row-2][col+1]=='*'){ 
				while(board.graph[board.row-row-2][col+1]=='*'){
				row=rand()%(board.row-1);
				col=rand()%(board.col-1);
				}
				board.graph[board.row-row-2][col+1]='*';
				printf("Placing mine at %d, %d\n",row,col); 
			}
		}
		
		for(i=0;i<board.row-1;++i){
			for(j=1;j<board.col;++j){
				if(board.graph[i][j]=='*'){
					continue;
				}
				else{
					for(k=-1;k<2;++k){
						for(l=-1;l<2;++l){
							if((i+k) >(board.row -1) || (i+k)<0||(j+k)<0||(j+k)>(board.col)){
								continue;
							}
							else{
								if(board.graph[i+k][j+l]=='*'){
									++m;
								}
								else{
									continue;
								}
							}
						}
					}
					board.graph[i][j]=(char)m+'0';
					m=0;
				}
			}
		}
	
}

void print_board(Mine board){

	int i,j;



	for(i = 0; i < board.row; ++i){
		for(j = 0; j < board.col; ++j){
	
			if(((j==0 ) && (i != (board.row-1)))||((i==(board.row-1))&&(j!=0))){
				printf("%2d ", board.graph[i][j]);
				}
			else{
				printf("%2c ", board.graph[i][j]);
				}
		}
		printf("\n");
	}

}

void destroy_board(Mine board){
	
	int i;

	for(i=0;i<board.row;++i){
		free(board.graph[i]);
		free(board.status[i]);
	}
	
	free(board.graph);
	free(board.status);
}
						


#endif



