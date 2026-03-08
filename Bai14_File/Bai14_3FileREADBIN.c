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

   if ((fptr = fopen("D:\\KHMT\\ngonngulaptrinh\\laptrinhc\\HOC_C\\Bai14_File\\ex4.bin","rb")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   for(n = 1; n < 5; ++n)
   {
      fread(&num, sizeof(struct threeNum), 1, fptr); 
      printf("n1: %d\tn2: %d\tn3: %d\n", num.n1, num.n2, num.n3);
   }

   unsigned char num2;
   int count = 0;
   while (fread(&num2, 1, 1, fptr)) {
      // in hex chữ hoa, đảm bảo 2 chữ số, có tiền tố 0x, ép kiểu rỏ ràng
      printf("0x%02X ", (unsigned) num2); // -> 0xAB
      if (count % 16 == 0 && (count != 0)) printf("\n");
      count++;
   }

   fclose(fptr);
  
   return 0;
}