#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//defining struct
typedef struct Point_struct {
   double x;
   double y;
} Point;

//function to find the perimeter.
int findPeri(FILE* inFile) {
   
   int onePoint[2];
   int numPts = 0;
   int i = 0;
   int j = 0;

   double peri = 0;

   // read in the lines from the file.
   fread(&numPts, sizeof(int), 1, inFile);

   j = numPts;

   Point arr[numPts];


   // while loop to find the perimeter 
   while (numPts != 0) {
      Point temp;
      fread(&onePoint, sizeof(int), 2, inFile);

      temp.x = onePoint[0];
      temp.y = onePoint[1];

      arr[numPts - 1] = temp; 
      numPts--;

   }

   for(i = 0; i < j-1; i ++ ){
      peri += sqrt(pow((arr[i].x - arr[i+1].x),2) + pow((arr[i].y - arr[i+1].y),2));
   }

   peri += sqrt(pow((arr[0].x - arr[j - 1].x),2) + pow((arr[0].y - arr[j - 1].y),2));

   printf("The perimeter is %.2f", peri); 

   return 0;

}

int main(int argc, char* argv[]){
   

   FILE* inFile = NULL;   // File pointer
   
   inFile = fopen(argv[1], "r");

   findPeri(inFile);  

   fclose(inFile);


   return 0;
}