#include <stdio.h>
int main()
{

  int var = 5;
  printf("var: %d\n", var);
  // Notice the use of & before var
  printf("address of var: %p\n", &var);

  int* p;
  p = &var;
  printf("var: %d\n", *p);

  *p = 100;
  printf("var: %d\n", *p);

  // Pointers and Arrays
  int i, x[6], sum = 0;
  printf("Enter 6 numbers: ");
  for(i = 0; i < 6; ++i) {
  // Equivalent to scanf("%d", &x[i]);
    scanf("%d", x+i);
  // Equivalent to sum += x[i]
    sum += *(x+i);
  }
  printf("Sum = %d", sum);

  return 0;
}