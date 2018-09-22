#include <stdio.h>
#include <stdlib.h>



int myTail(FILE* file, int N) {

  int count = 0;

  char *str = (char *)malloc(200 *sizeof(char));

  while (fgets(str, 200, file)){
	count++;
	   }
   
   // go back to beginning of file 
   rewind(file);

   

   // seek to the correct starting spot in the file
   if (N > count) {
	N = count;
}

   int i = 0;
   for (i = 0; i < count - N; i++) {
	fgets(str, 200, file);
   }
   

   // print until the end
   while (fgets(str, 200, file)){
	printf("%s", str);
}
   

   return 0;

}


int main(int argc, char *argv[]) {

   int N = atoi(argv[2]);

   // open file
   FILE *file = fopen(argv[1], "r");

   // count number of lines
   myTail(file, N);
   fclose(file);	


return 0;

} 
