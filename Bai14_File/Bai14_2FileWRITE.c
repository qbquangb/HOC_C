#include <stdio.h>
#include <stdlib.h>

int main()
{
   int num;
   FILE* fptr;

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen("D:\\KHMT\\ngonngulaptrinh\\laptrinhc\\HOC_C\\Bai14_File\\ex2.txt","w");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   printf("Enter num: ");
   scanf("%d",&num);

   fprintf(fptr,"%d",num);
   // Write some text to the file
  fprintf(fptr, "\nTrần Đình Thương\nXin chao\n");
   fclose(fptr);

   // ----------------------------------------------
   // Append Content To a File
   fptr = fopen("D:\\KHMT\\ngonngulaptrinh\\laptrinhc\\HOC_C\\Bai14_File\\ex2.txt","a");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   // Append some text to the file
  fprintf(fptr, "\nHi everybody!");

  // Close the file
  fclose(fptr);
   // ----------------------------------------------

   return 0;
}