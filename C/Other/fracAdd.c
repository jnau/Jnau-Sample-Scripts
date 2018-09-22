#include<stdio.h>

int main(void){

	int num1, num2, denum1, denum2, numerator, denominator;
	char slash1, slash2, space1, space2, space3, space4;

	printf("Please enter the first fraction to be added: ");
	scanf("%d", &num1);
	scanf("%c", &space1);
	scanf("%c", &slash1);
	scanf("%c", &space2);
	scanf("%d", &denum1);

	printf("Please enter the second fraction to be added: ");
	scanf("%d", &num2);
	scanf("%c", &space3);
	scanf("%c", &slash2);
	scanf("%c", &space4);
	scanf("%d", &denum2);

	numerator = (num1 * denum2) + (num2 * denum1);
	denominator = (denum1 * denum2);

	printf("%d/%d + %d/%d = %d/%d\n", num1,denum1,num2,denum2,numerator,denominator);

	return 0;
}
