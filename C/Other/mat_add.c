//purpose: asks the user for 2 matrices A, and B, and displays their sum, C.
#include<stdio.h>
#include<stdlib.h>

int addMatrix(){

	int **a, **b, **c;
	int numRow, numCol;	
	int i, j;
	
	//get the dimension of the matrix
	printf("Please enter the number of rows: ");
	scanf("%d",&numRow);
	printf("Please enter the number of columns: ");
	scanf("%d",&numCol);

	printf("Enter Matrix A\n");

	// create memory space for each elements
	a = (int**)malloc(numRow*sizeof(int*));
	for (i = 0; i < numRow; i++){
		a[i] = (int*)malloc(numCol*sizeof(int));
	}

	b = (int**)malloc(numRow*sizeof(int*));
	for (i = 0; i < numRow; i++){
		b[i] = (int*)malloc(numCol*sizeof(int));
	}

	c = (int**)malloc(numRow*sizeof(int*));
	for (i = 0; i < numRow; i++){
		c[i] = (int*)malloc(numCol*sizeof(int));
	}

	//take elements
	for (i = 0; i < numRow; i++){
		for (j = 0; j< numCol; j++){
		scanf("%d",&a[i][j]);
		}
	}

	printf("Enter Matrix B\n");
	for (i = 0; i < numRow; i++){
		for (j = 0; j< numCol; j++){
		scanf("%d",&b[i][j]);
		}
	}
	//take elements
	for (i = 0; i < numRow; i++){
		for (j = 0; j< numCol; j++){
		c[i][j] = a[i][j]+b[i][j];
		}
	}

	printf("A + B = \n");
	for (i = 0; i < numRow; i++){
		for (j = 0; j< numCol; j++){
		printf("%d ",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}
	
	
int main(){
	addMatrix();

	return 0;
}