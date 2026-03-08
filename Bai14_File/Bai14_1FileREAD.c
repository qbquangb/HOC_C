#include <stdio.h>
#include <stdlib.h>

int main()
{
   int num;
   FILE* fptr;

   if ((fptr = fopen("D:\\KHMT\\ngonngulaptrinh\\laptrinhc\\HOC_C\\Bai14_File\\ex.txt","r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   fscanf(fptr,"%d", &num);

   printf("Value of n=%d\n", num);

   // Store the content of the file
  char myString[100];

  // Read the content and print it
  while(fgets(myString, 100, fptr)) {
    printf("%s", myString);
  }

   fclose(fptr); 

   return 0;
}