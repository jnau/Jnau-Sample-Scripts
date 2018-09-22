#include <stdio.h>
#include <ctype.h>
#include <string.h>

//with this program, we will be asking the user for two words, and return to theuser if they are anagrams of each other. 


int check_anagram(char array1[], char array2[]){
//with this function we check the words and make them case insensitive.	
//here, we create arrays to sort the vectors.
	int num1[26] = {0}, num2[26] = {0}, i = 0;
	// we want them case insensitive, so we are making them all uppercase.
	for (i=0;array1[i]!='\0';i++){
		array1[i] = toupper(array1[i]);}
		for (i=0;array2[i]!='\0';i++){
			array2[i] = toupper(array2[i]);}
	//here, we make a library to see how many times a letter occurs
	for (i = 0; array1[i] != '\0'; i++){
		num1[array1[i] - 'A']++;}
	for (i = 0; array2[i] != '\0'; i++){
		num2[array2[i] - 'A']++;
}
	//for loop to run through every element, and if there's a difference, return 1.
	for (i = 0; i < 26; i++){
		if (num1[i] != num2[i]){
			return 1; 
			break;}
}
	return 0;}

int is_anagram() {
// here we state whether the words are anagrams.
	char input_1[21], input_2[21];
	char input_1o[21], input_2o[21];
	int flag;

	printf("Please enter the first word: ");
	scanf("%s", input_1o);

	printf("Please enter the second word: ");
	scanf("%s", input_2o);
	strcpy(input_1, input_1o);
	strcpy(input_2, input_2o);
	flag = check_anagram(input_1, input_2);

	if (flag == 0) {
		printf("%s is an anagram of %s\n", input_1o, input_2o);}
	else {
		printf("%s is NOT an anagram of %s\n", input_1o, input_2o);}

	return 0;
}

int main(){
	
	is_anagram();
	
	return 0;}
