#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int wordCount(FILE *inFile) {
	int count = 0;
	char str[1000];
	int i;

	//this will read every line in the file, until it reaches the end
	while (fgets(str, 1000, inFile)) {
		for (i = 1; str[i] != '\0'; i++) {
			if (isspace(str[i]) != 0) {
				count++;
				}
			}
		}

//the number of spaces there are, the number of words there will be. 
//This includes newlines and white spaces. 

	return count;
}


int main(int argc, char* argv[]) {

	FILE* inFile = fopen(argv[1], "r");
	int count;
	
	//here, we open the given file.
	count = wordCount(inFile);
	
	fclose(inFile);
	printf("There are %d word(s).", count);

	return 0;
}

