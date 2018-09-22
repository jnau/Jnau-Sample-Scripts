#include <stdio.h>
#include <stdlib.h>



int getAtoms(FILE *molecule)
{

   int i = 0;
   int atoms;

   for (i = 0; i < 1; i++)
   {
      fscanf(molecule, "%d", atoms);
 
   }
   return atoms;

}

void set_coord(FILE *molecule, numAtoms) 
{

   int i = 0;

   for (i =0, i < 4, i++) {
   
      if (i = 0) {
         continue; }  // i just need the loop to do nothing, i dont remember what the statement was
      else 
         fscanf(molecule, "%d %d %d %d", x_points, y_points, z_points, radius); //scan in each line 
   }
}





int main(int argc, char* argv[]) 
{
   FILE* molecule = NULL;
   FILE* molecule = fopen(argv[1], 'r');
   numAtoms = getAtoms(molecule);
   get_coord(molecule, numAtoms);
   fclose(molecule);

   return 0;
}
