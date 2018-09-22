mine_sweeper: condition.o main.o play_game.o
	gcc -g -Wall -o mine_sweeper.out condition.o main.o play_game.o

condition.o: condition.c mine_board.h
	gcc -g -Wall -c -o condition.o condition.c

main.o: main.c mine_board.h
	gcc -g -Wall -c -o main.o main.c 

play_game.o: play_game.c mine_board.h
	gcc -g -Wall -c -o play_game.o play_game.c

clean:
	rm *.out *.o    