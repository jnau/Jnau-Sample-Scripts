#include<stdio.h>

int main(void){
	int amount, hundred, fifty, twenty, ten, five, one;	
	
	printf("Please enter the amount of money you wish to withdraw: ");
	scanf("%d",&amount);

	hundred= amount/100;
	printf("You received %d hundred(s)\n", hundred);

	fifty = (amount%100)/50;
	printf("You received %d fifty(s)\n", fifty);

	twenty = ((amount%100)%50)/20;
	printf("You received %d twenty(s)\n", twenty);

	ten = (((amount%100)%50)%20)/10;
	printf("You received %d ten(s)\n", ten);
	
	five = ((((amount%100)%50)%20)%10)/5;
	printf("You received %d five(s)\n", five);

	one = ((((amount%100)%50)%20)%10)%5;
	printf("You received %d one(s)\n", one);

	return 0;
}
