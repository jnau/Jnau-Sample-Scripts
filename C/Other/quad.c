#include<stdio.h>
#include<math.h>
/* this program is meant to solve quadratic equations. It allows the user to
 * enter coefficients a, b and c and it will solve for x. */

int main(void){
	
	/*have the numbers as double to consider decimals.*/
	double a, b, c, x1, x2, discriminant;
	printf("Given a quadratic equation of the form a*x^2 + b * x + c\n");
	printf("Please enter a: ");
	scanf("%lf\n",&a);
	printf("Please enter b: ");
	scanf("%lf\n",&b);
	printf("Please enter c: ");
	scanf("%lf\n",&c);
	/*here we obtain the inputs of a, b and c.*/
	discriminant = b*b-4*a*c;
	x1 = (-b+sqrt(discriminant))/(2*a);
	x2 = (-b-sqrt(discriminant))/(2*a);
	/*these are the formulas for the discriminant, root x1 and x2. */			
	if (discriminant>0){
	/*if the discriminant is positive, there are 2 roots for x. */
		printf("There are 2 real solutions\n");
		printf("Solution 1: %.2lf\n", x1);
		printf("Solution 2: %.2lf", x2);
}
	else if (discriminant==0){
	/*if the discriminant is zero, there's only one root, and x1 = x2*/
		printf("There is one real solution: %.2lf", x1);
}											else{
	/* anything else is an imaginary number. */
		printf("There are no real solutions");
}
	return 0;

}
