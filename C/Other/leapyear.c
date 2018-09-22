#include <stdio.h>
/* The purpose of this program is to obtain a year from the user and tell them
 * whether or not that year is a leap year or not.*/

int main(void) {
	int yearInput; /*making the year an integer*/
	
	printf("Please enter a year: ");
	scanf("%d", &yearInput);

	/*here, we obtain the year that is imputted by the user.*/
	
	if ((yearInput%400 == 0)||(!(yearInput%100)||(yearInput%4== 0))) {
		printf("%d is a leap year.\n", yearInput); 
	/*If the year has no remainder after being divided by 100 or 400, AND
 * 4, then it is a leap year.*/
}
	else {
		printf("%d is not leap year.\n", yearInput);
	/*if not, then it will tell the user.*/
}
	return 0;

}
