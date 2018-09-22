#include <stdio.h>
#include <string.h>

//This program is meant to ask the user for a given word and it will return the plural
//form of it.
int is_plural(){ 
	char input_vocab[21];
	char vocab[21]; 
	int i = 0;
	int indexnum= 0;	
	
	//ask the user for a word and store it in the variable 'vocab'.
	printf("Please enter a word: ");
	scanf("%s", input_vocab);
	
	strcpy(vocab, input_vocab);
	indexnum = strlen(vocab)-1;

	for (i = indexnum; i >=0; i--){
	
	// here, we will run a check to see how to change the word to be plural.
		if (vocab[i] == 'y' && (vocab[i-1]=='a'||vocab[i-1]=='e'||vocab[i-1]=='i'||vocab[i-1]=='o'||vocab[i-1]=='u')){
			vocab[i+1] = 's';
			vocab[i+2] = '\0';
			printf("The plural from of %s is %s.\n", input_vocab, vocab);
			break;}

		else if (vocab[i] == 'y'){
			vocab[i] = 'i';
			vocab[i+1]='e';
			vocab[i+2]='s';
			vocab[i+3] = '\0';
			printf("The plural from of %s is %s.\n", input_vocab, vocab);
			break;}

		else if ((vocab[i-1] == 'c'|| vocab[i-1] == 's') && vocab[i] == 'h'){
			vocab[i+1]='e';
			vocab[i+2]='s';
			vocab[i+3] = '\0';
			printf("The plural from of %s is %s.\n", input_vocab, vocab);
			break;}

		else if (vocab[i] == 's' || vocab[i] == 'z' || vocab[i] == 'x'){
			vocab[i+1]='e';
			vocab[i+2]='s';
			vocab[i+3] = '\0';
			printf("The plural from of %s is %s.\n", input_vocab, vocab);
			break;}

		else if (vocab[i] == 'f'){
			vocab[i]='v';
			vocab[i+1]='e';
			vocab[i+2]='s';
			vocab[i+3] = '\0';
			printf("The plural from of %s is %s.\n", input_vocab, vocab);
			break;}

		else if (vocab[i] == 'e'&& vocab[i-1]=='f'){
			vocab[i-1]='v';
			vocab[i]= 'e';
			vocab[i+1]='s';
			vocab[i+2] = '\0';
			printf("The plural from of %s is %s.\n", input_vocab, vocab);
			break;}

		else{
			vocab[i+1]='s';
			vocab[i+2] = '\0';
			printf("The plural from of %s is %s.\n", input_vocab, vocab);
			break;}
	}
	return 0;}

int main() {
	is_plural();

return 0;
}
