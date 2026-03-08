/*

union: các trường chia sẻ cùng vùng nhớ (overlay); kích thước = kích thước của trường lớn nhất. 
Tại một thời điểm chỉ có một trường có giá trị hợp lệ (trường active). 
Dùng khi một biến có thể có nhiều “kiểu” khác nhau (variant) hoặc để tiết kiệm bộ nhớ.

*/

#include <stdio.h>

typedef union
{
   //defining a union
   char name[32];
   float salary;
   int workerNo;
} uJob;

typedef struct
{
   char name[32];
   float salary;
   int workerNo;
} sJob;

int main()
{

    uJob uJob1;
    uJob* uJob2;
    uJob2 = &uJob1;
    uJob1.workerNo = 10;
    (*uJob2).workerNo = 20;
    uJob2->workerNo = 30;

   printf("size of union = %d bytes", sizeof(uJob));
   printf("\nsize of structure = %d bytes\n", sizeof(sJob));

   return 0;
}