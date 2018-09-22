#include <stdio.h>
//This program is meant to show the user pascal's triangle to whatever level they decide.


//this function here is meant to calculate the binomial coefficient.
int binomCoe(int n, int k){
	int coeVal = 1;
	int i = 0;
	
	if (k <= n){
		for (i = 0; i < k; ++i){
			coeVal *= (n - i);
			coeVal /= (i + 1);}
}	
	return coeVal;}

int pascal_triangle (){
	int n;
	int line = 0;
	int i = 0;
	
	printf("Please enter how many levels of Pascal's Triangle you would like to see: ");
	scanf("%d",&n);
	
	
	//this for loop is meant to iterate through every line and print numbers in it.
	for (line = 0; line < n; line++){
	
	// Each line has the same number of integers equal to its line number
		for (i = 0; i <= line; i++){
			printf("%d ", binomCoe(line, i));
			}
		printf("\n");
}

	return 0;
}

int main () {
	pascal_triangle();
return 0;
}
