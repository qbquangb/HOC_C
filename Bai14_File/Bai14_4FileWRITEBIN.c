#include <stdio.h>
#include <stdlib.h>

struct threeNum
{
   int n1, n2, n3;
};

int main()
{
   int n;
   struct threeNum num;
   FILE *fptr;

   if ((fptr = fopen("D:\\KHMT\\ngonngulaptrinh\\laptrinhc\\HOC_C\\Bai14_File\\ex4.bin","wb")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   for(n = 1; n < 5; ++n)
   {
      num.n1 = n; // 1, 2, 3, 4
      num.n2 = 5*n; // 5, 10, 15, 20
      num.n3 = 5*n + 1; // 6, 11, 16, 21
      fwrite(&num, sizeof(struct threeNum), 1, fptr); 
   }
   fclose(fptr); 

   // -----------------------------------------------
   if ((fptr = fopen("D:\\KHMT\\ngonngulaptrinh\\laptrinhc\\HOC_C\\Bai14_File\\ex4.bin","ab")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }
   unsigned char arr_[] = {0x01, 0x03, 0x05, 0x07, 0x09, 0x11, 0x13, 0x15, 0x17, 0x19, 0x21, 0x23, 0xab, 0xff};
   fwrite(&arr_, sizeof(arr_), 1, fptr);
   fclose(fptr);
   // -----------------------------------------------
  
   return 0;
}