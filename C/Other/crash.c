#include<stdio.h>
#include<math.h>

int main(void){

	double train1Position, train2Position, speed1, speed2, coltime, coldis; 

	printf("Please enter the starting position of train 1: ");
	scanf("%lf",&train1Position);

	printf("Please enter the speed of train 1: ");
	scanf("%lf",&speed1);

	printf("Please enter the starting position of train 2: ");
	scanf("%lf",&train2Position);

	printf("Please enter the speed of train 2: ");
	scanf("%lf",&speed2);

	coltime = (train2Position-train1Position)/(speed1+speed2);
	coldis = (speed1*coltime)+train1Position;

	printf("The two trains will collide in %.2lf hours %.2lf miles down the track.", coltime, coldis);

	return 0;

}
	
	
